/* 
 * File:   Main.h
 * Author: goofanader
 *
 * Created on January 30, 2013, 10:56 AM
 */

#ifndef MAIN_H
#define	MAIN_H

#include "glm/glm.hpp"
#include "objects/GameObject.h"
#include "objects/mainMenu/DeferredShadingObject.h"

#define IS_SOUND_ON true
#define MAX_SHADERS 6

GameConstants* getGC();
GameConstants* getLC();
GameConstants* getSC();

DeferredShadingConstants* getDRC();
DeferredShadingConstants* getDSC();

unsigned int getWindowWidth();
unsigned int getWindowHeight();
std::string printVec3(glm::vec3 coordinates);
bool hasWon();
void setIfWon(bool winning);
bool canMoveMouse();
void setCanMoveMouse(bool moving);

glm::vec3 getRoomFloorHeight();
void setRoomFloorHeight(glm::vec3 newHeight);
float getRoomCeilHeight();
void setRoomCeilHeight(float newHeight);
#endif	/* MAIN_H */

