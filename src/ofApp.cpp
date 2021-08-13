#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // Adjust again
//    string filePath = "1-062-1kinect_frame_330_afterAdjusted_afterAdjusted.txt";

    
//    string filePath = "1-062-1kinect_frame_330.txt";
//    string filePath = "1-065_frame_180_afterAdjusted.txt";
    string filePath = "1-065_frame_180.txt";

//    string filePath = "1-083_frame_240.txt";
//    string filePath = "5-173-1kinect_frame_90.txt";
//    string filePath = "5-178-1-1kinect_frame_30.txt";
//    string filePath = "5-178-2_frame_150.txt";
    
    // SEQUENCE 1:
//    string filePath = "seq_1/0-390-1-1-1_frame_30.txt";
//    string filePath = "seq_1/0-390-1-1-2_frame_270.txt";
//    string filePath = "seq_1/0-390-1-1-3_frame_30.txt";
//    string filePath = "seq_1/0-390-1-1-4_frame_90.txt";
//    string filePath = "seq_1/0-390-1-1-5_frame_120.txt";
//    string filePath = "seq_1/0-390-1-1-7_frame_240.txt";
//    string filePath = "seq_1/0-390-1-1-8_frame_30.txt";
//    string filePath = "seq_1/0-390-1-1-9_frame_60.txt";
//    string filePath = "seq_1/0-390-1-1-10_frame_30.txt";
//    string filePath = "seq_1/0-390-1-1-2_frame_270.txt";
//    string filePath = "seq_1/0-390-1-1-13_frame_180.txt";
//    string filePath = "seq_1/0-390-1-1-14_frame_60.txt";
//    string filePath = "seq_1/0-390-1-1-15_frame_60.txt";
//    string filePath = "seq_1/0-390-1-1-16_frame_60.txt";
//    string filePath = "seq_1/0-390-1-1-17_frame_30.txt";


    
    export_file_name = filePath.substr(0, filePath.find("."));
    
    //Load file placed in bin/data
    ofFile file(filePath);
    
    if(!file.exists()){
        ofLogError("The file " + filePath + " is missing");
    }
    ofBuffer buffer(file);
    
    int index = 0;
    for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
        
        string line = *it;
        
        vector<string> words = ofSplitString(line, ",");
        
        float x = ofToFloat(words[0]);
        float y = ofToFloat(words[1]);
        float z = ofToFloat(words[2]);
                    
        ofSpherePrimitive sphere;
        sphere.setPosition(x, y, z);
        
        skeleton.push_back(sphere);
        
        Joint joint(x, y, z);
        // joint set children
        
        joint_skeleton.push_back(joint);
        
        
        index++;

        
    }
    
    gui.setup();
    gui.add(radius.setup("radius", 5.0, 0.01, 10.0));
    gui.add(scale.setup("scale", 250.0, 1.0, 1000.0));
    gui.add(label_offset.setup("label_offset", -0.01, -0.1, 0.1));
    gui.add(skeleton_offset.setup("skeleton_offset", 500, -200, 500));

    
    gui.add(resolution.setup("resolution", 2, 1, 10));
    

    gui.add(adjustSize.setup("adjustSize", 0.1, 0.001, 0.1));
    gui.add(showJointName.set("showJointName", false));
    gui.add(axisSize.setup("axisSize", 100, 0.1, 100));


    gui.add(skeletonRot.setup("skeletonRot", 0, 0, 360));
    gui.add(showOriginSkeleton.set("showOriginSkeleton", true));
    gui.add(adjustChildrenJoints.set("adjustChildrenJoints", true));
    gui.add(jointIndex.setup("jointIndex", 1, 0, 23));
    


    setJointChildren();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255);
    
    camera.begin();
    
    
    ofDrawAxis(axisSize);
    
    
    ofPushMatrix();   // scale
    ofScale(scale);
    if(showOriginSkeleton){
        drawSkeleton(joint_skeleton);
    }

    
    // draw loaded frame
    
    ofPushMatrix();
    ofTranslate(skeleton_offset/scale, 0, 0);
        
    draw20JointSkeleton(loaded_joints);
    ofPopMatrix();
    
    
    ofPopMatrix();  // scale
    
    camera.end();
    
    gui.draw();
}

void ofApp::keyPressed(int key){
    
    glm::vec3 adjustPos(0, 0, 0);
    
    if( key == OF_KEY_LEFT ){
        adjustPos.x -= adjustSize;
    }
    
    if( key == OF_KEY_RIGHT ){
        adjustPos.x += adjustSize;
    }
    
    if( key == OF_KEY_UP ){
        adjustPos.y += adjustSize;
    }
    
    if( key == OF_KEY_DOWN ){
        adjustPos.y -= adjustSize;
    }
    if(key == 'w')
    {
        adjustPos.z -= adjustSize;
    }
       
    if(key == 's'){
        adjustPos.z += adjustSize;
    }
    if(key == OF_KEY_LEFT || key == OF_KEY_RIGHT || key == OF_KEY_UP || key == OF_KEY_DOWN || key == 'w' || key == 's')
    {
        joint_skeleton[jointIndex].position += adjustPos;

        cout << joint_name[jointIndex] << " position: " << joint_skeleton[jointIndex].getPosition() << "\n" << endl;
        
        if(adjustChildrenJoints) {
            updateChildrenJoints(adjustPos);

        }
    }
    
    
    
    
    if (key == 'e') {
        
        // export 1 frame after adjust
//        file_name = "export/"+ export_file_name + "/" + export_file_name + "_Adjusted.txt";
        file_name = "export/"+ export_file_name + "_Adjusted.txt";
        
        
        ofFile frame_after(file_name, ofFile::WriteOnly);

        for(int i = 0; i < joint_skeleton.size(); i++)
        {
//            if(i == 4 || i == 5 || i == 14 || i == 19) {
//
//            }else{
                Joint & joint = joint_skeleton[i];
                glm::vec3 pos = joint.getPosition();
                frame_after << ofToString(pos.x) << "," <<
                          ofToString(pos.y) << "," <<
                          ofToString(pos.z) << "," <<
                endl;
//            }
        }
    }
    
    if (key == 'l') {
        loaded_joints.clear();
        string filePath = file_name;
        
        //Load file placed in bin/data
        ofFile file(filePath);
        
        if(!file.exists()){
            ofLogError("The file " + filePath + " is missing");
        }
        ofBuffer buffer(file);
        
        //Read file line by line
        

        
        for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
            
            string line = *it;
            
            vector<string> words = ofSplitString(line, ",");
            
            float x = ofToFloat(words[0]);
            float y = ofToFloat(words[1]);
            float z = ofToFloat(words[2]);
                        
            ofSpherePrimitive sphere;
            sphere.setPosition(x, y, z);
            
            loaded_joints.push_back(sphere);
            
        }
        
    }
    
}

void ofApp::drawSkeleton(std::vector<Joint>& joints){
    ofPushMatrix();
    
    for(int i = 0; i < joints.size(); i++)
    {
        ofSetColor(0);
        Joint & joint = joints[i];
        glm::vec3 pos = joint.getPosition();
        ofSpherePrimitive sphere;
        sphere.setPosition(pos);
        sphere.set(radius/scale, resolution);
        if(i == 4 || i == 5 || i == 14 || i == 19) {
            ofSetColor(0,20);
        }else{
            ofSetColor(0);
        }
        sphere.draw();
        if(showJointName){
             ofVec3f labelOffset(0, 0, label_offset);
            ofDrawBitmapString(joint_name[i], joint.getPosition() + labelOffset);
        }
        
    }
    if(joints.size()> 0) {
        //    0    Waist
        //    1    Spine    Waist    0
        ofDrawLine(joints[1].getPosition(), joints[0].getPosition());
        //    2    Chest    Spine    1
        ofDrawLine(joints[2].getPosition(), joints[1].getPosition());
        //    3    Neck    Chest    2
        ofDrawLine(joints[3].getPosition(), joints[2].getPosition());
        //    4    Head    Neck    3
        ofDrawLine(joints[4].getPosition(), joints[3].getPosition());
        //    5    Head Tip    Head    4
        ofDrawLine(joints[5].getPosition(), joints[4].getPosition());
        //    6    UpperLeg L    Waist    0
        ofDrawLine(joints[6].getPosition(), joints[0].getPosition());
        //    7    LowerLeg L    UpperLeg L    6
        ofDrawLine(joints[7].getPosition(), joints[6].getPosition());
        //    8    Foot L    LowerLeg L    7
        ofDrawLine(joints[8].getPosition(), joints[7].getPosition());
        //    9    Toes L    Foot L    8
        ofDrawLine(joints[9].getPosition(), joints[8].getPosition());
        //    10    UpperLeg R    Waist    0
        ofDrawLine(joints[10].getPosition(), joints[0].getPosition());
        //    11    LowerLeg R    UpperLeg R    10
        ofDrawLine(joints[11].getPosition(), joints[10].getPosition());
        //    12    Foot R    LowerLeg R    11
        ofDrawLine(joints[12].getPosition(), joints[11].getPosition());
        //    13    Toes R    Foot R    12
        ofDrawLine(joints[13].getPosition(), joints[12].getPosition());
        //    15    UpperArm L   Chest    2
        ofDrawLine(joints[15].getPosition(), joints[2].getPosition());
        //    16    ForeArm L    UpperArm L    15
        ofDrawLine(joints[16].getPosition(), joints[15].getPosition());
        //    17    Hand L    ForeArm L    16
        ofDrawLine(joints[17].getPosition(), joints[16].getPosition());
        //    18    FingerTip L    Hand L    17
        ofDrawLine(joints[18].getPosition(), joints[17].getPosition());
        //    19    Collar R    Chest    2
        ofDrawLine(joints[20].getPosition(), joints[2].getPosition());
        //    21    ForeArm R    UpperArm R    20
        ofDrawLine(joints[21].getPosition(), joints[20].getPosition());
        //    22    Hand R    ForeArm R    21
        ofDrawLine(joints[22].getPosition(), joints[21].getPosition());
        //    23    FingerTip R    Hand R    22
        ofDrawLine(joints[23].getPosition(), joints[22].getPosition());
    }
    ofPopMatrix();
}

void ofApp::draw20JointSkeleton(std::vector<ofSpherePrimitive>& joints){
    for(int i = 0; i < joints.size(); i++)
    {
        if(i == 4 || i == 5 || i == 14 || i == 19) {
            ofSetColor(255,0,0,20);
        }else{
            ofSetColor(0,0,255);
        }
        
        ofSpherePrimitive & joint = joints[i];
        glm::vec3 pos = joint.getPosition();
        joint.set(radius/scale, resolution);
        joint.draw();
        if(showJointName){
             ofVec3f labelOffset(0, 0, label_offset);
            ofDrawBitmapString(joint_name[i], joint.getPosition() + labelOffset);
        }
        
    }
    if(joints.size()> 0) {
        //    0    Waist
        //    1    Spine    Waist    0
        ofDrawLine(joints[1].getPosition(), joints[0].getPosition());
        //    2    Chest    Spine    1
        ofDrawLine(joints[2].getPosition(), joints[1].getPosition());
        //    3    Neck    Chest    2
        ofDrawLine(joints[3].getPosition(), joints[2].getPosition());
        //    4    Head    Neck    3
//        ofDrawLine(joints[4].getPosition(), joints[3].getPosition());
//        //    5    Head Tip    Head    4
//        ofDrawLine(joints[5].getPosition(), joints[4].getPosition());
        //    6    UpperLeg L    Waist    0
        ofDrawLine(joints[6].getPosition(), joints[0].getPosition());
        //    7    LowerLeg L    UpperLeg L    6
        ofDrawLine(joints[7].getPosition(), joints[6].getPosition());
        //    8    Foot L    LowerLeg L    7
        ofDrawLine(joints[8].getPosition(), joints[7].getPosition());
        //    9    Toes L    Foot L    8
        ofDrawLine(joints[9].getPosition(), joints[8].getPosition());
        //    10    UpperLeg R    Waist    0
        ofDrawLine(joints[10].getPosition(), joints[0].getPosition());
        //    11    LowerLeg R    UpperLeg R    10
        ofDrawLine(joints[11].getPosition(), joints[10].getPosition());
        //    12    Foot R    LowerLeg R    11
        ofDrawLine(joints[12].getPosition(), joints[11].getPosition());
        //    13    Toes R    Foot R    12
        ofDrawLine(joints[13].getPosition(), joints[12].getPosition());
        //    14    Collar L    Chest    2
//        ofDrawLine(joints[14].getPosition(), joints[2].getPosition());
        //    15    UpperArm L    Collar L    14   !!!CHANGEd to Chest 2
        ofDrawLine(joints[15].getPosition(), joints[2].getPosition());
        //    16    ForeArm L    UpperArm L    15
        ofDrawLine(joints[16].getPosition(), joints[15].getPosition());
        //    17    Hand L    ForeArm L    16
        ofDrawLine(joints[17].getPosition(), joints[16].getPosition());
        //    18    FingerTip L    Hand L    17
        ofDrawLine(joints[18].getPosition(), joints[17].getPosition());
        //    19    Collar R    Chest    2
//        ofDrawLine(joints[19].getPosition(), joints[2].getPosition());
        //    20    UpperArm R    Collar R    19   !!!CHANGEd to Chest 2
        ofDrawLine(joints[20].getPosition(), joints[2].getPosition());
        //    21    ForeArm R    UpperArm R    20
        ofDrawLine(joints[21].getPosition(), joints[20].getPosition());
        //    22    Hand R    ForeArm R    21
        ofDrawLine(joints[22].getPosition(), joints[21].getPosition());
        //    23    FingerTip R    Hand R    22
        ofDrawLine(joints[23].getPosition(), joints[22].getPosition());
    }
    
}

void ofApp::setJointChildren(){
    

    joint_skeleton[1].addChild(&joint_skeleton[2]);
    joint_skeleton[2].addChild(&joint_skeleton[3]);
    joint_skeleton[2].addChild(&joint_skeleton[15]);
    joint_skeleton[2].addChild(&joint_skeleton[20]);
    joint_skeleton[3].addChild(&joint_skeleton[4]);
    joint_skeleton[4].addChild(&joint_skeleton[5]);
    joint_skeleton[6].addChild(&joint_skeleton[7]);
    joint_skeleton[7].addChild(&joint_skeleton[8]);
    joint_skeleton[8].addChild(&joint_skeleton[9]);
    joint_skeleton[10].addChild(&joint_skeleton[11]);
    joint_skeleton[11].addChild(&joint_skeleton[12]);
    joint_skeleton[12].addChild(&joint_skeleton[13]);
    joint_skeleton[15].addChild(&joint_skeleton[16]);
    joint_skeleton[16].addChild(&joint_skeleton[17]);
    joint_skeleton[17].addChild(&joint_skeleton[18]);
    joint_skeleton[20].addChild(&joint_skeleton[21]);
    joint_skeleton[21].addChild(&joint_skeleton[22]);
    joint_skeleton[22].addChild(&joint_skeleton[23]);
   
//    joint_skeleton[1].addChild(joint_skeleton[2]);
//    joint_skeleton[2].addChild(joint_skeleton[3]);
//    joint_skeleton[2].addChild(joint_skeleton[15]);
//    joint_skeleton[2].addChild(joint_skeleton[20]);
//    joint_skeleton[3].addChild(joint_skeleton[4]);
//    joint_skeleton[4].addChild(joint_skeleton[5]);
//    joint_skeleton[6].addChild(joint_skeleton[7]);
//    joint_skeleton[7].addChild(joint_skeleton[8]);
//    joint_skeleton[8].addChild(joint_skeleton[9]);
//    joint_skeleton[10].addChild(joint_skeleton[11]);
//    joint_skeleton[11].addChild(joint_skeleton[12]);
//    joint_skeleton[12].addChild(joint_skeleton[13]);
//    joint_skeleton[15].addChild(joint_skeleton[16]);
//    joint_skeleton[16].addChild(joint_skeleton[17]);
//    joint_skeleton[17].addChild(joint_skeleton[18]);
//    joint_skeleton[20].addChild(joint_skeleton[21]);
//    joint_skeleton[21].addChild(joint_skeleton[22]);
//    joint_skeleton[22].addChild(joint_skeleton[23]);
    
    // TO TEST if this structure working
//    std::vector<Joint*> children_joint = joint_skeleton[1].getChildren();
//    for(auto joint: children_joint){
//        joint->position.x += 10;
//    }
}

void ofApp::updateChildrenJoints(glm::vec3 adjustPos){
    children_joint_toUpdate.clear();
    Joint curr = joint_skeleton[jointIndex];
    
    getAllNodes(&curr);
    
    for(auto joint: children_joint_toUpdate) {
        joint->position += adjustPos;
    }
//    while(curr.getChildren().size() > 0) {
//        std::vector<Joint*> children = curr.getChildren();
//        for(auto child : children) {
//            child->position += adjustPos;
//        }
//    }
}

void ofApp::getAllNodes(Joint* j){
    for (auto joint : j->getChildren()){
        if(j->getChildren().size() > 0) {
            children_joint_toUpdate.push_back(joint);
            getAllNodes(joint);
        }
    }
}




// if(i == 4 || i == 5 || i == 14 || i == 19) {
