//Arquivo de cabeçalho item.h

#ifndef _ITEM_H_
#define _ITEM_H_

class Item {  //Classe que representa as peças / bolinhas.
	
private:
	//Atributos
	int type; //as peças poderão ser de vários cores. E fica mais fácil dar um Rand em inteiros.

public:
	//Métodos
	Item(int type); //Construtor. Define o tipo.
    int getType(); //Retorna o tipo do item.
    void setType(int type); //Atribui o tipo.
    ~Item(); //Destrutor
};


#endif