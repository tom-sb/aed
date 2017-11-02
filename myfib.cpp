#include <iostream>
#include "fibonacci.h"
#include "stdlib.h"
#include "stddef.h"
#include "climits"
#include "fstream"
#include "iostream"

using namespace std;

template <typename T>
void Nodo<T>::print(ofstream &archivo){
    string c = "black";
    if(color == Black) c = "red";
    archivo<<valor<<" [label = \""<<valor<<"\" color=\""<<c<<"\"];"<<endl;
    for(auto iter = lst_hijos.begin(); iter != lst_hijos.end(); ++iter){
        archivo<<valor<<"->"<<(*iter)->valor<<endl;
        (*iter)->print(archivo);
    }
}


template <typename T>
Nodo<T>::Nodo(){
    p_padre = NULL;
    color = White;
    //degree = 0;
}

template <typename T>
Nodo<T>::Nodo(T _valor){
    valor = _valor;
    p_padre = NULL;
    color = White;
    //degree = 0;
}

template <typename T>
void Nodo<T>::noNodo(){
    for(auto it = lst_hijos.begin(); it != lst_hijos.end(); ++it){
        (*it)->noNodo();
    }
    delete this;
}

template <typename T>
bool Nodo<T>::nodo_find(T _valor,Nodo<T>*& nodo){
    //std::cout << "ENTRO A NODO_FIND" << '\n';
    if(this->valor == _valor){
        //std::cout << "IGUAL<<<<<<<<<<<<<<" << '\n';
        return true;
    }
    for(auto itt = lst_hijos.begin(); itt != lst_hijos.end(); ++itt){
        //std::cout << "FOR" << '\n';
        if((*itt)->valor == _valor){
            nodo = (*itt);
            //std::cout << "IGUAL222<<<<<<<<<<<" << '\n';
            return true;
        }
        // if((*it)->nodo_find(_valor,nodo))
        //     return true;
    }
    //std::cout << "NO FOR" << '\n';
    return false;
}

template <typename T>
typename list<Nodo<T>*>::iterator Nodo<T>::n_find(Nodo<T>* nodo){
    for(auto iter = lst_hijos.begin(); iter != lst_hijos.end(); ++iter){
        if(*iter == nodo)return iter;
    }
    return lst_hijos.end();
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
template <typename T>
void FibonacciHeap<T>::print(){
    ofstream archivo("eje.dot");
    if(archivo.fail()){
        cout<<"El archivo no se pudo abrir"<<endl;
        return;
    }
    archivo<<"digraph{"<<endl;
    for(auto iter = lst_roots.begin(); iter != lst_roots.end(); ++iter){
        (*iter)->print(archivo);
    }
    archivo<<"}";
    archivo.close();
    system("dot -Tpdf eje.dot -o eje.pdf");
}




template <typename T>
FibonacciHeap<T>::FibonacciHeap(){
    p_menor = NULL;
}

template <typename T>
void FibonacciHeap<T>::fib_insert(T _valor){
    Nodo<T>* nodo;
    if(this->fib_find(_valor,nodo)){
        //std::cout << "fib_find fue true" << '\n';
        return;
    }

    Nodo<T>* nuevo = new Nodo<T>(_valor);
    lst_roots.push_back(nuevo);
    if(!p_menor or p_menor->valor > _valor)
        p_menor = nuevo;
}

template <typename T>
T FibonacciHeap<T>::getMin(){
    return p_menor->valor;
}

// F IB -H EAP -E XTRACT -M IN (H )
// z ← min[H ]
// if z = NIL then
//     for each child x of z
//         do add x to the root list of H
//             p[x] ← NIL
//         remove z from the root list of H
//     if z = right[z] then
//         min[H ] ← NIL
//     else
//         min[H ] ← right[z]
//     C ONSOLIDATE (H )
//     n[H ] ← n[H ] − 1
// return z



template <typename T>
typename list<Nodo<T>*>::iterator FibonacciHeap<T>::f_find(Nodo<T>* menor){
    for(auto iter = lst_roots.begin(); iter != lst_roots.end(); ++iter){
        if(*iter == menor)return iter;
    }
    return lst_roots.end();
}


template <typename T>
T FibonacciHeap<T>::deleteMin(){
    T resultado = p_menor->valor;
    for(auto iter = p_menor->lst_hijos.begin(); iter != p_menor->lst_hijos.end(); ++iter){
        (*iter)->p_padre = NULL;
        lst_roots.push_back(*iter);
    }

    lst_roots.erase(f_find(p_menor));
    p_menor->valor = 100000;

    consolidate();
    return resultado;
}

template <typename T>
void FibonacciHeap<T>::consolidate(){
    map<int,Nodo<T>*> lista;
    for(auto iter = lst_roots.begin(); iter != lst_roots.end(); ++iter){
        if(p_menor->valor > (*iter)->valor)
            p_menor = *iter;
        verificarlLista(lista,*iter);
    }
    list<Nodo<T>*> tempList;
    for(auto iter = lista.begin(); iter != lista.end(); ++iter){
        if(iter->second)
            tempList.push_back(iter->second);
    }
    lst_roots = tempList;
}


template <typename T>
bool FibonacciHeap<T>::fib_find(T valor, Nodo<T>*& nodo){
    if(lst_roots.empty()){
        //std::cout << "entro a fib_find  = vacio" << '\n';
        return false;
    }
    for(auto it = lst_roots.begin(); it != lst_roots.end(); ++it){
        //std::cout << "entro a fib_find  = for -" <<(*it)->valor<< '\n';
        if((*it)->nodo_find(valor,nodo)){
            //cout <<" nodofind IGUALLL+-------+++-++++ "<< '\n';
            return true;
        }
    }
    //std::cout << "entro a fib_find  = false+++++++++++++++++++++*****" << '\n';
    return false;
}

template <typename T>
FibonacciHeap<T>::~FibonacciHeap(){
    for(auto iter = lst_roots.begin(); iter != lst_roots.end(); ++iter){
        (*iter)->noNodo();
    }
}


template <typename T>
void FibonacciHeap<T>::decreaseKey(T valor, T nuevoValor){
    Nodo<T>* nodo;
    if(!this->fib_find(valor,nodo))//si no existe en el heap
        return;//si no encuentra la clave no hace nada solo return
    nodo->valor = nuevoValor;
    if(p_menor->valor > nuevoValor)//si el nuevo valor es menor al puntero al minimo
        p_menor = nodo;//tenemos un nuevo minimo
    nodo->p_padre->lst_hijos.erase(nodo->p_padre->n_find(nodo));
    lst_roots.push_back(nodo);
    verificarColor(nodo);
    nodo->p_padre = nullptr;
}


template <typename T>
void FibonacciHeap<T>::verificarlLista(map<int,Nodo<T>*> &lista, Nodo<T>* iter){
    if(lista.find(iter->lst_hijos.size()) == lista.end()){
        lista[iter->lst_hijos.size()] = iter;
    }
    else if(lista[iter->lst_hijos.size()] == NULL){
        lista[iter->lst_hijos.size()] = iter;
    }
    else{
        if(iter->valor < lista[iter->lst_hijos.size()]->valor){
            int index = iter->lst_hijos.size();
            iter->lst_hijos.push_front(lista[index]);
            lista[index]->p_padre = iter;
            lista[index] = NULL;
            verificarlLista(lista,iter);
        }
        else{
            int index = iter->lst_hijos.size();
            lista[index]->lst_hijos.push_front(iter);
            iter->p_padre = lista[index];
            Nodo<T>* temp = lista[index];
            lista[index] = NULL;
            verificarlLista(lista,temp);
        }
    }
}


template <typename T>
void FibonacciHeap<T>::verificarColor(Nodo<T> *nodo){
    if(nodo->p_padre){//si tiene padre
        if(nodo->p_padre->color == Black){//si el color del padre es black
            if(nodo->p_padre->p_padre){//si tiene abuelo
                nodo->p_padre->p_padre->lst_hijos.erase(nodo->p_padre->p_padre->n_find((nodo->p_padre)));//busca en la lista de hijos del abuelo y borra al padre
                nodo->p_padre->color = White;
                lst_roots.push_back(nodo->p_padre);
                verificarColor(nodo->p_padre);
                nodo->p_padre->p_padre = NULL;
            }
        }
        else{
            nodo->p_padre->color = Black;
        }
    }
}
