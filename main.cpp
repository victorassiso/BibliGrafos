#include "src/lista/lista.h"

void testeLista() {
  //Lista grafo("input/grafo_componentes.txt");
  //Lista grafo("input/grafo_T1.txt");
  Lista grafo("input/grafo_1.txt");
  //Lista grafo("input/grafo_lista2.txt");
  
  grafo.imprimirListaEstrutura();

  //grafo.info();
  //cout << grafo.distancia(8, 6) << endl;
  //cout << grafo.diametro() << endl;
  //grafo.BFS(2);
  //grafo.DFS(2);
}

int main() {
  
  testeLista();

  return 0;
}