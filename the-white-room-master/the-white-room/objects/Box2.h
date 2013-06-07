/* 
 * File:   Box2.h
 * Author: goofanader
 *
 * Created on January 31, 2013, 6:34 AM
 */

#ifndef BOX2_H
#define	BOX2_H

#include "GameObject.h"

#define DRAW_CUBE true

class Box2 : public GameObject {
public:
    Box2();
    Box2(const Box2& orig);
    virtual ~Box2();
    void draw(glm::vec3 cameraPos, glm::vec3 lookAt, glm::vec3 lightPos, 
        glm::vec3 lightColor, GameConstants* gc, int shouldDarkenScreen);
    void update(float dt, GameObject* playerCamera, vec3 camLookAt);
    bool doesCollide(GameObject* other);
    std::string className();
    void onEvent(SoundPlayer *soundPlayer);
private:
    GameObject* cube;
};

#endif	/* BOX2_H */

