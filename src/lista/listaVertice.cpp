#include "listaVertice.h"

Vertice::Vertice(int e)
{
  rotulo = e;
  vizinho = nullptr;
  statusBusca = 0;
  pai = nullptr;
  nivel = 0;
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

void Vertice::setPai(Vertice* p)
{
  pai = p;
}

void Vertice::setNivel(int n)
{
  nivel = n;
}

Vizinho* Vertice::getVizinho()
{
  return vizinho;
}

void Vertice::setStatus(bool s)
{
  statusBusca = s;
}

bool Vertice::getStatus()
{
  return statusBusca;
}

Vertice* Vertice::getPai()
{
  return pai;
}

int Vertice::getNivel()
{
  return nivel;
}