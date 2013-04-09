//
//  laser.h
//  Fall2012final
//
//  Created by John Matthew Griffis on 12/10/12.
//
//

#ifndef Fall2012final_laser_h
#define Fall2012final_laser_h

// This file contains all the OF code. Make sure to "include" it:
#include "ofMain.h"

class laser {
    
public:
    
    void setup(float x, float y, float z);
    void update(float l, float maxlaserLength, int spd);
    void draw(float x, float y, float z, float x2, float y2, float z2, float l);
    
    int laserSpacing;
    float xPos1,xPos2,yPos1,yPos2,zPos1,zPos2;
    float currLaserLength;
    
    bool pulseColor; // Use this to change the color for a pulsing effect.
    
    int counter, counterMax; // Use to control pulsing.
    
};

#endif
