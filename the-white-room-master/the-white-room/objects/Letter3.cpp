/* 
 * File:   Letter3.cpp
 * Author: goofanader
 * 
 * Created on June 7, 2013, 10:16 AM
 */

#include "Letter3.h"

Letter3::Letter3() {
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
    
    isVisible = false;
    
    //depthMin = 0;
    //depthMax = 1;
    
    glGenTextures(1, &texNum);
    LoadTexture((char *)"objects/meshes/letter/Letter3A.bmp", texNum);
    hasTex = true;
    ignore = false;
    
    //doRotate(glm::vec3(1,0,0), -90);
    doRotate(glm::vec3(0,1,0), 180);

    doTranslate(glm::vec3(0.f, -3.85f - getAABBmin().y, 0.f));
    doTranslate(glm::vec3(27.f, 0.23f, -4.f));
}

Letter3::Letter3(const Letter3& orig) {
}

Letter3::~Letter3() {
}

std::string Letter3::className() {
    return "Letter3";
}

void Letter3::onEvent(SoundPlayer* soundPlayer) {
    if (isVisible) setIsReading(true, 3);
}