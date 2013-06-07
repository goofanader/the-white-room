/* 
 * File:   Box3.h
 * Author: goofanader
 *
 * Created on January 31, 2013, 6:34 AM
 */

#ifndef BOX3_H
#define	BOX3_H

#include "GameObject.h"

#define DRAW_CUBE true

class Box3 : public GameObject {
public:
    Box3();
    Box3(const Box3& orig);
    virtual ~Box3();
    void draw(glm::vec3 cameraPos, glm::vec3 lookAt, glm::vec3 lightPos, 
        glm::vec3 lightColor, GameConstants* gc, int shouldDarkenScreen);
    void update(float dt, GameObject* playerCamera, vec3 camLookAt);
    bool doesCollide(GameObject* other);
    std::string className();
    void onEvent(SoundPlayer *soundPlayer);
private:
    GameObject* cube;
};

#endif	/* BOX3_H */

