#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Joint.h"



class ofApp : public ofBaseApp{

public:
    
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void drawSkeleton(std::vector<Joint>& joints);
    void draw20JointSkeleton(std::vector<ofSpherePrimitive>& joints);
    void setJointChildren();
    void updateChildrenJoints(glm::vec3 adjustPos);
    void getAllNodes(Joint* j);

    std::vector<Joint*> children_joint_toUpdate;

    std::vector<Joint> joint_skeleton;
    std::vector<ofSpherePrimitive> skeleton;

    std::vector<ofSpherePrimitive> loaded_joints;
    std::vector<std::vector<ofSpherePrimitive>> frames;
    
    
    ofxPanel gui;
    ofxFloatSlider radius, scale, label_offset, skeleton_offset;
    ofxIntSlider resolution;
    ofxIntSlider jointIndex;
    ofParameter<bool> showJointName, showOriginSkeleton;
    ofxFloatSlider adjustSize, axisSize;
    ofxIntSlider skeletonRot;
    ofParameter<bool> adjustChildrenJoints;

    
    ofEasyCam camera;
    
    string export_file_name;
    string file_name;
    
    int frame_index = 180;
    int start_index = 180;
    int end_index = 181;

    
    string joint_name[24] = {"0 Waist",
                             "1 Spine",
                             "2 Chest",
                             "3 Neck",
                             "4 Head",
                             "5 Head Tip",
                             "6 UpperLeg L",
                             "7 LowerLeg L",
                             "8 Foot L",
                             "9 Toes L",
                             "10 UpperLeg R",
                             "11 LowerLeg R",
                             "12 Foot R",
                             "13 Toes R",
                             "14 Collar L",
                             "15 UpperArm L",
                             "16 ForeArm L",
                             "17 Hand L",
                             "18 FingerTip L",
                             "19 Collar R",
                             "20 UpperArm R",
                             "21 ForeArm R",
                             "22 Hand R",
                             "23 FingerTip R"
    };
    
    string joint_name_adjusted[24] = {"0 Waist",
                             "1 Spine",
                             "2 Chest",
                             "3 Neck",
                             "4 UpperLeg L",
                             "5 LowerLeg L",
                             "6 Foot L",
                             "7 Toes L",
                             "8 UpperLeg R",
                             "9 LowerLeg R",
                             "10 Foot R",
                             "11 Toes R",
                             "12 UpperArm L",
                             "13 ForeArm L",
                             "14 Hand L",
                             "15 FingerTip L",
                             "16 UpperArm R",
                             "17 ForeArm R",
                             "18 Hand R",
                             "19 FingerTip R"
    };
    
    
};
