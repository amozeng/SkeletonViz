#include "Joint.h"

Joint::Joint(float x, float y, float z){
    position.x = x;
    position.y = y;
    position.z = z;
}

glm::vec3 Joint::getPosition(){
    return position;
}

void Joint::setPosition(glm::vec3 p){
    position = p;
}

void Joint::setPosition(float x, float y, float z){
    position.x = x;
    position.y = y;
    position.z = z;
}

float Joint::getX(){
    return position.x;
}
float Joint::getY(){
    return position.y;
}

float Joint::getZ(){
    return position.z;
}



void Joint::setParent(Joint* p) {
    this->parent = p;
}


Joint* Joint::getParent(){
    return parent;
}

void Joint::addChild(Joint* c){
    children.push_back(c);
}

std::vector<Joint*> Joint::getChildren(){
    return children;
}

