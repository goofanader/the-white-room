/* 
 * File:   EastPainting.h
 * Author: goofanader
 *
 * Created on March 13, 2013, 9:12 PM
 */

#ifndef EASTPAINTING_H
#define	EASTPAINTING_H

#include "GameObject.h"
#include "MeshLoader.h"

class EastPainting : public GameObject {
public:
    EastPainting();
    EastPainting(const EastPainting& orig);
    virtual ~EastPainting();
    std::string className();
    void drawHighlight(glm::vec3 cameraPos, glm::vec3 lookAt, glm::vec3 lightPos, 
        glm::vec3 lightColor, GameConstants* gc);
private:

};

#endif	/* EASTPAINTING_H */

