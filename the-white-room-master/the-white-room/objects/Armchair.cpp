/* 
 * File:   Armchair.cpp
 * Author: goofanader
 * 
 * Created on February 12, 2013, 5:32 PM
 */

#include "Armchair.h"

Armchair::Armchair() {
    GLuint faceNBO;
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/armchair/chair.obj",
            IBOlen, VBO, IBO, NBO, TBO, AABBmin, AABBmax);
    dir = vec3(1.f, 0.f, 0.f);
    speed = 0.f;
    rotSpeed = 0.f;
    rotAxis = vec3(0.f, 1.f, 0.f);
    ambColor = vec3(1.f);
    diffColor = vec3(.5f);
    specColor = vec3(.5f);
    ambAlpha = 1.f;
    diffAlpha = 1.f;
    specAlpha = 1.f;
    shininess = 5;
    specStrength = 0.f;
    scale = glm::vec3(1.f);

    isClicked = false;
    
    doScale(glm::vec3(6.f));
    doRotate(glm::vec3(0.f, 1.f, 0.f), -90.f);
    doTranslate(glm::vec3(20.f,getRoomFloorHeight().y - getAABBmin().y, -ROOM_SIZE + 5.f));
    doTranslate(glm::vec3(-5.f, 0.f, 5.f));

    //this->doScale(glm::vec3(3.f));


    glGenTextures(1, &texNum);
    LoadTexture((char *)"objects/meshes/armchair/ChairTexture.bmp", texNum);
    hasTex = true;
    printf("%d\n", texNum);
}

Armchair::Armchair(const Armchair& orig) {
}

Armchair::~Armchair() {
}

void Armchair::drawHighlight(glm::vec3 cameraPos, glm::vec3 lookAt, glm::vec3 lightPos, 
        glm::vec3 lightColor, GameConstants* gc) {
    //do nothing, we don't want a highlight for the armchair. It's not selectable
}

std::string Armchair::className() {
    return "Armchair";
}
