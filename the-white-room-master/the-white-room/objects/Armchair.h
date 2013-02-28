/* 
 * File:   Armchair.h
 * Author: goofanader
 *
 * Created on February 12, 2013, 5:32 PM
 */

#ifndef ARMCHAIR_H
#define	ARMCHAIR_H

#include "MeshLoader.h"
#include "GameObject.h"

class Armchair : public GameObject {
public:
    Armchair();
    Armchair(const Armchair& orig);
    virtual ~Armchair();
    void drawHighlight(glm::vec3 cameraPos, glm::vec3 lookAt, glm::vec3 lightPos, 
        glm::vec3 lightColor, GameConstants* gc);
    
    /*void draw(glm::vec3 cameraPos, glm::vec3 lookAt, glm::vec3 lightPos, 
        glm::vec3 lightColor, GameConstants* gc);
    void update(float dt);
    bool doesCollide(GameObject* other);*/
    std::string className();
private:

};

#endif	/* ARMCHAIR_H */

