#include <sys/types.h>
#include <unistd.h>
#include "src/lista/lista.h"
#include "src/matriz/matriz.h"

int main() {
  Lista lista("input/txt/grafo_T2.txt");
  lista.imprimirEstruturaLista(); // [extra] [somente Lista]

  // lista.caminhoMinimo(1, 6, "output/CM2.txt");
  lista.arvoreMST(1, "output/MST.txt");

  return 0;
}