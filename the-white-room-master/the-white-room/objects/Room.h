/* 
 * File:   Room.h
 * Author: goofanader
 *
 * Created on January 30, 2013, 10:11 AM
 */

#ifndef ROOM_H
#define	ROOM_H

#include "GameObject.h"
#include "MeshLoader.h"

#define NUM_WALLS 6

class Room : public GameObject {
public:
    Room();
    Room(const Room& orig);
    virtual ~Room();

    void draw(glm::vec3 cameraPos, glm::vec3 lookAt,
            glm::vec3 lightPos, glm::vec3 lightColor, GameConstants *gc);
    void update(float dt);
    bool doesCollide(GameObject* other);
    std::string className();
private:
    GameObject room[NUM_WALLS];
    glm::vec3 northBoundRightMin, northBoundRightMax;
    glm::vec3 northBoundLeftMin, northBoundLeftMax;
};

#endif	/* ROOM_H */

