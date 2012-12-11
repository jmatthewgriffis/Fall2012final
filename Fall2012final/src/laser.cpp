//
//  laser.cpp
//  Fall2012final
//
//  Created by John Matthew Griffis on 12/10/12.
//
//

#include "laser.h"

//--------------------------------------------------------------

void laser::setup(float x, float y, float z) {
    
}

void laser::update(float l, float maxLaserLength) {
    
    // Check if the laser has stretched the length of the room
    // yet, and if not, stretch it:
    if (l < maxLaserLength) {
        l+=3;
    }
    if (l > maxLaserLength) {
        l = maxLaserLength;
    }
    // Set the result equal to an external variable we can use
    // in the other page:
    currLaserLength = l;
}

void laser::draw(float x, float y, float z, float l) {
    
    // Set lots of things equal to external variables:
    laserRight = x;
    laserLeft = x-l;
    laserY = y;
    laserZ = z;
    
    laserSpacing = 300;
    ofSetColor(255, 0, 0);
    ofSetLineWidth(200);
    ofLine(laserRight, laserY, laserZ, laserLeft, laserY, laserZ);
    ofSetColor(255); // Color reset.
}