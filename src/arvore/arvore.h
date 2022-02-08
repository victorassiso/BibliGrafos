#ifndef ARVORE_H
#define ARVORE_H

#include "noh.h"
#include <iostream>

template <class T>
class Arvore
{
  public:
    Arvore(T* r) {
      Noh<T>* nohRaiz = new Noh<T>(r);
      raiz = nohRaiz;
    };
    ~Arvore() {};

    Noh<T>* getRaiz() { return raiz; };

  private:
    Noh<T>* raiz;
};

#endif