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

GameConstants* getGC();
unsigned int getWindowWidth();
unsigned int getWindowHeight();
std::string printVec3Coordinates(glm::vec3 coordinates);

#endif	/* MAIN_H */

