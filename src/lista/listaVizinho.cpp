#ifndef LISTAVIZINHO
#define LISTAVIZINHO

#include "listaVizinho.h"

Vizinho::Vizinho(ListaVertice* ve, float p)
{
  vertice = ve;
  vizinho = nullptr;
  peso = p;
}

Vizinho::~Vizinho(){}

void Vizinho::setVizinho(Vizinho* vi) { vizinho = vi; }

Vizinho* Vizinho::getVizinho() { return vizinho; }
ListaVertice* Vizinho::getVertice() { return vertice; }
float Vizinho::getPeso() { return peso; }

#endif
