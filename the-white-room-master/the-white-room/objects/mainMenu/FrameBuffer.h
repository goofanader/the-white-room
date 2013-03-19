/* 
 * File:   FrameBuffer.h
 * Author: goofanader
 *
 * Created on March 18, 2013, 2:15 PM
 */

#ifndef FRAMEBUFFER_H
#define	FRAMEBUFFER_H

#include "DeferredShadingObject.h"
#include "../MeshLoader.h"

class FrameBuffer : public DeferredShadingObject {
public:
    FrameBuffer();
    FrameBuffer(const FrameBuffer& orig);
    virtual ~FrameBuffer();
    std::string className();
private:
    GLuint altTexNum;
};

#endif	/* FRAMEBUFFER_H */

