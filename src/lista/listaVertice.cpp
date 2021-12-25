#include "listaVertice.h"

Vertice::Vertice(int r)
{
  rotulo = r;
  vizinho = nullptr;
  statusBusca = 0;
  pai = nullptr;
  nivel = 0;
}

Vertice::~Vertice(){}

void Vertice::setVizinho(Vizinho* ptr) { vizinho = ptr; }
void Vertice::setPai(Vertice* p) { pai = p; }
void Vertice::setStatus(bool s) { statusBusca = s; }
void Vertice::setNivel(int n) { nivel = n; }

int Vertice::getRotulo() { return rotulo; }
Vizinho* Vertice::getVizinho() { return vizinho; }
bool Vertice::getStatus() { return statusBusca; }
Vertice* Vertice::getPai() { return pai; }
int Vertice::getNivel() { return nivel; }