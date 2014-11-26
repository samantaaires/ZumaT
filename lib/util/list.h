//Arquivo de cabeçalho list.h

#ifndef LIST_H_
#define LIST_H_

#include <cstddef>
#include "node.h"

template <class T>
class List {
private:
    //Atributos
    Node<T> * head; //Nó que é a cabeça.
    int size;
    


public:
    //Métodos
    List(); //Construtor
    void push(T* data, int position); //Inserir em uma posição.
    void push(T* data); 
    void pop(int position); //Remover da posição.
    void pop();
    int length(); //Retorna o tamanho da lista.
    T *get(int position); //Retorna o item daquela posição.
};

#include "list.inl"
#endif