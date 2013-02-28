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
    virtual void update(float dt, GameObject *playerCamera);
    virtual void onEvent(SoundPlayer *soundPlayer);

private:
    float rotating;
};

#endif	/* KNOB10_H */

