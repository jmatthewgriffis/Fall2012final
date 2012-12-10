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
    void update(float l, float maxlaserLength, float z);
    void draw(float x, float y, float z, float l);
    
    int laserSpacing;
    int laserRight, laserLeft, laserY, laserZ;
    float currLaserLength, currLaserZPos;
    float laserZVel;
    
};

#endif
