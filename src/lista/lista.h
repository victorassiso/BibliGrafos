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

    //Outros
    void buscaEApaga(vector<Vertice*>*, Vertice*);
    string setInfo();
    string infoAuxiliar(int*, vector<Vertice*>*);
    string BFSAuxiliar(int, vector<Vertice*>*);
    int BFSMaiorDistancia(Vertice*);
    void inexplorar();

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
