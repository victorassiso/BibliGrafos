#ifndef MATRIZ_H
#define MATRIZ_H

#include "matrizEstrutura.h"
#include "../arvore/arvore.h"
#include <bits/stdc++.h>
using namespace std;

class Matriz: public MatrizEstrutura
{
  public:
    Matriz(string arquivoOrigem);
    ~Matriz();

    void info(string arquivoDestino);
    int distancia(int r1, int r2); // BFS
    int diametro(); // BFS
    void arvoreBFS(int raizRotulo, string arquivoDestino);
    // void arvoreDFS(int raizRotulo, string arquivoDestino);
  
  private:
    // fstream arquivo;

    // Atributos Info
    int nArestas;
    int grauMinimo;
    int grauMaximo;
    double grauMedio;
    double grauMediana;
    int nComponentes;

    // Métodos Get Info
    int getNArestas();
    int getGrauMinimo();
    int getGrauMaximo();
    double getGrauMedio();
    double getGrauMediana();
    int getNComponentes();

    // Métodos Set Info
    void setNArestas(int);
    void setGrauMinimo(int);
    void setGrauMaximo(int);
    void setGrauMedio(double);
    void setGrauMediana(double);
    void setNComponentes(int);

    // Métodos Auxiliares
    string info2();
    string info3(vector<vector<MatrizVertice *>> *componentes);
    void desmarcarTodosOsVertices();
    MatrizVertice *pop_front(vector<MatrizVertice*> *Q);
    Noh<MatrizVertice> *pop_front(vector<Noh<MatrizVertice> *> *QNoh);
    int pop_front(vector<int> *QIndice);
    Noh<MatrizVertice>* marcar_e_inserir_vizinho(
      int *i,
      vector<int> *QIndice,
      vector<Noh<MatrizVertice> *> *QNoh,
      Noh<MatrizVertice> *vNoh
    );
    void marcar_e_inserir_raiz(
      int* indiceRaiz,
      vector<int>* QIndice,
      vector<Noh<MatrizVertice>*>* QNoh,
      Noh<MatrizVertice>* sNoh
    );
    void marcar_e_inserir(
      int *i,
      vector<int> *QIndice,
      vector<MatrizVertice*> *Q,
      vector<vector<MatrizVertice *>> *componentes,
      int *nComp
    );
    string imprimir_vertices_arvore(Noh<MatrizVertice> *vNoh);

};

#endif

