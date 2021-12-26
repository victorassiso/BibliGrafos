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
    Floresta BFS(int);
    void DFS(int);
  
  private:
    fstream arquivo;

    //Outros
    void buscaEApaga(vector<MatrizVertice*>*, MatrizVertice*);
    string setInfo();
    void infoBFS(MatrizVertice*, int*, vector<int>*, vector<MatrizVertice*>*, vector<vector<MatrizVertice*>>*, int);
    string BFSAuxiliar(int, vector<MatrizVertice*>*);
    int BFSMaiorDistancia(MatrizVertice*);

    //Arvore
    Arvore* criaArvoreNova(int rotuloRaiz);

    Arvore* getArvore(int indice);
    vector<Arvore*> getArvores();

    // void infoFLoresta();
    string infoArvore(Noh* raiz);

    //Info
    int getNVertices();
    int getNArestas();
    int getGrauMinimo();
    int getGrauMaximo();
    double getGrauMedio();
    int getGrauMediana();
    vector<int> getVetorTamanhoComponentes();
    int getNComponentes();

    void setNArestas(int);
    void setGrauMinimo(int);
    void setGrauMaximo(int);
    void setGrauMedio(double);
    void setGrauMediana(int);
    void setVetorTamanhoComponentes(vector<int>);
    void setNComponentes(int);

    int nArestas;
    int grauMinimo;
    int grauMaximo;
    double grauMedio;
    int grauMediana;
    vector<int> vetorTamanhoComponentes;
    vector<Arvore*> arvores;
    int nComponentes;
};

#endif