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
        room[i].diffColor = vec3(.8f);
        room[i].specColor = vec3(.8f);
        room[i].shininess = 1;
        room[i].specStrength = .24f;
        room[i].scale = glm::vec3(1.f);
    }

    //east wall
    room[2].doScale(vec3(1.f, ROOM_SIZE / ROOM_HEIGHT_DIVISION, ROOM_SIZE));
    room[2].doTranslate(vec3(-ROOM_SIZE, 0.f, 0.f));

    //west wall
    room[3].doScale(vec3(1.f, ROOM_SIZE / ROOM_HEIGHT_DIVISION, ROOM_SIZE));
    room[3].doTranslate(vec3(ROOM_SIZE, 0.f, 0.f));

    //north wall
    room[4].doScale(vec3(ROOM_SIZE, ROOM_SIZE / ROOM_HEIGHT_DIVISION, 1.f));
    std::cout << "north - Min: " << printVec3Coordinates(room[4].AABBmin);
    std::cout << "; Max: " << printVec3Coordinates(room[4].AABBmax) << std::endl;
    room[4].doTranslate(vec3(-(room[4].AABBmax.x + room[4].AABBmin.x) / 2.f, -(room[4].AABBmax.y + room[4].AABBmin.y) / 2.f, ROOM_SIZE));

    //south wall
    room[5].doScale(vec3(ROOM_SIZE, ROOM_SIZE / ROOM_HEIGHT_DIVISION, 1.f));
    room[5].doTranslate(vec3(0.f, 0.f, -ROOM_SIZE));

    //the ceiling
    room[0].doScale(vec3(ROOM_SIZE, 1.f, ROOM_SIZE));
    std::cout << "ceiling - Min: " << printVec3Coordinates(room[0].AABBmin);
    std::cout << "; Max: " << printVec3Coordinates(room[0].AABBmax) << std::endl;
    room[0].doTranslate(vec3(0.f, room[3].AABBmax.y, 0.f));

    //the floor
    room[1].doScale(vec3(ROOM_SIZE, 1.f, ROOM_SIZE));
    room[1].doTranslate(vec3(0.f, room[3].AABBmin.y, 0.f));
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
#if 0
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
