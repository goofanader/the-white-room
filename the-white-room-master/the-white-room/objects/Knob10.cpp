/* 
 * File:   Knob10.cpp
 * Author: goofanader
 * 
 * Created on February 24, 2013, 6:44 PM
 */

#include "Knob10.h"
#include "GameObject.h"

Knob10::Knob10() {
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
    LoadTexture((char *)"objects/meshes/radio/Knob2UV.bmp", texNum);
    printOpenGLError();
    hasTex = true;
    
    rotating = 90.f;
    
    //doScale(glm::vec3(3.f));
    //doRotate(glm::vec3(0,1,0), rotating);
    doTranslate(glm::vec3(-10, 0, 0));
}

Knob10::Knob10(const Knob10& orig) {
}

Knob10::~Knob10() {
}

std::string Knob10::className() { return "Knob10"; }