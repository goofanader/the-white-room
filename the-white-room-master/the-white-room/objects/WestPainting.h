/* 
 * File:   WestPainting.h
 * Author: goofanader
 *
 * Created on March 13, 2013, 9:12 PM
 */

#ifndef WESTPAINTING_H
#define	WESTPAINTING_H

#include "GameObject.h"
#include "MeshLoader.h"

class WestPainting : public GameObject {
public:
    WestPainting();
    WestPainting(const WestPainting& orig);
    virtual ~WestPainting();
    std::string className();
    void drawHighlight(glm::vec3 cameraPos, glm::vec3 lookAt, glm::vec3 lightPos, 
        glm::vec3 lightColor, GameConstants* gc);
private:

};

#endif	/* WESTPAINTING_H */

