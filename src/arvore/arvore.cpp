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

void Arvore::imprimeArvore(Noh* noh) {
  cout << noh->getRotulo() << endl;
  vector<Noh*> vetor = noh->getFilhos();

  for (int i=0; i<vetor.size(); i++) {
    imprimeArvore(vetor.at(i));
  }

}
