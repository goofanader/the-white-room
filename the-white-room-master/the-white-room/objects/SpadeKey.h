/* 
 * File:   SpadeKey.h
 * Author: goofanader
 *
 * Created on January 31, 2013, 6:34 AM
 */

#ifndef SPADEKEY_H
#define	SPADEKEY_H

#include "GameObject.h"
#include "MeshLoader.h"

class SpadeKey : public GameObject {
public:
    bool isHeld, isInKeyhole;

    SpadeKey();
    SpadeKey(const SpadeKey& orig);
    virtual ~SpadeKey();
    //void update(float dt, GameObject* playerCamera);
    bool doesCollide(GameObject* other);
    std::string className();
    void onEvent(SoundPlayer *soundPlayer);
    void update(float dt, GameObject* playerCamera, vec3 camLookAt);

};

#endif	/* SPADEKEY_H */

