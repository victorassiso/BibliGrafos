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
    fstream arquivo;
  
  protected:
    vector<vector<bool>> matriz;
    vector<MatrizVertice*> vetor_vertices;

    MatrizEstrutura(string);
    ~MatrizEstrutura();

    int inserirVertice(int);  
    void inserirAresta(int, int);  
    MatrizVertice* buscaVertical(int rotulo, int* indice);

    vector<vector<bool>> getMatriz();

};
#endif
