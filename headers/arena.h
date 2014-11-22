#ifndef _ARENA_H_
#define _ARENA_H_

#include "item.h"
#include "position.h"
#include "shooter.h"
#include "list.h"

class Arena{
private:
	//Atributos
	Shooter *shooter;
	List<Position> *path;
	int height;
	int width;
	int initial_size;
	int initial_show_size;
	int** arena;

public:
	//Métodos
	Arena(int, int, int, int);
	void addPosition(Position*);
	void orderPath(int, int, int, int);
	void shoot();
};


#endif