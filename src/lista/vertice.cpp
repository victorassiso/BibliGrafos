#include "vertice.h"

Vertice::Vertice(int e)
{
  rotulo = e;
  vizinho = nullptr;
}

Vertice::~Vertice(){}

int Vertice::getRotulo()
{
  return rotulo;
}

void Vertice::setVizinho(Vizinho* ptr)
{
  vizinho = ptr;
}

Vizinho* Vertice::getVizinho()
{
  return vizinho;
}
