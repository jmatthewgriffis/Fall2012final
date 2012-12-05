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
    
    // Image credit:
    // http://www.ibiblio.org/wm/paint/auth/vinci/joconde/joconde.jpg :
    mona.loadImage("pics/mona_lisa.jpg");
    
    // Movement:
    forward = false;
    backward = false;
    left = false;
    right = false;
    playerVel = 10;
    
    // Establish sizes first to refer to them when positioning.
    canvasSide = 500;
    playerRad = 50;
    floorLength = 1000;
    floorWidth = 1000;
    
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
    
    // You might think you'd want to change the position of the
    // object when the object is moving, and for x and y that's
    // true. However, for z, since we don't have a camera following
    // the player object, it would appear to grow smaller or larger,
    // and we don't want that. So we move the world instead, shifting
    // its position on the z-axis to keep the player object at the same
    // scale while giving the illusion of movement. I'll move the world
    // for ya, darling:
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
    
    // Setting the rect mode does not affect the 3D box. But it
    // DOES affect the images:
    ofSetRectMode(OF_RECTMODE_CENTER);
    
    // The floor. This looks like a mess but it's not so bad. We
    // simply draw the floor by connecting the four corners as
    // vertices, and position them all relative to the existing objects
    // so all the architecture moves together:
    ofSetColor(0, 0, 255);
    ofBeginShape();
    // Back-left corner:
    ofVertex((ofGetWidth()/2)-(floorWidth/2), (ofGetHeight()/2)+(canvasSide/2), canvasZ+(canvasSide/2));
    // Back-right corner:
    ofVertex((ofGetWidth()/2)+(floorWidth/2), (ofGetHeight()/2)+(canvasSide/2), canvasZ+(canvasSide/2));
    // Front-right corner:
    ofVertex((ofGetWidth()/2)+(floorWidth/2), (ofGetHeight()/2)+(canvasSide/2), canvasZ+(canvasSide/2)+(floorWidth/2)+floorLength);
    // Front-left corner:
    ofVertex((ofGetWidth()/2)-(floorWidth/2), (ofGetHeight()/2)+(canvasSide/2), canvasZ+(canvasSide/2)+(floorWidth/2)+floorLength);
    ofEndShape();
    ofSetColor(255); // Color reset.
    
    // The canvas:
    ofSetColor(0); // Canvas is invisible. Change to 255 for white.
    ofBox(canvasX, canvasY, canvasZ, canvasSide);
    ofSetColor(255); // Color reset.
    //ofRect(ofGetWidth()/2, ofGetHeight()/2, 100, 100, 100);
    
    // Draw a pic (I used math to reduce the original image's dimensions
    // to fit within the 500x500 box. I would use Max Width and Max Height
    // but I don't know how or if that's even possible):
    mona.draw(canvasX, canvasY, canvasZ+(canvasSide/2), 321, 500);
    
    // The player-character:
    
    // Debug to test positioning by changing color when player and
    // canvas are at the same depth:
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