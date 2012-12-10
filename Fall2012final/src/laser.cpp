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

void laser::update() {
    
}

void laser::draw(float x, float y, float z) {
    
    ofSetColor(255, 0, 0);
    ofSetLineWidth(200);
    ofLine(x, y, z, x-200, y, z);
    ofSetColor(255); // Color reset.
}