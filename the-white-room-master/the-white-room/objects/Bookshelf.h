/* 
 * File:   Bookshelf.h
 * Author: goofanader
 *
 * Created on February 14, 2013, 6:06 AM
 */

#ifndef BOOKSHELF_H
#define	BOOKSHELF_H

#include "GameObject.h"
#include "MeshLoader.h"

class Bookshelf : public GameObject {
public:
    Bookshelf();
    Bookshelf(const Bookshelf& orig);
    virtual ~Bookshelf();
    void onEvent(SoundPlayer *soundPlayer);
    std::string className();
    void drawHighlight(glm::vec3 cameraPos, glm::vec3 lookAt, glm::vec3 lightPos, 
        glm::vec3 lightColor, GameConstants* gc);
private:
    glm::vec3 hitTestAABBmin;
    glm::vec3 hitTestAABBmax;
    GameObject *shelf;
};

#endif	/* BOOKSHELF_H */

