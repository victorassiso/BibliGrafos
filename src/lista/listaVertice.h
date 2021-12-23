#ifndef LISTAVERTICE_H
#define LISTAVERTICE_H

using namespace std;

// Diz que a classe existe sem inicializá-la
class Vizinho;

class Vertice
{
  public:
    Vertice(int);
    ~Vertice();
    
    void setVizinho(Vizinho*);

    int getRotulo();
    Vizinho* getVizinho();

    void setStatus(bool);
    void setPai(Vertice*);
    void setNivel(int);
    bool getStatus();
    Vertice* getPai();
    int getNivel();

  private:
    int rotulo;
    Vizinho* vizinho;
    bool statusBusca; //false - Não explorado; true - Explorado;
    Vertice* pai;
    int nivel;
};

#endif