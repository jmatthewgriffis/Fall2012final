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
    
    bool forward, backward, left, right; // Use for movement.
    
    float playerX, playerY, playerZ; // Positioning.
    float canvasX, canvasY, canvasZ; // Positioning.
    int playerRad, canvasSide; // Sizing.
    int playerVel; // Speed.
    
    /* Note to self: need to fix weird warping issue where moving too
     far to the right or left warps the player-object's shape in the
     direction of the canvas. This may be due to the contingent z-
     positoning.*/
    
};
