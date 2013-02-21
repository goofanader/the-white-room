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

GameObject* createBox1() { return new Box1(); }
GameObject* createBox2() { return new Box2(); }
GameObject* createBox3() { return new Box3(); }
GameObject* createBox4() { return new Box4(); }

GameObject* createRadio() { return new Radio(); }
GameObject* createTable() { return new Table(); }
GameObject* createPlant1() { return new Plant1(); }
GameObject* createPlant6() { return new Plant6(); }

GameObject* createChandelier() { return new Chandelier(); }

GameObject* createClock() { return new Clock(); }
GameObject* createBookshelf() { return new Bookshelf(); }
GameObject* createBook1() { return new Book1(); }
GameObject* createBook2() { return new Book2(); }
GameObject* createBook3() { return new Book3(); }

GameObject* createMooseHead() { return new MooseHead(); }

struct {
    GameObject* (*fn)();
    const char* key;
}

functionLookupTable[] = {
    { &createDoor, "WhiteDoor"},
    { &createSafe, "Safe"},
    { &createRoom, "Room"},
    { &createArmchair, "Armchair"},
    { &createBox1, "Box1"},
    { &createBox2, "Box2"},
    { &createBox3, "Box3"},
    { &createBox4, "Box4"},
    { &createRadio, "Radio"},
    { &createPlant1, "Plant1"},
    { &createPlant6, "Plant6"},
    { &createChandelier, "Chandelier"},
    { &createClock, "Clock"},
    { &createBookshelf, "Bookshelf"},
    { &createBook1, "Book1"},
    { &createBook2, "Book2"},
    { &createBook3, "Book3"},
    { &createMooseHead, "MooseHead"},
    { &createTable, "Table"},
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
int plant1, plant6, radio;

void initializeIndices() {
    door = -1;
    book1 = -1;
    book2 = -1;
    book3 = -1;
    
    plant1 = plant6 = radio = -1;
}

int getDoorNum() { return door; }
int getBook1Num() { return book1; }
int getBook2Num() { return book2; }
int getBook3Num() { return book3; }
int getPlant1Num() { return plant1; }
int getPlant6Num() { return plant6; }
int getRadioNum() { return radio; }

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
