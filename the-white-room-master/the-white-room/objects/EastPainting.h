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
private:

};

#endif	/* EASTPAINTING_H */

