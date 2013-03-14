/* 
 * File:   ObjectCreation.cpp
 * Author: goofanader
 * 
 * Created on January 31, 2013, 2:22 AM
 */

#include "ObjectCreation.h"
#include "../objects/AllObjects.h"

GameObject* createRoom() { return new Room(); }
GameObject* createDoor() { return new WhiteDoor(); }

GameObject* createSafe() { return new Safe(); }

GameObject* createArmchair() { return new Armchair(); }
GameObject* createArmchair2() { return new Armchair2(); }

GameObject* createRadio() { return new Radio(); }
GameObject* createKnob100() { return new Knob100(); }
GameObject* createKnob10() { return new Knob10(); }
GameObject* createTable() { return new Table(); }

GameObject* createPlant1() { return new Plant1(); }
GameObject* createPlant6() { return new Plant6(); }
GameObject* createPlant0() { return new Plant0(); }
GameObject* createRoundTable() { return new RoundTable(); }

GameObject* createChandelier() { return new Chandelier(); }

GameObject* createClock() { return new Clock(); }
GameObject* createBookshelf() { return new Bookshelf(); }
GameObject* createBook1() { return new Book1(); }
GameObject* createBook2() { return new Book2(); }
GameObject* createBook3() { return new Book3(); }

GameObject* createMooseHead() { return new MooseHead(); }
GameObject* createFireplace() { return new Fireplace(); }

GameObject* createHeartKey() { return new HeartKey(); }
GameObject* createDiamondKey() { return new DiamondKey(); }
GameObject* createSpadeKey() { return new SpadeKey(); }
GameObject* createClubKey() { return new ClubKey(); }

GameObject* createBox1() { return new Box1; }
GameObject* createBox2() { return new Box2; }
GameObject* createBox3() { return new Box3; }
GameObject* createBox4() { return new Box4; }

GameObject* createEastPainting() { return new EastPainting(); }
GameObject* createWidePainting() { return new WidePainting(); }
GameObject* createWestPainting() { return new WestPainting(); }

struct {
    GameObject* (*fn)();
    const char* key;
}

functionLookupTable[] = {
    { &createDoor, "WhiteDoor"},
    { &createSafe, "Safe"},
    { &createRoom, "Room"},
    { &createArmchair, "Armchair"},
    { &createArmchair2, "Armchair2"},
    { &createRadio, "Radio"},
    { &createPlant1, "Plant1"},
    { &createPlant6, "Plant6"},
    { &createPlant0, "Plant0"},
    { &createChandelier, "Chandelier"},
    { &createClock, "Clock"},
    { &createBookshelf, "Bookshelf"},
    { &createBook1, "Book1"},
    { &createBook2, "Book2"},
    { &createBook3, "Book3"},
    { &createMooseHead, "MooseHead"},
    { &createTable, "Table"},
    { &createKnob100, "Knob100"},
    { &createKnob10, "Knob10"},
    { &createRoundTable, "RoundTable"},
    { &createFireplace, "Fireplace"},
    { &createHeartKey, "HeartKey"},
    { &createDiamondKey, "DiamondKey"},
    { &createSpadeKey, "SpadeKey"},
    { &createClubKey, "ClubKey"},
    { &createEastPainting, "EastPainting"},
    { &createWidePainting, "WidePainting"},
    { &createWestPainting, "WestPainting"},
    { &createBox1, "Box1"},
    { &createBox2, "Box2"},
    { &createBox3, "Box3"},
    { &createBox4, "Box4"},
    { NULL, NULL}
};

GameObject* lookupAndCall(const string& name) {
    for (int i = 0; functionLookupTable[i].fn; i++)
        if (name == functionLookupTable[i].key) {
            return (*(functionLookupTable[i].fn))();
        }
    return NULL;
}

int door, book1, book2, book3;
int plant1, plant6, radio, knob10, knob100;
int clubKey, spadeKey, diamondKey, heartKey, safe;

void initializeIndices() {
    door = -1;
    book1 = -1;
    book2 = -1;
    book3 = -1;
    
    plant1 = plant6 = radio = knob10 = knob100 = -1;
    
    clubKey = spadeKey = diamondKey = heartKey = -1;
    
    safe = -1;
}

int getDoorNum() { return door; }
int getBook1Num() { return book1; }
int getBook2Num() { return book2; }
int getBook3Num() { return book3; }
int getPlant1Num() { return plant1; }
int getPlant6Num() { return plant6; }
int getRadioNum() { return radio; }
int getKnob10Num() { return knob10; }
int getKnob100Num() { return knob100; }
int getClubKeyNum() { return clubKey; }
int getSpadeKeyNum() { return spadeKey; }
int getDiamondKeyNum() { return diamondKey; }
int getHeartKeyNum() { return heartKey; }
int getSafeNum() { return safe; }

void setDoorNum(int index) {
    door = index;
}

void setBook1Num(int index) {
    book1 = index;
}

void setBook2Num(int index) {
    book2 = index;
}

void setBook3Num(int index) {
    book3 = index;
}

void setPlant1Num(int index) { plant1 = index; }
void setPlant6Num(int index) { plant6 = index; }
void setRadioNum(int index) { radio = index; }
void setKnob10Num(int index) { knob10 = index; }
void setKnob100Num(int index) { knob100 = index; }
void setHeartKeyNum(int index) { heartKey = index; }
void setDiamondKeyNum(int index) { diamondKey = index; }
void setClubKeyNum(int index) { clubKey = index; }
void setSpadeKeyNum(int index) { spadeKey = index; }
void setSafeNum(int index) { safe = index; }

struct {
    void (*fn)(int);
    const char* key;
}

indexLookupTable[] = {
    { &setDoorNum, "WhiteDoor"},
    { &setBook1Num, "Book1"},
    { &setBook2Num, "Book2"},
    { &setBook3Num, "Book3"},
    
    { &setPlant1Num, "Plant1"},
    { &setPlant6Num, "Plant6"},
    { &setRadioNum, "Radio"},
    { &setKnob10Num, "Knob10"},
    { &setKnob100Num, "Knob100"},
    
    { &setHeartKeyNum, "HeartKey"},
    { &setDiamondKeyNum, "DiamondKey"},
    { &setSpadeKeyNum, "SpadeKey"},
    { &setClubKeyNum, "ClubKey"},
    { &setSafeNum, "Safe"},
    { NULL, NULL}
};

void setObjectIndex(const string& name, int index) {
    std::cout << "Look for index of " << name << std::endl;
    for (int i = 0; indexLookupTable[i].fn; i++) {
        if (name == indexLookupTable[i].key) {
            (*(indexLookupTable[i].fn))(index);
            break;
        }
    }
}
