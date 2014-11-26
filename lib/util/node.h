//Arquivo de cabeçalho node.h

#ifndef NODE_H_
#define NODE_H_

template <class T>
class Node {

public:
    //Atributos
    Node<T> *next;
    T *data; //Tipo genérico de dados.
};

#endif