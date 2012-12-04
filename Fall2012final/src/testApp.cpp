#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    // Housekeeping:
    ofSetCircleResolution(60);
    ofEnableSmoothing();
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofBackground(0);
}

//--------------------------------------------------------------
void testApp::update(){
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    // The canvas:
    ofSetColor(255,0,0);
    ofRect(ofGetWidth()/2, ofGetHeight()/2, 100, 100, 100);
    
    // The player-character;
    ofSetColor(255);
    ofSphere(ofGetWidth()/2, ofGetHeight()/2, 0, 50);
    
    // Reset color:
    ofSetColor(255);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
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