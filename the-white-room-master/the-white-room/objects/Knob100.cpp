/* 
 * File:   Knob100.cpp
 * Author: goofanader
 * 
 * Created on February 24, 2013, 6:44 PM
 */

#include "Knob100.h"
#include "GameObject.h"

Knob100::Knob100() {
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/radio/Knob.obj",
            IBOlen, VBO, IBO, NBO, TBO, AABBmin, AABBmax);
    dir = vec3(1.f, 0.f, 0.f);
    speed = 0.f;
    rotSpeed = 0.f;
    rotAxis = vec3(0.f, 1.f, 0.f);
    ambColor = vec3(.75f);
    diffColor = vec3(0.1, 0.74, 0.32);
    specColor = vec3(.5f);
    shininess = 5;
    specStrength = 0.f;
    scale = glm::vec3(1.f);

    texNum = numTextures();
    textureEnum = GL_TEXTURE0 + texNum;
    printOpenGLError();
    LoadTexture((char *)"objects/meshes/radio/KnobUVbrass.bmp", texNum);
    printOpenGLError();
    hasTex = true;
    
    rotating = 18.f;
    
    doScale(glm::vec3(0.75f));
    //doRotate(glm::vec3(1,0,0), rotating);
    doTranslate(glm::vec3(27.f, 0, -1.f));
    
    station = 1000;
}

Knob100::Knob100(const Knob100& orig) {
}

Knob100::~Knob100() {
}

int Knob100::getStation() {
    return station;
}

void Knob100::update(float dt, GameObject *playerCamera){
    //make it so it always faces the player
    float rotY, rotA;
    vec3 up = glm::vec3(0.f, 1.f, 0.f);

    vec3 loc = playerCamera->trans - this->trans;

    vec3 axis = glm::cross(up, loc);
    //vec3 axis = up * loc;

    if(loc.z == 0 && loc.x == 0)
        rotY = 0;
    else
        rotY = atan2(loc.x, loc.z) * 180.0/3.14 - 90;

    rotA = 90 - asin(glm::length(axis)/(glm::length(loc))) * 180.0 / 3.14;

    if(loc.y > 0)
        rotA = -rotA;

    this->rotate = glm::mat4(1.f);
    doRotate(axis,rotA);

    doRotate(up, rotY);
    doRotate(glm::vec3(1.f,0.f,0.f), rotating);

    //doRotate(up, 90.f);
    
    if (isHighlighted) {
        highlightColor = highlightColor + vec3(HIGHLIGHT_SPEED);

        if (highlightColor.x > 1.f) {
            highlightColor = vec3(1.f);
        }
        
        highlightAlpha += HIGHLIGHT_SPEED;
        if (highlightAlpha > 1.f) {
            highlightAlpha = 1.f;
        }
    } else {
        isHighlightDisappearing = true;
        highlightColor = highlightColor - vec3(HIGHLIGHT_SPEED);
        
        if (highlightColor.x < 0.f) {
            highlightColor = vec3(0.f);
        }
        
        highlightAlpha -= HIGHLIGHT_SPEED;
        if (highlightAlpha < 0.f) {
            isHighlightDisappearing = false;
            highlightAlpha = 0.f;
        }
    }
}

void Knob100::onEvent(SoundPlayer *soundPlayer){
    soundPlayer->playSound("TryRadio");

    rotating += 36.f;
    
    station += 100;
    
    if (station > 1500) {
        station = 600;
    }
}

std::string Knob100::className() { return "Knob100"; }
