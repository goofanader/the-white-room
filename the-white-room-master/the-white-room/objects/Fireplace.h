/* 
 * File:   Fireplace.h
 * Author: goofanader
 *
 * Created on February 19, 2013, 6:32 PM
 */

#ifndef FIREPLACE_H
#define	FIREPLACE_H

#include "GameObject.h"
#include "MeshLoader.h"

class Fireplace : public GameObject {
public:
    Fireplace();
    Fireplace(const Fireplace& orig);
    virtual ~Fireplace();
    virtual void update(float dt, GameObject *playerCamera, vec3 camLookAt);
    void drawHighlight(glm::vec3 cameraPos, glm::vec3 lookAt, glm::vec3 lightPos, 
        glm::vec3 lightColor, GameConstants* gc);
    float rotY;
    std::string className();
private:

};

#endif	/* FIREPLACE_H */

