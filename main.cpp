#include <sys/types.h>
#include <unistd.h>
#include "src/lista/lista.h"
#include "src/matriz/matriz.h"

void testeLista() {

  char x;
  Lista grafo3("input/txt/grafo_3.txt");

  // Raiz 1
  grafo3.DFS(1);
  cin >> x;

  // Raiz 2
  grafo3.DFS(2);
  cin >> x;

  // Raiz 3
  grafo3.DFS(3);
  cin >> x;




}

void testeMatriz() {
  Matriz grafo("input/txt/grafo_1.txt");

}

int main() {
  
  testeLista();
  // testeMatriz();

  return 0;
}