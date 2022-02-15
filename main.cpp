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
  Lista lista("input/txt/grafo_T2.txt");
  lista.imprimirEstruturaLista(); // [extra] [somente Lista]

  // lista.info("output/lista_INFO.txt");
  // lista.arvoreBFS(1, "output/lista_BFS.txt");
  // lista.arvoreDFS(1, "output/lista_DFS.txt");
  int Ldistancia = lista.caminhoMinimo(1, 9, "output/CM.txt");
  cout << "lista_Distância: " << Ldistancia << endl;
  // int Ldiametro = lista.diametroBFS();
  // cout << "lista_Diametro: " << Ldiametro << endl;

  // // Constrói grafo usando estrutura de matriz;
  // Matriz matriz("input/txt/grafo_lista2.txt");
  // matriz.imprimirMatrizEstrutura();

  // matriz.info("output/matriz_INFO.txt");
  // matriz.arvoreBFS(1, "output/matriz_BFS.txt");
  // matriz.arvoreDFS(1, "output/matriz_DFS.txt");
  // int Mdistancia = matriz.distancia(1, 9);
  // cout << "matriz_Distância: " << Mdistancia << endl;
  // int Mdiametro = matriz.diametro();
  // cout << "matriz_Diâmetro: " << Mdiametro << endl;

  return 0;
}