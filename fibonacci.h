#ifndef FIBONACCI_H
#define FIBONACCI_H
//#include <iostream>
#include "list"
#include "map"
#include <stdlib.h>
#include <stddef.h>
#include "nodofib.h"
// #include "iostream"
using namespace std;

template <typename T>
class FibonacciHeap{
public:
    list<Nodo<T>*> lst_roots;
    Nodo<T>* p_menor;

//////public:
    FibonacciHeap();
    void fib_insert(T valor);
    T getMin();
    T deleteMin();
    void print();
    void decreaseKey(T,T);
    void consolidate();
    bool fib_find(T valor, Nodo<T> *&nodo);
    virtual ~FibonacciHeap();
    typename list<Nodo<T>*>::iterator f_find(Nodo<T>* menor);
    void verificarlLista(map<int,Nodo<T>*>&,Nodo<T>*);
    void verificarColor(Nodo<T>*);
};
#endif
