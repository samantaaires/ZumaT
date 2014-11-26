//Arquivo de cabeçalho item.h
#ifndef _GAMEENGINE_H_
#define _GAMEENGINE_H_

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include <stdio.h>
#include <stdbool.h>
#include <ctime>

#include "game/arena.h"

class GameEngine {  //Classe que representa as peças / bolinhas.
	
private:
	//Atributos
	const int LARGURA_TELA = 640;
	const int ALTURA_TELA = 480;
	 
	ALLEGRO_DISPLAY *janela = NULL;
	ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
	ALLEGRO_FONT *fonte = NULL;


	Arena * arena;
	int score;
	double timeToMove;
	double itemRenderSize;
	bool gameOver;

	bool inicialize();

	void print();
	bool checkShoot(int);
	void missShoot();
	int calculateScore(int);

public:
	//Métodos
	GameEngine(Arena*);
	int start();
	int start(int argc, char**);
};


#endif