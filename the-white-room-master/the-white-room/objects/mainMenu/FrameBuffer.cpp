/* 
 * File:   FrameBuffer.cpp
 * Author: goofanader
 * 
 * Created on March 18, 2013, 2:15 PM
 */

#include "FrameBuffer.h"

FrameBuffer::FrameBuffer() {
    MeshLoader::loadVertexBufferObjectFromMesh("objects/mainMenu/meshes/FrameBuffer.obj",
            IBOlen, VBO, IBO, NBO, TBO, AABBmin, AABBmax);

    dir = vec3(1.f, 0.f, 0.f);
    speed = 0.f;
    rotSpeed = 0.f;
    rotAxis = vec3(0.f, 1.f, 0.f);
    ambColor = vec3(1.f, 1.f, 1.f);
    shininess = 5;
    specStrength = 0.f;
    scale = vec3(1.f);//glm::vec3(getWindowWidth() / 2.f, getWindowHeight() / 2.f, 1.f);
    //doTranslate(vec3(1.f));

    //glGenTextures(1, &texNum);
    //LoadTexture((char *) "objects/mainMenu/meshes/keyboardKeys/wasd.bmp", texNum);
    //glGenTextures(1, &altTexNum);
    //LoadTexture((char *) "objects/mainMenu/meshes/mouse/mouseUnselected.bmp", altTexNum);
    hasTex = true;
}

FrameBuffer::FrameBuffer(const FrameBuffer& orig) {
}

FrameBuffer::~FrameBuffer() {
}

std::string FrameBuffer::className() {
    return "FrameBuffer";
}