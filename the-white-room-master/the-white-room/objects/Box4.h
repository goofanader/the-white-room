/* 
 * File:   Box1.h
 * Author: goofanader
 *
 * Created on January 31, 2013, 6:34 AM
 */

#ifndef BOX4_H
#define	BOX4_H

#include "GameObject.h"

class Box4 : public GameObject {
public:
    Box4();
    Box4(const Box4& orig);
    virtual ~Box4();
    void draw(glm::vec3 cameraPos, glm::vec3 lookAt, glm::vec3 lightPos, 
        glm::vec3 lightColor, GameConstants* gc);
    void update(float dt);
    bool doesCollide(GameObject* other);
    std::string className();
    void onEvent(SoundPlayer *soundPlayer);
    void resetEvent(SoundPlayer *soundPlayer);
private:
    GameObject* cube;
};

#endif	/* BOX4_H */

