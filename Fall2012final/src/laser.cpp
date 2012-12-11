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
    
    if (l < maxLaserLength) {
        l++;
    }
    currLaserLength = l;
}

void laser::draw(float x, float y, float z, float l) {
    
    laserRight = x;
    laserLeft = x-l;
    laserY = y;
    laserZ = z;
    laserSpacing = 300;
    ofSetColor(0, 255, 0);
    ofSetLineWidth(200);
    ofLine(laserRight, laserY, laserZ, laserLeft, laserY, laserZ);
    ofSetColor(255); // Color reset.
}