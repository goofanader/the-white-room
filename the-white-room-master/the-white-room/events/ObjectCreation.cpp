/* 
 * File:   ObjectCreation.cpp
 * Author: goofanader
 * 
 * Created on January 31, 2013, 2:22 AM
 */

#include "ObjectCreation.h"
#include "../objects/AllObjects.h"

//we really need to make a .h just for object class #includes -_-

GameObject* createDoor() {
    cout << "made a door" << endl;
    return new WhiteDoor();
}

GameObject* createSafe() {
    cout << "made a safe" << endl;
    return new Safe();
}

GameObject* createRoom() {
    cout << "made a room" << endl;
    return new Room();
}

GameObject* createArmchair() {
    cout << "made an armchair" << endl;
    return new Armchair();
}

GameObject* createBox1() {
    return new Box1();
}

GameObject* createBox2() {
    return new Box2();
}

GameObject* createBox3() {
    return new Box3();
}

GameObject* createBox4() {
    return new Box4();
}

GameObject* createRadio() {
    return new Radio();
}

GameObject* createPlant1() {
    return new Plant1();
}
 
GameObject* createPlant6() {
    return new Plant6();
}

GameObject* createChandelier() {
    return new Chandelier();
}

GameObject* createClock() {
    return new Clock();
}

GameObject* createBookshelf() {
    return new Bookshelf();
}

GameObject* createBook1() {
    return new Book1();
}

GameObject* createBook2() {
    return new Book2();
}

GameObject* createBook3() {
    return new Book3();
}

GameObject* createMooseHead() {
    return new MooseHead();
}

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
    { NULL, NULL}
};

GameObject* lookupAndCall(const string& name) {
    for (int i = 0; functionLookupTable[i].fn; i++)
        if (name == functionLookupTable[i].key) {
            return (*(functionLookupTable[i].fn))();
        }
    return NULL;
}
