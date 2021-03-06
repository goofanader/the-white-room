/* 
 * File:   ClubKey.h
 * Author: goofanader
 *
 * Created on January 31, 2013, 6:34 AM
 */

#ifndef CLUBKEY_H
#define	CLUBKEY_H

#include "GameObject.h"
#include "MeshLoader.h"

class ClubKey : public GameObject {
public:
    bool isHeld, isInKeyhole;

    ClubKey();
    ClubKey(const ClubKey& orig);
    virtual ~ClubKey();
    //void update(float dt, GameObject* playerCamera);
    bool doesCollide(GameObject* other);
    std::string className();
    void onEvent(SoundPlayer *soundPlayer);
    void update(float dt, GameObject* playerCamera, vec3 camLookAt);
};

#endif	/* CLUBKEY_H */

