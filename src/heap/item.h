#ifndef ITEM_H
#define ITEM_H

#include "../lista/listaVertice.h"
#include <vector>
using namespace std;

class Item
{
  private:
    ListaVertice *elemento;
    float chave;
    Item *pai;

  public:
    Item(ListaVertice *_elemento, float _chave) {
      elemento = _elemento;
      chave = _chave;
    };
    ~Item() {};

    ListaVertice * getVertice() { return elemento; };
    float getChave() { return chave; };
    void setChave(float newChave) { chave = newChave; };
    Item * getPai() { return pai; };
    void setPai(Item *p) { pai = p; };
};

#endif