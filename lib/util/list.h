//Arquivo de cabeçalho list.h

#ifndef LIST_H_
#define LIST_H_

#include <cstddef>
#include "node.h"

template <class T>
class List {
private:
    //Atributos
    Node<T> * head;
    int size;
    


public:
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