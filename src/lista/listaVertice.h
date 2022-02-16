#ifndef LISTAVERTICE_H
#define LISTAVERTICE_H

using namespace std;

// Diz que a classe existe sem inicializá-la
class Vizinho;

class ListaVertice
{
  public:
    ListaVertice(int);
    ~ListaVertice();
    
    void setVizinho(Vizinho*);
    void setStatus(bool);
    void setDist(float dist);

    Vizinho* getVizinho();
    bool getStatus();
    int getRotulo();
    float getDist();

  private:
    int rotulo;
    Vizinho* vizinho;
    bool statusBusca; //false - Não explorado; true - Explorado;
    float dist;
};

#endif