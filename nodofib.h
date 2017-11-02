#ifndef NODOFIB_H
#define NODOFIB_H

#include <iostream>
#include "list"
#include "map"
#include <stdlib.h>
#include <stddef.h>
// #include "fstream"
// #include "iostream"

using namespace std;
enum Colores{
    White, Black
};

template <typename T>
class Nodo{
public:
    T valor;
    Nodo<T>* p_padre;
    bool color;
    list<Nodo<T>*> lst_hijos;
    /////int degree;
    /////////////metodos/////
    Nodo();
    Nodo(T);
    void noNodo();
    void print(ofstream &archivo);
    typename list<Nodo<T>*>::iterator n_find(Nodo<T>*);
    bool nodo_find(T,Nodo<T>*&);
};
#endif
