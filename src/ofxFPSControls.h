//
//  ofxFPSControls.h
//
//  Created by Tiago Rezende on 6/21/15.
//
//

#ifndef __RayWarper__ofxFPSControls__
#define __RayWarper__ofxFPSControls__

#include "ofMain.h"

class ofxFPSCamera: public ofCamera {
public:
    struct keymap {
        vector<int> keys;
        inline bool map(int key) {
            for(int i = 0; i < keys.size(); i++) {
                if(keys[i]==key) return true;
            }
            return false;
        }
        keymap() {};
        keymap(int k) {
            keys.push_back(k);
        };
        keymap(int k, int l) {
            keys.push_back(k);
            keys.push_back(l);
        };
    };
    keymap key_fwd, key_back;
    keymap key_strafe_left, key_strafe_right, key_strafe_up, key_strafe_down;
    keymap key_roll_cw, key_roll_ccw, key_yaw_left, key_yaw_right, key_pitch_up, key_pitch_down, key_roll_reset;
    
    ofVec3f upvector;
    ofxFPSCamera();
    float movespeed, rollspeed, sensitivity;
    virtual ~ofxFPSCamera();
    virtual void enableControls();
    virtual void disableControls();
    
protected:
    int activeFrame;
    bool controlsEnabled;
    bool b_fwd, b_back;
    bool b_strafe_left, b_strafe_right, b_strafe_up, b_strafe_down;
    bool b_roll_cw, b_roll_ccw, b_yaw_left, b_yaw_right, b_pitch_up, b_pitch_down, b_roll_reset;
    void update(ofEventArgs&);
    void keyPressed(ofKeyEventArgs&);
    void keyReleased(ofKeyEventArgs&);
    void mouseMoved(ofMouseEventArgs&);
    void mouseDragged(ofMouseEventArgs&);
    void updateCameraRoll();
    void updateCameraPosition();
    void updateCameraRotation(ofMouseEventArgs&);
    
};

#endif /* defined(__RayWarper__ofxFPSControls__) */
