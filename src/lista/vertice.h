#ifndef VERTICE_H
#define VERTICE_H

using namespace std;

// Diz que a classe existe sem inicializá-la
class Vizinho;

class Vertice
{
  public:
    Vertice(int);
    ~Vertice();
    
    void setVizinho(Vizinho*);
    void setStatus(int);

    int getRotulo();
    Vizinho* getVizinho();
    int getStatus();

  private:
    int rotulo;
    Vizinho* vizinho;
    int statusBusca; //0 - Descoberto; 1 - Explorado; 2 - Desconhecido;
};

#endif