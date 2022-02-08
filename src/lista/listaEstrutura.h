#ifndef LISTAESTRUTURA_H
#define LISTAESTRUTURA_H

#include "listaVertice.h"
#include "listaVizinho.h"
#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class ListaEstrutura
{   
  public:
    void imprimirEstruturaLista();

  private:
    vector<ListaVertice*> vetor_vertices;
    
    // Atributos Info
    int nVertices;
    
    // Métodos Set Info
    void setNVertices(int);
    
  protected:
    ListaEstrutura(string arquivoOrigem);
    ~ListaEstrutura();

    // Métodos Auxiliares
    ListaVertice* inserirVertice(int rotulo);
    ListaVertice* buscaVertical(int rotulo);
    void inserirVizinho(ListaVertice* v1, ListaVertice* v2);
    Vizinho* buscaHorizontal(ListaVertice* );
    
    //Métodos Get Info
    int getNVertices();
};

#endif
