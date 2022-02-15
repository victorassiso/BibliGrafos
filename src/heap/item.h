#ifndef ITEM_H
#define ITEM_H

#include "../lista/listaVertice.h"
#include "../matriz/matrizVertice.h"
#include <vector>
using namespace std;

template <class T>
class Item
{
  private:
    T* vertice;
    float dist;

  public:
    Item(T* v, float d) {
      vertice = v;
      dist = d;
    };
    ~Item() {};


};

template class Item<ListaVertice*>;
template class Item<MatrizVertice*>;
#endif