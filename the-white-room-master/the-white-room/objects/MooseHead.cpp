/* 
 * File:   MooseHead.cpp
 * Author: goofanader
 * 
 * Created on February 19, 2013, 6:32 PM
 */

#include "MooseHead.h"
#include "glm/glm.hpp"

MooseHead::MooseHead() {
    GLuint faceNBO;
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/moosehead/MooseHead1.obj",
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
    doScale(glm::vec3(ROOM_SIZE / 10.f));
    doRotate(glm::vec3(0, 1, 0), 90.f);
    doTranslate(glm::vec3(-ROOM_SIZE - getAABBmin().x,
            getRoomCeilHeight() - getAABBmax().y - 1.f, -17.f));
    //when we have the textures

    texNum = numTextures();
    textureEnum = GL_TEXTURE0 + texNum;
    LoadTexture((char *) "objects/meshes/moosehead/MooseUV.bmp", texNum);
    hasTex = true;
    //printf("%d\n", texNum);
}

MooseHead::MooseHead(const MooseHead& orig) {
}

MooseHead::~MooseHead() {
}

void MooseHead::update(float dt, GameObject *playerCamera){
    //make it so it always faces the player
    /*float rotY, rotA;
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
    doRotate(up, 90.f);
    */
}

std::string MooseHead::className() {
    return "MooseHead";
}
