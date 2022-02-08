#ifndef LISTAVIZINHO
#define LISTAVIZINHO

#include "listaVizinho.h"

Vizinho::Vizinho(ListaVertice* ve)
{
  vertice = ve;
  vizinho = nullptr;
}

Vizinho::~Vizinho(){}

void Vizinho::setVizinho(Vizinho* vi) { vizinho = vi; }
//void Vizinho::setPeso(float p) { peso = p; }

Vizinho* Vizinho::getVizinho() { return vizinho; }
//float Vizinho::getPeso() { return peso; }
ListaVertice* Vizinho::getVertice() { return vertice; }

#endif
