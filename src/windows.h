#pragma once

#include "ofMain.h"
#include "ofxFensterManager.h"
#include "ofxCv.h"
#include "ofxFaceTracker.h"


class cameraCaptureWindow: public ofxFensterListener
{
public:

    ofVideoGrabber* capture;

    cameraCaptureWindow(ofVideoGrabber* cam)
    {
        this->capture = cam;
    }

    ~cameraCaptureWindow()
    {
        cout << "Image Listener destroyed" << endl;
    }

    void setup()
    {
        ofSetVerticalSync(true);
        capture->initGrabber(640, 480);
    }

    void update()
    {
        capture->update();
    }

    void draw()
    {
        capture->draw(0,0);
    }
};

class faceTrackerWindow: public ofxFensterListener
{
public:

    ofVideoGrabber* capture;
    ofxFaceTracker* tracker;

    ofVec2f position;
    float scale;
    ofVec3f orientation;
    ofMatrix4x4 rotationMatrix;

    vector<ofVec2f> normalizedFaceTexCoords;

    ofImage mOverlayImage;

    faceTrackerWindow(ofVideoGrabber* cam, ofxFaceTracker* t)
    {
        this->capture = cam;
        this->tracker = t;
    }

    ~faceTrackerWindow()
    {
        cout << "Image Listener destroyed" << endl;
    }

    void setup()
    {

        ofSetVerticalSync(true);
        ofEnableAlphaBlending();

        tracker->setup();
        tracker->setRescale(.5);

        mOverlayImage.loadImage("chessBoard.png");
        normalizedFaceTexCoords.clear();
    }

    void update()
    {
        if(capture->isFrameNew())
        {

            tracker->update(ofxCv::toCv(*capture));

            position = tracker->getPosition();
            scale = tracker->getScale();
            orientation = tracker->getOrientation();
            rotationMatrix = tracker->getRotationMatrix();
        }
    }

    void draw()
    {
        ofBackground(0);
       // capture->draw(0,0);
        if(tracker->getFound())
        {
            ofSetupScreenOrtho(640, 480, OF_ORIENTATION_UNKNOWN, true, -1000, 1000);
            ofTranslate(position.x,position.y);
            ofxCv::applyMatrix(rotationMatrix);
            ofScale(scale,scale,scale);

            ofMesh faceMesh = tracker->getObjectMesh();

            // if first time we detect a face, fill faceTexCoord vector with normalized index values
            //    this is so we have a reference triangle-strip mesh to use when binding texture.
            //    if we always use the values in the current mesh it will:
            //    (1) have to be calculated/normalized every time, and
            //    (2) look "flat"
            if(normalizedFaceTexCoords.size() <= 0)
            {
                ofVec2f minT(1000,1000), maxT(0,0);
                for(int i=0; i<faceMesh.getNumTexCoords(); i++)
                {
                    ofVec2f fv = faceMesh.getTexCoord(i);
                    if(fv.x > maxT.x)
                    {
                        maxT.x = fv.x;
                    }
                    if(fv.x < minT.x)
                    {
                        minT.x = fv.x;
                    }
                    if(fv.y > maxT.y)
                    {
                        maxT.y = fv.y;
                    }
                    if(fv.y < minT.y)
                    {
                        minT.y = fv.y;
                    }
                }

                for(int i=0; i<faceMesh.getNumTexCoords(); i++)
                {
                    ofVec2f fv = faceMesh.getTexCoord(i);
                    fv.x = ofMap(fv.x, minT.x, maxT.x, 0, 1.0);
                    fv.y = ofMap(fv.y, minT.y, maxT.y, 0, 1.0);
                    normalizedFaceTexCoords.push_back(fv);
                }
            }

            // use vector of normalized tex coords to scale image and map it onto mesh
            for(int i=0; i<normalizedFaceTexCoords.size()&&i<faceMesh.getNumTexCoords(); i++)
            {
                ofVec2f fv = normalizedFaceTexCoords.at(i);
                fv.x *= mOverlayImage.width;
                fv.y *= mOverlayImage.height;
                faceMesh.setTexCoord(i, fv);
            }

          //  faceMesh.enableTextures();
          //  mOverlayImage.getTextureReference().bind();
            ofSetColor(255);
            faceMesh.draw();
          //  mOverlayImage.getTextureReference().unbind();
        }
    }
};

class faceOverlayWindow: public ofxFensterListener
{
public:

    ~faceOverlayWindow()
    {
        cout << "Image Listener destroyed" << endl;
    }
};
