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
    void imprimirListaEstrutura();

  private:
    fstream arquivo;
  
  protected:
    vector<Vertice*> vetor_vertices;

    ListaEstrutura(string);
    ~ListaEstrutura();

    Vertice* inserirVertice(int);
    Vertice* buscaVertical(int); //Vertices do grafo
    
    void inserirVizinho(Vertice*, Vertice*);
    Vizinho* buscaHorizontal(Vertice*); //Vizinhos de um vértice
};

#endif
