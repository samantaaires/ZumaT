#include <stdio.h>
#include <game/arena.h>
#include <game/game_engine.h>

void loadArena(Arena * arena, char* filename){}

int main( int argc, char* argv[] ){
	std::cout << "loading arena - ";
	Arena * arena = new Arena(argv[1]); //Carrega os dados da arena baseado no arquivos
	if(!arena->orderPath()){ //Ordena o caminho, se o caminho estiver errado finaliza o programas
		std::cout << "invalid path" << std::endl;
	}else{
		std::cout << "done" << std::endl;
		GameEngine * gameEngine = new GameEngine(arena); //Carrega o allegro
		gameEngine->start(); // Inicia o jogo
	}
	return 0;
}

