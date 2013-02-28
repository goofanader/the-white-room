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

#define WHITE_DOOR getDoorNum()
#define BOOK1 getBook1Num()
#define BOOK2 getBook2Num()
#define BOOK3 getBook3Num()
#define PLANT1 getPlant1Num()
#define PLANT6 getPlant6Num()
#define RADIO getRadioNum()
#define KNOB10 getKnob10Num()
#define KNOB100 getKnob100Num()

using namespace std;

void initializeIndices();
GameObject* lookupAndCall(const string& name);
void setObjectIndex(const string& name, int index);

int getDoorNum();
int getBook1Num();
int getBook2Num();
int getBook3Num();
int getPlant1Num();
int getPlant6Num();
int getRadioNum();
int getKnob10Num();
int getKnob100Num();
#endif	/* OBJECTCREATION_H */

