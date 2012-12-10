#pragma once

#include "ofMain.h"

class testApp : public ofBaseApp{
    
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
    
    bool forward, backward, left, right, jump; // Use for movement.
    
    // Positioning:
    float playerX, playerY, playerZ, canvasX, canvasY, canvasZ,
    centerW, centerH, leftWallx, rightWallx, floorHeight, ceilingHeight,
    canvasFront;
    
    int playerRad, canvasSide, floorLength, floorWidth; // Sizing.
    
    float xVel, yVel, jumpSpd, gravity; // Speed.
    
    ofImage davinci;
    ofImage mondrian;
    
    /* It'd be nice to figure out how to make elements be drawn in front
     or behind each other based on their z-position.
     
     Update: I talked with Patricio about this and he says there is no fix for this that he's aware of. */
    
};
