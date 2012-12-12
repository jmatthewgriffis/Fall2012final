#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    // Housekeeping:
    ofSetCircleResolution(60);
    ofSetSphereResolution(60);
    ofEnableSmoothing();
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofBackground(0);
    
    
    // The windows:
    // Image credit:
    // http://good-wallpapers.com/wallpapers/15912/1280_Starry%20Sky.jpg :
    nightSky.loadImage("pics/night_sky_texture.jpg");
    
    
    // The paintings:
    // Image credit:
    // http://www.ibiblio.org/wm/paint/auth/vinci/joconde/joconde.jpg :
    davinci.loadImage("pics/davinci.jpg");
    // Image credit:
    // http://www.ibiblio.org/wm/paint/auth/mondrian/broadway.jpg
    mondrian.loadImage("pics/mondrian.jpg");
    
    
    // The music ( I used this utility to generate the mp3 file from the YouTube video: http://www.youtube-mp3.org/ ):
    // Music credit:
    // http://youtu.be/x84m3YyO2oU
    daft.loadSound("music/daft.mp3");
    // Music credit:
    // http://youtu.be/XAYhNHhxN0A
    impossible.loadSound("music/impossible.mp3");
    
    lasered = false; // Boolean for collision.
    lpause = true; // Stall laser movement.
    onePress = false; // Use this to prevent repeat calls to play a music track.
    playDaft = false;
    playImpossible = false;
    fakeFadeDaft = false;
    fakeFadeImpossible = false;
    
    // Movement:
    forward = false;
    backward = false;
    left = false;
    right = false;
    xVel = 5;
    yVel = 0;
    jumpSpd = -7.8;
    gravity = 0.3;
    laserZVel = 0;
    laserXVel = 0;
    extendSpd = 3; // How quickly horizontal lasers stretch across the room.
    extendSpd2 = 6; // How quickly vertical lasers stretch across the room.
    direction = 1;
    direction2 = 1;
    lcounter = 0; // This will count up to initiate laser movement.
    ltimer = 120; // This is what lcounter counts towards.
    reduce = 1.0; // Use this to fake the music fading out (or maybe it's real).
    fadeCounter = 0; // Use this to time the fading out.
    fadeSpeed = 15; // Use this to set the speed of fading out.
    
    windowsill.r = 100;
    windowsill.g = 100;
    windowsill.b = 100;
    
    // Establish sizes first to refer to them when positioning.
    canvasSide = 500;
    playerRad = 50;
    floorLength = 1800; // This should be NHLASERS/laserSpacing.
    floorWidth = 1200; // This should be NVLASERS/laserSpacing.
    laserLength = 0;
    laserLengthV = 0;
    
    // Make code more readable:
    centerW = ofGetWidth()/2;
    centerH = ofGetHeight()/2;
    floorHeight = centerH+(canvasSide/2);
    ceilingHeight = floorHeight-764;
    laserHeight = floorHeight-20;
    
    playerX = centerW;
    playerY = floorHeight-playerRad;
    playerZ = 150;
    canvasZ = -floorLength-(canvasSide/2);
    
    // It's necessary to initialize the lasers in order to run
    // their setup functions and get the effects of the contents:
    for (int i=0; i<NHLASERS; i++) {
        myLasers[i].setup(0, 0, 0);
    }
    for (int i=0; i<NVLASERS; i++) {
        myLasersV[i].setup(0, 0, 0);
    }
}

//--------------------------------------------------------------
void testApp::update(){
    
    // Have to initialize these variables in the update function,
    // because they are dependent on other variables (that update):
    canvasFront = canvasZ+(canvasSide/2);
    roomFront = canvasFront+floorLength;
    leftWallx = centerW-(floorWidth/2);
    rightWallx = centerW+(floorWidth/2);
    canvasX = centerW;
    canvasY = centerH-100;
    
    /* You might think you'd want to change the position of the object
     when the object is moving. However, for z, since we don't have a
     camera following the player object, it would appear to grow smaller
     or larger, and we don't want that. So we move the world instead,
     shifting its position on the z-axis to keep the player object at the
     same scale while giving the illusion of movement. We do the same on
     the x and y axis to prevent weird warping and just give smoother movement.
     I'll move the world for ya, darling: */
    if (forward == true) {
        if (playerZ > canvasFront+playerRad) {
            canvasZ += xVel;
        }
    }
    if (backward == true) {
        // Give the player a little freedom to pull back from the room
        // but not much:
        if (playerZ < roomFront+300) {
            canvasZ -= xVel;
        }
        
    }
    if (left == true) {
        if (playerX > leftWallx+playerRad) {
            centerW += xVel;
        }
    }
    if (right == true) {
        if (playerX < rightWallx-playerRad) {
            centerW -= xVel;
        }
    }
    
    // Update the player's yPos with velocity at all times (but mostly
    // velocity will be zero):
    playerY += yVel;
    
    /* Check if player is in the air, and if so, update the yVel with gravity.
     This check isn't strictly necessary as the floor collision code below stops
     the player from falling farther, but this way is maybe a little more efficient
     since it's not having to undo the constant addition of gravity. It may not make
     a difference, though: */
    if (playerY < floorHeight-playerRad) {
        yVel += gravity;
    }
    
    if (jump == true) {
        yVel = jumpSpd; // Give some yVel for a jump!
        jump = false; // This prevents multiple jumps.
    }
    
    // Let's make sure the player can't fall through the floor or get stuck:
    if (playerY > floorHeight-playerRad) {
        playerY = floorHeight-playerRad;
        yVel = 0;
    }
    
    
    
    //__________________________________________________________
    
    
    
    // Let's do stuff with lasers!
    
    // First, a for loop to cycle through all of the horizontal lasers:
    for (int i=0; i<NHLASERS; i++) {
        
        // Collision detection between the player and the lasers. Hitting a laser
        // currently makes the displayed painting disappear, as reflected in the draw:
        if (playerX+playerRad > myLasers[i].xPos1) {
            if (playerX-playerRad < myLasers[i].xPos2) {
                if (playerY+playerRad > myLasers[i].yPos1) {
                    if (playerY-playerRad < myLasers[i].yPos2) {
                        if (playerZ+playerRad >= myLasers[i].zPos1) {
                            if (playerZ-playerRad <= myLasers[i].zPos2) {
                                lasered = true;
                            }
                        }
                    }
                    
                }
            }
        }
        
        // Update the lasers' length and z-pos:
        
        // Position the lasers on the z-axis (not including movement) and store each value in
        // its own array element:
        laserZs[i] = canvasFront+(myLasers[i].laserSpacing/2)+(myLasers[i].laserSpacing*i);
        
        // Modify the lasers' z-pos based on their own velocity:
        laserZsMod[i] = laserZs[i] + laserZVel;
        
        // Feed variables into the lasers' update function:
        myLasers[i].update(laserLength, floorWidth, extendSpd);
        
        // Set a variable on this page equal to the updated result from the laser's function:
        laserLength = myLasers[i].currLaserLength;
        
        // Collision detection: if a laser hits the front or back of the room, all
        // the lasers reverse direction:
        if (laserZsMod[i] <= canvasFront || laserZsMod[i] >= roomFront) {
            direction *= -1;
        }
    }
    
    // Now, a for loop to cycle through all of the vertical lasers:
    for (int i=0; i<NVLASERS; i++) {
        
        // Collision detection between the player and the lasers. Hitting a laser
        // currently makes the displayed painting disappear, as reflected in the draw:
        if (playerX+playerRad > myLasersV[i].xPos1) {
            if (playerX-playerRad < myLasersV[i].xPos2) {
                if (playerY+playerRad > myLasersV[i].yPos1) {
                    if (playerY-playerRad < myLasersV[i].yPos2) {
                        if (playerZ+playerRad >= myLasersV[i].zPos1) {
                            if (playerZ-playerRad <= myLasersV[i].zPos2) {
                                lasered = true;
                            }
                        }
                    }
                    
                }
            }
        }
        
        // Update the lasers' length and x-pos:
        
        // Position the lasers on the x-axis (not including movement) and store each value in
        // its own array element:
        laserXs[i] = leftWallx+(myLasersV[i].laserSpacing/2)+(myLasersV[i].laserSpacing*i);
        
        // Modify the lasers' x-pos based on their own velocity:
        laserXsMod[i] = laserXs[i] + laserXVel;
        
        // Feed variables into the lasers' update function:
        myLasersV[i].update(laserLengthV, floorLength, extendSpd2);
        
        // Set a variable on this page equal to the updated result from the laser's function:
        laserLengthV = myLasersV[i].currLaserLength;
        
        // Collision detection: if a laser hits the right or left of the room, all
        // the lasers reverse direction:
        if (laserXsMod[i] <= leftWallx || laserXsMod[i] >= rightWallx) {
            direction2 *= -1;
        }
    }
    
    /* Because of the way we will draw the lasers, constantly referring their original position to
     the relative location of the architecture, we cannot give the lasers their own independent
     movement the usual way. So, we use an unorthodox method - each frame we increase or decrease
     the displacement from the lasers' original positions using a "velocity" incremented by a
     directional integer. It does the trick: */
    
    // First we check if the lasers have stretched across the full width of the room
    // and then if they have stretched across the full length of the room:
    if (laserLength == floorWidth) {
        if (laserLengthV == floorLength) {
            // If so, we check if the timer has reached its goal and if not, add to it:
            if (lcounter < ltimer) {
                lcounter ++;
            }
            // If the timer has reached its goal, we turn off the lasers' movement boolean. The
            // effect is that the lasers stretch across the room, pause for a set interval, then move:
            else {
                lpause = false;
            }
        }
    }
    
    // We check if the lasers should move, and if so, move them:
    if (lpause == false) {
        laserZVel += direction;
        laserXVel += direction2;
    }
    
    
    
    //__________________________________________________________
    
    //cout<<playDaft<<endl;
    
    // Let's play some music:
    
    /* Here's how this works. We check if music should change condition. If it should, we
     check if it's already playing. If it's not, we check if other music is already playing.
     If it is, we fade out that music and play this music. If other music is not playing, we
     play this music. If this music is already playing, we stop it cold (no fade out). Either
     way, we immediately turn off the boolean so the condition doesn't change again until
     the player has released and then repressed the button.*/
    if (playDaft == true) {
        if (daft.getIsPlaying() == false) {
            if (impossible.getIsPlaying() == true) {
                fakeFadeImpossible = true;
            }
            else {
                // We set the volume to full in case we previously turned down the
                // volume (by fading the music out):
                daft.setVolume(reduce);
                daft.play();
                playDaft = false;
            }
        }
        else {
            daft.stop();
            playDaft = false;
        }
    }
    
    if (playImpossible == true) {
        if (impossible.getIsPlaying() == false) {
            if (daft.getIsPlaying() == true) {
                fakeFadeDaft = true;
            }
            else {
            impossible.setVolume(reduce);
            impossible.play();
                playImpossible = false;
            }
        }
        else {
            impossible.stop();
            playImpossible = false;
        }
    }
    
    /* I didn't find a built-in option for fading out sounds. Pfft, who needs one?
     I can make this myself, and I did. Here's how it works. We check if the music
     should fade out. If so, we start a counter. When the counter reaches a certain
     total, it reduces the volume of the music by an increment and resets the counter.
     We constantly check the music's volume, and once it reaches zero, we reset the
     volume control (so it can be used again later) and stop the music from playing
     (since it's still going, even though it's silent. As a final touch, we turn off
     the fade-out boolean and reset the counter. Note that if we started the music
     playing again, it would play at its reduced volume, which is why when playing the
     music we reset the volume to full. */
    if (fakeFadeDaft == true) {
        fadeCounter ++;
        if (fadeCounter >= fadeSpeed) {
            reduce -= 0.1;
            daft.setVolume(reduce);
            fadeCounter = 0;
        }
        if (daft.getVolume() <= 0.0) {
            reduce = 1.0;
            daft.stop();
            fakeFadeDaft = false;
            fadeCounter = 0;
        }
    }
    
    if (fakeFadeImpossible == true) {
        fadeCounter ++;
        if (fadeCounter >= fadeSpeed) {
            reduce -= 0.1;
            impossible.setVolume(reduce);
            fadeCounter = 0;
        }
        if (impossible.getVolume() <= 0.0) {
            reduce = 1.0;
            impossible.stop();
            fakeFadeImpossible = false;
            fadeCounter = 0;
        }
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    
    //cout<<lasered<<endl; // Debug.
    
    // Setting the rect mode affects the images:
    ofSetRectMode(OF_RECTMODE_CENTER);
    
    
    
    //__________________________________________________________
    
    
    
    // Let's build a building! One surface at a time!
    
    /* The floor. This looks like a mess but it's not so bad. We simply
     draw the floor by positioning the four corners as vertices, relative
     to the existing objects so all the architecture moves together: */
    ofSetColor(20);
    ofBeginShape();
    // Back-left corner:
    ofVertex(leftWallx, floorHeight, canvasFront);
    // Back-right corner:
    ofVertex(rightWallx, floorHeight, canvasFront);
    // Front-right corner:
    ofVertex(rightWallx, floorHeight, roomFront);
    // Front-left corner:
    ofVertex(leftWallx, floorHeight, roomFront);
    ofEndShape();
    ofSetColor(255); // Color reset.
    
    // The left wall (same as with the floor):
    ofSetColor(10);
    ofBeginShape();
    // Back-lower corner:
    ofVertex(leftWallx, floorHeight, canvasFront);
    // Back-upper corner:
    ofVertex(leftWallx, ceilingHeight, canvasFront);
    // Front-upper corner:
    ofVertex(leftWallx, ceilingHeight, roomFront);
    // Front-lower corner:
    ofVertex(leftWallx, floorHeight, roomFront);
    ofEndShape();
    ofSetColor(255); // Color reset.
    
    // The right wall:
    ofSetColor(10);
    ofBeginShape();
    // Back-lower corner:
    ofVertex(rightWallx, floorHeight, canvasFront);
    // Back-upper corner:
    ofVertex(rightWallx, ceilingHeight, canvasFront);
    // Front-upper corner:
    ofVertex(rightWallx, ceilingHeight, roomFront);
    // Front-lower corner:
    ofVertex(rightWallx, floorHeight, roomFront);
    ofEndShape();
    ofSetColor(255); // Color reset.
    
    
    // The back wall:
    ofSetColor(15);
    ofBeginShape();
    // Lower-left corner:
    ofVertex(leftWallx, floorHeight, canvasFront);
    // Upper-left corner:
    ofVertex(leftWallx, ceilingHeight, canvasFront);
    // Upper-right corner:
    ofVertex(rightWallx, ceilingHeight, canvasFront);
    // Lower-right corner:
    ofVertex(rightWallx, floorHeight, canvasFront);
    ofEndShape();
    ofSetColor(255); // Color reset.
    
    
    // The ceiling:
    ofSetColor(20);
    ofBeginShape();
    // Back-left corner:
    ofVertex(leftWallx, ceilingHeight, canvasFront);
    // Back-right corner:
    ofVertex(rightWallx, ceilingHeight, canvasFront);
    // Front-right corner:
    ofVertex(rightWallx, ceilingHeight, roomFront);
    // Front-left corner:
    ofVertex(leftWallx, ceilingHeight, roomFront);
    ofEndShape();
    ofSetColor(255); // Color reset.
    
    
    // Building complete!
    
    ofSetColor(0,0,255);
    ofLine(leftWallx, floorHeight, roomFront, rightWallx, floorHeight, roomFront);
    ofLine(leftWallx, floorHeight, roomFront, leftWallx, ceilingHeight, roomFront);
    ofLine(rightWallx, floorHeight, roomFront, rightWallx, ceilingHeight, roomFront);
    ofLine(leftWallx, ceilingHeight, roomFront, rightWallx, ceilingHeight, roomFront);
    
    
    
    //__________________________________________________________
    
    
    
    // The windows:
    
    // I thank my good friend Patricio Gonzales Vivo for instructing
    // me in how to use mesh. I still don't totally get what it does,
    // but I understand it enough to use it for cool effect here:
    
    // Left-front window:
    ofSetColor(255); // Color reset.
    
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    // Upper-right point:
    mesh.addVertex(ofPoint(leftWallx,canvasY-200,roomFront-600));
    mesh.addTexCoord(ofPoint(leftWallx,canvasY-200,roomFront-600));
    
    // Upper-left point:
    mesh.addTexCoord(ofPoint(leftWallx,canvasY-200,roomFront-200));
    mesh.addVertex(ofPoint(leftWallx,canvasY-200,roomFront-200));
    
    // Lower-right point:
    mesh.addTexCoord(ofPoint(leftWallx,canvasY+200,roomFront-600));
    mesh.addVertex(ofPoint(leftWallx,canvasY+200,roomFront-600));
    
    // Lower-left point:
    mesh.addTexCoord(ofPoint(leftWallx,canvasY+200,roomFront-200));
    mesh.addVertex(ofPoint(leftWallx,canvasY+200,roomFront-200));
    
    nightSky.getTextureReference().bind();
    mesh.draw();
    nightSky.getTextureReference().unbind();
    
    // Let's fake that the windows are recessed:
    ofSetColor(windowsill);
    ofLine(leftWallx, canvasY+200, roomFront-200, leftWallx, canvasY+200, roomFront-600);
    ofLine(leftWallx, canvasY+200, roomFront-600, leftWallx, canvasY-200, roomFront-600);
    ofLine(leftWallx, canvasY-200, roomFront-200, leftWallx, canvasY-200, roomFront-600);
    
    
    // Left-middle window:
    ofSetColor(255); // Color reset.
    
    ofMesh mesh2;
    mesh2.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    // Upper-right point:
    mesh2.addVertex(ofPoint(leftWallx,canvasY-200,roomFront-1100));
    mesh2.addTexCoord(ofPoint(leftWallx,canvasY-200,roomFront-1100));
    
    // Upper-left point:
    mesh2.addTexCoord(ofPoint(leftWallx,canvasY-200,roomFront-700));
    mesh2.addVertex(ofPoint(leftWallx,canvasY-200,roomFront-700));
    
    // Lower-right point:
    mesh2.addTexCoord(ofPoint(leftWallx,canvasY+200,roomFront-1100));
    mesh2.addVertex(ofPoint(leftWallx,canvasY+200,roomFront-1100));
    
    // Lower-left point:
    mesh2.addTexCoord(ofPoint(leftWallx,canvasY+200,roomFront-700));
    mesh2.addVertex(ofPoint(leftWallx,canvasY+200,roomFront-700));
    
    nightSky.getTextureReference().bind();
    mesh2.draw();
    nightSky.getTextureReference().unbind();
    
    // Let's fake that the windows are recessed:
    ofSetColor(windowsill);
    ofLine(leftWallx, canvasY+200, roomFront-700, leftWallx, canvasY+200, roomFront-1100);
    ofLine(leftWallx, canvasY+200, roomFront-1100, leftWallx, canvasY-200, roomFront-1100);
    ofLine(leftWallx, canvasY-200, roomFront-700, leftWallx, canvasY-200, roomFront-1100);
    
    
    // Left-back window:
    ofSetColor(255); // Color reset.
    
    ofMesh mesh3;
    mesh3.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    // Upper-right point:
    mesh3.addVertex(ofPoint(leftWallx,canvasY-200,roomFront-1600));
    mesh3.addTexCoord(ofPoint(leftWallx,canvasY-200,roomFront-1600));
    
    // Upper-left point:
    mesh3.addTexCoord(ofPoint(leftWallx,canvasY-200,roomFront-1200));
    mesh3.addVertex(ofPoint(leftWallx,canvasY-200,roomFront-1200));
    
    // Lower-right point:
    mesh3.addTexCoord(ofPoint(leftWallx,canvasY+200,roomFront-1600));
    mesh3.addVertex(ofPoint(leftWallx,canvasY+200,roomFront-1600));
    
    // Lower-left point:
    mesh3.addTexCoord(ofPoint(leftWallx,canvasY+200,roomFront-1200));
    mesh3.addVertex(ofPoint(leftWallx,canvasY+200,roomFront-1200));
    
    nightSky.getTextureReference().bind();
    mesh3.draw();
    nightSky.getTextureReference().unbind();
    
    // Let's fake that the windows are recessed:
    ofSetColor(windowsill);
    ofLine(leftWallx, canvasY+200, roomFront-1200, leftWallx, canvasY+200, roomFront-1600);
    ofLine(leftWallx, canvasY+200, roomFront-1600, leftWallx, canvasY-200, roomFront-1600);
    ofLine(leftWallx, canvasY-200, roomFront-1200, leftWallx, canvasY-200, roomFront-1600);
    
    
    // Right-front window:
    ofSetColor(255); // Color reset.
    
    ofMesh mesh4;
    mesh4.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    // Upper-right point:
    mesh4.addVertex(ofPoint(rightWallx,canvasY-200,roomFront-600));
    mesh4.addTexCoord(ofPoint(rightWallx,canvasY-200,roomFront-600));
    
    // Upper-left point:
    mesh4.addTexCoord(ofPoint(rightWallx,canvasY-200,roomFront-200));
    mesh4.addVertex(ofPoint(rightWallx,canvasY-200,roomFront-200));
    
    // Lower-right point:
    mesh4.addTexCoord(ofPoint(rightWallx,canvasY+200,roomFront-600));
    mesh4.addVertex(ofPoint(rightWallx,canvasY+200,roomFront-600));
    
    // Lower-left point:
    mesh4.addTexCoord(ofPoint(rightWallx,canvasY+200,roomFront-200));
    mesh4.addVertex(ofPoint(rightWallx,canvasY+200,roomFront-200));
    
    nightSky.getTextureReference().bind();
    mesh4.draw();
    nightSky.getTextureReference().unbind();
    
    // Let's fake that the windows are recessed:
    ofSetColor(windowsill);
    ofLine(rightWallx, canvasY+200, roomFront-200, rightWallx, canvasY+200, roomFront-600);
    ofLine(rightWallx, canvasY+200, roomFront-600, rightWallx, canvasY-200, roomFront-600);
    ofLine(rightWallx, canvasY-200, roomFront-200, rightWallx, canvasY-200, roomFront-600);
    
    
    // Right-middle window:
    ofSetColor(255); // Color reset.
    
    ofMesh mesh5;
    mesh5.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    // Upper-right point:
    mesh5.addVertex(ofPoint(rightWallx,canvasY-200,roomFront-1100));
    mesh5.addTexCoord(ofPoint(rightWallx,canvasY-200,roomFront-1100));
    
    // Upper-left point:
    mesh5.addTexCoord(ofPoint(rightWallx,canvasY-200,roomFront-700));
    mesh5.addVertex(ofPoint(rightWallx,canvasY-200,roomFront-700));
    
    // Lower-right point:
    mesh5.addTexCoord(ofPoint(rightWallx,canvasY+200,roomFront-1100));
    mesh5.addVertex(ofPoint(rightWallx,canvasY+200,roomFront-1100));
    
    // Lower-left point:
    mesh5.addTexCoord(ofPoint(rightWallx,canvasY+200,roomFront-700));
    mesh5.addVertex(ofPoint(rightWallx,canvasY+200,roomFront-700));
    
    nightSky.getTextureReference().bind();
    mesh5.draw();
    nightSky.getTextureReference().unbind();
    
    // Let's fake that the windows are recessed:
    ofSetColor(windowsill);
    ofLine(rightWallx, canvasY+200, roomFront-700, rightWallx, canvasY+200, roomFront-1100);
    ofLine(rightWallx, canvasY+200, roomFront-1100, rightWallx, canvasY-200, roomFront-1100);
    ofLine(rightWallx, canvasY-200, roomFront-700, rightWallx, canvasY-200, roomFront-1100);
    
    
    // Right-back window:
    ofSetColor(255); // Color reset.
    
    ofMesh mesh6;
    mesh6.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    // Upper-right point:
    mesh6.addVertex(ofPoint(rightWallx,canvasY-200,roomFront-1600));
    mesh6.addTexCoord(ofPoint(rightWallx,canvasY-200,roomFront-1600));
    
    // Upper-left point:
    mesh6.addTexCoord(ofPoint(rightWallx,canvasY-200,roomFront-1200));
    mesh6.addVertex(ofPoint(rightWallx,canvasY-200,roomFront-1200));
    
    // Lower-right point:
    mesh6.addTexCoord(ofPoint(rightWallx,canvasY+200,roomFront-1600));
    mesh6.addVertex(ofPoint(rightWallx,canvasY+200,roomFront-1600));
    
    // Lower-left point:
    mesh6.addTexCoord(ofPoint(rightWallx,canvasY+200,roomFront-1200));
    mesh6.addVertex(ofPoint(rightWallx,canvasY+200,roomFront-1200));
    
    nightSky.getTextureReference().bind();
    mesh6.draw();
    nightSky.getTextureReference().unbind();
    
    // Let's fake that the windows are recessed:
    ofSetColor(windowsill);
    ofLine(rightWallx, canvasY+200, roomFront-1200, rightWallx, canvasY+200, roomFront-1600);
    ofLine(rightWallx, canvasY+200, roomFront-1600, rightWallx, canvasY-200, roomFront-1600);
    ofLine(rightWallx, canvasY-200, roomFront-1200, rightWallx, canvasY-200, roomFront-1600);
    
    
    // Top-front window:
    ofSetColor(255); // Color reset.
    
    ofMesh mesh7;
    mesh7.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    // Upper-right point:
    mesh7.addVertex(ofPoint(canvasX+300,ceilingHeight,roomFront-300));
    mesh7.addTexCoord(ofPoint(canvasX+300,ceilingHeight,roomFront-300));
    
    // Upper-left point:
    mesh7.addTexCoord(ofPoint(canvasX-300,ceilingHeight,roomFront-300));
    mesh7.addVertex(ofPoint(canvasX-300,ceilingHeight,roomFront-300));
    
    // Lower-right point:
    mesh7.addTexCoord(ofPoint(canvasX+300,ceilingHeight,roomFront-700));
    mesh7.addVertex(ofPoint(canvasX+300,ceilingHeight,roomFront-700));
    
    // Lower-left point:
    mesh7.addTexCoord(ofPoint(canvasX-300,ceilingHeight,roomFront-700));
    mesh7.addVertex(ofPoint(canvasX-300,ceilingHeight,roomFront-700));
    
    nightSky.getTextureReference().bind();
    mesh7.draw();
    nightSky.getTextureReference().unbind();
    
    // Let's fake that the windows are recessed:
    ofSetColor(windowsill);
    ofLine(canvasX+300,ceilingHeight,roomFront-300, canvasX+300,ceilingHeight,roomFront-700);
    ofLine(canvasX+300,ceilingHeight,roomFront-700,canvasX-300,ceilingHeight,roomFront-700);
    ofLine(canvasX-300,ceilingHeight,roomFront-300,canvasX-300,ceilingHeight,roomFront-700);
    
    
    // Top-back window:
    ofSetColor(255); // Color reset.
    
    ofMesh mesh8;
    mesh8.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    // Upper-right point:
    mesh8.addVertex(ofPoint(canvasX+300,ceilingHeight,roomFront-1100));
    mesh8.addTexCoord(ofPoint(canvasX+300,ceilingHeight,roomFront-1100));
    
    // Upper-left point:
    mesh8.addTexCoord(ofPoint(canvasX-300,ceilingHeight,roomFront-1100));
    mesh8.addVertex(ofPoint(canvasX-300,ceilingHeight,roomFront-1100));
    
    // Lower-right point:
    mesh8.addTexCoord(ofPoint(canvasX+300,ceilingHeight,roomFront-1500));
    mesh8.addVertex(ofPoint(canvasX+300,ceilingHeight,roomFront-1500));
    
    // Lower-left point:
    mesh8.addTexCoord(ofPoint(canvasX-300,ceilingHeight,roomFront-1500));
    mesh8.addVertex(ofPoint(canvasX-300,ceilingHeight,roomFront-1500));
    
    nightSky.getTextureReference().bind();
    mesh8.draw();
    nightSky.getTextureReference().unbind();
    
    // Let's fake that the windows are recessed:
    ofSetColor(windowsill);
    ofLine(canvasX+300,ceilingHeight,roomFront-1100, canvasX+300,ceilingHeight,roomFront-1500);
    ofLine(canvasX+300,ceilingHeight,roomFront-1500,canvasX-300,ceilingHeight,roomFront-1500);
    ofLine(canvasX-300,ceilingHeight,roomFront-1100,canvasX-300,ceilingHeight,roomFront-1500);
    
    
    
    //__________________________________________________________
    
    
    
    // The paintings:
    
    /* Want to get fancy? Use mesh. It's not useful right now:
     ofSetColor(255); // Color reset.
     
     ofMesh mesh;
     mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
     
     // Upper-right point:
     mesh.addVertex(ofPoint(canvasX+(canvasSide/2),canvasY-(canvasSide/2),canvasFront));
     mesh.addTexCoord(ofPoint(canvasX+(canvasSide/2),canvasY-(canvasSide/2),canvasFront));
     
     // Upper-left point:
     mesh.addTexCoord(ofPoint(canvasX-(canvasSide/2),canvasY-(canvasSide/2),canvasFront));
     mesh.addVertex(ofPoint(canvasX-(canvasSide/2),canvasY-(canvasSide/2),canvasFront));
     
     // Lower-right point:
     mesh.addTexCoord(ofPoint(canvasX+(canvasSide/2),canvasY+(canvasSide/2),canvasFront));
     mesh.addVertex(ofPoint(canvasX+(canvasSide/2),canvasY+(canvasSide/2),canvasFront));
     
     // Lower-left point:
     mesh.addTexCoord(ofPoint(canvasX-(canvasSide/2),canvasY+(canvasSide/2),canvasFront));
     mesh.addVertex(ofPoint(canvasX-(canvasSide/2),canvasY+(canvasSide/2),canvasFront));
     
     davinci.getTextureReference().bind();
     mesh.draw();
     davinci.getTextureReference().unbind();
     */
    
    ofSetColor(60, 50, 23); // Dark brown.
    ofRect(canvasX, canvasY, canvasFront, 341, 520); // Picture frame.
    ofSetColor(127); // This is cool. Limiting the color range to closer to
    // grayscale makes the painting appear as though in dim lighting conditions.
    
    // Draw a pic (I used math to reduce the original image's dimensions
    // to fit within the 500x500 box. I would use Max Width and Max Height
    // but I don't know how or if that's even possible):
    if (lasered == false) {
        davinci.draw(canvasX, canvasY, canvasFront, 321, 500);
    }
    //mondrian.draw(canvasX, canvasY, canvasFront, ?, ?);
    
    ofSetColor(255); // Color reset.
    
    
    
    
    //__________________________________________________________
    
    
    
    // Laser grid:
    
    // Lasers parallel to the x-axis ("horizontal" lasers):
    for (int i=0; i<NHLASERS; i++) {
        myLasers[i].draw(rightWallx-laserLength, laserHeight, laserZsMod[i], rightWallx, laserHeight, laserZsMod[i], laserLength);
    }
    
    // Lasers parallel to the z-axis ("vertical" lasers):
    for (int i=0; i<NVLASERS; i++) {
        myLasersV[i].draw(laserXsMod[i], laserHeight, canvasFront, laserXsMod[i], laserHeight, canvasFront+laserLengthV, laserLengthV);
    }
    
    
    //__________________________________________________________
    
    
    
    // The player-character:
    
    // Debug to test positioning by changing color when player and
    // canvas are at the same depth:
    if (canvasZ >= playerZ-playerRad-(canvasSide/2)) {
        ofSetColor(0, 255, 0); // Green.
    }
    else {
        ofSetColor(0,130,255); // Blue.
    }
    ofSphere(playerX, playerY, playerZ, playerRad);
    
    ofSetColor(255); // Color reset.
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    // Use WASD and arrow keys so people can play however they
    // are comfortable:
    switch (key) {
        case OF_KEY_UP:
        case 'w':
        case 'W':
            forward = true;
            break;
            
        case OF_KEY_DOWN:
        case 's':
        case 'S':
            backward = true;
            break;
            
        case OF_KEY_LEFT:
        case 'a':
        case 'A':
            left = true;
            break;
            
        case OF_KEY_RIGHT:
        case 'd':
        case 'D':
            right = true;
            break;
            
        case ' ':
            // Check if player is on the floor:
            if (playerY == floorHeight-playerRad) {
                jump = true;
            }
            break;
            
        case 'r':
        case 'R':
            if (lasered == true) {
                lasered = false;
            }
            break;
            
        case '1':
            /* What happens here and in the following music-related
             examples is that we check if the button is already pressed.
             If it is not, we trigger the music track and IMMEDIATELY
             indicate the button is already pressed, which remains the case
             until we release the key. This prevents repeat calls if the
             player holds the key down.*/
            if (onePress == false) {
                playDaft = true;
                onePress = true;
            }
            break;
            
        case '2':
            if (onePress == false) {
                playImpossible = true;
                onePress = true;
            }
            break;
    }
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    switch (key) {
        case OF_KEY_UP:
        case 'w':
        case 'W':
            forward = false;
            break;
            
        case OF_KEY_DOWN:
        case 's':
        case 'S':
            backward = false;
            break;
            
        case OF_KEY_LEFT:
        case 'a':
        case 'A':
            left = false;
            break;
            
        case OF_KEY_RIGHT:
        case 'd':
        case 'D':
            right = false;
            break;
            
        case ' ':
            jump = false;
            break;
            
        case '1':
            onePress = false;
            break;
            
        case '2':
            onePress = false;
            break;
    }
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
    
}