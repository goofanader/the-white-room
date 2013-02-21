/* 
 * File:   Chandelier.cpp
 * Author: goofanader
 * 
 * Created on February 13, 2013, 12:35 PM
 */

#include "Chandelier.h"

Chandelier::Chandelier() {
    
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/chandelier/Chandelier.obj",
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
    doScale(glm::vec3(3.f));
    doTranslate(glm::vec3(0.f,
            getRoomCeilHeight() - AABBmax.y + .5f, 0.f));
    //this->doScale(glm::vec3(3.f));

    texNum = numTextures();
    LoadTexture((char *) "objects/meshes/chandelier/chandUV.bmp", texNum);
    hasTex = true;

    printf("%d\n", texNum);
    printf("finished Chandelier\n");
}

Chandelier::Chandelier(const Chandelier& orig) {
}

Chandelier::~Chandelier() {
}

bool Chandelier::doesCollide(GameObject* other) {
    return false;
}

std::string Chandelier::className() {
    return "Chandelier";
}
