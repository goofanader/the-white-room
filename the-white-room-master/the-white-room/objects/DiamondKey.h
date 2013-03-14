/* 
 * File:   DiamondKey.h
 * Author: goofanader
 *
 * Created on January 31, 2013, 6:34 AM
 */

#ifndef DIAMONDKEY_H
#define	DIAMONDKEY_H

#include "GameObject.h"
#include "MeshLoader.h"

class DiamondKey : public GameObject {
public:
    bool isHeld, isInKeyhole;

    DiamondKey();
    DiamondKey(const DiamondKey& orig);
    virtual ~DiamondKey();
    //void update(float dt, GameObject* playerCamera);
    bool doesCollide(GameObject* other);
    std::string className();
    void onEvent(SoundPlayer *soundPlayer);
    void update(float dt, GameObject* playerCamera, vec3 camLookAt);
private:
    glm::vec3 initTranslate;
};

#endif	/* DIAMONDKEY_H */

