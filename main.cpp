#include <stdio.h>
#include <game/arena.h>
#include <game/game_engine.h>

void loadArena(Arena * arena, char* filename){}

int main( int argc, char* argv[] ){
	Arena * arena = new Arena(argv[1]);
	GameEngine * gameEngine = new GameEngine(arena);
	gameEngine->start();
	return 0;
}

