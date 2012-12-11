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
    
    laserZVel = 5;
    
}

void laser::update(float l, float maxLaserLength, float z) {
    
    if (l < maxLaserLength) {
        l++;
    }
    currLaserLength = l;
    
    //z ++;
    //currLaserZPos = z;
    
    //cout<<z<<endl;
    
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