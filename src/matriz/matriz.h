#ifndef MATRIZ_H
#define MATRIZ_H

#include "matrizEstrutura.h"
#include "../arvore/floresta.h"
#include <bits/stdc++.h>
using namespace std;

class Matriz: public MatrizEstrutura
{
  public:
    Matriz(string);
    ~Matriz();

    void info();
    int distancia(int r1, int r2);
    int diametro();
    void BFS(int);
    void DFS(int);
  
  private:
    fstream arquivo;

    //Outros
    void buscaEApaga(vector<MatrizVertice*>*, MatrizVertice*);
    string setInfo();
    void infoBFS(MatrizVertice*, int*, vector<int>*, vector<MatrizVertice*>*, vector<vector<MatrizVertice*>>*, int);
    string BFSAuxiliar(int, vector<MatrizVertice*>*);
    int BFSMaiorDistancia(MatrizVertice*);

    //Info
    int getNVertices();
    int getNArestas();
    int getGrauMinimo();
    int getGrauMaximo();
    double getGrauMedio();
    int getGrauMediana();
    int getNComponentes();

    void setNVertices(int);
    void setNArestas(int);
    void setGrauMinimo(int);
    void setGrauMaximo(int);
    void setGrauMedio(double);
    void setGrauMediana(int);
    void setNComponentes(int);

    int nVertices;
    int nArestas;
    int grauMinimo;
    int grauMaximo;
    double grauMedio;
    int grauMediana;
    int nComponentes;
};

#endif