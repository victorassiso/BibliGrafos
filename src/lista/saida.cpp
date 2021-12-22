#include "saida.h"

Saida::Saida(string nomeArquivo): Lista(nomeArquivo)
{
  Vizinho* iterator;
  vector<int> vetor_grau;
  int grau = 0;
  int nA = 0;


  for (int i = 0; i < Lista::vetor_vertices.size(); i++)
  {
    iterator = vetor_vertices.at(i)->getVizinho();
    while (iterator)//caso vizinho nao seja nulo
    {
      grau++;
      nA++;
      iterator = iterator->getVizinho();
    }
    vetor_grau.push_back(grau);
    grau = 0;
  }
    sort(vetor_grau.begin(), vetor_grau.end());

    nVertices = vetor_vertices.size();
    nArestas = nA/2;
    grauMinimo = vetor_grau.front();
    grauMaximo = vetor_grau.back();
    grauMedio = nA/(double)nVertices;
    cout << "Debug: " << grauMedio << endl;

    if (vetor_grau.size() % 2 != 0) 
      grauMediana = vetor_grau.at(vetor_grau.size() / 2);
    else
      grauMediana = (vetor_grau.at((vetor_grau.size()-1)/2) + vetor_grau.at(vetor_grau.size()/2));

    cout << "Debug2: " << grauMedio << endl;
    
}

Saida::~Saida(){}

int Saida::getNumeroDeVertices()
{
  return nVertices;
}

int Saida::getNumeroDeArestas()
{
  return nArestas;
}

int Saida::getGrauMinimo()
{
  return grauMinimo;
}

int Saida::getGrauMaximo()
{
  return grauMaximo;
}

double Saida::getGrauMedio()
{
  return grauMedio;
}

int Saida::getMedianaDeGrau()
{
  return grauMediana;
}