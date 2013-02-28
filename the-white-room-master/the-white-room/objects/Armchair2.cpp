/* 
 * File:   Armchair2.cpp
 * Author: goofanader
 * 
 * Created on February 12, 2013, 5:32 PM
 */

#include "Armchair2.h"

Armchair2::Armchair2() {
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
    doRotate(glm::vec3(0.f, 1.f, 0.f), 90.f);
    doTranslate(glm::vec3(-20.f,getRoomFloorHeight().y - getAABBmin().y, -ROOM_SIZE + 5.f));
    doTranslate(glm::vec3(10.f, 0.f, 5.f));

    //this->doScale(glm::vec3(3.f));


    texNum = numTextures();
    textureEnum = GL_TEXTURE0 + texNum;
    LoadTexture((char *)"objects/meshes/armchair/ChairTexture.bmp", texNum);
    hasTex = true;
    printf("%d\n", texNum);
}

Armchair2::Armchair2(const Armchair2& orig) {
}

Armchair2::~Armchair2() {
}

void Armchair2::drawHighlight(glm::vec3 cameraPos, glm::vec3 lookAt, glm::vec3 lightPos, 
        glm::vec3 lightColor, GameConstants* gc) {
    //do nothing, we don't want a highlight for the armchair. It's not selectable
}

std::string Armchair2::className() {
    return "Armchair2";
}
