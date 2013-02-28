/* 
 * File:   RoundTable.h
 * Author: goofanader
 *
 * Created on February 21, 2013, 12:15 PM
 */

#ifndef ROUNDTABLE_H
#define	ROUNDTABLE_H

#include "GameObject.h"
#include "MeshLoader.h"

class RoundTable : public GameObject {
public:
    RoundTable();
    RoundTable(const RoundTable& orig);
    virtual ~RoundTable();
    void drawHighlight(glm::vec3 cameraPos, glm::vec3 lookAt, glm::vec3 lightPos, 
        glm::vec3 lightColor, GameConstants* gc);
    std::string className();
private:

};

#endif	/* ROUNDTABLE_H */

