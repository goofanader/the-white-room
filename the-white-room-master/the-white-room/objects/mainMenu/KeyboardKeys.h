/* 
 * File:   KeyboardKeys.h
 * Author: goofanader
 *
 * Created on March 18, 2013, 2:15 PM
 */

#ifndef KEYBOARDKEYS_H
#define	KEYBOARDKEYS_H

#include "DeferredShadingObject.h"
#include "../MeshLoader.h"

class KeyboardKeys : public DeferredShadingObject {
public:
    KeyboardKeys();
    KeyboardKeys(const KeyboardKeys& orig);
    virtual ~KeyboardKeys();
    std::string className();
private:
    GLuint altTexNum;
};

#endif	/* KEYBOARDKEYS_H */

