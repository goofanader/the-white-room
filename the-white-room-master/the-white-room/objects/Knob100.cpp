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
    LoadTexture((char *)"objects/meshes/radio/KnobUV.bmp", texNum);
    printOpenGLError();
    hasTex = true;
    
    rotating = 90.f;
    
    //doScale(glm::vec3(3.f));
    //doRotate(glm::vec3(0,1,0), rotating);
    doTranslate(glm::vec3(10, 0, 0));
}

Knob100::Knob100(const Knob100& orig) {
}

Knob100::~Knob100() {
}

std::string Knob100::className() { return "Knob100"; }