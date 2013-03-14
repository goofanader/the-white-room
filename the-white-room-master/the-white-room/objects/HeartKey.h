/* 
 * File:   HeartKey.h
 * Author: goofanader
 *
 * Created on January 31, 2013, 6:34 AM
 */

#ifndef HEARTKEY_H
#define	HEARTKEY_H

#include "GameObject.h"
#include "MeshLoader.h"

class HeartKey : public GameObject {
public:
    bool isHeld, isInKeyhole;
    
    HeartKey();
    HeartKey(const HeartKey& orig);
    virtual ~HeartKey();
    void update(float dt, GameObject* playerCamera, vec3 camLookAt);
    bool doesCollide(GameObject* other);
    std::string className();
    void onEvent(SoundPlayer *soundPlayer);
};

#endif	/* HEARTKEY_H */

