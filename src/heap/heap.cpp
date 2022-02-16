#include "heap.h"

// Método constutor do Heap
Heap::Heap() { heap = {0}; };

// Método destrutor do Heap
Heap::~Heap() { heap = {nullptr}; };

// Retorna i/2
int Heap::pai(int i) { return i >> 1; }

// Retorna i*2
int Heap::esq(int i) { return i << 1; }

// Retorna i*2+1
int Heap::dir(int i) { return (i << 1) + 1; }

// ShiftUp
void Heap::subir(int i) {
  while(pai(i) >= 1 && heap.at(pai(i))->getChave() > heap.at(i)->getChave()) {
    troca(pai(i), i);
    i = pai(i);
  }
};

// ShiftDown
void Heap::descer(int i) {
  // Variaveis
  int tamanho = heap.size();
  int menor;

  // while(true)
  while (true) {
    // Se existe dir
    if (dir(i) < tamanho) {
      // Definir menor
      if (heap.at(esq(i))->getChave() <= heap.at(dir(i))->getChave())
        menor = esq(i);
      else
        menor = dir(i);
      // Se atual > menor
      if (heap.at(i)->getChave() > heap.at(menor)->getChave()) {
        // troca(atual, menor)
        // cout << heap.at(i)->getChave() << " : " << heap.at(menor)->getChave() << endl;
        troca(i, menor);
        // cout << heap.at(i)->getChave() << " : " << heap.at(menor)->getChave() << endl;
        // atual = menor
        i = menor;
      } else {
        return ;
      }
    } else {
      // Se existe esq
      if (esq(i) < tamanho) {
        // Se atual > esq
        if (heap.at(i)->getChave() > heap.at(esq(i))->getChave()) {
          // troca(atual, esq)
          // cout << heap.at(i)->getChave() << " : " << heap.at(menor)->getChave() << endl;
          troca(i, esq(i));
          // cout << heap.at(i)->getChave() << " : " << heap.at(menor)->getChave() << endl;
          // atualiza i
          i = esq(i);
        } else {
          return ;
        }
      } else {
        return ;
      }
    }
    // cout << "loop" << endl;
    
  }
};

// Troca
void Heap::troca(int a, int b) {
  Item *prtItemA = heap.at(a);
  heap.at(a) = heap.at(b);
  heap.at(b) = prtItemA;
}

// Insere novo item no heap
void Heap::inserir(ListaVertice *_item, float _chave) {
  // 1. Adicionar elemento na última posição da árvore
  Item *newItem = new Item(_item, _chave);
  heap.push_back(newItem);

  // 2. Trocar posição com pai até garantir heap-order (subir)
  subir(heap.size()-1);
};

Item * Heap::extrair() {
  // 1. Remover raiz e mover último elemento para raiz
  Item *raiz = heap.at(1);
  heap.at(1) = heap.at(heap.size()-1);
  heap.pop_back();

  // 2. Trocar de posição com menor filho até garantir heap-order (descer)
  descer(1);

  return raiz;
};

Item * Heap::atualizar(int i, float newChave) {
  // Chave muda de valor acessando diretamente o elemento
  Item *_item = heap.at(i);
  _item->setChave(newChave);

  // Subir ou descer de acordo até garantir heap-order
  // Se pai < atual, subir(). Else descer()
  subir(i);
  descer(i);

  return _item;
}

Item * Heap::getRaiz() { return heap.at(1); };

int Heap::getIndice(ListaVertice *elemento) {
  int i = 1;

  while (i < heap.size() && elemento != heap.at(i)->getVertice())
    i++;
  
  if (i == heap.size())
    return -1;
  
  return i;
}

float Heap::getChave(ListaVertice *elemento) {
  int i = getIndice(elemento);
  return heap.at(i)->getChave();
}

float Heap::getChave(int i) {
  return heap.at(i)->getChave();
}

void Heap::imprimirHeap() {
  int comparador = 1;
  for (int i = 1; i < heap.size(); i++) {
    cout << heap.at(i)->getVertice()->getRotulo() << "(" << heap.at(i)->getChave() << ")";
    if (i == comparador) {
      cout << endl;
      comparador = comparador*2 + 1;
    }
  }
  cout << endl << endl;
}
