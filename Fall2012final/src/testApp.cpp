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
    
    // The paintings:
    
    // Image credit:
    // http://www.ibiblio.org/wm/paint/auth/vinci/joconde/joconde.jpg :
    davinci.loadImage("pics/davinci.jpg");
    
    // Image credit:
    // http://www.ibiblio.org/wm/paint/auth/mondrian/broadway.jpg
    mondrian.loadImage("pics/mondrian.jpg");
    
    // Movement:
    forward = false;
    backward = false;
    left = false;
    right = false;
    xVel = 5;
    yVel = 0;
    jumpSpd = -7.8;
    gravity = 0.3;
    
    // Establish sizes first to refer to them when positioning.
    canvasSide = 500;
    playerRad = 50;
    floorLength = 1000;
    floorWidth = 1250;
    
    // Make code more readable:
    centerW = ofGetWidth()/2;
    centerH = ofGetHeight()/2;
    floorHeight = centerH+(canvasSide/2);
    ceilingHeight = floorWidth-(floorWidth/3); // Temporary value.
    
    playerX = centerW;
    playerY = floorHeight-playerRad;
    playerZ = 150;
    canvasZ = -1000;
    
    //playerZ = canvasZ+(canvasSide/2)+playerRad; // Debug - test
    // comparative placement.
}

//--------------------------------------------------------------
void testApp::update(){
    
    // Have to initialize these variables in the update function,
    // because they are dependent on other variables (that update):
    canvasFront = canvasZ+(canvasSide/2);
    leftWallx = centerW-(floorWidth/2);
    rightWallx = centerW+(floorWidth/2);
    canvasX = centerW;
    canvasY = centerH;
    
    /* You might think you'd want to change the position of the object
     when the object is moving. However, for z, since we don't have a
     camera following the player object, it would appear to grow smaller
     or larger, and we don't want that. So we move the world instead,
     shifting its position on the z-axis to keep the player object at the
     same scale while giving the illusion of movement. We do the same on
     the x and y axis to prevent weird warping and just give smoother movement.
     I'll move the world for ya, darling: */
    if (forward == true) {
        if (playerZ > canvasFront+playerRad) {
            canvasZ += xVel;
        }
    }
    if (backward == true) {
        canvasZ -= xVel;
    }
    if (left == true) {
        if (playerX > leftWallx+playerRad) {
            centerW += xVel;
        }
    }
    if (right == true) {
        if (playerX < rightWallx-playerRad) {
            centerW -= xVel;
        }
    }
    
    // Update the player's yPos with velocity at all times (but mostly
    // velocity will be zero):
    playerY += yVel;
    
    // Check if player is in the air, and if so, update the yVel with
    // gravity. This check isn't strictly necessary as the floor collision
    // code below stops the player from falling farther, but this way
    // is maybe a little more efficient since it's not having to undo the
    // constant addition of gravity. It may not make a difference, though:
    if (playerY < floorHeight-playerRad) {
        yVel += gravity;
    }
    
    if (jump == true) {
        yVel = jumpSpd; // Give some yVel for a jump!
        jump = false; // This prevents multiple jumps.
    }
    
    // Let's make sure the player can't fall through the floor or get stuck:
    if (playerY > floorHeight-playerRad) {
        playerY = floorHeight-playerRad;
        yVel = 0;
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    
    // Setting the rect mode does not affect the 3D box. But it
    // DOES affect the images:
    ofSetRectMode(OF_RECTMODE_CENTER);
    
    //__________________________________________________________
    
    // Let's build a building! One surface at a time!
    
    // The floor. This looks like a mess but it's not so bad. We
    // simply draw the floor by positioning the four corners as
    // vertices, relative to the existing objects so all the
    // architecture moves together:
    ofSetColor(166,137,23);
    ofBeginShape();
    // Back-left corner:
    ofVertex(leftWallx, floorHeight, canvasFront);
    // Back-right corner:
    ofVertex(rightWallx, floorHeight, canvasFront);
    // Front-right corner:
    ofVertex(rightWallx, floorHeight, canvasFront+floorLength);
    // Front-left corner:
    ofVertex(leftWallx, floorHeight, canvasFront+floorLength);
    ofEndShape();
    ofSetColor(255); // Color reset.
    
    // The left wall (same as with the floor):
    ofSetColor(173,143,23);
    ofBeginShape();
    // Back-lower corner:
    ofVertex(leftWallx, floorHeight, canvasFront);
    // Back-upper corner:
    ofVertex(leftWallx, floorHeight-ceilingHeight, canvasFront);
    // Front-upper corner:
    ofVertex(leftWallx, floorHeight-ceilingHeight, canvasFront+floorLength);
    // Front-lower corner:
    ofVertex(leftWallx, floorHeight, canvasFront+floorLength);
    ofEndShape();
    ofSetColor(255); // Color reset.
    
    // The right wall:
    ofSetColor(173,143,23);
    ofBeginShape();
    // Back-lower corner:
    ofVertex(rightWallx, floorHeight, canvasFront);
    // Back-upper corner:
    ofVertex(rightWallx, floorHeight-ceilingHeight, canvasFront);
    // Front-upper corner:
    ofVertex(rightWallx, floorHeight-ceilingHeight, canvasFront+floorLength);
    // Front-lower corner:
    ofVertex(rightWallx, floorHeight, canvasFront+floorLength);
    ofEndShape();
    ofSetColor(255); // Color reset.
    
    
    // The back wall:
    ofSetColor(179,156,70);
    ofBeginShape();
    // Lower-left corner:
    ofVertex(leftWallx, floorHeight, canvasFront);
    // Upper-left corner:
    ofVertex(leftWallx, floorHeight-ceilingHeight, canvasFront);
    // Upper-right corner:
    ofVertex(rightWallx, floorHeight-ceilingHeight, canvasFront);
    // Lower-right corner:
    ofVertex(rightWallx, floorHeight, canvasFront);
    ofEndShape();
    ofSetColor(255); // Color reset.
    
    
    // The ceiling:
    ofSetColor(166,137,23);
    ofBeginShape();
    // Back-left corner:
    ofVertex(leftWallx, floorHeight-ceilingHeight, canvasFront);
    // Back-right corner:
    ofVertex(rightWallx, floorHeight-ceilingHeight, canvasFront);
    // Front-right corner:
    ofVertex(rightWallx, floorHeight-ceilingHeight, canvasFront+floorLength);
    // Front-left corner:
    ofVertex(leftWallx, floorHeight-ceilingHeight, canvasFront+floorLength);
    ofEndShape();
    ofSetColor(255); // Color reset.
    
    
    // Building complete!
    
    //__________________________________________________________
    
    // The canvas:
    ofSetColor(0); // Canvas is invisible. Change to 255 for white.
    ofBox(canvasX, canvasY, canvasZ, canvasSide);
    ofSetColor(255); // Color reset.
    //ofRect(ofGetWidth()/2, ofGetHeight()/2, 100, 100, 100);
    
    // Draw a pic (I used math to reduce the original image's dimensions
    // to fit within the 500x500 box. I would use Max Width and Max Height
    // but I don't know how or if that's even possible):
    davinci.draw(canvasX, canvasY, canvasZ+(canvasSide/2), 321, 500);
    
    // Draw a pic (need to fill in dimensions and uncomment):
    //mondrian.draw(canvasX, canvasY, canvasZ+(canvasSide/2), ?, ?);
    
    // The player-character:
    
    // Debug to test positioning by changing color when player and
    // canvas are at the same depth:
    if (canvasZ >= playerZ-playerRad-(canvasSide/2)) {
        ofSetColor(0, 255, 0);
    }
    else {
        ofSetColor(0,130,255);
    }
    ofSphere(playerX, playerY, playerZ, playerRad);
    
    // Reset color:
    ofSetColor(255);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    switch (key) {
        case OF_KEY_UP:
        case 'w':
        case 'W':
            forward = true;
            break;
            
        case OF_KEY_DOWN:
        case 's':
        case 'S':
            backward = true;
            break;
            
        case OF_KEY_LEFT:
        case 'a':
        case 'A':
            left = true;
            break;
            
        case OF_KEY_RIGHT:
        case 'd':
        case 'D':
            right = true;
            break;
            
        case ' ':
            // Check if player is on the floor:
            if (playerY == floorHeight-playerRad) {
                jump = true;
            }
            break;
    }
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    switch (key) {
        case OF_KEY_UP:
        case 'w':
        case 'W':
            forward = false;
            break;
            
        case OF_KEY_DOWN:
        case 's':
        case 'S':
            backward = false;
            break;
            
        case OF_KEY_LEFT:
        case 'a':
        case 'A':
            left = false;
            break;
            
        case OF_KEY_RIGHT:
        case 'd':
        case 'D':
            right = false;
            break;
            
        case ' ':
            jump = false;
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