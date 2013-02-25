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
    virtual void update(float dt, GameObject *playerCamera);
    std::string className();
private:
    float rotating;
};

#endif	/* KNOB100_H */

