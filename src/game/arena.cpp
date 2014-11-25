#include "game/arena.h"

Arena::Arena(char * filename){
	this->path = new List<Position>();
	this->items = new List<Item>();

	//LoadParametersFromFile
	std::cout << "loading arena - ";
	std::ifstream infile;
	infile.open(filename);
	std::string line;

	int i = 0;

	if (infile.is_open()){
		while (std::getline(infile, line)){
			std::stringstream iss(line);
			if (i == 0){
				iss >> this->height >> this->width;
			}
			if (i == 1){
				iss >> this->initial_size;
			}
			if (i == 2){
				iss >> this->show_size;

			}
			if (i > 2){
				for(int j = 0; j < line.length(); j++){
					if (line[j] == '@'){
						this->addPosition(j, i-3);
						this->i_x = j;
						this->i_y = i-3;
					}
					if (line[j] == '1'){
						this->addPosition(j, i-3);
					}
					if (line[j] == 'X'){
						this->addPosition(j, i-3);
						this->e_x = j;
						this->e_y = i-3;
					}
				}
			}
			i++;
		}
		this->orderPath();
		std::cout << "done" << std::endl;
	}

	for (int i = 0; i< initial_size; i++){
		this->items->push(new Item(i%4));
	}
	this->shooter =  new Shooter(height, this->e_x/2);
	this->shooter->reload(0);
}

void Arena::addPosition(int x, int y){
	Position * pos = new Position(y, x);
	path->push(pos);
}

void Arena::orderPath(){
	List<Position> * aux = new List<Position>();
	int x = this->i_x;
	int y = this->i_y;
	aux->push(this->path->get(this->searchPosition(x, y)));
	int position;
	int last_move = 0;
	while(aux->length() < this->path->length()){
		position = this->searchPosition(x+1, y);
		if(position > -1 && last_move != 2 ){
			x++;
			last_move = 1;
			aux->push(this->path->get(this->searchPosition(x, y)));
		}
		position = this->searchPosition(x-1, y);
		if(position > -1 && last_move != 1){
			x--;
			last_move = 2;
			aux->push(this->path->get(this->searchPosition(x, y)));
		}

		position = this->searchPosition(x, y+1);
		if(position > -1 && last_move != 4){
			y++;
			last_move = 3;
			aux->push(this->path->get(this->searchPosition(x, y)));
		}
		position = this->searchPosition(x, y-1);
		if(position > -1 && last_move != 3){
			y--;
			last_move = 4;
			aux->push(this->path->get(this->searchPosition(x, y)));
		}
	}
	this->path = aux;
}

int Arena::searchPosition(int x, int y){
	int i = 1;
	int location = -1;
	Position * aux;
	while(i <= this->path->length()){
		aux = this->path->get(i);
		if (aux->x == x && aux->y == y)
			location = i;
		i++;
	}
	return location;
}

void Arena::print(){
	for(int i = 0; i < this->height; i++){
		for(int j = 0; j < this->height; j++){
			int p = this->searchPosition(j, i);
			// std::cout << p;
			if (p < show_size && p > -1)
				std::cout << this->items->get(p)->getType();
			else if(j == this->shooter->position->x && j == this->shooter->position->y)
				std::cout << 'S';
			else if (this->i_x == j && this->i_y == i )
				std::cout << '@';
			else if (this->e_x == j && this->e_y == i )
				std::cout << 'X';
			else if(p == -1)
				std::cout << " ";
			else
				std::cout << ".";
		}
		std::cout << std::endl;
	}
}

int Arena::checkShoot(int p){
	int locations[250];
	int finded = 0;
	int score = 0;
	int pos;
	
	locations[finded] = p;
	finded++;

	//Checar para esquerda
	pos = p-1;
	while(this->items->get(pos)->getType() == this->items->get(p)->getType() && pos > 0){
		locations[finded] = pos;
		finded++;
		pos--;
	}
	//checar para direita
	pos = p+1;
	while(this->items->get(pos)->getType() == this->items->get(p)->getType() && pos <= this->items->length()){
		locations[finded] = pos;
		finded++;
		pos++;
	}

	if (finded >= 3){
		while(finded > 0){
			finded--;
			this->items->pop(locations[finded]);
			score += 1;
		}
	}
	return score;
}


//GETS
int Arena::getHeight(){
	return this->height;
}
int Arena::getWidth(){
	return this->width;
}
List<Item>* Arena::getItems(){
	return this->items;
}

Shooter * Arena::getShooter(){
	return this->shooter;
}