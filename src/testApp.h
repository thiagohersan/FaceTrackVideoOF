#pragma once

#include <string>
#include <iostream>

#include "ofMain.h"
#include "ofxFensterManager.h"
#include "ofxCv.h"
#include "ofxFaceTracker.h"
#include "windows.h"

class testApp : public ofBaseApp {

public:
    void setup();
    void update();
    void draw();

    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    ofVideoGrabber cam;
    ofxFaceTracker tracker;

    cameraCaptureWindow* ccw;
    faceTrackerWindow* ftw;
    faceOverlayWindow* fow;

};
