#ifndef NOH_H
#define NOH_H

#include <vector>
using namespace std;

class Noh
{
  public:
    Noh(int rotulo);
    ~Noh();

    Noh* getPai();
    int getRotulo();
    vector<Noh*> getFilhos();
    Noh* getFilho(int indice);
    int getNivel();
    bool getStatus();

    void setPai(Noh* pai);
    void setFilho(Noh* filho);
    void setNivel(int nivel);
    void setStatus(bool status);

  private:
    int rotulo;
    Noh* pai;
    vector<Noh*> filhos;
    int nivel;
    bool status;
    
};

#endif