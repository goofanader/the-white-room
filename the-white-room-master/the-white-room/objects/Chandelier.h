/* 
 * File:   Chandelier.h
 * Author: goofanader
 *
 * Created on February 13, 2013, 12:35 PM
 */

#ifndef CHANDELIER_H
#define	CHANDELIER_H

#include "GameObject.h"
#include "MeshLoader.h"

class Chandelier : public GameObject {
public:
    Chandelier();
    Chandelier(const Chandelier& orig);
    virtual ~Chandelier();
    std::string className();
    bool doesCollide(GameObject *other);
    void drawHighlight(glm::vec3 cameraPos, glm::vec3 lookAt, glm::vec3 lightPos, 
        glm::vec3 lightColor, GameConstants* gc);
private:

};

#endif	/* CHANDELIER_H */

