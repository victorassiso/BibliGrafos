#ifndef NOH_H
#define NOH_H

#include "../lista/listaVertice.h"
#include <vector>
using namespace std;

class Noh
{
  public:
    Noh(int rotulo);
    Noh(ListaVertice* listaVertice);
    ~Noh();

    Noh* getPai();
    int getNivel();
    bool getStatus();
    Noh* getFilho(int indice);
    vector<Noh*> getFilhos();
    int getRotulo();
    ListaVertice* getVertice();

    void setPai(Noh* pai);
    void setFilho(Noh* filho);
    void setNivel(int nivel);
    void setStatus(bool status);

  private:
    int rotulo;
    ListaVertice* listaVertice;
    Noh* pai;
    vector<Noh*> filhos;
    int nivel;
    bool status;
    
};

#endif