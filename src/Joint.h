#pragma once
#include "ofMain.h"

class Joint {
public:
    
    Joint(float x, float y, float z);
    glm::vec3 getPosition();
    void setPosition(glm::vec3 p);
    void setPosition(float x, float y, float z);
    float getX();
    float getY();
    float getZ();
    
    void setParent(Joint* p);
    Joint* getParent();
    void addChild(Joint* c);
    std::vector<Joint*> getChildren();

    
    glm::vec3 position;
    Joint * parent;
    std::vector<Joint*> children;
};
