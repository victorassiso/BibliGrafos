#include <fstream>
#include <vector>
using namespace std;

class Lista: public ListaEstrutura
{
  public:
    void info(); //
    int distancia(int, int);
    int diametro();
    void BFS(int);
    void DFS(int);
  private:
    fstream arquivo;

    int getNVertices();
    int getNArestas();
    int getGrauMinimo();
    int getGrauMaximo();
    double getGrauMedio();
    int getGrauMediana();

    int nVertices;
    int nArestas;
    int grauMinimo;
    int grauMaximo;
    double grauMedio;
    int grauMediana;
};

class ListaEstrutura
{
  protected:
    Vertice* inserirVertice(int);
    void inserirVizinho(Vertice*, Vertice*);
    Vertice* buscaVertical(int); //Vertices do grafo
    Vizinho* buscaHorizontal(Vertice*); //Vizinhos de um vértice
    vector<Vertice*> vetor_vertices;
  private:
    fstream arquivo;
};

class Vertice
{
  public:
    Vertice(int);
    ~Vertice();
    void setVizinho(Vizinho*);
    void setStatus(bool);
    void setPai(Vertice*);
    void setNivel(int);
    int getRotulo();
    Vizinho* getVizinho();
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