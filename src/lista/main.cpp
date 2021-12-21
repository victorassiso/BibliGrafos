#include "lista.h"

int testeVertice()
{
  Vertice v1(1);  
  cout << v1.getRotulo() << endl;

  return 0;
}

int testeVizinho()
{
  Vertice ve1(1);  
  Vertice ve2(2);

  Vizinho vi2(&ve2);
  ve1.setVizinho(&vi2);

  cout << ve1.getRotulo() << " --> " << ve1.getVizinho()->getVertice()->getRotulo() << endl;
  

  return 0;
}

int testeLista()
{
  Lista grafo("grafo.txt");
  grafo.imprimirLista();

  return 0;
}
int main() {

  //testeVertice();
  //testeVizinho();
  testeLista();

  return 0;
}