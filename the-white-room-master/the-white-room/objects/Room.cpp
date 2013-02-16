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

//#define ROOM_SIZE 20.f
#define GROUND_POS -.5f

Room::Room() {
    //cube for the room/floor
    Mesh *tile = GeometryCreator::CreateCube(vec3(2.f, 0.1f, 2.f));

    //Get the ceiling mesh, set it to room 0
    GLuint faceNBO;
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/room/RoomCeilingNew.obj",
            room[0].IBOlen, room[0].VBO, room[0].IBO, room[0].NBO, faceNBO,
            room[0].AABBmin, room[0].AABBmax);

    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/room/RoomFloor.obj",
            room[1].IBOlen, room[1].VBO, room[1].IBO, room[1].NBO, faceNBO,
            room[1].AABBmin, room[1].AABBmax);

    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/room/RoomWallEast1.obj",
            room[2].IBOlen, room[2].VBO, room[2].IBO, room[2].NBO, faceNBO,
            room[2].AABBmin, room[2].AABBmax);

    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/room/RoomWallWest1.obj",
            room[3].IBOlen, room[3].VBO, room[3].IBO, room[3].NBO, faceNBO,
            room[3].AABBmin, room[3].AABBmax);
    

    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/room/RoomWallNorth1.obj",
            room[4].IBOlen, room[4].VBO, room[4].IBO, room[4].NBO, faceNBO,
            room[4].AABBmin, room[4].AABBmax);

    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/room/RoomWallSouth2.obj",
            room[5].IBOlen, room[5].VBO, room[5].IBO, room[5].NBO, faceNBO,
            room[5].AABBmin, room[5].AABBmax);
#if 0
#endif
    int startIndex = 0;

    //move this to own class, probably.
    for (int i = startIndex; i < NUM_WALLS; i++) {
        if (false) {
            room[i].VBO = tile->PositionHandle;
            room[i].IBO = tile->IndexHandle;
            room[i].IBOlen = tile->IndexBufferLength;
            room[i].NBO = tile->NormalHandle;
        }
        room[i].dir = vec3(1.f, 0.f, 0.f);
        room[i].speed = 0.f;
        room[i].rotSpeed = 0.f;
        room[i].rotAxis = vec3(0.f, 1.f, 0.f);
        room[i].color = vec3(1.f, 1.f, 1.f);
        room[i].shininess = 5;
        room[i].specStrength = 0.f;
        room[i].scale = glm::vec3(1.f);

        if (false && i == 5) {
            room[i].AABBmin = glm::vec3(-1.f, -.05f, -1.f);
            room[i].AABBmax = glm::vec3(1.f, 0.05f, 1.f);
            room[i].doScale(glm::vec3(ROOM_SIZE));
        }
    }

    room[0].doScale(vec3(ROOM_SIZE, ROOM_SIZE, ROOM_SIZE));
    room[0].doTranslate(vec3(0.f, ROOM_SIZE -
            ((room[0].AABBmax.x - room[0].AABBmin.x) / 10), 0.f));
    room[1].doScale(vec3(ROOM_SIZE, ROOM_SIZE, ROOM_SIZE));
    room[1].doTranslate(vec3(0.f, -ROOM_SIZE +
            ((room[1].AABBmax.x - room[1].AABBmin.x) / 10), 0.f));
    room[2].doScale(vec3(ROOM_SIZE, ROOM_SIZE, ROOM_SIZE));
    room[2].doTranslate(vec3(-ROOM_SIZE, 0.f, 0.f));
    room[3].doScale(vec3(ROOM_SIZE, ROOM_SIZE, ROOM_SIZE));
    room[3].doTranslate(vec3(ROOM_SIZE, 0.f, 0.f));
    room[4].doScale(vec3(ROOM_SIZE, ROOM_SIZE, ROOM_SIZE));
    room[4].doTranslate(vec3(0.f, -1.5f * (ROOM_SIZE / 10.f), ROOM_SIZE));
    room[5].doScale(vec3(ROOM_SIZE, ROOM_SIZE, ROOM_SIZE));
    room[5].doTranslate(vec3(0.f, 0.f, -ROOM_SIZE));

    std::cout << "====\nAABBmin 1: " << room[0].AABBmin.x << ", " << room[0].AABBmin.y;
    std::cout << ", " << room[0].AABBmin.z << "; AABBmax1: " << room[0].AABBmax.x;
    std::cout << ", " << room[0].AABBmax.y << ", " << room[0].AABBmax.z << "\n=====" << std::endl;

    float temp;

#if 0
    room[0].doTranslate(vec3(0.f, GROUND_POS - (ROOM_SIZE / 2.0f), 0.f));
    room[1].doTranslate(vec3(0.f, ROOM_SIZE + GROUND_POS, 0.f));


    //room[2].doRotate(vec3(0.f, 0.f, 1.f), 90);
    room[2].doRotate(vec3(0.f, 0.f, 1.f), 90);
    room[2].doTranslate(vec3(ROOM_SIZE, (ROOM_SIZE + GROUND_POS) / 2.f, 0.f));
    float temp = room[2].AABBmax.x;
    room[2].AABBmax.x = room[2].AABBmin.x;
    room[2].AABBmin.x = temp;

    room[3].doRotate(vec3(0.f, 0.f, 1.f), 90);
    room[3].doTranslate(vec3(-ROOM_SIZE, (ROOM_SIZE + GROUND_POS) / 2.f, 0.f));
    temp = room[3].AABBmax.x;
    room[3].AABBmax.x = room[3].AABBmin.x;
    room[3].AABBmin.x = temp;

    room[4].doRotate(vec3(1.f, 0.f, 0.f), 90);
    room[4].doTranslate(vec3(0.f, (ROOM_SIZE + GROUND_POS) / 2.f, -ROOM_SIZE));


    room[5].doRotate(vec3(1.f, 0.f, 0.f), 90);
    room[5].doTranslate(vec3(0.f, (ROOM_SIZE + GROUND_POS) / 2.f, ROOM_SIZE));
    #endif
#if 1
#endif
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

void Room::update(float dt) {
    for (int i = 0; i < NUM_WALLS; i++) {
        //room[i].update((float) (dt));
        //AKA hardcoding the bounds of the room....
    }
}

bool Room::doesCollide(GameObject* other) {
#if 1
    for (int i = 2; i < NUM_WALLS; i++) {
        //printf("room %d:\n", i);
#if 0
        printf("room %d. AABBmin: (%lf, %lf, %lf);", i, room[i].AABBmin.x,
                room[i].AABBmin.y, room[i].AABBmin.z);
        printf(" AABBmax: (%lf, %lf, %lf)\n=========\n", room[i].AABBmax.x,
                room[i].AABBmax.y, room[i].AABBmax.z);
#endif
        if (room[i].doesCollide(other)) {
            //printf("nya\n");
            return true;
        }
    }
#endif
    return false;
}

std::string Room::className() {
    return "Room";
}