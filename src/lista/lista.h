#ifndef LISTA_H
#define LISTA_H

#include "listaVertice.h"
#include "listaVizinho.h"
#include "listaEstrutura.h"
#include "../arvore/arvore.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <iomanip>

class Lista: public ListaEstrutura
{

  public:
    Lista(string inputFile);
    ~Lista();
    
    //T1:
    void info(string arquivoDestino);
    int distanciaSemPeso(int r1, int r2); // BFS
    int diametroSemPeso(); // BFS
    void arvoreBFS(int raizRotulo, string arquivoDestino);
    void arvoreDFS(int raizRotulo, string arquivoDestino);
    
    // T2:
    //int distanciaPesosPositivos(int r1, int r2); // Dijkstra
    //int distanciaPesosNegativos(int r1, int r2); // Floyd-Warshall ou Bellman-Ford
    //int distanciaSemPeso(int r1); // BFS
    //int distanciaPesosPositivos(int r1); // Dijkstra
    //int distanciaPesosNegativos(int r1); // Floyd-Warshall ou Bellman-Ford
    
  private:
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

    //Métodos Auxiliares
    string info2();
    string info3(vector<vector<ListaVertice*>>* componentes);
    // [DEBUG] void debugDFS(string acao,Noh* uNoh, Noh* sNoh, vector<Noh*> pNoh);
};

#endif
