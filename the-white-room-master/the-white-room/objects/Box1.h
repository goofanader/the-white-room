/* 
 * File:   Box1.h
 * Author: goofanader
 *
 * Created on January 31, 2013, 6:34 AM
 */

#ifndef BOX1_H
#define	BOX1_H

#include "GameObject.h"

#define DRAW_CUBE true

class Box1 : public GameObject {
public:
    Box1();
    Box1(const Box1& orig);
    virtual ~Box1();
    void draw(glm::vec3 cameraPos, glm::vec3 lookAt, glm::vec3 lightPos, 
        glm::vec3 lightColor, GameConstants* gc, int shouldDarkenScreen);
    void update(float dt, GameObject* playerCamera, vec3 camLookAt);
    bool doesCollide(GameObject* other);
    std::string className();
    void onEvent(SoundPlayer *soundPlayer);
private:
    GameObject* cube;
};

#endif	/* BOX1_H */

