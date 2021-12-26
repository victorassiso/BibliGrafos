#include "arvore.h"

Arvore::Arvore(int rotuloRaiz) {
  Noh* nohRaiz = new Noh(rotuloRaiz);
  raiz = nohRaiz;
}

Arvore::~Arvore() {}

Noh* Arvore::insereNoh(int rotuloFilho, Noh* pai) {
  Noh* nohFilho = new Noh(rotuloFilho);
  pai->setFilho(nohFilho);

  return nohFilho;
}

Noh* Arvore::getRaiz() { return raiz; }

void Arvore::setTamanho(int t) { tamanho = t; }

int Arvore::getTamanho() { return tamanho; }
