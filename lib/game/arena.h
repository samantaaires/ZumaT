#ifndef _ARENA_H_
#define _ARENA_H_

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "game/item.h"
#include "game/position.h"
#include "game/shooter.h"
#include "util/list.h"

class Arena{
private:
	//Atributos
	Shooter *shooter;
	List<Position> *path;
	List<Item> * items;
	int height;
	int width;

public:
	//PublicAttibutes
	Item * shootedItem;
	Position * shootedItemPosition;
	int initial_size;
	int show_size;
	int i_x, i_y, e_x, e_y;

	
	//Métodos
	Arena(char*);
	void addPosition(int, int);
	void orderPath();
	int searchPosition(int, int);
	int checkShoot(int);
	void shoot();
	void print();
	int getHeight();
	int getWidth();
	List<Item>* getItems();
	Shooter * getShooter();
};


#endif