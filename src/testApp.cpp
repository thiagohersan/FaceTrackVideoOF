#include "testApp.h"

using namespace ofxCv;

//--------------------------------------------------------------
void testApp::setup(){
	ofSetVerticalSync(true);
	ofEnableAlphaBlending();
	cam.initGrabber(640, 480);
	
	tracker.setup();
	tracker.setRescale(.5);
	
	mImage.loadImage("chessBoard.png");
	normalizedFaceTexCoords.clear();
}

//--------------------------------------------------------------
void testApp::update(){
	cam.update();
	if(cam.isFrameNew()) {
		tracker.update(toCv(cam));
		position = tracker.getPosition();
		scale = tracker.getScale();
		orientation = tracker.getOrientation();
		rotationMatrix = tracker.getRotationMatrix();
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(0);
	ofSetColor(255);
	cam.draw(0, 0);
	ofSetColor(255,255,0);
	ofDrawBitmapString(ofToString((int) ofGetFrameRate()), 10, cam.height+20);
	
	if(tracker.getFound()) {
		ofSetupScreenOrtho(640, 480, OF_ORIENTATION_UNKNOWN, true, -1000, 1000);
		ofTranslate(position.x,position.y-240);
		applyMatrix(rotationMatrix);
		ofScale(scale,scale,scale);
		
		ofMesh faceMesh = tracker.getObjectMesh();
		
		// if first time we detect a face, fill faceTexCoord vector with normalized index values
		//    this is so we have a reference triangle-strip mesh to use when binding texture.
		//    if we always use the values in the current mesh it will:
		//    (1) have to be calculated/normalized every time, and
		//    (2) look "flat"
		if(normalizedFaceTexCoords.size() <= 0){
			ofVec2f minT(1000,1000), maxT(0,0);
			for(int i=0; i<faceMesh.getNumTexCoords(); i++){
				ofVec2f fv = faceMesh.getTexCoord(i);
				if(fv.x > maxT.x) {
					maxT.x = fv.x;
				}
				if(fv.x < minT.x) {
					minT.x = fv.x;
				}
				if(fv.y > maxT.y) {
					maxT.y = fv.y;
				}
				if(fv.y < minT.y) {
					minT.y = fv.y;
				}
			}
			
			for(int i=0; i<faceMesh.getNumTexCoords(); i++){
				ofVec2f fv = faceMesh.getTexCoord(i);
				fv.x = ofMap(fv.x, minT.x, maxT.x, 0, 1.0);
				fv.y = ofMap(fv.y, minT.y, maxT.y, 0, 1.0);
				normalizedFaceTexCoords.push_back(fv);
			}
		}
		
		// use vector of normalized tex coords to scale image and map it onto mesh
		for(int i=0; i<normalizedFaceTexCoords.size()&&i<faceMesh.getNumTexCoords(); i++){
			ofVec2f fv = normalizedFaceTexCoords.at(i);
			fv.x *= mImage.width;
			fv.y *= mImage.height;
			faceMesh.setTexCoord(i, fv);
		}
		
		faceMesh.enableTextures();
		mImage.getTextureReference().bind();
		ofSetColor(255);
		faceMesh.draw();
		mImage.getTextureReference().unbind();
				
		/*
		 addMessage("/gesture/mouth/width", tracker.getGesture(ofxFaceTracker::MOUTH_WIDTH));
		 addMessage("/gesture/mouth/height", tracker.getGesture(ofxFaceTracker::MOUTH_HEIGHT));
		 addMessage("/gesture/eyebrow/left", tracker.getGesture(ofxFaceTracker::LEFT_EYEBROW_HEIGHT));
		 addMessage("/gesture/eyebrow/right", tracker.getGesture(ofxFaceTracker::RIGHT_EYEBROW_HEIGHT));
		 addMessage("/gesture/eye/left", tracker.getGesture(ofxFaceTracker::LEFT_EYE_OPENNESS));
		 addMessage("/gesture/eye/right", tracker.getGesture(ofxFaceTracker::RIGHT_EYE_OPENNESS));
		 addMessage("/gesture/jaw", tracker.getGesture(ofxFaceTracker::JAW_OPENNESS));
		 addMessage("/gesture/nostrils", tracker.getGesture(ofxFaceTracker::NOSTRIL_FLARE));
		 */
		//// OR
		/*
		 ofPolyline leftEye = tracker.getImageFeature(ofxFaceTracker::LEFT_EYE);
		 ofPolyline rightEye = tracker.getImageFeature(ofxFaceTracker::RIGHT_EYE);
		 ofPolyline faceOutline = tracker.getImageFeature(ofxFaceTracker::FACE_OUTLINE);
		 */
	}
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
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