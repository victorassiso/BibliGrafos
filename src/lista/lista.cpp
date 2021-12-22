#include "lista.h"

Lista::Lista(string nomeArquivo)
{
  int arquivo_V1, arquivo_V2;

  arquivo.open(nomeArquivo, fstream::in);

  if (!arquivo.is_open())
  {
    cout << "Arquivo nao existe." << endl;
    return;
  }

  int i = 0;
  while (arquivo.good())
  {
    arquivo >> arquivo_V1 >> arquivo_V2;
    int rotulo1 = arquivo_V1;
    int rotulo2 = arquivo_V2;
    Vertice *v1 = inserirVertice(rotulo1);
    Vertice *v2 = inserirVertice(rotulo2);
    inserirVizinho(v1, v2);
    inserirVizinho(v2, v1);
  }
  arquivo.close();
}

Lista::~Lista(){}

Vertice* Lista::inserirVertice(int rotulo)
{
  Vertice* verticeExiste = buscaVertical(rotulo);
  if (!verticeExiste)
  {
    Vertice* new_vertice = new Vertice(rotulo);
    vetor_vertices.push_back(new_vertice);

    return new_vertice;
  }
  else
  {
    return verticeExiste;
  }
}

Vertice* Lista::buscaVertical(int rotulo)
{
  if (vetor_vertices.size() < 1)
    return nullptr;
  
  for (int i = 0; i < vetor_vertices.size(); i++) {
    if (rotulo == vetor_vertices.at(i)->getRotulo())
      return vetor_vertices.at(i);
  }

  return nullptr;
}


//Atribui-se v2 como vizinho de v1
void Lista::inserirVizinho(Vertice* v1, Vertice* v2)
{
  Vizinho* new_vizinho = new Vizinho(v2);

  //Procura-se o ultimo vizinho de v1
  Vizinho* ultimoVizinho = buscaHorizontal(v1);
  
  if (!ultimoVizinho){
    v1->setVizinho(new_vizinho);
  }
  else {
    ultimoVizinho->setVizinho(new_vizinho);
  }

}



Vizinho* Lista::buscaHorizontal(Vertice* v)
{
  if (!v->getVizinho()){
    return nullptr;
  }
  
  Vizinho* iterator = v->getVizinho();
  while (iterator->getVizinho())
  {
    iterator = iterator->getVizinho();
  };

  return iterator;
}


void Lista::imprimirLista()
{
  Vizinho* iterator;
  for (int i = 0; i < vetor_vertices.size(); i++) {
    cout << vetor_vertices.at(i)->getRotulo();

    iterator = vetor_vertices.at(i)->getVizinho();
    while(iterator)
    {
      cout << " --> " << iterator->getVertice()->getRotulo();
      iterator = iterator->getVizinho();
    }

    cout << endl;
  }
}
