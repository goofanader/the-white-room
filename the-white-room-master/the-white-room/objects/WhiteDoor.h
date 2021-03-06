/* 
 * File:   WhiteDoor.h
 * Author: goofanader
 *
 * Created on January 30, 2013, 11:04 PM
 */

#ifndef WHITEDOOR_H
#define	WHITEDOOR_H

#include "GameObject.h"
#include "MeshLoader.h"

class WhiteDoor : public GameObject {
public:
    WhiteDoor();
    WhiteDoor(const WhiteDoor& orig);
    virtual ~WhiteDoor();
    
    /*void draw(glm::vec3 cameraPos, glm::vec3 lookAt,
            glm::vec3 lightPos, glm::vec3 lightColor, GameConstants *gc);*/
    void update(float dt, GameObject* playerCamera, vec3 camLookAt);
    /*bool doesCollide(GameObject* other);*/

    void onEvent(SoundPlayer *soundPlayer);
    
    std::string className();
private:
    GameObject* door;
    GameObject* knob;
    bool isClosed;
    float doorAngle;
    double timeSpent;
    glm::vec3 prevAABBmin;
    bool setNewBounds;
};

#endif	/* WHITEDOOR_H */

