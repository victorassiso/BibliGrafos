#include "src/lista/lista.h"
#include "src/matriz/matriz.h"

void testeLista() {
  //Lista grafo("input/grafo_componentes.txt");
  //Lista grafo("input/grafo_T1.txt");
  Lista grafo("input/grafo_1.txt");
  //Lista grafo("input/grafo_lista2.txt");
  
  //grafo.imprimirListaEstrutura();

  grafo.info();
  //cout << grafo.distancia(8, 6) << endl;
  //cout << grafo.diametro() << endl;
  //grafo.BFS(2);
  //grafo.DFS(2);
}

void testeMatriz() {
  Matriz grafo("input/txt/grafo_T1.txt");
  //grafo.imprimirMatrizEstrutura();
  grafo.BFS(2);
}

int main() {
  
  //testeLista();
  testeMatriz();

  return 0;
}