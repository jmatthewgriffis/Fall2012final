#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    // Housekeeping:
    ofSetCircleResolution(60);
    ofSetSphereResolution(60);
    ofEnableSmoothing();
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofBackground(0);
    
    // Movement:
    forward = false;
    backward = false;
    left = false;
    right = false;
}

//--------------------------------------------------------------
void testApp::update(){
    
    if (forward == true) {
        //sphere.z += 10;
    }
    if (backward == true) {
        
    }
    if (left == true) {
        
    }
    if (right == true) {
        
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    
    // The canvas:
    ofSetColor(255);
    ofSetRectMode(OF_RECTMODE_CENTER);
    //ofRect(ofGetWidth()/2, ofGetHeight()/2, 100, 100, 100);
    ofBox(ofGetWidth()/2, ofGetHeight()/2, -200, 100);
    
    // The player-character;
    ofSetColor(255,0,0);
    ofSphere(ofGetWidth()/2, ofGetHeight()/2, 0, 50);
    
    // Reset color:
    ofSetColor(255);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    switch (key) {
        case OF_KEY_UP:
            forward = true;
            break;
            
        case OF_KEY_DOWN:
            backward = true;
            break;
            
        case OF_KEY_LEFT:
            left = true;
            break;
            
        case OF_KEY_RIGHT:
            right = true;
            break;
    }
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    switch (key) {
        case OF_KEY_UP:
            forward = false;
            break;
            
        case OF_KEY_DOWN:
            backward = false;
            break;
            
        case OF_KEY_LEFT:
            left = false;
            break;
            
        case OF_KEY_RIGHT:
            right = false;
            break;
    }
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