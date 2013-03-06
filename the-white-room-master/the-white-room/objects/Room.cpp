/* 
 * File:   Room.cpp
 * Author: goofanader
 * 
 * Created on January 30, 2013, 10:11 AM
 */
#include <sstream>
#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Room.h"

#define GROUND_POS -.5f

Room::Room() {
    //cube for the room/floor
    //Mesh *tile = GeometryCreator::CreateCube(vec3(2.f, 0.1f, 2.f));

    //Get the ceiling mesh, set it to room 0
    GLuint faceNBO;
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/room/RoomCeilingNew.obj",
            room[0].IBOlen, room[0].VBO, room[0].IBO, room[0].NBO, room[0].TBO,
            room[0].AABBmin, room[0].AABBmax);

    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/room/RoomFloor.obj",
            room[1].IBOlen, room[1].VBO, room[1].IBO, room[1].NBO, room[1].TBO,
            room[1].AABBmin, room[1].AABBmax);

    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/room/RoomWallEast1.obj",
            room[2].IBOlen, room[2].VBO, room[2].IBO, room[2].NBO, room[2].TBO,
            room[2].AABBmin, room[2].AABBmax);

    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/room/RoomWallWest.obj",
            room[3].IBOlen, room[3].VBO, room[3].IBO, room[3].NBO, room[3].TBO,
            room[3].AABBmin, room[3].AABBmax);

    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/room/RoomWallNorth1.obj",
            room[4].IBOlen, room[4].VBO, room[4].IBO, room[4].NBO, room[4].TBO,
            room[4].AABBmin, room[4].AABBmax);

    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/room/RoomWallSouth2.obj",
            room[5].IBOlen, room[5].VBO, room[5].IBO, room[5].NBO, room[5].TBO,
            room[5].AABBmin, room[5].AABBmax);

    int startIndex = 0;
    for (int i = startIndex; i < NUM_WALLS; i++) {
        room[i].dir = vec3(1.f, 0.f, 0.f);
        room[i].speed = 0.f;
        room[i].rotSpeed = 0.f;
        room[i].rotAxis = vec3(0.f, 1.f, 0.f);
        if (i < 2) {
            room[i].ambColor = vec3(1.f, 1.f, 1.f);
        } else {
            room[i].ambColor = vec3(1.f, 1.f, 1.f);
        }
        room[i].diffColor = vec3(.35f);
        room[i].specColor = vec3(.5f);
        room[i].shininess = 1.f;
        room[i].specStrength = 3.f;
        room[i].scale = glm::vec3(1.f);
        room[i].texNum = numTextures();
        if (i == 3) {
            room[i].texNum2 = numTextures();
            room[i].hasTex2 = true;
        }
        room[i].textureEnum = GL_TEXTURE0 + room[i].texNum;
        room[i].hasTex = true;
    }
    
    for (int i = 0; i < NUM_WALLS; i++) {
        std::cout << "texNum, room " << i << ": " << room[i].texNum << std::endl;
    }
    
    //load textures
    printOpenGLError();
    LoadTexture((char *)"objects/meshes/room/CeilingUV.bmp", room[0].texNum);
    printOpenGLError();
    LoadTexture((char *)"objects/meshes/room/FloorUV.bmp", room[1].texNum);
    printOpenGLError();
    LoadTexture((char *)"objects/meshes/room/EastUV.bmp", room[2].texNum);
    printOpenGLError();
    LoadTexture((char *)"objects/meshes/room/WestUV_Spot.bmp", room[3].texNum2);
    LoadTexture((char *)"objects/meshes/room/WestUV.bmp", room[3].texNum);
 printOpenGLError();
    LoadTexture((char *)"objects/meshes/room/NorthUV.bmp", room[4].texNum);
    printOpenGLError();
    LoadTexture((char *)"objects/meshes/room/SouthUV.bmp", room[5].texNum);
    printOpenGLError();

    //east wall
    room[2].doScale(vec3(1.f, ROOM_SIZE / ROOM_HEIGHT_DIVISION, ROOM_SIZE));
    room[2].doTranslate(vec3(-ROOM_SIZE, 0.f, 0.f));

    //west wall
    room[3].doScale(vec3(1.f, ROOM_SIZE / ROOM_HEIGHT_DIVISION, ROOM_SIZE));
    room[3].doRotate(vec3(0,1,0), 180);
    room[3].doTranslate(vec3(ROOM_SIZE, 0.f, 0.f));

    //north wall
    room[4].doScale(vec3(ROOM_SIZE, ROOM_SIZE / ROOM_HEIGHT_DIVISION, 1.f));
    std::cout << "north - Min: " << printVec3(room[4].getAABBmin());
    std::cout << "; Max: " << printVec3(room[4].getAABBmax()) << std::endl;
    room[4].doTranslate(vec3(-(room[4].getAABBmax().x + room[4].getAABBmin().x) / 2.f,
            -(room[4].getAABBmax().y + room[4].getAABBmin().y) / 2.f, ROOM_SIZE));

    northBoundLeftMin = room[4].getAABBmin();
    northBoundLeftMax = glm::vec3(room[4].getAABBmin().x / 2.f + 
            (ROOM_SIZE / 5.f) + 5.f, room[4].getAABBmax().y, room[4].getAABBmax().z);
    northBoundRightMin = glm::vec3(room[4].getAABBmax().x / 2.f - 
            (ROOM_SIZE / 5.f) - 5.f, room[4].getAABBmin().y, room[4].getAABBmin().z);
    northBoundRightMax = room[4].getAABBmax();

    //south wall
    room[5].doScale(vec3(ROOM_SIZE, ROOM_SIZE / ROOM_HEIGHT_DIVISION, 1.f));
    room[5].doTranslate(vec3(0.f, 0.f, -ROOM_SIZE));

    //the ceiling
    room[0].doScale(vec3(ROOM_SIZE, 1.f, ROOM_SIZE));
    std::cout << "ceiling - Min: " << printVec3(room[0].getAABBmin());
    std::cout << "; Max: " << printVec3(room[0].getAABBmax()) << std::endl;
    room[0].doTranslate(vec3(0.f, room[3].getAABBmax().y, 0.f));

    //the floor
    room[1].doScale(vec3(ROOM_SIZE, 1.f, ROOM_SIZE));
    room[1].doTranslate(vec3(0.f, room[3].getAABBmin().y, 0.f));

    //GameObject::roomHeight = room[3].AABBmax.y;
    AABBmin = glm::vec3(-200.f);
    AABBmax = glm::vec3(-200.f);
    
    setRoomFloorHeight(glm::vec3(0.f, room[3].getAABBmin().y, 0.f));
    setRoomCeilHeight(room[3].getAABBmax().y);
}

Room::Room(const Room& orig) {
}

Room::~Room() {
}

void Room::draw(glm::vec3 cameraPos, glm::vec3 lookAt, glm::vec3 lightPos,
        glm::vec3 lightColor, GameConstants *gc) {
    for (int i = 0; i < NUM_WALLS; i++) {
        room[i].draw(cameraPos, lookAt, lightPos, lightColor, gc);
    }
}

void Room::update(float dt, GameObject* playerCamera) {
    for (int i = 0; i < NUM_WALLS; i++) {
        //room[i].update((float) (dt));
        //AKA hardcoding the bounds of the room....
    }
}

bool Room::doesCollide(GameObject* other) {
#if 1
    for (int i = 2; i < NUM_WALLS; i++) {
        if (!hasWon() || (hasWon() && i != 4)) {
            if (room[i].doesCollide(other)) {
                //printf("nya\n");
                return true;
            }
        } else {
            if (northBoundLeftMin.x <= other->getAABBmax().x &&
                    //this->northBoundLeftMin.y <= other->AABBmax.y &&
                    this->northBoundLeftMin.z <= other->getAABBmax().z &&
                    this->northBoundLeftMax.x >= other->getAABBmin().x &&
                    //this->northBoundLeftMax.y >= other->AABBmin.y &&
                    this->northBoundLeftMax.z >= other->getAABBmin().z) {
                return true;
            }
            if (this->northBoundRightMin.x <= other->getAABBmax().x &&
                    //this->northBoundRightMin.y <= other->AABBmax.y &&
                    this->northBoundRightMin.z <= other->getAABBmax().z &&
                    this->northBoundRightMax.x >= other->getAABBmin().x &&
                    //this->northBoundRightMax.y >= other->AABBmin.y &&
                    this->northBoundRightMax.z >= other->getAABBmin().z) {
                return true;
            }
        }
    }
#endif
    return false;
}

std::string Room::className() {
    return "Room";
}
