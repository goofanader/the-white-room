/* 
 * File:   Knob10.h
 * Author: goofanader
 *
 * Created on February 24, 2013, 6:44 PM
 */

#ifndef KNOB10_H
#define	KNOB10_H

#include "GameObject.h"
#include "MeshLoader.h"

class Knob10 : public GameObject {
public:
    Knob10();
    Knob10(const Knob10& orig);
    virtual ~Knob10();
    std::string className();
    virtual void update(float dt, GameObject *playerCamera, vec3 camLookAt);
    virtual void onEvent(SoundPlayer *soundPlayer);
    int getStation();
    void draw(glm::vec3 cameraPos, glm::vec3 lookAt, glm::vec3 lightPos, 
        glm::vec3 lightColor, GameConstants* gc, int shouldDarkenScreen);

private:
    float rotating;
    float rotAnim;
    int station;
    GameObject *arrow;
};

#endif	/* KNOB10_H */

