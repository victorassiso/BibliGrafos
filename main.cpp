#include <sys/types.h>
#include <unistd.h>
#include "src/lista/lista.h"
#include "src/matriz/matriz.h"

int main() {
  // Classes Disponíveis:
  // - Lista
  // - Matriz
  
  // Métodos disponíveis:
  // - info
  // - ArvoreBFS
  // - ArvoreDFS
  // - distanciaSemPeso
  // - diametroSemPeso
  // - imprimirEstruturaLista [extra] [somente Lista]
  // - imprimirEstruturaMatriz [extra] [somente Matriz]


  // Exemplo: 
  
  // Constrói grafo usando estrutura de lista
  // Lista lista("input/txt/grafo_lista2.txt");

  // lista.info("output/grafo_lista2_info.txt");
  // lista.arvoreBFS(1, "output/grafo_lista2_arvoreBFS.txt");
  // lista.arvoreDFS(1, "output/grafo_lista2_arvoreDFS.txt");
  // lista.distanciaSemPeso(1, 9);
  // lista.diametroSemPeso();
  // lista.imprimirEstruturaLista(); // [extra] [somente Lista]

  // Constrói grafo usando estrutura de matriz;
  Matriz matriz("input/txt/grafo_DFS.txt");

  matriz.imprimirMatrizEstrutura();
  // int D;

  // Distância
  // D = matriz.distancia(1, 3);
  // cout << "Distancia: " << D << endl;
  
  // Diâmetro
  // D = matriz.diametro();
  // cout << "Diâmetro: " << D << endl;
  
  // matriz.arvoreBFS(1, "output/BFS_Matriz_lista2.txt");
  matriz.arvoreDFS(1, "output/DFS");
  // matriz.info("output/INFO.txt");

  return 0;
}