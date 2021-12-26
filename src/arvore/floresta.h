#ifndef FLORESTA_H
#define FLORESTA_H

#include "arvore.h"

class Floresta {
  public:
    Floresta();
    ~Floresta();

    Arvore* criaArvoreNova(int rotuloRaiz);

    Arvore* getArvore(int indice);
    vector<Arvore*> getArvores();

    void infoFLoresta();
    void infoArvore(Noh* raiz);

  private:
  vector<Arvore*> arvores;
};

#endif