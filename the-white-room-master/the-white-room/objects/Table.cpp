/* 
 * File:   Table.cpp
 * Author: goofanader
 * 
 * Created on February 21, 2013, 12:15 PM
 */

#include "Table.h"

Table::Table() {
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/table/Table3.obj",
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
    
    texNum = numTextures();
    LoadTexture((char *)"objects/meshes/table/Table2.bmp", texNum);
    hasTex = true;

    isClicked = false;
    doRotate(glm::vec3(0,1,0), 90);
    doScale(glm::vec3(ROOM_SIZE / 5.f, ROOM_SIZE / 4.f, ROOM_SIZE / 5.f));
    doTranslate(glm::vec3(0.f, 
            getRoomFloorHeight().y - getAABBmin().y, 0.f));
    //when we have the textures

 /*texNum = numTextures();
    LoadTexture((char *)"objects/meshes/table/tableUV.bmp", texNum);
    hasTex = true;
    printf("%d\n", texNum);*/
}

Table::Table(const Table& orig) {
}

Table::~Table() {
}

std::string Table::className() {
    return "Table";
}