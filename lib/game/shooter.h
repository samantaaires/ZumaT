//Arquivo de cabeçalho shooter.h

#ifndef _SHOOTER_H_
#define _SHOOTER_H_

#include "game/item.h"
#include "game/position.h"

class Shooter{ //Classe que representa o atirador.
public:
	//Atributos
	Position *position; //Tem as coordenadas de onde ele tá.
	Item *item; //Qual item irá atirar.

	//Métodos
	Shooter(int, int); //Construtor. Define os pontos x e y.
	void reload(int type); // Recarrega a arma com um item aleatório;
	Item* shoot(); // Lança o item.
	void moveLeft();
	void moveRight();
};

#endif