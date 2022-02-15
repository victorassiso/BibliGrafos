#ifndef MINHEAP_H
#define MINHEAP_H

#include "item.h"
#include <iostream>


template <class T>
class MinHeap {
  private:
    vector<Item<T> *> filaP;

    int pai(int i) { return i >> 1; } // i/2 
    int esq(int i) { return i << 1; } // i*2
    int dir(int i) { return (i << 1) + 1; } // i*2+1
  
  public:
    MinHeap() { filaP = {NULL}; };
    ~MinHeap() {};

    void sobe() {
      
    };

    void desce() {
      
    };

    Item<T> *getMin() const { return filaP.at(1); };

    void inserirItem(T *vertice, float dist) {
      Item<T> *item = new Item<T>(vertice, dist);

      filaP.push_back(item);

      int i = filaP.size()-1;
      while(pai(i) >= 1 && filaP.at(pai(i)) > filaP.at(i)) {
        swap(filaP.at(pai(i)), filaP.at(i));
        i = pai(i);
      }
    };
    
    Item<T> *extrairMin() {
      Item<T> *min = filaP.at(1);

      // Determina indice do ultimo elemento
      int i = filaP.size()-1;

      // Atribui último elemento à raiz e apaga último elemento
      filaP.at(1) = filaP.at(i);
      filaP.pop_back();

      int tamanho = filaP.size();
      int menor;
      int maior;
      while (true) {
        
        // Se houver esq e dir
        if (esq(i) <= tamanho-1 && dir(i) <= tamanho-1) {

          // Definir o menor e o maior
          if (filaP.at(esq(i))->getPeso() <= filaP.at(dir(i))->getPeso()) {
            menor = esq(i);
            maior = dir(i);
          } else {
            menor = dir(i);
            maior = esq(i);
          }

          // Se atual > menor
          if (filaP.at(i)->getPeso() > filaP.at(menor)->getPeso())
            // swap (atual, menor)
            swap(filaP.at(i), filaP.at(menor));
          // Se não
          else {
            // Se atual > maior
            if (filaP.at(i)->getPeso() > filaP.at(maior)->getPeso())
              //swap(atual, maior)
              swap(filaP.at(i), filaP.at(maior));
          }
        // Se não
        } else {
          // Se houver apenas esq
          if (esq(i) <= tamanho) {
            // Se atual > esq
            if (filaP.at(i)->getPeso() > filaP.at(esq)->getPeso())
              // swap(atual, esq)
              swap(filaP.at(i), filaP.at(esq))
          }
          // parar while
          return min;
        }
      }
    };

    void atualizaChave(int indice) {
      if (filaP.at(indice) < filaP.at(pai(indice))) {
        int i = filaP.size()-1;
        while(pai(i) >= 1 && filaP.at(pai(i)) > filaP.at(i)) {
          swap(filaP.at(pai(i)), filaP.at(i));
          i = pai(i);
        }
      } else {
        

      
      int tamanho = filaP.size();
      int menor;
      int maior;
      while (true) {
        
        // Se houver esq e dir
        if (esq(i) <= tamanho-1 && dir(i) <= tamanho-1) {

          // Definir o menor e o maior
          if (filaP.at(esq(i))->getPeso() <= filaP.at(dir(i))->getPeso()) {
            menor = esq(i);
            maior = dir(i);
          } else {
            menor = dir(i);
            maior = esq(i);
          }

          // Se atual > menor
          if (filaP.at(i)->getPeso() > filaP.at(menor)->getPeso())
            // swap (atual, menor)
            swap(filaP.at(i), filaP.at(menor));
          // Se não
          else {
            // Se atual > maior
            if (filaP.at(i)->getPeso() > filaP.at(maior)->getPeso())
              //swap(atual, maior)
              swap(filaP.at(i), filaP.at(maior));
          }
        // Se não
        } else {
          // Se houver apenas esq
          if (esq(i) <= tamanho) {
            // Se atual > esq
            if (filaP.at(i)->getPeso() > filaP.at(esq)->getPeso())
              // swap(atual, esq)
              swap(filaP.at(i), filaP.at(esq))
          }
          // parar while
          return min;
        }
      }
    }
};

// Tipos válidos

template class MinHeap<ListaVertice*>;
template class MinHeap<MatrizVertice*>;

#endif