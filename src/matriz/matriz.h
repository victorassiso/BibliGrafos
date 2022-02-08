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

    // void info();
    int distancia(int r1, int r2);
    // int diametro();
    // void arvoreBFS(int);
    // void arvoreDFS(int);
  
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

};

#endif