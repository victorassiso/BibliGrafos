#ifndef LISTA_H
#define LISTA_H

#include "vertice.h"
#include "vizinho.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Lista
{
  public:
    Lista(string);
    ~Lista();

    Vertice* inserirVertice(int);
    Vertice* buscaVertical(int); //Vertices do grafo
    
    void inserirVizinho(Vertice*, Vertice*);
    Vizinho* buscaHorizontal(Vertice*); //Vizinhos de um vértice
    
    void imprimirLista();
    
  private:
    //Objetos
    fstream arquivo;
  
  protected:
    vector<Vertice*> vetor_vertices;
};

#endif
