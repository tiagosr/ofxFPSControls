//
//  ofxFPSControls.cpp
//
//  Created by Tiago Rezende on 6/21/15.
//
//

#include "ofxFPSControls.h"

ofxFPSCamera::ofxFPSCamera():
b_back(false),b_fwd(false),
b_strafe_down(false),b_strafe_up(false),
b_strafe_left(false), b_strafe_right(false),
b_roll_ccw(false),b_roll_cw(false),
b_yaw_left(false),b_yaw_right(false),
b_roll_reset(false),controlsEnabled(false),
b_pitch_up(false),b_pitch_down(false),
upvector(0, 1, 0),

movespeed(1), rollspeed(1), sensitivity(1),

key_fwd('w', OF_KEY_UP), key_back('s', OF_KEY_DOWN),
key_strafe_left('a', OF_KEY_LEFT), key_strafe_right('d', OF_KEY_RIGHT),
key_roll_ccw('q'), key_roll_cw('e'),
key_roll_reset(-1),key_strafe_down(-1),key_strafe_up(-1),
key_yaw_left(-1),key_yaw_right(-1),
key_pitch_up(-1),key_pitch_down(-1)
{
    ofAddListener(ofEvents().update, this, &ofxFPSCamera::update);
    ofAddListener(ofEvents().keyPressed, this, &ofxFPSCamera::keyPressed);
    ofAddListener(ofEvents().keyReleased, this, &ofxFPSCamera::keyReleased);
    ofAddListener(ofEvents().mouseMoved, this, &ofxFPSCamera::mouseMoved);
    ofAddListener(ofEvents().mouseDragged, this, &ofxFPSCamera::mouseDragged);
}
ofxFPSCamera::~ofxFPSCamera() {
    ofRemoveListener(ofEvents().update, this, &ofxFPSCamera::update);
    ofRemoveListener(ofEvents().keyPressed, this, &ofxFPSCamera::keyPressed);
    ofRemoveListener(ofEvents().keyReleased, this, &ofxFPSCamera::keyReleased);
    ofRemoveListener(ofEvents().mouseMoved, this, &ofxFPSCamera::mouseMoved);
    ofRemoveListener(ofEvents().mouseDragged, this, &ofxFPSCamera::mouseDragged);
}
void ofxFPSCamera::enableControls() {
    ofSetCursorPosition(ofGetWindowWidth()/2, ofGetWindowHeight()/2);
    ofGrabCursor();
    controlsEnabled = true;
    activeFrame = ofGetFrameNum()+1;
}
void ofxFPSCamera::disableControls() {
    ofReleaseCursor();
    controlsEnabled = false;
}

void ofxFPSCamera::update(ofEventArgs&) {
    if (controlsEnabled) {
        if(b_back||b_fwd||b_strafe_left||b_strafe_right||b_strafe_up||b_strafe_down) {
            updateCameraPosition();
        }
        if(b_roll_ccw||b_roll_cw||b_roll_reset||b_yaw_left||b_yaw_right||b_pitch_up||b_pitch_down) {
            updateCameraRoll();
        }
    }
}
void ofxFPSCamera::keyPressed(ofKeyEventArgs& key) {
    if(!controlsEnabled) return;
    if      (key_fwd.map(key.key))          b_fwd = true;
    else if (key_back.map(key.key))         b_back = true;
    else if (key_strafe_left.map(key.key))  b_strafe_left = true;
    else if (key_strafe_up.map(key.key))    b_strafe_up = true;
    else if (key_strafe_right.map(key.key)) b_strafe_right = true;
    else if (key_strafe_down.map(key.key))  b_strafe_down = true;
    else if (key_roll_ccw.map(key.key))     b_roll_ccw = true;
    else if (key_roll_cw.map(key.key))      b_roll_cw = true;
    else if (key_roll_reset.map(key.key))   b_roll_reset = true;
    else if (key_yaw_left.map(key.key))     b_yaw_left = true;
    else if (key_yaw_right.map(key.key))    b_yaw_right = true;
    else if (key_pitch_up.map(key.key))     b_pitch_up = true;
    else if (key_pitch_down.map(key.key))   b_pitch_down = true;
}
void ofxFPSCamera::keyReleased(ofKeyEventArgs& key) {
    if(!controlsEnabled) return;
    if      (key_fwd.map(key.key))          b_fwd = false;
    else if (key_back.map(key.key))         b_back = false;
    else if (key_strafe_left.map(key.key))  b_strafe_left = false;
    else if (key_strafe_up.map(key.key))    b_strafe_up = false;
    else if (key_strafe_right.map(key.key)) b_strafe_right = false;
    else if (key_strafe_down.map(key.key))  b_strafe_down = false;
    else if (key_roll_ccw.map(key.key))     b_roll_ccw = false;
    else if (key_roll_cw.map(key.key))      b_roll_cw = false;
    else if (key_roll_reset.map(key.key))   b_roll_reset = false;
    else if (key_yaw_left.map(key.key))     b_yaw_left = false;
    else if (key_yaw_right.map(key.key))    b_yaw_right = false;
    else if (key_pitch_up.map(key.key))     b_pitch_up = false;
    else if (key_pitch_down.map(key.key))   b_pitch_down = false;
}
void ofxFPSCamera::mouseMoved(ofMouseEventArgs& mouse) {
    if (controlsEnabled) updateCameraRotation(mouse);
}
void ofxFPSCamera::mouseDragged(ofMouseEventArgs& mouse) {
    if (controlsEnabled) updateCameraRotation(mouse);
}
void ofxFPSCamera::updateCameraRoll() {
    float angle = rollspeed * ofGetLastFrameTime();
    if (b_roll_ccw||b_roll_cw) {
        roll(angle*(b_roll_ccw-b_roll_cw));
        upvector = getUpDir();
    }
    if (b_roll_reset) {
        roll(-this->getRoll());
        upvector = ofVec3f(0, 1, 0);
    }
}
void ofxFPSCamera::updateCameraPosition() {
    float speed = movespeed * ofGetLastFrameTime();
    move((getLookAtDir()*(b_fwd-b_back)+
          getSideDir()*(b_strafe_left-b_strafe_right)+
          getUpDir()*(b_strafe_up-b_strafe_down))*movespeed);
}
void ofxFPSCamera::updateCameraRotation(ofMouseEventArgs& mouse) {
    ofVec2f center(ofGetWindowWidth()/2, ofGetWindowHeight()/2);
    if (ofGetFrameNum() < activeFrame) {
        mouse.set(center);
    }
    
    ofVec2f mousedelta = (mouse - center)*sensitivity;
    
    rotate(mousedelta.y, getSideDir());
    rotate(mousedelta.x, upvector);
    
    ofSetCursorPosition(center.x, center.y);
}