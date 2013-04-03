#include "testApp.h"

using namespace ofxCv;

//--------------------------------------------------------------
void testApp::setup(){
	// SETTING UP MULTIPLE WINDOWS WITH OFXFENSTER

    //IF the following code is uncommented, all the following windows should be created on the second display, if there is one available
	ofxDisplayList displays = ofxDisplayManager::get()->getDisplays();
	ofxDisplay* disp = displays[0];
	cout << "displays found: " << displays.size() << endl;
	if(displays.size() > 1)
		disp = displays[1];
	ofxFensterManager::get()->setActiveDisplay(disp);

    int winW=640, winH=480;

    ccw = new cameraCaptureWindow(&cam);
    ftw = new faceTrackerWindow(&cam, &tracker);

    ofxFenster* win=ofxFensterManager::get()->createFenster(0, 0, winW, winH, OF_WINDOW);
    win->addListener(ccw);
    win->setWindowTitle("camera capture");

    win=ofxFensterManager::get()->createFenster(0, 0, winW, winH, OF_WINDOW);
    win->addListener(ftw);
    win->setWindowTitle("face tracking");

	//setup of fensterListener does not get called automatically yet
	ccw->setup();
	ftw->setup();

	// FINISH WINDOW SETUP
}

//--------------------------------------------------------------
void testApp::update(){
	// done in fenster windows
}

//--------------------------------------------------------------
void testApp::draw(){
	// why is this here?
    ofBackground(0);
    ofSetColor(255,255,0);
    string appInfo = "Face tracking prototype.\nf - toggle fullscreen\nd - redetect face\nFPS: " + ofToString(ofGetFrameRate()) + "\n";
    ofDrawBitmapString(appInfo, 10, 20);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    if(key=='f')
		ofxFensterManager::get()->getPrimaryWindow()->toggleFullscreen();
    if(key=='d')
        tracker.reset();
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
