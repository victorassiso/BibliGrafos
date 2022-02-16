#include <sys/types.h>
#include <unistd.h>
#include "src/lista/lista.h"
#include "src/matriz/matriz.h"

int main() {
  Lista lista("input/txt/grafo_T2.txt");
  lista.imprimirEstruturaLista(); // [extra] [somente Lista]

  lista.caminhoMinimo(1, 9, "output/CM.txt");

  return 0;
}