#ifndef ARVORE_H
#define ARVORE_H

#include "noh.h"
#include <iostream>

class Arvore
{
  public:
    Arvore(int rotuloRaiz);
    ~Arvore();

    Noh* insereNoh(int rotulo, Noh* pai);

    Noh* getRaiz();

  private:
    Noh* raiz;

};

#endif