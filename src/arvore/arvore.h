#ifndef ARVORE_H
#define ARVORE_H

#include "noh.h"
#include "../lista/listaVertice.h"
#include <iostream>

class Arvore
{
  public:
    Arvore(int rotuloRaiz);
    Arvore(ListaVertice* rotuloRaiz);
    ~Arvore();

    Noh* insereNoh(int rotuloFilho, Noh* pai);
    Noh* insereNoh(ListaVertice* verticeFilho, Noh* pai);

    Noh* getRaiz();

    void setTamanho(int tamanho);
    int getTamanho();

  private:
    Noh* raiz;
    int tamanho;

};

#endif