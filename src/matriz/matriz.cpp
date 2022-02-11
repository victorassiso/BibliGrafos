#include "matriz.h"

Matriz::Matriz(string arquivoOrigem): MatrizEstrutura(arquivoOrigem) {}

Matriz::~Matriz() {}

////////////////////////////////////////////////////////////////////////////////
void Matriz::info(string arquivoDestino) {
  string BFS = info2();
  ofstream outfile(arquivoDestino);

  cout << "Construindo arquivo de saida INFO..." << endl;

  outfile << "Número de Vértices: " << getNVertices() << endl;
  outfile << "Número de Arestas: " << getNArestas() << endl;
  outfile << "Grau Mínimo: " << getGrauMinimo() << endl;
  outfile << "Grau Máximo: " << getGrauMaximo() << endl;
  outfile << "Grau Médio: " << getGrauMedio() << endl;
  outfile << "Grau Mediana: " << getGrauMediana() << endl;
  outfile << "Número de Componentes conexas: " << getNComponentes() << endl;
  outfile << BFS << endl;
  outfile.close();

  cout << "Arquivo construido com sucesso!\n" << endl;
}

////////////////////////////////////////////////////////////////////////////////
string Matriz::info2() {

  cout << "Gerando Info..." << endl;

  // Inicializa variáveis da BFS
  vector<MatrizVertice*> Q;
  vector<int> QIndice;
  int vIndice;
  MatrizVertice *v;
  MatrizVertice *w;
  MatrizVertice *s;
  int maiorDiametro = 0;
  int i = 0;

  //Inicializa vairáveis INFO
  int nA = 0;
  int grau = 0;
  int nComp = 0;
  vector<int> vetor_graus;
  vector<vector<MatrizVertice*>> componentes;
  string outfile = "~~ Informações Gerais ~~";

  // 1. Desmarcar todos os vértices
  desmarcarTodosOsVertices();

  // Define raiz inicial
  vIndice = 0;
  s = vetor_vertices.at(0);

  // 2. Definir Fila Q vazia
  Q = {};
  QIndice = {};

  // 3. Marcar s e inserir s na fila Q
  marcar_e_inserir(&vIndice, &QIndice, &Q, &componentes, &nComp);
  cout << "Q.size(): " << Q.size() << endl;

  // Para cada Componente Conexa
  bool existeNovaComponenteConexa = true;
  while (existeNovaComponenteConexa) {

    // 4. Enquanto Q não estiver vazia
    while (Q.size() > 0) {
      cout << "Q.size(): " << Q.size() << endl;
      
      // 5. Retirar v de Q
      v = pop_front(&Q);
      vIndice = pop_front(&QIndice);
      /*[DEBUG]*/cout << "Remover " << v->getRotulo() << endl;

      // 6. Para todo vizinho w de v faça
      // 6.1 Varrer a linha indiceRaiz referente ao rótulo r1
      for (int i = 0; i < vIndice; i++) {
        // 6.2 Se w for vizinho de v
        if (matriz.at(vIndice).at(i)) {

        // [INFO] Incrementar nA e grau
        nA++;
        grau++;
          
          // 7. Se w não estiver marcado
          if (!vetor_vertices.at(i)->getStatus()) {
            
            // 8. e 9. Marcar w e inserir w em Q
            marcar_e_inserir(&i, &QIndice, &Q, &componentes, &nComp);
          }
        }
      }    
      
      // 6.1 Varrer a coluna indiceRaiz referente ao rótulo r1
      for (int i = vIndice+1; i < vetor_vertices.size(); i++) {
        // 6.2 Se w for vizinho de v
        if (matriz.at(i).at(vIndice)) {

        // [INFO] Incrementar nA e grau
        nA++;
        grau++;

          // 7. Se w não estiver marcado
          if (!vetor_vertices.at(i)->getStatus()) {

            // 8. e 9. Marcar w e inserir w em Q
            marcar_e_inserir(&i, &QIndice, &Q, &componentes, &nComp);
          }
        }
      }

      // [INFO] Inserir grau de v em vetor_graus e zerar grau de v
      vetor_graus.push_back(grau);
      grau = 0;
    }

    // Se ainda houverem vértices desconhecidos, isto é, uma nova componente conexa
    do {
      i++;
    } while (i < vetor_vertices.size() && vetor_vertices.at(i)->getStatus());
    
    if (i < vetor_vertices.size()) {
      // [INFO]
      nComp++; // Incrementar nComp

      // 8. e 9. Marcar w e inserir w em Q
      marcar_e_inserir(&i, &QIndice, &Q, &componentes, &nComp);

    } else {
      existeNovaComponenteConexa = false;
    }


  }
  
  cout << "Arquivo de saída Info gerado com sucesso!" << endl;
  
  ///////////////////

  // [INFO]
  //set Info
  setNArestas(nA/2);
  sort(vetor_graus.begin(), vetor_graus.end());
  setGrauMaximo(vetor_graus.back());
  setGrauMinimo(vetor_graus.front());
  setGrauMedio(nA/(double)getNVertices());
  setNComponentes(nComp+1);

  if (vetor_graus.size() % 2 != 0) 
    setGrauMediana((double)(vetor_graus.at((double)vetor_graus.size() / 2)));
  else
    setGrauMediana((double)(((double)vetor_graus.at((double)(vetor_graus.size()-1)/2) + (double)vetor_graus.at(((double)vetor_graus.size())/2))/2));
  
  outfile += info3(&componentes);

  return outfile;
  /*
  cout << "Construindo Árvore Geradora (BFS)..." << endl;


  // 1. Desmarcar todos os vértices
  desmarcarTodosOsVertices();

  // Inicializar variáveis
  int indiceRaiz = 0;
  vector<MatrizVertice*> Q;
  vector<int> QIndice;
  int vIndice;
  MatrizVertice* v;
  MatrizVertice* w;
  MatrizVertice* s = vetor_vertices.at(0);
  
  // Definir Cabeçalho
  string outfile = "~~ Árvore Geradora (DFS) ~~\n\n";

  // 2. Definir Fila Q vazia
  Q = {};
  QIndice = {};

  // 3. Marcar s e inserir s na fila Q
  s->setStatus(true);
  Q.push_back(s);
  QIndice.push_back(indiceRaiz);
  cout << "Inserir " << s->getRotulo() << endl;
  outfile += "Vertice: " + to_string(s->getRotulo()) + ";\n";

  // 4. Enquanto Q não estiver vazia
  while (Q.size() > 0) {
    
    // 5. Retirar v de Q
    v = Q.front();
    Q.erase(Q.begin());
    vIndice = QIndice.front();
    QIndice.erase(QIndice.begin());
    cout << "Remover " << v->getRotulo() << endl;

    // 6. Para todo vizinho w de v faça
    // 6.1 Varrer a linha indiceRaiz referente ao rótulo r1
    for (int i = 0; i < vIndice; i++) {
      // 6.2 Se w for vizinho de v
      if (matriz.at(vIndice).at(i)) {

        // 7. Se w não estiver marcado
        if (!vetor_vertices.at(i)->getStatus()) {
          
          // 8. Marcar w
          vetor_vertices.at(i)->setStatus(true);
          
          // 9. Inserir w em Q
          w = vetor_vertices.at(i);
          Q.push_back(w);
          QIndice.push_back(i);
          cout << "Inserir " << w->getRotulo() << endl;

          // Imprimir novo vértice
          outfile += "Vertice: " + to_string(w->getRotulo()) + ";\n";
        }
      }
    }    
    
    // 6.1 Varrer a coluna indiceRaiz referente ao rótulo r1
    for (int i = vIndice+1; i < vetor_vertices.size(); i++) {
      // 6.2 Se w for vizinho de v
      if (matriz.at(i).at(vIndice)) {

        // 7. Se w não estiver marcado
        if (!vetor_vertices.at(i)->getStatus()) {
          
          // 8. Marcar w
          vetor_vertices.at(i)->setStatus(true);
          
          // 9. Inserir w em Q
          w = vetor_vertices.at(i);
          Q.push_back(w);
          QIndice.push_back(i);
          cout << "Inserir " << w->getRotulo() << endl;

          // Imprimir novo vértice
          outfile += "Vertice: " + to_string(w->getRotulo()) + ";\n";
        }
      }
    }
    cout << "Debug" << endl;
    cout << Q.size() << endl;
  }

  cout << "Árvore constuída com sucesso!" << endl;

  return outfile;



  /*
  cout << "Analisando o grafo..." << endl;
  
  // Definir variáveis BFS
  vector<MatrizVertice*> Q;
  MatrizVertice* s = vetor_vertices.at(0);
  vector<int> QIndice;
  int vIndice = 0;
  MatrizVertice* v;
  MatrizVertice* w;
  int i = 0;

  // Definir variáveis INFO
  int nA = 0;
  int grau = 0;
  int nComp = 0;
  vector<int> vetor_graus;
  vector<vector<MatrizVertice*>> componentes;
  string outfile = "";

  // 1. Desmarcar todos os vértices
  desmarcarTodosOsVertices();

  // 2. Definir fila Q vazia
  Q = {};
  QIndice = {};

  // 3. Marcar s e inserir s na fila Q
  s->setStatus(true);
  Q.push_back(s);
  QIndice.push_back(vIndice);
  cout << "Marcar " << s->getRotulo() << endl;
  cout << "Inserir " << s->getRotulo() << endl;

  // [INFO] Insere s na componente nComp
  componentes.push_back({s});

  // Para cada Componente Conexa
  bool existeNovaComponenteConexa = true;
  while (existeNovaComponenteConexa) {

    // 4. Enquanto Q não estiver vazia
    while (Q.size() > 0) {

      // 5. Retirar v de Q
      v = Q.front();
      Q.erase(Q.begin());

      vIndice = QIndice.front();
      QIndice.erase(QIndice.begin());

      cout << "Remover " << v->getRotulo() << endl;
      
      // 6. Para todo vizinho w de v
        // 6.1 Varrer a linha indiceRaiz referente ao rótulo r1
        for (int i = 0; i < vIndice; i++) {
          // 6.2 Se w for vizinho de v
          if (matriz.at(vIndice).at(i)) {
            cout << vIndice << endl;
            // Incrementa número de arestas
            nA++;
            // Incrementa grau de v
            grau++;

            // 7. Se w não estiver marcado
            if (!vetor_vertices.at(i)->getStatus()) {
              w = vetor_vertices.at(i);

              // 8. Marcar w
              w->setStatus(true);
              cout << "Marcar " << vetor_vertices.at(i)->getRotulo() << endl;
              
              // 9. Inserir w em Q
              Q.push_back(w);
              QIndice.push_back(i);
              cout << "Inserir " << vetor_vertices.at(i)->getRotulo() << endl;

              // [INFO] Inserir w na componente nComp
              componentes.at(nComp).push_back(w);
            }
          }
        }    
        
        // 6.1 Varrer a coluna indiceRaiz referente ao rótulo r1
        for (int i = vIndice+1; i < vetor_vertices.size(); i++) {
          // 6.2 Se w for vizinho de v
          if (matriz.at(i).at(vIndice)) {
            cout << vIndice << endl;
            
            // Incrementa número de arestas
            nA++;
            // Incrementa grau de v
            grau++;

            // 7. Se w não estiver marcado
            if (!vetor_vertices.at(i)->getStatus()) {
              w = vetor_vertices.at(i);
              
              // 8. Marcar w
              w->setStatus(true);
              cout << "Marcar " << vetor_vertices.at(i)->getRotulo() << endl;
              
              // 9. Inserir w em Q
              Q.push_back(w);
              QIndice.push_back(i);
              cout << "Inserir " << vetor_vertices.at(i)->getRotulo() << endl;

              // [INFO] Inserir w na componente nComp
              componentes.at(nComp).push_back(w);
            }
          }
        }
        vetor_graus.push_back(grau);
        grau = 0;
    }
    
    // Se ainda houverem vértices desconhecidos, isto é, uma nova componente conexa
    do {
      i++;
    } while (i < vetor_vertices.size() && vetor_vertices.at(i)->getStatus());
    
    if (i < vetor_vertices.size()) {
      // 3. Marcar s e inserir s na fila Q
      s = vetor_vertices.at(i);
      s->setStatus(true);
      cout << "Marcar " << s->getRotulo() << endl;
      Q.push_back(s);
      cout << "Inserir " << s->getRotulo() << " na fila Q" << endl;

      // Incrementar nComp
      nComp++;
      // [INFO] Insere s na componente nComp
      componentes.push_back({s});

    } else {
      existeNovaComponenteConexa = false;
    }

  }
  ///////////////////////
  // [INFO]
  // set Info
  setNArestas(nA/2);
  sort(vetor_graus.begin(), vetor_graus.end());
  setGrauMaximo(vetor_graus.back());
  setGrauMinimo(vetor_graus.front());
  setGrauMedio(nA/(double)getNVertices());
  setNComponentes(nComp+1);

  if (vetor_graus.size() % 2 != 0) 
    setGrauMediana((double)(vetor_graus.at((double)vetor_graus.size() / 2)));
  else
    setGrauMediana((double)(((double)vetor_graus.at((double)(vetor_graus.size()-1)/2) + (double)vetor_graus.at(((double)vetor_graus.size())/2))/2));
  
  // outfile += info3(&componentes);

  return outfile;
  */

}

string Matriz::info3(vector<vector<MatrizVertice *>> *componentes) {
  cout << "Ordenando componentes...\n" << endl;
  cout << "componentes: " << componentes->size() << endl;
  // Cabeçalho
  string outfile = "\n** Componentes Conexas: **\n\n";
  
  vector<vector<MatrizVertice*>> Vcomponentes = *componentes;
  
  sort(componentes->rbegin(), componentes->rend(),
    [](vector<MatrizVertice*> a, vector<MatrizVertice*> b){
      return a.size() < b.size();
    });

  for (int i = 0; i < componentes->size(); i++) {
    outfile += "Componente: " + to_string(i+1) + ";\t Tamanho: " + to_string(componentes->at(i).size()) + "\n";
    for (int j = 0; j < componentes->at(i).size(); j++) {
      outfile += to_string(componentes->at(i).at(j)->getRotulo()) + "\n";
    }
    outfile += "\n";
  }

  return outfile;
}

////////////////////////////////////////////////////////////////////////////////
// Retorna a distância entre r1 e r2 ou Nulo caso não haja caminho entre os vértices
int Matriz::distancia(int r1, int r2) {

  cout << "Iniciando cálculo da distância..." << endl;

  // Quando r1 e r2 são iguais a distância é zero
  if (r1 == r2) {
    return 0;
  }

  // Busca o endereço do vértice que armazena r1 e seu indice no vetor_vertices
  int indiceRaiz;
  MatrizVertice* raiz = buscaVertical(r1, &indiceRaiz);
  if (!raiz){
    cout << "Vertice raiz não encontrado!" << endl;
    return -1;
  }

  // Inicializa variáveis
  vector<Noh<MatrizVertice> *> QNoh;
  vector<int> QIndice;
  int vIndice;
  Noh<MatrizVertice> *vNoh;
  Noh<MatrizVertice> *wNoh;
  Noh<MatrizVertice> *sNoh;
  MatrizVertice *w;
  int maiorDiametro = 0;

  // 1. Desmarcar todos os vértices
  desmarcarTodosOsVertices();

  // Define raiz inicial
  Arvore<MatrizVertice> arvore(raiz);
  sNoh = arvore.getRaiz();

  // 2. Definir Fila Q vazia
  QNoh = {};
  QIndice = {};

  // 3. Marcar s e inserir s na fila Q
  marcar_e_inserir_raiz(&indiceRaiz, &QIndice, &QNoh, sNoh);

  // 4. Enquanto Q não estiver vazia
  while (QNoh.size() > 0) {
  //while (Qint.size() > 0) {
    
    // 5. Retirar v de Q
    vNoh = pop_front(&QNoh);
    vIndice = pop_front(&QIndice);
    // /*[DEBUG]*/cout << "Remover " << vNoh->getVertice()->getRotulo() << endl;

    // 6. Para todo vizinho w de v faça
    // 6.1 Varrer a linha indiceRaiz referente ao rótulo r1
    for (int i = 0; i < vIndice; i++) {
      // 6.2 Se w for vizinho de v
      if (matriz.at(vIndice).at(i)) {

        // 7. Se w não estiver marcado
        if (!vetor_vertices.at(i)->getStatus()) {
          
          // 8. e 9. Marcar w e inserir w em Q
          wNoh = marcar_e_inserir_vizinho(&i, &QIndice, &QNoh, vNoh);
          
          // Verifica se r2 foi encontrado
          if (wNoh->getVertice()->getRotulo() == r2) {
            // Se sim, retorna a distância
            cout << "Distância calculada com sucesso!" << endl;
            return wNoh->getNivel();
          }
        }
      }
    }    
    
    // 6.1 Varrer a coluna indiceRaiz referente ao rótulo r1
    for (int i = vIndice+1; i < vetor_vertices.size(); i++) {
      // 6.2 Se w for vizinho de v
      if (matriz.at(i).at(vIndice)) {

        // 7. Se w não estiver marcado
        if (!vetor_vertices.at(i)->getStatus()) {

          // 8. e 9. Marcar w e inserir w em Q
          wNoh = marcar_e_inserir_vizinho(&i, &QIndice, &QNoh, vNoh);

          // Verifica se r2 foi encontrado
          if (wNoh->getVertice()->getRotulo() == r2) {
            // Se sim, retorna a distância
            cout << "Distância calculada com sucesso!" << endl;
            return wNoh->getNivel();
          }
        }
      }
    }
  }
      
  cout << "Não existe caminho entre r1 e r2" << endl;
  return -1;
}

////////////////////////////////////////////////////////////////////////////////
// Gera arquivo de saída com árvore geradora BFS
void Matriz::arvoreBFS(int raizRotulo, string arquivoDestino) {
  cout << "Construindo Árvore Geradora BFS..." << endl;

  // Busca o endereço do vértice que armazena raizRotulo e seu indice no vetor_vertices
  int indiceRaiz;
  MatrizVertice* raiz = buscaVertical(raizRotulo, &indiceRaiz);
  if (!raiz){
    cout << "Vértice raiz não encontrado!" << endl;
    return ;
  }

  // Inicializa variáveis
  vector<Noh<MatrizVertice> *> QNoh;
  vector<int> QIndice;
  int vIndice;
  Noh<MatrizVertice> *vNoh;
  Noh<MatrizVertice> *wNoh;
  Noh<MatrizVertice> *sNoh;
  MatrizVertice *w;
  int maiorDiametro = 0;
  ofstream outfile(arquivoDestino);

  // Imprimir Cabeçalho
  outfile << "~~ Árvore Geradora (BFS) ~~" << endl << endl;

  // 1. Desmarcar todos os vértices
  desmarcarTodosOsVertices();

  // Define raiz inicial
  Arvore<MatrizVertice> arvore(raiz);
  sNoh = arvore.getRaiz();

  // 2. Definir Fila Q vazia
  QNoh = {};
  QIndice = {};

  // 3. Marcar s e inserir s na fila Q
  marcar_e_inserir_raiz(&indiceRaiz, &QIndice, &QNoh, sNoh);
  outfile << imprimir_vertices_arvore(sNoh) << endl;
  // Imprimir novo vértice (raiz)
  

  // 4. Enquanto Q não estiver vazia
  while (QNoh.size() > 0) {
  //while (Qint.size() > 0) {
    
    // 5. Retirar v de Q
    vNoh = pop_front(&QNoh);
    vIndice = pop_front(&QIndice);
    // /*[DEBUG]*/cout << "Remover " << vNoh->getVertice()->getRotulo() << endl;

    // 6. Para todo vizinho w de v faça
    // 6.1 Varrer a linha indiceRaiz referente ao rótulo r1
    for (int i = 0; i < vIndice; i++) {
      // 6.2 Se w for vizinho de v
      if (matriz.at(vIndice).at(i)) {

        // 7. Se w não estiver marcado
        if (!vetor_vertices.at(i)->getStatus()) {
          
          // 8. e 9. Marcar w e inserir w em Q
          wNoh = marcar_e_inserir_vizinho(&i, &QIndice, &QNoh, vNoh);
          outfile << imprimir_vertices_arvore(wNoh) << endl;

        }
      }
    }    
    
    // 6.1 Varrer a coluna indiceRaiz referente ao rótulo r1
    for (int i = vIndice+1; i < vetor_vertices.size(); i++) {
      // 6.2 Se w for vizinho de v
      if (matriz.at(i).at(vIndice)) {

        // 7. Se w não estiver marcado
        if (!vetor_vertices.at(i)->getStatus()) {

          // 8. e 9. Marcar w e inserir w em Q
          wNoh = marcar_e_inserir_vizinho(&i, &QIndice, &QNoh, vNoh);
          outfile << imprimir_vertices_arvore(wNoh) << endl;

        }
      }
    }
  }
      
  cout << "Árvore Geradora BFS construída com sucesso!" << endl;
}

////////////////////////////////////////////////////////////////////////////////
// Retorna o diâmetro do grafo
int Matriz::diametro() {
  cout << "Iniciando cálculo do diâmetro..." << endl;

  // Inicializa variáveis
  vector<Noh<MatrizVertice> *> QNoh;
  vector<int> QIndice;
  int vIndice;
  Noh<MatrizVertice> *vNoh;
  Noh<MatrizVertice> *wNoh;
  Noh<MatrizVertice> *sNoh;
  MatrizVertice *w;
  int maiorDiametro = 0;

  // Para cada vértice
  for (int i = 0; i < vetor_vertices.size(); i++) {

    // 1. Desmarcar todos os vértices
    desmarcarTodosOsVertices();

    // Define raiz inicial
    int indiceRaiz = i;
    MatrizVertice *raiz = vetor_vertices.at(i);
    Arvore<MatrizVertice> arvore(raiz);
    sNoh = arvore.getRaiz();

    // 2. Definir Fila Q vazia
    QNoh = {};
    QIndice = {};

    // 3. Marcar s e inserir s na fila Q
    marcar_e_inserir_raiz(&indiceRaiz, &QIndice, &QNoh, sNoh);

    // 4. Enquanto Q não estiver vazia
    while (QNoh.size() > 0) {
    //while (Qint.size() > 0) {
      
      // 5. Retirar v de Q
      vNoh = pop_front(&QNoh);
      vIndice = pop_front(&QIndice);
      // /*[DEBUG]*/cout << "Remover " << vNoh->getVertice()->getRotulo() << endl;

      // 6. Para todo vizinho w de v faça
      // 6.1 Varrer a linha indiceRaiz referente ao rótulo r1
      for (int i = 0; i < vIndice; i++) {
        // 6.2 Se w for vizinho de v
        if (matriz.at(vIndice).at(i)) {

          // 7. Se w não estiver marcado
          if (!vetor_vertices.at(i)->getStatus()) {
            
            // 8. e 9. Marcar w e inserir w em Q
            wNoh = marcar_e_inserir_vizinho(&i, &QIndice, &QNoh, vNoh);
          }
        }
      }    
      
      // 6.1 Varrer a coluna indiceRaiz referente ao rótulo r1
      for (int i = vIndice+1; i < vetor_vertices.size(); i++) {
        // 6.2 Se w for vizinho de v
        if (matriz.at(i).at(vIndice)) {

          // 7. Se w não estiver marcado
          if (!vetor_vertices.at(i)->getStatus()) {

            // 8. e 9. Marcar w e inserir w em Q
            wNoh = marcar_e_inserir_vizinho(&i, &QIndice, &QNoh, vNoh);
          }
        }
      }
    }
    
    // Atualizar maiorDiametro
    if (wNoh->getNivel() > maiorDiametro) {
      maiorDiametro = wNoh->getNivel();
    }
    
    // Destroir arvore atual
    arvore.~Arvore();
  }
  
  cout << "Diâmetro calculado com sucesso!" << endl;

  return maiorDiametro;
}

void Matriz::desmarcarTodosOsVertices() {
  for (int i = 0; i < vetor_vertices.size(); i++) {
    vetor_vertices.at(i)->setStatus(false);
  }
}

MatrizVertice* Matriz::pop_front(vector<MatrizVertice*> *fila) {
  MatrizVertice* v = fila->front();
  fila->erase(fila->begin());

  return v;
}

Noh<MatrizVertice>* Matriz::pop_front(vector<Noh<MatrizVertice>*> *fila) {
  Noh<MatrizVertice>* n = fila->front();
  fila->erase(fila->begin());

  return n;
}

int Matriz::pop_front(vector<int> *fila) {
  int i = fila->front();
  fila->erase(fila->begin());

  return i;
}

Noh<MatrizVertice>* Matriz::marcar_e_inserir_vizinho(int *i, vector<int> *QIndice, vector<Noh<MatrizVertice>*> *QNoh, Noh<MatrizVertice> *vNoh) {
  
  Noh<MatrizVertice>* wNoh = new Noh<MatrizVertice>(vetor_vertices.at(*i)); // Cria novo Noh e atribui endereço a wNoh
  
  // 8. Marcar w
  wNoh->getVertice()->setStatus(true);
  // /*[DEBUG]*/cout << "Marcar " << wNoh->getVertice()->getRotulo() << endl;
  
  // 9. Inserir w em Q
  QNoh->push_back(wNoh); // Insere WNoh na fila QNoh
  QIndice->push_back(*i); // Insere indice de W na fila QIndice
  // /*[DEBUG]*/cout << "Inserir " << wNoh->getVertice()->getRotulo() << endl;
  wNoh->setPai(vNoh);
  wNoh->setNivel(vNoh->getNivel()+1);

  return wNoh;
}

void Matriz::marcar_e_inserir_raiz(int *indiceRaiz, vector<int> *QIndice, vector<Noh<MatrizVertice>*> *QNoh, Noh<MatrizVertice> *sNoh) {
  
  sNoh->getVertice()->setStatus(true); // Marcar S
  QNoh->push_back(sNoh); // Inserir SNoh na fila QNoh
  QIndice->push_back(*indiceRaiz); // Inserir indice de S na fila QIndice
  // /*[DEBUG]*/ cout << "Marcar " << sNoh->getVertice()->getRotulo() << endl;
  // /*[DEBUG]*/ cout << "Inserir " << sNoh->getVertice()->getRotulo() << endl;
  // Corrigir Raiz;
  sNoh->setPai(nullptr);
  sNoh->setNivel(0);
  
}

string Matriz::imprimir_vertices_arvore(Noh<MatrizVertice> *vNoh) {
  string outfile;
  string rotulo = to_string(vNoh->getVertice()->getRotulo());
  string nivel = to_string(vNoh->getNivel());
  string pai = vNoh->getPai() ?
    to_string(vNoh->getPai()->getVertice()->getRotulo()) :
    "nullptr";
  
  outfile = "Rótulo: " + rotulo + ";\tPai: " + pai + ";\tNível: " + nivel;
  
  return outfile;
}

void Matriz::marcar_e_inserir(int *i, vector<int> *QIndice, vector<MatrizVertice*> *Q, vector<vector<MatrizVertice *>> *componentes, int *nComp) { 
  MatrizVertice *v = vetor_vertices.at(*i);
  v->setStatus(true);
  Q->push_back(v);
  QIndice->push_back(*i);
  cout << "Marcar " << v->getRotulo() << endl;
  cout << "Inserir " << v->getRotulo() << endl;

  // [INFO]
  cout << "Debug01" << endl;
  cout << *nComp << endl;
  if (*i > 0) {
    if (componentes->size() > *nComp){
      componentes->at(*nComp).push_back(v); // Insere v na componente nComp
    } else {
      componentes->push_back({v});
    }
  } else {
    cout << "Debug0else" << endl;
    componentes->push_back({v}); // Insere v na componente nComp
  }
  cout << "Debug02" << endl;

}

//INFO

void Matriz::setNArestas(int nA) {nArestas = nA;}
void Matriz::setGrauMinimo(int gminimo) {grauMinimo = gminimo;}
void Matriz::setGrauMaximo(int gmaximo) {grauMaximo = gmaximo;}
void Matriz::setGrauMedio(double gmedio) {grauMedio = gmedio;}
void Matriz::setGrauMediana(double gmediana) {grauMediana = gmediana;}
void Matriz::setNComponentes(int nComp) { nComponentes = nComp; }

int Matriz::getNArestas() {return nArestas;}
int Matriz::getGrauMinimo() {return grauMinimo;}
int Matriz::getGrauMaximo() {return grauMaximo;}
double Matriz::getGrauMedio() {return grauMedio;}
double Matriz::getGrauMediana() {return grauMediana;}
int Matriz::getNComponentes() { return nComponentes; }