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

string Lista::setInfo()
{
  vector<vector<Vertice*>> componentes;; //Vértices(rótulos) de cada componente

  //Inicia valores para BFS
  vector<Vertice*> desconhecidos = vetor_vertices;
  
  //Coloca todos os status em desconhecido
  for (int i = 0; i < vetor_vertices.size(); i++) {
    vetor_vertices.at(i)->setStatus(false);
  }
  
  //Cabeçalho
  string outfile = "\n** Componentes Conexas: **\n\n";
  
  //Declara variáveis Info
  vector<int> vetor_grau;
  int nA = 0;
  int nComp = 0;
  
  //Chama BFS para cada componente
  bool done = false;
  while(!done){
    infoBFS(desconhecidos.at(0), &nA, &vetor_grau, &desconhecidos, &componentes, nComp);//
    nComp++;
    
    //Info

    //Caso na haja mais vértices desconhecidos, sai do loop
    if (desconhecidos.size() < 1)
      done = true;
  };

  //String Componetes
  sort(componentes.rbegin(), componentes.rend(),
    [](vector<Vertice*> a, vector<Vertice*> b){
      return a.size() < b.size();
    });

  for (int i = 0; i < componentes.size(); i++) {
    outfile += "Componente: " + to_string(i+1);
    outfile += "\nTamanho: " + to_string(componentes.at(i).size());
    outfile += "\nVértices: ";

    for (int j = 0; j < componentes.at(i).size(); j++) {
      outfile += to_string(componentes.at(i).at(j)->getRotulo()) + ", ";
    }
    outfile += "\n\n";
  }
  
  sort(vetor_grau.begin(), vetor_grau.end());

  setNVertices(vetor_vertices.size());
  setNArestas(nA/2);
  setGrauMaximo(vetor_grau.back());
  setGrauMinimo(vetor_grau.front());
  setGrauMedio(nA/(double)nVertices);
  setNComponentes(nComp);

  if (vetor_grau.size() % 2 != 0) 
      setGrauMediana(vetor_grau.at(vetor_grau.size() / 2));
    else
      setGrauMediana((vetor_grau.at((vetor_grau.size()-1)/2) + vetor_grau.at((vetor_grau.size())/2))/2);

  return outfile;
}

void Lista::infoBFS(Vertice* raiz, int* nA, vector<int>* vetor_grau, vector<Vertice*>* desconhecidos, vector<vector<Vertice*>>* componentes, int nComp)
{
  
  vector<Vertice*> descobertos;
  vector<Vertice*> verticesComp;
  componentes->push_back(verticesComp);
  Vertice* root = raiz;//1
  Vertice* atual = root; //1
  Vizinho* iterator = root->getVizinho();//2
  descobertos.push_back(atual);//descobertos {1}
  componentes->at(nComp).push_back(atual);
  this->buscaEApaga(desconhecidos, atual);
  int grau = 0;


  while(descobertos.size() > 0){
    
    while(iterator)
    {
      atual = iterator->getVertice();//2//4//6
      iterator = iterator->getVizinho();//4//6//null
      *nA = *nA + 1;//1
      grau ++;//1
      
      //Se status= false || nao está na lista
      if ( !atual->getStatus() && find(descobertos.begin(), descobertos.end(), atual) == descobertos.end()) {
        descobertos.push_back(atual);// descobertos
        componentes->at(nComp).push_back(atual);
        this->buscaEApaga(desconhecidos, atual);
      }
    }
    root->setStatus(true);
    vetor_grau->push_back(grau);
    grau = 0;
    descobertos.erase(descobertos.begin());
    
    if (descobertos.size() > 0) {
      root = descobertos.at(0);
      atual = root;
      iterator = root->getVizinho();
    }
  }
}

void Lista::BFS(int rotulo)
{
  // cout << "BFS em andamento..." << endl;
  // auto timenow = chrono::system_clock::to_time_t(chrono::system_clock::now());
  // cout << timenow << endl;
  int nComponente = 1;
  ofstream outfile("output/BFS.txt");

  //Coloca todos os status em desconhecido
  for (int i = 0; i < vetor_vertices.size(); i++) {
    vetor_vertices.at(i)->setStatus(false);
  }
  
  outfile << "BFS:" << endl;
  outfile << "+---------+------+-------+" << endl;
  outfile << "| Vértice | Pai  | Nível |" << endl;
  outfile << "+------------------------+" << endl;
  outfile << "|      Componente " << nComponente << "      |" << endl;
  outfile << "+---------+------+-------+" << endl;

  Vertice* raiz = this->buscaVertical(rotulo);
  if (!raiz){
    cout << "Vertice não encontrado." << endl;
    return ;
  }
  
  vector<Vertice*> descobertos; //Fila
  vector<Vertice*> desconhecidos = vetor_vertices;
  Vertice* root = raiz; 
  Vertice* atual = raiz; 
  Vizinho* iterator = raiz->getVizinho();
  root->setNivel(0);
  root->setPai(nullptr);
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
  // cout << "BFS concluída." << endl;
  
}

string Lista::BFSAuxiliar(int nComp, vector<Vertice*>* desconhecidos)
{
  string outfile;
 
  outfile = "+------------------------+\n";
  outfile += "|      Componente " + to_string(nComp) + "      |\n";
  outfile + "+---------+------+-------+\n";
  
  vector<Vertice*> descobertos;
  Vertice* root = desconhecidos->at(0);; 
  Vertice* atual = root; 
  Vizinho* iterator = root->getVizinho();
  root->setNivel(0);
  root->setPai(nullptr);
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

void Lista::DFS(int rotulo)
{
  int nComponente = 1;
  ofstream outfile("output/DFS.txt");

  //Coloca todos os status em desconhecido
  for (int i = 0; i < vetor_vertices.size(); i++) {
    vetor_vertices.at(i)->setStatus(false);
  }
  
  outfile << "DFS:" << endl;
  outfile << "+---------+------+-------+" << endl;
  outfile << "| Vértice | Pai  | Nível |" << endl;
  outfile << "+------------------------+" << endl;
  outfile << "|      Componente " << nComponente << "      |" << endl;
  outfile << "+---------+------+-------+" << endl;

  Vertice* raiz = this->buscaVertical(rotulo);
  if (!raiz){
    cout << "Vertice não encontrado." << endl;
    return ;
  }
  
  vector<Vertice*> descobertos; //Pilha
  vector<Vertice*> desconhecidos = vetor_vertices;
  Vertice* atual = raiz; //2
  Vertice* root = raiz; //2
  Vizinho* iterator = raiz->getVizinho(); //1
  atual->setNivel(0);
  atual->setPai(nullptr);
  descobertos.push_back(atual);

  this->buscaEApaga(&desconhecidos, atual);
  int i = 0;
  outfile << "|		" << rotulo << "   | Null  |   " << raiz->getNivel() <<"   |" << endl;
  while(descobertos.size() > 0) {
    
    if(iterator){//iterator != null
      if (!iterator->getVertice()->getStatus() && find(descobertos.begin(), descobertos.end(), iterator->getVertice()) == descobertos.end()) {
        atual = iterator->getVertice();//1
        iterator = atual->getVizinho();//2
        descobertos.push_back(atual);
        atual->setPai(root);
        atual->setNivel(root->getNivel()+1);
        root = atual;
        this->buscaEApaga(&desconhecidos, atual);
        outfile << "|\t\t" << atual->getRotulo() << "\t\t|\t\t" << atual->getPai()->getRotulo() << "\t\t|\t\t" << atual->getNivel() <<"\t\t|" << endl;
      } else {//iterator descoberto ou explorado
        iterator = iterator->getVizinho();
      }
    } else {
      if(atual != raiz) {
        atual->setStatus(true);          
        descobertos.pop_back();
        root = atual->getPai();
        atual = atual->getPai();//5
        if (atual){
          iterator = atual->getVizinho();//2//1//1//5//4//1
          atual->setPai(atual->getPai());
        }
        
        if(desconhecidos.size() > 0)
          this->buscaEApaga(&desconhecidos, atual);
      } else {
        descobertos.pop_back();
      }

    }
  }
  outfile.close();
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
  cout << "Iniciando cálculo da distância..." << endl;
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
  cout << "Término do cálculo da distância.." << endl;
  return -1;
}

void Lista::buscaEApaga(vector<Vertice*>* vetor, Vertice* vertice)
{
  if (vetor->size() < 1)
  {
    cout << "vetor vazio." << endl;
    return ;
  }
  
  for (int i = 0; i < vetor->size(); i++) {
    if (vertice == vetor->at(i)){
      vetor->erase(vetor->begin()+i);
      return ;
    }
  }

  return ;
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
  vector<Vertice*> descobertos; //Fila
  Vertice* root = raiz; 
  Vertice* atual = raiz; 
  Vizinho* iterator = raiz->getVizinho();
  root->setNivel(0);
  atual->setPai(nullptr);

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

