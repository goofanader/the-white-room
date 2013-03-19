/* 
 * File:   Mouse.h
 * Author: goofanader
 *
 * Created on March 18, 2013, 2:15 PM
 */

#ifndef MOUSE_H
#define	MOUSE_H

#include "DeferredShadingObject.h"
#include "../MeshLoader.h"

class Mouse : public DeferredShadingObject {
public:
    Mouse();
    Mouse(const Mouse& orig);
    virtual ~Mouse();
    std::string className();
private:
    GLuint altTexNum;
};

#endif	/* MOUSE_H */

