/* 
 * File:   WhiteDoor.cpp
 * Author: goofanader
 * 
 * Created on January 30, 2013, 11:04 PM
 */
#include <iostream>
#include "WhiteDoor.h"
#include "glm/gtx/integer.hpp"

#define GROUND_POS -0.5f

WhiteDoor::WhiteDoor() {
    GLuint faceNBO;
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/door/Door.obj",
            IBOlen, VBO, IBO, NBO, faceNBO, AABBmin, AABBmax);
    
#if 0
    //cube for the room/floor
    Mesh *doorMesh = GeometryCreator::CreateCube(vec3(.1f, 6.f, 3.f));
    Mesh *knobMesh = GeometryCreator::CreateSphere(vec3(.1f), 32, 32);

    door = new GameObject();
    door->VBO = doorMesh->PositionHandle;
    door->IBO = doorMesh->IndexHandle;
    door->IBOlen = doorMesh->IndexBufferLength;
    door->NBO = doorMesh->NormalHandle;
    door->dir = vec3(1.f, 0.f, 0.f);
    door->speed = 0.f;
    door->rotSpeed = 0.f;
    door->rotAxis = vec3(0.f, 1.f, 0.f);
    door->color = vec3(1.f, 1.f, 1.f);
    door->shininess = 5;
    door->specStrength = 0.f;
    door->scale = glm::vec3(1.f);

    knob = new GameObject();
    knob->VBO = knobMesh->PositionHandle;
    knob->IBO = knobMesh->IndexHandle;
    knob->IBOlen = knobMesh->IndexBufferLength;
    knob->NBO = knobMesh->NormalHandle;
    knob->dir = vec3(1.f, 0.f, 0.f);
    knob->speed = 0.f;
    knob->rotSpeed = 0.f;
    knob->rotAxis = vec3(0.f, 1.f, 0.f);
    knob->color = vec3(1.f, 1.f, 1.f);
    knob->shininess = 5;
    knob->specStrength = 0.f;
    knob->scale = glm::vec3(1.f);

    door->AABBmin = glm::vec3(-.05f, -3.f, -1.5f);
    door->AABBmax = glm::vec3(.05f, 3.f, 1.5f);

    door->doTranslate(vec3(9.5f, GROUND_POS - 1.5f, 0.f));
    knob->doTranslate(vec3(-.2f, 0.f, 1.2f) + door->trans);

    AABBmin = door->AABBmin;
    AABBmax = door->AABBmax;

    std::cout << "door->trans: ";
    printf("(%lf, %lf, %lf)\n", door->trans.x, door->trans.y, door->trans.z);

    //setTrans(vec3(9.5f, GROUND_POS - 1.5f, 0.f));
#endif
    
    dir = vec3(1.f, 0.f, 0.f);
    speed = 0.f;
    rotSpeed = 0.f;
    rotAxis = vec3(0.f, 1.f, 0.f);
    shininess = 5;
    specStrength = 0.f;
    scale = glm::vec3(1.f);
    ambColor = glm::vec3(1.f);
    diffColor = glm::vec3(.8f);
    specColor = glm::vec3(.8f);
    isClicked = false;
    isClosed = true;
    
    doorAngle = 180.f;
    
    doScale(glm::vec3(ROOM_SIZE / 5.f));
    
    doRotate(glm::vec3(0, 1, 0), doorAngle);
    doRotate(glm::vec3(0,0,1), -doorAngle);
    doTranslate(glm::vec3(1.75f, -2.f/*-ROOM_SIZE / 2.f + 4*/, ROOM_SIZE - .5f));
}

WhiteDoor::WhiteDoor(const WhiteDoor& orig) {
}

WhiteDoor::~WhiteDoor() {
}
#if 0
void WhiteDoor::draw(glm::vec3 cameraPos, glm::vec3 lookAt,
        glm::vec3 lightPos, glm::vec3 lightColor, GameConstants *gc) {
#if 0
    door->draw(cameraPos, lookAt, lightPos, lightColor, gc);
    knob->draw(cameraPos, lookAt, lightPos, lightColor, gc);
#endif
    draw(cameraPos, lookAt, lightPos, lightColor, gc);
    //printf("coo\n");
}
#endif

void WhiteDoor::update(float dt) {
    glm::vec3 prevBoundMin = AABBmin;
    
    
    if (!isClosed && ) {
        doorAngle = 1;
        doRotate(glm::vec3(0,1,0), doorAngle);
        
        float distanceX = sqrt(pow(AABBmin.x - prevBoundMin.x, 2));
        std::cout << "distance: " << distanceX << std::endl;
        //doTranslate(glm::vec3(distanceX,0,0));
        doTranslate(glm::vec3(1, 0,0));
    }
}
/*
bool WhiteDoor::doesCollide(GameObject* other) {
    //printf("hello\n");
#if 0
    return door->doesCollide(other);
#endif
    return this->doesCollide(other);
}
*/
void WhiteDoor::onEvent(SoundPlayer *soundPlayer){
    soundPlayer->playSound("TryDoor");
#if 0
    door->color = (glm::vec3(1.f, 0.f, 0.f));
    knob->color = (glm::vec3(1.f, 0.f, 0.f));
#endif
    //ambColor = glm::vec3(1.f, 0.f, 0.f);
    isClosed = false;
}

std::string WhiteDoor::className() {
    return "WhiteDoor";
}
