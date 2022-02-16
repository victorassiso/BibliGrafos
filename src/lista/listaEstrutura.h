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
  private:
    int nVertices;
    int tipoGrafo;
    
    void setNVertices(int nVertices);
    void setTipoGrafo(int tipoGrafo);

  protected:
    ListaEstrutura(string arquivoOrigem);
    ~ListaEstrutura();

    vector<ListaVertice*> vetor_vertices;

    // Métodos Auxiliares
    ListaVertice* inserirVertice(int rotulo);
    ListaVertice* buscaVertical(int rotulo);
    void inserirVizinho(ListaVertice *v1, ListaVertice *v2, float peso);
    Vizinho* ultimoVizinho(ListaVertice *vertice);
    bool buscaHorizontal(ListaVertice *v1, ListaVertice *v2);
    
    int getNVertices();
    int getTipoGrafo();

  public:
    void imprimirEstruturaLista();
    vector<ListaVertice*> * getVertices();
    
};

#endif
