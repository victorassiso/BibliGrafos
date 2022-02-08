#ifndef MATRIZESTRUTURA_H
#define MATRIZESTRUTURA_H

#include "matrizVertice.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class MatrizEstrutura
{   
  public:
    void imprimirMatrizEstrutura();
  
  private: 
    // INFO
    int nVertices;

  protected:
    MatrizEstrutura(string);
    ~MatrizEstrutura();
    
    vector<vector<bool>> matriz;
    vector<MatrizVertice*> vetor_vertices;
    
    // Métodos Auxiliares
    int inserirVertice(int);  
    void inserirAresta(int, int);  
    MatrizVertice* buscaVertical(int rotulo, int* indice);
    MatrizVertice* buscaVertical(int rotulo);
    
    // INFO
    void setNVertices(int);
    int getNVertices();

};
#endif
