#include "game/arena.h"

Arena::Arena(char * filename){
	this->path = new List<Position>();
	this->items = new List<Item>();

	std::ifstream infile;
	infile.open(filename);
	std::string line;

	int i = 0; //contador de linha

	//LoadParametersFromFile
	if (infile.is_open()){
		while (std::getline(infile, line)){
			std::stringstream iss(line);
			if (i == 0){ //linha 1 com altura e largura da arenas
				iss >> this->height >> this->width;
			}
			if (i == 1){ //Linha 2 com tamanho inicial da lista de items
				iss >> this->initial_size;
			}
			if (i == 2){ //Linha 3 com tamanho inicial que aparece na arena
				iss >> this->show_size;
			}
			if (i > 2){ //Demais linhas com a arena
				//Adiciona cada posição encontrada na arena
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
	}
	srand (time(NULL));
	//Inicializ a lista de itens
	for (int i = 0; i< initial_size; i++){
		this->items->push(new Item(rand()%5));
	}
	//Inicialisa o atirador
	this->shooter =  new Shooter(height, this->e_x/2);
	//Recarrega o atirador
	this->shooter->reload(getRandomTypeFromItemPool());
}


//Adiciona uma posição na arena
void Arena::addPosition(int x, int y){
	Position * pos = new Position(y, x);
	path->push(pos);
}

//Ordena o caminha de forma que a primeira posição da lista é o começo e a ultima o fim
bool Arena::orderPath(){
	List<Position> * aux = new List<Position>();
	int x = this->i_x;
	int y = this->i_y;
	aux->push(this->path->get(this->searchPosition(x, y)));
	int position;
	int last_move = 0;
	bool order_tentative = false;
	while(aux->length() < this->path->length()){
		//procura pra direita
		position = this->searchPosition(x+1, y);
		if(position > -1 && last_move != 2 ){
			x++;
			last_move = 1;
			order_tentative = true;
			aux->push(this->path->get(this->searchPosition(x, y)));
		}
		//procura pra esquerda
		position = this->searchPosition(x-1, y);
		if(position > -1 && last_move != 1){
			x--;
			last_move = 2;
			order_tentative = true;
			aux->push(this->path->get(this->searchPosition(x, y)));
		}

		//procura pra baixo
		position = this->searchPosition(x, y+1);
		if(position > -1 && last_move != 4){
			y++;
			last_move = 3;
			order_tentative = true;
			aux->push(this->path->get(this->searchPosition(x, y)));
		}
		//procura pra cima
		position = this->searchPosition(x, y-1);
		if(position > -1 && last_move != 3){
			y--;
			last_move = 4;
			order_tentative = true;
			aux->push(this->path->get(this->searchPosition(x, y)));
		}

		//Se nao achar pra nenhum lado o caminho é invalido
		if(order_tentative == true){
			order_tentative = false;
		}else{
			return false;
		}
	}
	this->path = aux;
	return true;
}


//Procura o indice de uma posição baseado nas cordenadas x e y
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

//imprime a arena no terminal
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

//Verifica o local de impacto "p" para itens do mesmo tipo
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

	//Se achou mais que 3 estora todos
	if (finded >= 3){
		while(finded > 0){
			finded--;
			this->items->pop(locations[finded]);
			score += 1;
		}
	}
	return score;
}

//Retorna um tipo de item contido na lista de itens
int Arena::getRandomTypeFromItemPool(){
	int p = this->items->length();
	p = rand() % p+1;
	return this->items->get(p)->getType();
}

//Ação de atirar com o shooter
void Arena::shoot(){
	//So atira se nao tiver nemhum outro item atirado na arena
	if(this->shootedItem == NULL){
        this->shootedItem = this->shooter->shoot();
        this->shootedItemPosition = new Position(this->shooter->position->y, this->shooter->position->x);
    }
	this->shooter->reload(getRandomTypeFromItemPool());
}


//Se o os items chegarem no fim o jogo acaba
//Show size = localização dos itens
bool Arena::gameEnded(){
	return this->show_size >= this->path->length();
}

int Arena::getPathLength(){
	return this->path->length();
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