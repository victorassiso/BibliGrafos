#include "noh.h"

Noh::Noh(int r)
{
  rotulo = r;
  pai = nullptr;
  filhos = {};
  nivel = 0;
  status = false;
}

Noh::~Noh() {}

Noh* Noh::getPai() { return pai; }
int Noh::getRotulo() { return rotulo; }
int Noh::getNivel() { return nivel; }
bool Noh::getStatus() { return status; }
vector<Noh*> Noh::getFilhos() { return filhos; }
Noh* Noh::getFilho(int indice) { return filhos.at(indice); }

void Noh::setPai(Noh* p) { pai = p; }
void Noh::setFilho(Noh* f) { filhos.push_back(f); }
void Noh::setNivel(int n) { nivel = n; }
void Noh::setStatus(bool s) { status = s; }


