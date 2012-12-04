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
    playerVel = 10;
    
    canvasSide = 500;
    playerRad = 50;
    canvasX = ofGetWidth()/2;
    canvasY = ofGetHeight()/2;
    canvasZ = -1000;
    playerX = ofGetWidth()/2;
    // We want the base of the canvas and the base of the player
    // to appear to be on the same floor (which is viewed as scaling
    // into the screen). So we set the yPos of the player equal to the
    // yPos of the canvas, accounting for the respective sizes:
    playerY = canvasY+(canvasSide/2)-playerRad;
    playerZ = 0;
    //playerZ = canvasZ+(canvasSide/2)+playerRad; // Debug - test
    // comparative placement.
}

//--------------------------------------------------------------
void testApp::update(){
    
    if (forward == true) {
        canvasZ += playerVel;
    }
    if (backward == true) {
        canvasZ -= playerVel;
    }
    if (left == true) {
        playerX -= playerVel;
    }
    if (right == true) {
        playerX += playerVel;
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    
    // The canvas:
    ofSetColor(255);
    ofSetRectMode(OF_RECTMODE_CENTER);
    //ofRect(ofGetWidth()/2, ofGetHeight()/2, 100, 100, 100);
    ofBox(canvasX, canvasY, canvasZ, canvasSide);
    
    // The player-character:
    // Debug to test positioning:
    if (canvasZ >= playerZ-playerRad-(canvasSide/2)) {
        ofSetColor(0, 255, 0);
    }
    else {
    ofSetColor(255,0,0);
    }
    ofSphere(playerX, playerY, playerZ, playerRad);
    
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