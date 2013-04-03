#pragma once

#include "ofMain.h"
#include "ofxFensterManager.h"
#include "ofxCv.h"
#include "ofxFaceTracker.h"

class cameraCaptureWindow: public ofxFensterListener {

public:
    cameraCaptureWindow();
    ~cameraCaptureWindow();
    
	void setup();
    void update();
    void draw();
	
	ofVideoGrabber* capture;
};

class faceTrackerWindow: public ofxFensterListener {

public:
    faceTrackerWindow();
    ~faceTrackerWindow();

    void setup();
    void update();
    void draw();
	
	ofVideoGrabber* capture;
    ofxFaceTracker* tracker;
	
    ofVec2f position;
    float scale;
    ofVec3f orientation;
    ofMatrix4x4 rotationMatrix;
	
    vector<ofVec2f> normalizedFaceTexCoords;
	
    ofImage mOverlayImage;
};

class faceOverlayWindow: public ofxFensterListener {

public:
    ~faceOverlayWindow(){
        cout << "Image Listener destroyed" << endl;
    }
};
