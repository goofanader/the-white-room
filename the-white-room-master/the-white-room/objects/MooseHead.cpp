/* 
 * File:   MooseHead.cpp
 * Author: goofanader
 * 
 * Created on February 19, 2013, 6:32 PM
 */

#include "MooseHead.h"

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
    shininess = 5;
    specStrength = 0.f;
    scale = glm::vec3(1.f);

    isClicked = false;
    doScale(glm::vec3(ROOM_SIZE / 10.f));
    doRotate(glm::vec3(0,1,0), 90.f);
    doTranslate(glm::vec3(-ROOM_SIZE - AABBmin.x, 
            getRoomCeilHeight() - AABBmax.y - 1.f, -17.f));
    //when we have the textures
/*
 texNum = numTextures();
    LoadTexture((char *)"objects/meshes/armchair/ChairTexture.bmp", texNum);
    hasTex = true;
    printf("%d\n", texNum);*/
}

MooseHead::MooseHead(const MooseHead& orig) {
}

MooseHead::~MooseHead() {
}

std::string MooseHead::className() {
    return "MooseHead";
}