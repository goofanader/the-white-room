/* 
 * File:   ObjectCreation.h
 * Author: goofanader
 *
 * Created on January 31, 2013, 2:22 AM
 */

#ifndef OBJECTCREATION_H
#define	OBJECTCREATION_H

#include <stdio.h>
#include <iostream>
#include <string>

#include "../objects/GameObject.h"

using namespace std;

GameObject* lookupAndCall(const string& name);
#endif	/* OBJECTCREATION_H */

