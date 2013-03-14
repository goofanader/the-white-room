/* 
 * File:   WidePainting.h
 * Author: goofanader
 *
 * Created on March 13, 2013, 9:12 PM
 */

#ifndef WIDEPAINTING_H
#define	WIDEPAINTING_H

#include "GameObject.h"
#include "MeshLoader.h"

class WidePainting : public GameObject {
public:
    WidePainting();
    WidePainting(const WidePainting& orig);
    virtual ~WidePainting();
    std::string className();
    void drawHighlight(glm::vec3 cameraPos, glm::vec3 lookAt, glm::vec3 lightPos, 
        glm::vec3 lightColor, GameConstants* gc);
private:

};

#endif	/* WIDEPAINTING_H */

