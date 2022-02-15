#ifndef LISTA_H
#define LISTA_H

#include "listaVertice.h"
#include "listaVizinho.h"
#include "listaEstrutura.h"
#include "../arvore/arvore.h"
#include "../heap/minHeap.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <iomanip>

#define INFINITO    100000000000000000000
class Lista: public ListaEstrutura
{

  public:
    Lista(string inputFile);
    ~Lista();
    
    void info(string arquivoDestino);
    int distanciaBFS(int r1, int r2); // BFS
    int diametroBFS(); // BFS
    void arvoreBFS(int raizRotulo, string arquivoDestino);
    void arvoreDFS(int raizRotulo, string arquivoDestino);
    int caminhoMinimo(int r1, int r2, string arquivoDestino);
    
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

    // Métodos Auxiliares
    string info2();
    string info3(vector<vector<ListaVertice*>>* componentes);
    void desmarcarTodosOsVertices();
    int caminhoBFS(int r1, int r2, string arquivoDestino);
    int caminhoDijkstra(int r1, int r2, string arquivoDestino);
    int grau(ListaVertice *vertice);
};

#endif
