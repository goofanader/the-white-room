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
#define HEART getHeartKeyNum()
#define SPADE getSpadeKeyNum()
#define CLUB getClubKeyNum()
#define DIAMOND getDiamondKeyNum()
#define SAFE getSafeNum()
#define LETTER1 getLetter1Num()
#define LETTER2 getLetter2Num()
#define LETTER3 getLetter3Num()
#define LETTER4 getLetter4Num()

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
int getHeartKeyNum();
int getDiamondKeyNum();
int getClubKeyNum();
int getSpadeKeyNum();
int getSafeNum();
int getLetter1Num();
int getLetter2Num();
int getLetter3Num();
int getLetter4Num();

#endif	/* OBJECTCREATION_H */

