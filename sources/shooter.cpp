//Arquivo de corpo shooter.cpp

#include "shooter.h"

Shooter::Shooter(){
	this->position = new Position(0,0);
}

void Shooter::reload(int type){
	this->item = new Item(type);
}

Item* Shooter::shoot(){
	return this->item;
}

void Shooter::moveLeft(){
	if(this->position->x > 0){
		this->position->x--;
	}
}

void Shooter::moveRight(){
	this->position->x++;
}