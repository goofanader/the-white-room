/* 
 * File:   Ending.h
 * Author: goofanader
 *
 * Created on March 18, 2013, 2:15 PM
 */

#ifndef ENDING_H
#define	ENDING_H

#include "../GameObject.h"
#include "../MeshLoader.h"

class Ending : public GameObject {
public:
    Ending();
    Ending(const Ending& orig);
    virtual ~Ending();
    std::string className();
    
    bool isItLoading();
    void setIsLoading(bool loading);
    void update(float dt, GameObject* playerCamera, vec3 camLookAt);
private:
    GLuint altTexNum;
    bool isLoading;
};

#endif	/* ENDING_H */

