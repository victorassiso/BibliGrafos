#include "matrizEstrutura.h"

MatrizEstrutura::MatrizEstrutura(string nomeArquivo)
{
  int arquivo_V1, arquivo_V2;

  arquivo.open(nomeArquivo, fstream::in);

  if (!arquivo.is_open())
  {
    cout << "Arquivo nao existe." << endl;
    return;
  }

  int nVertices;
  arquivo >> nVertices;

  matriz.resize(nVertices);
  for (int i=0; i<nVertices; i++)
    matriz.at(i).resize(i);
  
  
  while (arquivo.good()) {
    arquivo >> arquivo_V1 >> arquivo_V2;
    int indiceV1 = inserirVertice(arquivo_V1);
    int indiceV2 = inserirVertice(arquivo_V2);
    inserirAresta(indiceV1, indiceV2);
    inserirAresta(indiceV2, indiceV1);
  };
  arquivo.close();
}

MatrizEstrutura::~MatrizEstrutura(){}

int MatrizEstrutura::inserirVertice(int rotulo)
{
  int indice;
  MatrizVertice* verticeExiste = buscaVertical(rotulo, &indice);//2º
  if (!verticeExiste)
  {
    MatrizVertice* new_vertice = new MatrizVertice(rotulo);
    vetor_vertices.push_back(new_vertice);
    return vetor_vertices.size()-1;
  }
  else
  {
    return indice;
  }
}

MatrizVertice* MatrizEstrutura::buscaVertical(int rotulo, int* indice)
{
  int i = 0;
  if (vetor_vertices.size() < 1) {
    *indice = -1;
    return nullptr;
  }
  
  for (i = 0; i < vetor_vertices.size(); i++) {
    if (rotulo == vetor_vertices.at(i)->getRotulo()){
      *indice = i;
      return vetor_vertices.at(i);

    }
  }


  return nullptr;
}

void MatrizEstrutura::inserirAresta(int indice1, int indice2)
{
  int maior;
  int menor;
  if (indice1 > indice2) {
    maior = indice1;
    menor = indice2;
  } else {
    maior = indice2;
    menor = indice1;
  }

  matriz.at(maior).at(menor) = true;
}

void MatrizEstrutura::imprimirMatrizEstrutura()
{
  int j;
  for (int i = 0; i < matriz.size(); i++) {
    cout << "[" << i << "][0] -> | ";
    for (j = 0; j < matriz.at(i).size(); j++) {
      cout << "   " << matriz.at(i).at(j) << "   | ";
    }
    cout << "[" << i << "][" << j << "] |" << endl;
  }
}