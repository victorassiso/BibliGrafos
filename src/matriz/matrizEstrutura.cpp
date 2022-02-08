#include "matrizEstrutura.h"
#include <sys/types.h>
#include <unistd.h>

MatrizEstrutura::MatrizEstrutura(string nomeArquivo) {
  cout << "Matriz em construção..." << endl;

  // Inicializa Variáveis
  int arquivo_V1, arquivo_V2;
  int nVertices;
  int x = 0;
  fstream arquivo;

  // Verifica arquivo de input
  arquivo.open(nomeArquivo, fstream::in);
  if (!arquivo.is_open())
  {
    cout << "Arquivo nao existe." << endl;
    return;
  }

  // Lê primeira linha do arquivo e seta número de vértices do grafo
  arquivo >> nVertices;
  setNVertices(nVertices);

  // Define a matriz em formato triangular
  // (número de colunas de cada linha é igual ao indice da linha)
  matriz.resize(nVertices);
  for (int i=0; i<nVertices; i++)
    matriz.at(i).resize(i);
  
  // Lê arquivo txt e insere os vértices na matriz
  while (arquivo.good()) {
    arquivo >> arquivo_V1 >> arquivo_V2;
    int indiceV1 = inserirVertice(arquivo_V1);
    int indiceV2 = inserirVertice(arquivo_V2);
    inserirAresta(indiceV1, indiceV2);
    inserirAresta(indiceV2, indiceV1);
  };

  arquivo.close();

  cout << "Construção da Matriz concluída." << endl;
}

MatrizEstrutura::~MatrizEstrutura(){}

// Insere um novo vértice no vetor_vertices caso ele já não exista
int MatrizEstrutura::inserirVertice(int rotulo)
{
  int indice;
  
  // Não permite que vértices repetidos sejam adicionados 
  MatrizVertice* verticeExiste = buscaVertical(rotulo, &indice);//2º
  if (!verticeExiste)
  {
    // Cria vértice novo, o insere no vetor_vertices e retorna seu indice
    MatrizVertice* new_vertice = new MatrizVertice(rotulo);
    vetor_vertices.push_back(new_vertice);
    return vetor_vertices.size()-1;
  }
  else
  {
    // Caso vértice já exista, retorna seu indice no vetor_vertices
    return indice;
  }
}

// Busca e retorna vértice que armazena rótulo passado por parâmetro
// Retorna indice do vértice no vetor_vertices por parâmetro
// Retorna nullptr caso não exista
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

// Busca e retorna o vértice que armazena o rótulo passado por parâmetro
// Retorna nullptr caso não exista
MatrizVertice* MatrizEstrutura::buscaVertical(int rotulo)
{
  int i = 0;
  if (vetor_vertices.size() < 1) {
    return nullptr;
  }
  
  for (i = 0; i < vetor_vertices.size(); i++) {
    if (rotulo == vetor_vertices.at(i)->getRotulo()){
      return vetor_vertices.at(i);
    }
  }
  return nullptr;
}

// Seta em true coordenada na matriz que liga dois vértices
void MatrizEstrutura::inserirAresta(int indice1, int indice2)
{
  if (indice1 == indice2)
    return;

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

// Imprime Estrutura da matriz
void MatrizEstrutura::imprimirMatrizEstrutura() {

  int i;
  int j;
  cout << "       ↓        ↓" << endl;
  cout << "  | rótulo | índice |" << endl;
  for (i = 0; i < matriz.size(); i++) {
    cout << "  |    " << vetor_vertices.at(i)->getRotulo() << "   |    " << i << "   |";
    for (j = 0; j < matriz.at(i).size(); j++) {
      cout << " " << matriz.at(i).at(j) << " |";
    }
    cout << endl;
  }

  cout << "  +--------+--------+";
  for (int i = 0; i < matriz.size(); i++) {
    cout << "---+";
  }

  cout << endl << "→ |   --   | índice |";
  for (int i = 0; i < matriz.size(); i++) {
    cout << " " << i << " |";
  }
  cout << endl;

  cout << "  +--------+--------+";
  for (int i = 0; i < matriz.size(); i++) {
    cout << "---+";
  }

  cout << endl << "→ | rótulo |   --   |";
  for (int i = 0; i < matriz.size(); i++) {
    cout << " " << vetor_vertices.at(i)->getRotulo() << " |";
  }
  cout << endl;
}

void MatrizEstrutura::setNVertices(int nVe) { nVertices = nVe; }
int MatrizEstrutura::getNVertices() { return nVertices; }
