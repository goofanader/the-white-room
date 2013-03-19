/* 
 * File:   FakeOpening.h
 * Author: goofanader
 *
 * Created on March 18, 2013, 2:15 PM
 */

#ifndef FAKEOPENING_H
#define	FAKEOPENING_H

#include "../GameObject.h"
#include "../MeshLoader.h"

class FakeOpening : public GameObject {
public:
    FakeOpening();
    FakeOpening(const FakeOpening& orig);
    virtual ~FakeOpening();
    std::string className();
    
    bool isItLoading();
    void setIsLoading(bool loading);
    void update(float dt, GameObject* playerCamera, vec3 camLookAt);
private:
    GLuint altTexNum;
    bool isLoading;
};

#endif	/* FAKEOPENING_H */

