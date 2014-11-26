//Arquivo de cabeçalho arena.h

#ifndef _ARENA_H_
#define _ARENA_H_

#include <stdlib.h>
#include <time.h>     
#include <fstream> 
#include <sstream> 
#include <string>
#include <iostream>
#include "game/item.h"
#include "game/position.h"
#include "game/shooter.h"
#include "util/list.h"

class Arena{ //Classe que representa a área que será rodado o jogo.
private:
	//Atributos privados
	Shooter *shooter; //Na arena temos o atirador.
	List<Position> *path; //Uma lista com o caminho válido (lido de um arquivo .txt).
	List<Item> * items; //Uma lista com os itens (bolinhas).
	int height; //Altura
	int width; //Largura

public:
	//Atributos públicos
	Item * shootedItem; //Item atirado.
	Position * shootedItemPosition;
	int initial_size;
	int show_size; //Localização dos itens. Os itens aparentes do caminho.
	int i_x, i_y, e_x, e_y;

	
	//Métodos
	Arena(char*); //Constutor.
	void addPosition(int, int); //Adiciona na posição x e y.
	bool orderPath(); //Ordenar o caminho que as bolinhas irão seguir.
	int searchPosition(int, int);
	int checkShoot(int);
	void shoot();
	void print();
	int getHeight(); //Retorna a altura.
	int getWidth(); //Retorna a largura.
	List<Item>* getItems(); //Retorna a lista de itens.
	Shooter * getShooter(); //Retorna o atirador.
	int getRandomTypeFromItemPool(); //Gerar um item de maneira aleatória.
	bool gameEnded();
	int getPathLength();
};


#endif