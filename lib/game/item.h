//Arquivo de cabeçalho item.h

#ifndef _ITEM_H_
#define _ITEM_H_

class Item {  //Classe que representa as peças / bolinhas.
	
private:
	//Atributos
	int type; //as peças poderão ser de vários tipos, por isso o tipo é genérico.

public:
	//Métodos
	Item(int type);
    int getType();
    void setType(int type);
    ~Item();
};


#endif