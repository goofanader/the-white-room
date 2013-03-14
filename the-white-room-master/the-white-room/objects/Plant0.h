/* 
 * File:   Plant0.h
 * Author: goofanader
 *
 * Created on February 13, 2013, 12:36 PM
 */

#ifndef PLANT0_H
#define	PLANT0_H

#include "GameObject.h"
#include "MeshLoader.h"

class Plant0 : public GameObject {
public:
    Plant0();
    Plant0(const Plant0& orig);
    virtual ~Plant0();
    std::string className();
    void onEvent(SoundPlayer *soundPlayer);
    void update(float dt, GameObject* playerCamera, vec3 camLookAt);
private:
    float rotating;
};

#endif	/* PLANT0_H */

