#include "lista.h"

Lista::Lista(string nomeArquivo): ListaEstrutura(nomeArquivo){}
Lista::~Lista(){}

void Lista::info()
{
  setInfo();
  ofstream outfile("../../output/grafoInfo.txt");

  outfile << "Número de Vértices: " << getNVertices() << endl;
  outfile << "Número de Arestas: " << getNArestas() << endl;
  outfile << "Grau Mínimo: " << getGrauMinimo() << endl;
  outfile << "Grau Máximo: " << getGrauMaximo() << endl;
  outfile << "Grau Médio: " << getGrauMedio() << endl;
  outfile << "Grau Mediana: " << getGrauMediana() << endl;

  outfile.close();
}

void Lista::setInfo()
{
  Vizinho* iterator;
  vector<int> vetor_grau;
  int grau = 0;
  int nA = 0;

  for (int i = 0; i < Lista::vetor_vertices.size(); i++) {
    iterator = vetor_vertices.at(i)->getVizinho();
    while (iterator) {//caso vizinho nao seja nulo
      grau++;
      nA++;
      iterator = iterator->getVizinho();
    }
    vetor_grau.push_back(grau);
    grau = 0;
  }
    sort(vetor_grau.begin(), vetor_grau.end());

    setNVertices(vetor_vertices.size());
    setNArestas(nA/2);
    setGrauMinimo(vetor_grau.front());
    setGrauMaximo(vetor_grau.back());
    setGrauMedio(nA/(double)nVertices);

    if (vetor_grau.size() % 2 != 0) 
      setGrauMediana(vetor_grau.at(vetor_grau.size() / 2));
    else
      setGrauMediana((vetor_grau.at((vetor_grau.size()-1)/2) + vetor_grau.at((vetor_grau.size())/2))/2);
}

void Lista::setNVertices(int nVe) {nVertices = nVe;}
void Lista::setNArestas(int nA) {nArestas = nA;}
void Lista::setGrauMinimo(int gminimo) {grauMinimo = gminimo;}
void Lista::setGrauMaximo(int gmaximo) {grauMaximo = gmaximo;}
void Lista::setGrauMedio(double gmedio) {grauMedio = gmedio;}
void Lista::setGrauMediana(int gmediana) {grauMediana = gmediana;}

int Lista::getNVertices() {return nVertices;}
int Lista::getNArestas() {return nArestas;}
int Lista::getGrauMinimo() {return grauMinimo;}
int Lista::getGrauMaximo() {return grauMaximo;}
double Lista::getGrauMedio() {return grauMedio;}
int Lista::getGrauMediana() {return grauMediana;}

int Lista::distancia(int r1, int r2)
{
  //passar tudo pra false

  Vertice* raiz = this->buscaVertical(r1);
  if (!raiz){
    cout << "Vertice não encontrado." << endl;
    return -1;
  }
  
  vector<Vertice*> descobertos; //Fila
  Vertice* root = raiz; 
  Vertice* atual = raiz;
  
  Vizinho* iterator = raiz->getVizinho();
  
  descobertos.push_back(atual);
  int nivel = 0;
  root->setNivel(nivel);

  while(descobertos.size() > 0){
    
    while(iterator)
    {
      atual = iterator->getVertice();
      iterator = iterator->getVizinho();
      //Se status= false || nao está na lista
      if ( !atual->getStatus() && find(descobertos.begin(), descobertos.end(), atual) == descobertos.end()) {
        descobertos.push_back(atual);
        atual->setNivel(root->getNivel()+1);
        if(atual->getRotulo() == r2)
          return atual->getNivel();
      }
    }
    root->setStatus(true);

    descobertos.erase(descobertos.begin());
    
    if (descobertos.size() > 0) {
      root = descobertos.at(0);
      atual = root;
      iterator = root->getVizinho();
    }
  }
  return -1;
}

void Lista::BFS(int rotulo)
{
  ofstream outfile("../../output/BFS.txt");

  outfile << "BFS:" << endl;

  outfile << "+---------+------+-------+" << endl;
  outfile << "| Vértice | Pai  | Nível |" << endl;
  outfile << "+---------+------+-------+" << endl;

  //passar tudo pra false

  Vertice* raiz = this->buscaVertical(rotulo);

  vector<Vertice*> descobertos; //Fila
  Vertice* root = raiz; 
  Vertice* atual = raiz; 
  Vizinho* iterator = raiz->getVizinho();
  root->setNivel(0);
  descobertos.push_back(atual);

  outfile << "|\t\t" << rotulo << "\t\t|\t\tNull\t|\t\t" << root->getNivel() <<"\t\t|" << endl;

  while(descobertos.size() > 0){
    
    while(iterator)
    {
      atual = iterator->getVertice();
      iterator = iterator->getVizinho();

      //Se status= false || nao está na lista
      if ( !atual->getStatus() && find(descobertos.begin(), descobertos.end(), atual) == descobertos.end()) {
        
        descobertos.push_back(atual);
        atual->setPai(root);
        atual->setNivel(root->getNivel()+1);
        outfile << "|\t\t" << atual->getRotulo() << "\t\t|\t\t" << atual->getPai()->getRotulo() << "\t\t|\t\t" << atual->getNivel() <<"\t\t|" << endl;
      }
    }
    root->setStatus(true);

    descobertos.erase(descobertos.begin());
    
    if (descobertos.size() > 0) {
      root = descobertos.at(0);
      atual = root;
      iterator = root->getVizinho();
    } 
  }
}