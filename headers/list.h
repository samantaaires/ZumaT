//Arquivo de cabeçalho list.h

#ifndef LIST_H_
#define LIST_H_

#include <iostream>


template <class T>
class List {

public:
    //Atributos
    List *next;
    T *data; //Tipo genérico de dados.

    //Métodos
    List();
    void push(T* data, int position);
    void push(T* data);
    void pop(int position);
    void pop();
    int length();
    T *get(int position);
};

#include "list.inl"
#endif