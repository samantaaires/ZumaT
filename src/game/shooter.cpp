//Arquivo de corpo shooter.cpp

#include "game/shooter.h"

Shooter::Shooter(int y, int x){
	this->position = new Position(y,x);
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