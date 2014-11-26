//Arquivo de corpo shooter.cpp

#include "game/shooter.h"

Shooter::Shooter(int y, int x){
	this->position = new Position(y,x); //Aloca uma nova posição com os valores de x e y.
}

void Shooter::reload(int type){
	this->item = new Item(type); //Carrega o valor do atributo item da classe com um novo tipo qualquer e item.
}

Item* Shooter::shoot(){
	return this->item; //Retorna o valor do item da classe. É o que será atirado.
}

void Shooter::moveLeft(){
	if(this->position->x > 0){
		this->position->x--;	
	}
}

void Shooter::moveRight(){
	this->position->x++;
}