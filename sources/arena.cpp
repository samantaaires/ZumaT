#include "arena.h"

Arena::Arena(int height, int width, int initial_size, int initial_show_size){
	this->shooter =  new Shooter();
	this->shooter->reload(0);
	this->path = new List<Position>;
	this->height = height;
	this->width = width;
	this->initial_size = initial_size;
	this->initial_show_size = initial_show_size;
}


void Arena::addPosition(Position * pos){
	path->push(pos);
}

void Arena::orderPath(int initial_i, int initial_j, int end_i, int end_j){

}