#include "floresta.h"

Floresta::Floresta() {}
Floresta::~Floresta() {}

Arvore* Floresta::criaArvoreNova(int rotuloRaiz) {
  Arvore* arvoreNova = new Arvore(rotuloRaiz);
  arvores.push_back(arvoreNova);

  return arvoreNova;
}

Arvore* Floresta::getArvore(int indice) {
  return arvores.at(indice);
}

vector<Arvore*> Floresta::getArvores() {
  return arvores;
}

void Floresta::infoFLoresta() {


  for (int i=0; i<this->getArvores().size(); i++) {
  cout << "**** Componente " << i+1 << " ****"<< endl;
    this->infoArvore(getArvores().at(i)->getRaiz());
    cout << endl; 
  }
}

void Floresta::infoArvore(Noh* noh) {
  cout << "Vértice: " << noh->getRotulo();
  cout << " | Nível: " << noh->getNivel();
  cout << " | Pai: " << (noh->getPai() ? noh->getPai()->getRotulo() : 0) << endl;

  vector<Noh*> vetor = noh->getFilhos();

  for (int i=0; i<vetor.size(); i++) {
    infoArvore(vetor.at(i));
  }

}

