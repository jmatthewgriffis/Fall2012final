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
    
    /* Note to self: need to fix weird warping issue where moving too
     far to the right or left warps the player-object's shape in the
     direction of the canvas. This may be due to the contingent z-
     positoning.*/
    
    /* Also it'd be nice to figure out how to make elements be drawn in front
     or behind each other based on their z-position. */
    
};
