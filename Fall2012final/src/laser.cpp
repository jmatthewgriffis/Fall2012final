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
    pulseColor = false;
    counter = 0;
    counterMax = 30;
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
    
    // Control color using a counter. Everytime the counter
    // maxes out, we reset it and switch the color:
    if (counter < counterMax) {
        counter++;
    }
    else if (counter >= counterMax) {
        pulseColor = !pulseColor; // This flips the boolean.
        counter=0; // This resets the counter.
    }
}

void laser::draw(float x, float y, float z, float x2, float y2, float z2, float l) {
    
    // Set lots of things equal to external variables:
    xPos1 = x;
    xPos2 = x2;
    yPos1 = y;
    yPos2 = y2;
    zPos1 = z;
    zPos2 = z2;
    
    laserSpacing = 300;
    
    // Change color based on the counter and boolean:
    if (pulseColor == true) {
        ofSetColor(255, 0, 50);
    }
    else if (pulseColor == false) {
        ofSetColor(255, 0, 0);
    }
    
    
    ofSetLineWidth(200);
    // Use the external variables (which copy the data fed into the draw function)
    // to draw the laser(s):
    ofLine(xPos1, yPos1, zPos1, xPos2, yPos2, zPos2);
    ofSetColor(255); // Color reset.
}