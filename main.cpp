#include "src/lista/lista.h"
#include "src/matriz/matriz.h"
#include <time.h>
#include <iostream>

void testeT2(int indexGrafo, int nrep){
  
  Lista lista("input/txt/grafo_W_" + to_string(indexGrafo) + "_1.txt");
  // string output = "output/grafo" + to_string(indexGrafo) + "/";
  ofstream outfile("output/tempo_grafo_w_"+to_string(indexGrafo)+"_1.txt");

  // // Distância 1 pra 10
  // lista.caminhoMinimo(1, 10, output+"dist_1pra10.txt");
  
  // // Distância 1 pra 20
  // lista.caminhoMinimo(1, 20, output+"dist_1pra10.txt");
  
  // // Distância 1 pra 30
  // lista.caminhoMinimo(1, 30, output+"dist_1pra10.txt");
  
  // // Distância 1 pra 40
  // lista.caminhoMinimo(1, 40, output+"dist_1pra10.txt");
  
  // // Distância 1 pra 50
  // lista.caminhoMinimo(1, 50, output+"dist_1pra10.txt");

  float tempo = 0;
  for (int i = 0; i < nrep; i++) {
    srand(i);
    int raiz = 1+rand()%lista.getNVertices();
    
    clock_t inicio = clock();

    cout << "\nGrafo " << indexGrafo << ": " << endl;
    lista.caminhoMinimo(raiz, "output/temp.txt");
    
    tempo += float(float((clock() - inicio))/CLOCKS_PER_SEC);
    cout << "Tempo(s): "<< float(float((clock() - inicio))/CLOCKS_PER_SEC) << endl;
  }
  
  outfile << "Tempo Médio(s): " << tempo/nrep << endl << endl;


};

int main() {
  
  testeT2(3, 5);
  
  return 0;
}