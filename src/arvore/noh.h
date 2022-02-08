#ifndef NOH_H
#define NOH_H

#include "../lista/listaVertice.h"
#include "../matriz/matrizVertice.h"
#include <vector>
using namespace std;

template <class T>
class Noh
{
  public:
    Noh(T* v) {
      vertice = v;
      pai = nullptr;
      nivel = 0;
    };
    ~Noh() {};

    Noh* getPai() { return pai; };
    vector<Noh*> getFilhos() { return filhos; }
    Noh* getFilho(int indice) { return filhos.at(indice); }
    int getNivel() { return nivel; };
    T* getVertice() { return vertice; };

    void setPai(Noh* p) {
      pai = p;
      if (p) {
        p->filhos.push_back(this);
      }
    };

    void setNivel(int n) { nivel = n; };

  private:
    T* vertice;
    Noh* pai;
    vector<Noh*> filhos;
    int nivel;
};

template class Noh<ListaVertice*>;
template class Noh<MatrizVertice*>;
#endif