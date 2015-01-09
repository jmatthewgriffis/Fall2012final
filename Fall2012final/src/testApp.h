/* This is a game by me, J. Matthew Griffis. Anything I didn't 
 take from the Internet is (c)2012 John Matthew Griffis. I 
 made this for the final project of the Fall 2012 semester of 
 my studies for the MFA in Design and Technology at Parsons 
 the New School for Design.
 */

#pragma once

#include "ofMain.h"
#include "laser.h"

#define NHLASERS 6
#define NVLASERS 4

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
    
    //__________________________________________________________
    
    // Player and environment:
    
    bool forward, backward, left, right, jump; // Use for movement.
    
    bool closeToRestart; // Use for the restart control panel.
    
    bool grabPainting; // Use to detect proximity to painting.
    bool paintingGrabbed; // Time to win.
    bool denied; // Use to exasperate.
    bool unpressSpace; // Use to force a second press of SPACE.
    int textCounter, textCounterMax; // Use to time some text.
    int deniedCounter, deniedCounterMax; // Use to time exasperating the player.
    
    
    // Positioning:
    float playerX, playerY, playerZ, capeY, capeZ, canvasX, canvasY, canvasZ,
    centerW, centerH, leftWallx, rightWallx, floorHeight, ceilingHeight,
    canvasFront, roomFront, centerRects;
    
    float playerRad, handRad, footRad, canvasSide, davinciWidth, davinciHeight, floorLength, floorWidth; // Sizing.
    
    float xVel, yVel, jumpSpd, gravity, textVel; // Speed.
    
    ofColor windowsill, light, lightPatch;
    
    //__________________________________________________________
    
    // Laser grid:
    
    float laserLength, laserLengthV, laserHeight;
    int laserZVel, laserXVel, extendSpd, extendSpd2;
    int direction, direction2; // Boolean-like, to control direction.
    int lcounter, ltimer; // Use to control the timing of the lasers.
    
    bool lasered; // Use for detecting collisions with lasers.
    bool lpause; // Use for stalling the laser movement.
    
    laser myLasers [NHLASERS]; // Array of horizontal lasers.
    float laserZs [NHLASERS]; // Array of z-pos variables.
    float laserZsMod [NHLASERS]; // Array of modified z-pos variables.
    
    laser myLasersV [NVLASERS]; // Array of vertical lasers.
    float laserXs [NVLASERS]; // Array of x-pos variables.
    float laserXsMod [NVLASERS]; // Array of modified x-pos variables.
    
    ofSoundPlayer laser;
    ofSoundPlayer ouch;
    ofSoundPlayer grab;
    
    //__________________________________________________________
    
    // Art:
    
    ofImage davinci, mondrian;
    
    // Texture for the windows:
    
    ofImage nightSky;
    
    //__________________________________________________________
    
    // Jams:
    
    ofSoundPlayer daft, impossible;
    
    bool playDaft, playImpossible, onePress, fakeFadeDaft, fakeFadeImpossible, closeToMusic;
    
    float reduce;
    
    int fadeCounter, fadeSpeed;
    
    //__________________________________________________________
    
    /* It'd be nice to figure out how to make elements be drawn in front
     or behind each other based on their z-position.
     
     Update: I talked with Patricio about this and he says there is no fix for this that he's aware of. */
    
};
