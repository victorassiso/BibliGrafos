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
    
    int getRotulo();
    void setVizinho(Vizinho*);
    Vizinho* getVizinho();


  private:
    int rotulo;
    Vizinho* vizinho;
};

#endif