/* 
 * File:   Knob100.h
 * Author: goofanader
 *
 * Created on February 24, 2013, 6:44 PM
 */

#ifndef KNOB100_H
#define	KNOB100_H

#include "GameObject.h"
#include "MeshLoader.h"

class Knob100 : public GameObject {
public:
    Knob100();
    Knob100(const Knob100& orig);
    virtual ~Knob100();
    virtual void update(float dt, GameObject *playerCamera, vec3 camLookAt);
    virtual void onEvent(SoundPlayer *soundPlayer);
    std::string className();
    int getStation();
    void draw(glm::vec3 cameraPos, glm::vec3 lookAt, glm::vec3 lightPos, 
        glm::vec3 lightColor, GameConstants* gc);
private:
    float rotating;
    float rotAnim;
    int station;
    GameObject *arrow;
};

#endif	/* KNOB100_H */

