/* 
 * File:   Plant1.h
 * Author: goofanader
 *
 * Created on February 13, 2013, 12:36 PM
 */

#ifndef PLANT1_H
#define	PLANT1_H

#include "GameObject.h"
#include "MeshLoader.h"

class Plant1 : public GameObject {
public:
    Plant1();
    Plant1(const Plant1& orig);
    virtual ~Plant1();
    std::string className();
    void onEvent(SoundPlayer *soundPlayer);
    void update(float dt, GameObject* playerCamera, vec3 camLookAt);
private:
    float rotating;
};

#endif	/* PLANT1_H */

