#include "noh.h"

Noh::Noh(int r)
{
  rotulo = r;
  listaVertice = nullptr;
  pai = nullptr;
  filhos = {};
  nivel = 0;
  status = false;
}

Noh::Noh(ListaVertice* v)
{
  rotulo = v->getRotulo();
  listaVertice = v;
  pai = nullptr;
  filhos = {};
  nivel = 0;
  status = false;
}

Noh::~Noh() {}

Noh* Noh::getPai() { return pai; }
int Noh::getNivel() { return nivel; }
bool Noh::getStatus() { return status; }
Noh* Noh::getFilho(int indice) { return filhos.at(indice); }
vector<Noh*> Noh::getFilhos() { return filhos; }
int Noh::getRotulo() { return rotulo; }
ListaVertice* Noh::getVertice() { return listaVertice; }

void Noh::setPai(Noh* p) { pai = p; }
void Noh::setNivel(int n) { nivel = n; }
void Noh::setStatus(bool s) { status = s; }
void Noh::setFilho(Noh* f) { filhos.push_back(f); }


