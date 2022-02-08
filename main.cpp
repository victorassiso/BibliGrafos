#include <sys/types.h>
#include <unistd.h>
#include "src/lista/lista.h"
// #include "src/matriz/matriz.h"

int main() {
  // Classes Disponíveis:
  // - Lista
  // - Matriz
  
  // Métodos disponíveis para ambas as classes:
  // - info
  // - ArvoreBFS
  // - ArvoreDFS
  // - distanciaSemPeso
  // - diametroSemPeso
  // - imprimirEstruturaLista [extra] [somente Lista]
  // - imprimirEstruturaMatriz [extra] [somente Matriz]


  // Exemplo: 
  string input = "input/txt/grafo_lista2.txt";
  string output = "output/grafo_lista2.txt";
  
  // Constrói grafo usando estrutura de lista
  Lista lista(input);

  lista.info("output/grafo_lista2_info.txt");
  lista.arvoreBFS(1, "output/grafo_lista2_arvoreBFS.txt");
  lista.arvoreDFS(1, "output/grafo_lista2_arvoreDFS.txt");
  lista.distanciaSemPeso(1, 9);
  lista.diametroSemPeso();
  lista.imprimirEstruturaLista(); // [extra] [somente Lista]

  // Constrói grafo usando estrutura de matriz;
  // Matriz matriz(input);



  return 0;
}