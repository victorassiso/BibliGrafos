#include "listaEstrutura.h"

// Método construtor da lista de adjacência
ListaEstrutura::ListaEstrutura(string arquivoOrigem) {
  cout << "A Lista está sendo construída..."<< endl;

  int rotulo1, rotulo2;
  
  fstream arquivo;
  arquivo.open(arquivoOrigem, fstream::in);

  if (!arquivo.is_open())
  {
    cout << "Arquivo nao existe." << endl;
    return;
  }

  int nVertices;
  arquivo >> nVertices;

  this->setNVertices(nVertices);

  while (arquivo.good())
  {
    arquivo >> rotulo1 >> rotulo2;
    ListaVertice *v1 = inserirVertice(rotulo1);
    ListaVertice *v2 = inserirVertice(rotulo2);
    inserirVizinho(v1, v2);
    inserirVizinho(v2, v1);
  }
  arquivo.close();
  cout << "Lista construída com sucesso!" << endl << endl;
  // timenow = chrono::system_clock::to_time_t(chrono::system_clock::now());
  // cout << timenow << endl;
}

// Método destrutor da lista de adjacência
ListaEstrutura::~ListaEstrutura() { }

// Insere um novo vértice na lista de adjacência e retorna seu ponteiro
ListaVertice* ListaEstrutura::inserirVertice(int rotulo) {
  ListaVertice* verticeExiste = buscaVertical(rotulo);
  if (!verticeExiste)
  {
    ListaVertice* new_vertice = new ListaVertice(rotulo);
    vetor_vertices.push_back(new_vertice);

    return new_vertice;
  }
  else
  {
    return verticeExiste;
  }
}

// Busca vértice através de seu rótulo e retorna seu ponteiro
ListaVertice* ListaEstrutura::buscaVertical(int rotulo) {
  if (vetor_vertices.size() < 1)
    return nullptr;
  
  for (int i = 0; i < vetor_vertices.size(); i++) {
    if (rotulo == vetor_vertices.at(i)->getRotulo())
      return vetor_vertices.at(i);
  }

  return nullptr;
}

//Atribui v2 como vizinho de v1
void ListaEstrutura::inserirVizinho(ListaVertice* v1, ListaVertice* v2) {
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

// Retorna um ponteiro para o último vizinho de um vértice
Vizinho* ListaEstrutura::buscaHorizontal(ListaVertice* v) {
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

// Imprime a estrutura da lista de adjacência
void ListaEstrutura::imprimirEstruturaLista() {
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

// Define atributo nVertices (número de vértices na lista de adjacência)
void ListaEstrutura::setNVertices(int nVe) { nVertices = nVe; }
// Retorna valor inteiro nVertices (número de vértices na lista de adjacência)
int ListaEstrutura::getNVertices() { return nVertices; }