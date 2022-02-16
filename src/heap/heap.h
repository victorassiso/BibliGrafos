#ifndef HEAP_H
#define HEAP_H

#include "item.h"
#include "math.h"
#include "../lista/lista.h"
#include <iostream>

class Heap {
  private:

    int pai(int i); // i/2 
    int esq(int i); // i*2
    int dir(int i); // i*2+1
    void subir(int i);
    void descer(int i);
    void troca(int a, int b);
    
  public:
    vector<Item *> heap;
    Heap();
    ~Heap();

    void inserir(ListaVertice *elemento, float chave);
    Item * extrair();
    Item * getRaiz();
    Item * atualizar(int i, float newChave);
    float getChave(ListaVertice *elemento);
    float getChave(int i);
    int getIndice(ListaVertice *elemento);
    void imprimirHeap ();
    
};

#endif