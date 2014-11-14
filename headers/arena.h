#ifndef _ARENA_H_
#define _ARENA_H_
#include "Item.h"
#include "position.h"

template <class T>
class Arena{
private:
	//Atributos
	Shooter *shooter;
	List<Position> *path;
	int height;
	int width;
	int[][] arena;

public:
	//Métodos
	Arena();
	void shoot();
};
