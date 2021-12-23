#include "lista.h"

Lista::Lista(string nomeArquivo): ListaEstrutura(nomeArquivo){}
Lista::~Lista(){}

void Lista::info()
{
  string BFS = setInfo();
  ofstream outfile("output/grafoInfo.txt");

  outfile << "Número de Vértices: " << getNVertices() << endl;
  outfile << "Número de Arestas: " << getNArestas() << endl;
  outfile << "Grau Mínimo: " << getGrauMinimo() << endl;
  outfile << "Grau Máximo: " << getGrauMaximo() << endl;
  outfile << "Grau Médio: " << getGrauMedio() << endl;
  outfile << "Grau Mediana: " << getGrauMediana() << endl;
  outfile << "Número de Componentes conexas: " << getNComponentes() << endl;

  outfile << BFS << endl;

  outfile.close();
}

//setInfo(Antigo)
/*
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
*/

string Lista::setInfo()
{
  int nComp = 1;
  int nA = 0;
  int grau = 0;
  vector<int> vetor_grau;

  for (int i = 0; i < vetor_vertices.size(); i++) {
    vetor_vertices.at(i)->setStatus(false);
  }
  
  string outfile;
  
  outfile =  "+------------------------+\n";
  outfile += "|  Componentes Conexas   |\n";
  outfile += "+------------------------+\n";
  outfile += "|      Componente " + to_string(nComp) + "      |\n";
  outfile += "+---------+------+-------+\n";
  
  //passar tudo pra false

  Vertice* root = vetor_vertices.at(0);
  if (!root){
    cout << "Vertice não encontrado." << endl;
    return "";
  }
  
  vector<Vertice*> descobertos; //Fila
  vector<Vertice*> desconhecidos = vetor_vertices; //Fila
  Vertice* atual = root; 
  Vizinho* iterator = root->getVizinho();
  root->setNivel(0);
  descobertos.push_back(atual);
  this->buscaEApaga(&desconhecidos, atual);
  
  outfile += "|\t\t\t\t" + to_string(root->getRotulo()) + "\t\t\t\t|\n";

  while(descobertos.size() > 0){
    
    while(iterator)
    {
      atual = iterator->getVertice();
      iterator = iterator->getVizinho();
      nA++;
      grau++;
      //Se status= false || nao está na lista
      if ( !atual->getStatus() && find(descobertos.begin(), descobertos.end(), atual) == descobertos.end()) {
        descobertos.push_back(atual);
        this->buscaEApaga(&desconhecidos, atual);
        atual->setPai(root);
        atual->setNivel(root->getNivel()+1);
        outfile += "|\t\t\t\t" + to_string(atual->getRotulo()) + "\t\t\t\t|\n";
      }
    }
    vetor_grau.push_back(grau);
    grau = 0;

    root->setStatus(true);

    descobertos.erase(descobertos.begin());
    
    if (descobertos.size() > 0) {
      root = descobertos.at(0);
      atual = root;
      iterator = root->getVizinho();
    }
  }

    if (desconhecidos.size() > 0) {
      nComp++;
      outfile += infoAuxiliar(&nComp, &desconhecidos);
    }
  
  /////////////////////////////
  setNVertices(vetor_vertices.size());
  setNArestas(nA/2);
  setGrauMinimo(vetor_grau.front());
  setGrauMaximo(vetor_grau.back());
  setGrauMedio(nA/(double)nVertices);
  
  sort(vetor_grau.begin(), vetor_grau.end());
  
  if (vetor_grau.size() % 2 != 0) 
    setGrauMediana(vetor_grau.at(vetor_grau.size() / 2));
  else
    setGrauMediana((vetor_grau.at((vetor_grau.size()-1)/2) + vetor_grau.at((vetor_grau.size())/2))/2);

  setNComponentes(nComp);

  return outfile;
}

void Lista::setNVertices(int nVe) {nVertices = nVe;}
void Lista::setNArestas(int nA) {nArestas = nA;}
void Lista::setGrauMinimo(int gminimo) {grauMinimo = gminimo;}
void Lista::setGrauMaximo(int gmaximo) {grauMaximo = gmaximo;}
void Lista::setGrauMedio(double gmedio) {grauMedio = gmedio;}
void Lista::setGrauMediana(int gmediana) {grauMediana = gmediana;}
void Lista::setNComponentes(int nComp) {nComponentes = nComp;}

int Lista::getNVertices() {return nVertices;}
int Lista::getNArestas() {return nArestas;}
int Lista::getGrauMinimo() {return grauMinimo;}
int Lista::getGrauMaximo() {return grauMaximo;}
double Lista::getGrauMedio() {return grauMedio;}
int Lista::getGrauMediana() {return grauMediana;}
int Lista::getNComponentes() {return nComponentes;}

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
  int nComponente = 1;
  ofstream outfile("output/BFS.txt");

  for (int i = 0; i < vetor_vertices.size(); i++) {
    vetor_vertices.at(i)->setStatus(false);
  }
  
  outfile << "BFS:" << endl;
  outfile << "+---------+------+-------+" << endl;
  outfile << "| Vértice | Pai  | Nível |" << endl;
  outfile << "+------------------------+" << endl;
  outfile << "|      Componente " << nComponente << "      |" << endl;
  outfile << "+---------+------+-------+" << endl;
  
  //passar tudo pra false

  Vertice* raiz = this->buscaVertical(rotulo);
  if (!raiz){
    cout << "Vertice não encontrado." << endl;
    return ;
  }
  
  vector<Vertice*> descobertos; //Fila
  vector<Vertice*> desconhecidos = vetor_vertices; //Fila
  Vertice* root = raiz; 
  Vertice* atual = raiz; 
  Vizinho* iterator = raiz->getVizinho();
  root->setNivel(0);
  descobertos.push_back(atual);
  this->buscaEApaga(&desconhecidos, atual);
  
  outfile << "|\t\t" << rotulo << "\t\t|\t\tNull\t|\t\t" << root->getNivel() <<"\t\t|" << endl;

  while(descobertos.size() > 0){
    
    while(iterator)
    {
      atual = iterator->getVertice();
      iterator = iterator->getVizinho();

      //Se status= false || nao está na lista
      if ( !atual->getStatus() && find(descobertos.begin(), descobertos.end(), atual) == descobertos.end()) {
        descobertos.push_back(atual);
        this->buscaEApaga(&desconhecidos, atual);
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
  
    if (desconhecidos.size() > 0) {
      outfile << BFSAuxiliar(nComponente+1, &desconhecidos);
    }
  
  outfile.close();
}

int Lista::diametro()
{
  int maiorDiametro = 0;
  int diametroAtual;

  for (int i=0; i<vetor_vertices.size(); i++) {
    diametroAtual = BFSMaiorDistancia(vetor_vertices.at(i));
    if (maiorDiametro < diametroAtual) {
      maiorDiametro = diametroAtual;
    }
  }

  return maiorDiametro;
}

int Lista::BFSMaiorDistancia(Vertice* raiz)
{
  //passar tudo pra false

  vector<Vertice*> descobertos; //Fila
  Vertice* root = raiz; 
  Vertice* atual = raiz; 
  Vizinho* iterator = raiz->getVizinho();
  root->setNivel(0);
  descobertos.push_back(atual);

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

  return root->getNivel()+1;
}

void Lista::buscaEApaga(vector<Vertice*>* vetor, Vertice* vertice)
{
  if (vetor->size() < 1)
    return ;
  
  for (int i = 0; i < vetor->size(); i++) {
    if (vertice == vetor->at(i)){
      vetor->erase(vetor->begin()+i);
      return ;
    }
  }

  return ;
}

string Lista::BFSAuxiliar(int nComp, vector<Vertice*>* desconhecidos)
{
  string outfile;
 
  outfile = "+------------------------+\n";
  outfile += "|      Componente " + to_string(nComp) + "      |\n";
  outfile + "+---------+------+-------+\n";
  
  //passar tudo pra false
  vector<Vertice*> descobertos;
  Vertice* root = desconhecidos->at(0);; 
  Vertice* atual = root; 
  Vizinho* iterator = root->getVizinho();
  root->setNivel(0);
  descobertos.push_back(atual);
  this->buscaEApaga(desconhecidos, atual);

  outfile += "|\t\t";
  outfile += to_string(root->getRotulo());
  outfile += "\t\t|\t\tNull\t|\t\t";
  outfile += to_string(root->getNivel());
  outfile += "\t\t|\n";

  while(descobertos.size() > 0){
    
    while(iterator)
    {
      atual = iterator->getVertice();
      iterator = iterator->getVizinho();

      //Se status= false || nao está na lista
      if ( !atual->getStatus() && find(descobertos.begin(), descobertos.end(), atual) == descobertos.end()) {
        descobertos.push_back(atual);
        this->buscaEApaga(desconhecidos, atual);

        atual->setPai(root);
        atual->setNivel(root->getNivel()+1);

        outfile += "|\t\t" + to_string(atual->getRotulo());
        outfile += "\t\t|\t\t" + to_string(atual->getPai()->getRotulo());
        outfile += "\t\t|\t\t" + to_string(atual->getNivel());
        outfile += "\t\t|\n";
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
    if (desconhecidos->size() > 0){
      nComp++;
      outfile += BFSAuxiliar(nComp, desconhecidos);
    }
    
  
  return outfile;
}

string Lista::infoAuxiliar(int* nComp, vector<Vertice*>* desconhecidos)
{
  string outfile;
  
  outfile =  "+------------------------+\n";
  outfile += "|      Componente " + to_string(*nComp) + "      |\n";
  outfile += "+---------+------+-------+\n";
  
  //passar tudo pra false
  vector<Vertice*> descobertos;
  Vertice* root = desconhecidos->at(0);; 
  Vertice* atual = root; 
  Vizinho* iterator = root->getVizinho();
  root->setNivel(0);
  descobertos.push_back(atual);
  this->buscaEApaga(desconhecidos, atual);

  outfile += "|\t\t" + to_string(root->getRotulo()) + "\t\t|\n";

  while(descobertos.size() > 0){
    
    while(iterator)
    {
      atual = iterator->getVertice();
      iterator = iterator->getVizinho();

      //Se status= false || nao está na lista
      if ( !atual->getStatus() && find(descobertos.begin(), descobertos.end(), atual) == descobertos.end()) {
        descobertos.push_back(atual);
        this->buscaEApaga(desconhecidos, atual);
        outfile += "|\t\t" + to_string(atual->getRotulo()) + "\t\t|\n";
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
    if (desconhecidos->size() > 0){
      *nComp++;
      outfile += infoAuxiliar(nComp, desconhecidos);
    }
  
  return outfile;
}