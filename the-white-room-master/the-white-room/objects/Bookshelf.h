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
    bool doesCollide(GameObject *other);
private:
    glm::vec3 hitTestAABBmin;
    glm::vec3 hitTestAABBmax;
    GameObject *shelf;
};

#endif	/* BOOKSHELF_H */

