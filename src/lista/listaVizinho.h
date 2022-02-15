#ifndef VIZINHO_H
#define VIZINHO_H

using namespace std;

class ListaVertice; // Diz que a classe existe sem inicializá-la

class Vizinho
{
  public:
    Vizinho(ListaVertice* vertice, float peso);
    ~Vizinho();
    
    void setVizinho(Vizinho* vizinho);
    
    ListaVertice* getVertice();
    Vizinho* getVizinho();
    float getPeso();

  private:
    ListaVertice* vertice;
    Vizinho* vizinho;
    float peso;
};

#endif