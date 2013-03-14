/* 
 * File:   Box1.cpp
 * Author: goofanader
 * 
 * Created on January 31, 2013, 6:34 AM
 */

#include "Box1.h"

Box1::Box1() {
    Mesh *cubeMesh = GeometryCreator::CreateCube(vec3(1.f));

    cube = new GameObject();
    cube->VBO = cubeMesh->PositionHandle;
    cube->IBO = cubeMesh->IndexHandle;
    cube->IBOlen = cubeMesh->IndexBufferLength;
    cube->NBO = cubeMesh->NormalHandle;
    cube->dir = vec3(1.f, 0.f, 0.f);
    cube->speed = 0.f;
    cube->rotSpeed = 0.f;
    cube->rotAxis = vec3(0.f, 1.f, 0.f);
    cube->ambColor = vec3(1.f, 1.f, 1.f);
    cube->shininess = 5;
    cube->specStrength = 0.f;
    cube->scale = glm::vec3(1.f);
    
    cube->AABBmin = vec3(1.f) / 2.f * -1.f;
    cube->AABBmax = vec3(1.f) / 2.f;
    cube->doTranslate(vec3(4.f,-1.f,4.f));
    
    AABBmin = cube->AABBmin;
    AABBmax = cube->AABBmax;
    //setTrans(vec3(4.f,-1.f,4.f));
    
    this->ambColor = cube->ambColor;
}

Box1::Box1(const Box1& orig) {
}

Box1::~Box1() {
}

void Box1::draw(glm::vec3 cameraPos, glm::vec3 lookAt, glm::vec3 lightPos,
        glm::vec3 lightColor, GameConstants* gc) {
    if (DRAW_CUBE)
        cube->draw(cameraPos, lookAt, lightPos, lightColor, gc);
}

void Box1::update(float dt, GameObject* playerCamera, vec3 camLookAt){
}

bool Box1::doesCollide(GameObject* other) {
    return false;
}

std::string Box1::className() {
    return "Box1";
}

void Box1::onEvent(SoundPlayer* soundPlayer) {
}