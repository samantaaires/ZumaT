//Arquivo de cabeçalho shooter.h

#ifndef _SHOOTER_H_
#define _SHOOTER_H_

#include "game/item.h"
#include "game/position.h"

class Shooter{
public:
	//Atributos
	Position *position;
	Item *item;

	//Métodos
	Shooter(int, int);
	void reload(int type); // Recarrega a arma com um item aleatório;
	Item* shoot(); // Lançar o item.
	void moveLeft();
	void moveRight();
};

#endif