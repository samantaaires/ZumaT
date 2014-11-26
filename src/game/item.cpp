//Arquivo de corpo item.cpp

#include "game/item.h"
#include <iostream>

Item::Item(int type) {
    this->type = type;
}

int Item::getType() {
    return this->type;
}

void Item::setType(int type) {
    this->type = type;
}

Item::~Item() { 
    //dtor
}