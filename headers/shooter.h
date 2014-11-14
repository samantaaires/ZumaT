//Arquivo de cabeçalho shooter.h

#ifndef _SHOOTER_H_
#define _SHOOTER_H_
#include "item.h"
#include "position.h"
class Shooter{
public:
	//Atributos
	Position *pos;
	Item *item;

	//Métodos
	Shooter();
	void reload(int type); // Recarrega a arma com um item aleatório;
	Item* shoot(); // Lançar o item.
	void moveLeft();
	void moveRight();
};

#endif