/* 
 * File:   Fireplace.cpp
 * Author: goofanader
 * 
 * Created on February 19, 2013, 6:32 PM
 */

#include "Fireplace.h"
#include "glm/glm.hpp"

Fireplace::Fireplace() {
    GLuint faceNBO;
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/fireplace/Fireplace.obj",
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
    doScale(glm::vec3(2.5 * ROOM_SIZE / 10.f));
    //doRotate(glm::vec3(0, 1, 0), 90.f);
    doTranslate(glm::vec3(0.f, getRoomFloorHeight().y - getAABBmin().y, -ROOM_SIZE + getAABBmax().z));
    //when we have the textures

    glGenTextures(1, &texNum);
    LoadTexture((char *) "objects/meshes/fireplace/marbleUV.bmp", texNum);
    hasTex = true;
    ignore = true;
    //printf("%d\n", texNum);
}

Fireplace::Fireplace(const Fireplace& orig) {
}

Fireplace::~Fireplace() {
}

void Fireplace::drawHighlight(glm::vec3 cameraPos, glm::vec3 lookAt, glm::vec3 lightPos, 
        glm::vec3 lightColor, GameConstants* gc) {
    //do nothing, we don't want a highlight for the moosehead. It's not selectable
}

void Fireplace::update(float dt, GameObject *playerCamera, vec3 camLookAt){

}

std::string Fireplace::className() {
    return "Fireplace";
}
