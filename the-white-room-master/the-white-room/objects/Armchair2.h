/* 
 * File:   Armchair2.h
 * Author: goofanader
 *
 * Created on February 12, 2013, 5:32 PM
 */

#ifndef ARMCHAIR2_H
#define	ARMCHAIR2_H

#include "MeshLoader.h"
#include "GameObject.h"

class Armchair2 : public GameObject {
public:
    Armchair2();
    Armchair2(const Armchair2& orig);
    virtual ~Armchair2();
    void drawHighlight(glm::vec3 cameraPos, glm::vec3 lookAt, glm::vec3 lightPos, 
        glm::vec3 lightColor, GameConstants* gc);
    
    /*void draw(glm::vec3 cameraPos, glm::vec3 lookAt, glm::vec3 lightPos, 
        glm::vec3 lightColor, GameConstants* gc);
    void update(float dt);
    bool doesCollide(GameObject* other);*/
    std::string className();
private:

};

#endif	/* ARMCHAIR2_H */

