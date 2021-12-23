#ifndef LISTA_H
#define LISTA_H

#include "listaVertice.h"
#include "listaVizinho.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

#include "listaEstrutura.h"

class Lista: public ListaEstrutura
{
  public:
    Lista(string);
    ~Lista();
    
    void info();
    int distancia(int r1, int r2);
    int diametro();
    void BFS(int);
    void DFS(int);
    
  private:
    fstream arquivo;

    //Auxiliares
    

    //Info
    int getNVertices();
    int getNArestas();
    int getGrauMinimo();
    int getGrauMaximo();
    double getGrauMedio();
    int getGrauMediana();

    void setNVertices(int);
    void setNArestas(int);
    void setGrauMinimo(int);
    void setGrauMaximo(int);
    void setGrauMedio(double);
    void setGrauMediana(int);

    void setInfo();

    int nVertices;
    int nArestas;
    int grauMinimo;
    int grauMaximo;
    double grauMedio;
    int grauMediana;
};

#endif
