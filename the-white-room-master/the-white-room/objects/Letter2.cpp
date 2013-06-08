/* 
 * File:   Letter2.cpp
 * Author: goofanader
 * 
 * Created on June 7, 2013, 10:16 AM
 */

#include "Letter2.h"

Letter2::Letter2() {
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/letter/LetterB.obj",
            IBOlen, VBO, IBO, NBO, TBO, AABBmin, AABBmax);
    dir = vec3(1.f, 0.f, 0.f);
    speed = 0.f;
    rotSpeed = 0.f;
    rotAxis = vec3(0.f, 1.f, 0.f);
    ambColor = vec3(1.f);
    diffColor = vec3(.5f);
    specColor = vec3(.5f);
    ambAlpha = 1.0f;
    diffAlpha = 1.0f;
    specAlpha = 1.0f;
    shininess = 5;
    specStrength = 0.f;
    scale = glm::vec3(1.f);
    rotate = glm::mat4(1.f);
    
    //depthMin = 0;
    //depthMax = 1;
    
    glGenTextures(1, &texNum);
    LoadTexture((char *)"objects/meshes/letter/Letter2A.bmp", texNum);
    hasTex = true;
    ignore = false;
    isVisible = false;
    
    //doRotate(glm::vec3(1,0,0), -90);
    //doRotate(glm::vec3(0,1,0), 90);
    doTranslate(glm::vec3(-20.f,getRoomFloorHeight().y - getAABBmin().y, -ROOM_SIZE + 5.f));
    doTranslate(glm::vec3(6.f, 3.05f, 5.f));
}

Letter2::Letter2(const Letter2& orig) {
}

Letter2::~Letter2() {
}

std::string Letter2::className() {
    return "Letter2";
}

void Letter2::onEvent(SoundPlayer* soundPlayer) {
    if (isVisible) setIsReading(true, 2);
}