#include "vertice.h"

Vertice::Vertice(int e)
{
  rotulo = e;
  vizinho = nullptr;
  statusBusca = 0;
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

void Vertice::setStatus(int s)
{
  statusBusca = s;
}

int Vertice::getStatus()
{
  return statusBusca;
}