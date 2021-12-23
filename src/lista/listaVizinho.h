#ifndef VIZINHO_H
#define VIZINHO_H

using namespace std;

class Vertice; // Diz que a classe existe sem inicializá-la

class Vizinho
{
  public:
    Vizinho(Vertice*);
    ~Vizinho();
    
    void setVizinho(Vizinho*);
    Vertice* getVertice();
    Vizinho* getVizinho();


  private:
    Vertice* vertice;
    Vizinho* vizinho;
};

#endif