#include "floresta.h"

Floresta::Floresta() {}
Floresta::~Floresta() {}

Arvore* Floresta::criaArvoreNova(int rotuloRaiz) {
  Arvore* arvoreNova = new Arvore(rotuloRaiz);
  return arvoreNova;
}

Arvore* Floresta::getArvore(int indice) {
  return arvores.at(indice);
}

vector<Arvore*> Floresta::getArvores() {
  return arvores;
}
