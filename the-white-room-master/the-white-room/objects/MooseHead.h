/* 
 * File:   MooseHead.h
 * Author: goofanader
 *
 * Created on February 19, 2013, 6:32 PM
 */

#ifndef MOOSEHEAD_H
#define	MOOSEHEAD_H

#include "GameObject.h"
#include "MeshLoader.h"

class MooseHead : public GameObject {
public:
    MooseHead();
    MooseHead(const MooseHead& orig);
    virtual ~MooseHead();
    virtual void update(float dt, GameObject *playerCamera, vec3 camLookAt);
    void drawHighlight(glm::vec3 cameraPos, glm::vec3 lookAt, glm::vec3 lightPos, 
        glm::vec3 lightColor, GameConstants* gc);
    float rotY;
    std::string className();
private:

};

#endif	/* MOOSEHEAD_H */

