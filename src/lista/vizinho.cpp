#include "vizinho.h"

Vizinho::Vizinho(Vertice* ve)
{
  vertice = ve;
  vizinho = nullptr;
}

Vizinho::~Vizinho(){}

void Vizinho::setVizinho(Vizinho* vi)
{
  vizinho = vi;
}

Vertice* Vizinho::getVertice()
{
  return vertice;
}

Vizinho* Vizinho::getVizinho()
{
  return vizinho;
}