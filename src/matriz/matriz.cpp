#include "matriz.h"

Matriz::Matriz(string arquivoOrigem): MatrizEstrutura(arquivoOrigem) {}

Matriz::~Matriz() {}

void Matriz::info(string arquivoDestino) {
  string BFS = info2();
  ofstream outfile(arquivoDestino);

  cout << "Construindo arquivo de saida INFO...\n" << endl;

  outfile << "Número de Vértices: " << getNVertices() << endl;
  outfile << "Número de Arestas: " << getNArestas() << endl;
  outfile << "Grau Mínimo: " << getGrauMinimo() << endl;
  outfile << "Grau Máximo: " << getGrauMaximo() << endl;
  outfile << "Grau Médio: " << getGrauMedio() << endl;
  outfile << "Grau Mediana: " << getGrauMediana() << endl;
  outfile << "Número de Componentes conexas: " << getNComponentes() << endl;
  outfile << BFS << endl;
  outfile.close();

  cout << "Arquivo construido com sucesso!\n\n" << endl;
}

string Matriz::info2() {
  cout << "Analisando o grafo...\n" << endl;
  
  // Definir variáveis BFS
  vector<MatrizVertice*> Q;
  MatrizVertice* s = vetor_vertices.at(0);
  vector<int> QIndice;
  int vIndice = 0;
  MatrizVertice* v;

  // Definir variáveis INFO
  int nA = 0;
  int grau = 0;
  int nComp = 0;
  vector<int> vetor_graus;
  vector<vector<MatrizVertice*>> componentes;
  string outfile = "";

  // 1. Desmarcar todos os vértices
  for (int i = 0; i < vetor_vertices.size(); i++) {
    vetor_vertices.at(i)->setStatus(false);
  }

  // 2. Definir fila Q vazia
  Q = {};
  QIndice = {};

  // 3. Marcar s e inserir s na fila Q
  s->setStatus(true);
  Q.push_back(s);
  QIndice.push_back(vIndice);
  // cout << "Inserir " << s->getRotulo() << endl;
  // cout << "Marcar " << s->getRotulo() << endl;

  // 4. Enquanto Q não estiver vazia
  while (Q.size() > 0) {

    // 5. Retirar v de Q
    v = Q.front();
    Q.erase(Q.begin());
    vIndice = QIndice.front();
    QIndice.erase(QIndice.begin());
    // cout << "Remover " << v->getRotulo() << endl;

    // 6. Para todo vizinho w de v faça
      // 6.1 Varrer a linha indiceRaiz referente ao rótulo r1
      for (int i = 0; i < vIndice; i++) {
        // 6.2 Se w for vizinho de v
        if (matriz.at(vIndice).at(i)) {
          
          // Incrementa número de arestas
          nA++;
          // Incrementa grau de v
          grau++;

          // 7. Se w não estiver marcado
          if (!vetor_vertices.at(i)->getStatus()) {
            
            // 8. Marcar w
            vetor_vertices.at(i)->setStatus(true);
            // cout << "Marcar " << vetor_vertices.at(i)->getRotulo() << endl;
            
            // 9. Inserir w em Q
            Q.push_back(vetor_vertices.at(i));
            QIndice.push_back(i);
            // cout << "Inserir " << vetor_vertices.at(i)->getRotulo() << endl;
          }
        }
      }    
      
      // 6.1 Varrer a coluna indiceRaiz referente ao rótulo r1
      for (int i = vIndice+1; i < vetor_vertices.size(); i++) {
        // 6.2 Se w for vizinho de v
        if (matriz.at(i).at(vIndice)) {
          
          // Incrementa número de arestas
          nA++;
          // Incrementa grau de v
          grau++;

          // 7. Se w não estiver marcado
          if (!vetor_vertices.at(i)->getStatus()) {
            
            // 8. Marcar w
            vetor_vertices.at(i)->setStatus(true);
            // cout << "Marcar " << vetor_vertices.at(i)->getRotulo() << endl;
            
            // 9. Inserir w em Q
            Q.push_back(vetor_vertices.at(i));
            QIndice.push_back(i);
            // cout << "Inserir " << vetor_vertices.at(i)->getRotulo() << endl;
          }
        }
      }
      vetor_graus.push_back(grau);
      grau = 0;
  }

  ///////////////////////
  // [INFO]
  // set Info
  setNArestas(nA/2);
  sort(vetor_graus.begin(), vetor_graus.end());
  setGrauMaximo(vetor_graus.back());
  setGrauMinimo(vetor_graus.front());
  setGrauMedio(nA/(double)getNVertices());
  // setNComponentes(nComp+1);

  if (vetor_graus.size() % 2 != 0) 
    setGrauMediana((double)(vetor_graus.at((double)vetor_graus.size() / 2)));
  else
    setGrauMediana((double)(((double)vetor_graus.at((double)(vetor_graus.size()-1)/2) + (double)vetor_graus.at(((double)vetor_graus.size())/2))/2));
  
  // outfile += info3(&componentes);

  return outfile;
}

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
    cout << "Vertice raiz não encontrado." << endl;
    return -1;
  }

  // 1. Desmarcar todos os vértices
  for (int i = 0; i < vetor_vertices.size(); i++) {
    vetor_vertices.at(i)->setStatus(false);
  }

  // Inicializa variáveis
  vector<Noh<MatrizVertice>*> QNoh;
  vector<int> QIndice;
  int vIndice;
  Noh<MatrizVertice>* vNoh;
  Noh<MatrizVertice>* wNoh;
  MatrizVertice* w;
  Arvore<MatrizVertice> arvore(raiz);
  Noh<MatrizVertice>* sNoh = arvore.getRaiz();

  // 2. Definir Fila Q vazia
  QNoh = {};
  QIndice = {};

  // 3. Marcar s e inserir s na fila Q
  sNoh->getVertice()->setStatus(true);
  QNoh.push_back(sNoh);
  QIndice.push_back(indiceRaiz);
  // cout << "Inserir " << sNoh->getVertice()->getRotulo() << endl;
  sNoh->setPai(nullptr);
  sNoh->setNivel(0);

  // 4. Enquanto Q não estiver vazia
  while (QNoh.size() > 0) {
  //while (Qint.size() > 0) {
    
    // 5. Retirar v de Q
    vNoh = QNoh.front();
    QNoh.erase(QNoh.begin());
    vIndice = QIndice.front();
    QIndice.erase(QIndice.begin());
    // cout << "Remover " << vNoh->getVertice()->getRotulo() << endl;

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
          wNoh = new Noh<MatrizVertice>(vetor_vertices.at(i));
          QNoh.push_back(wNoh);
          QIndice.push_back(i);
          // cout << "Inserir " << wNoh->getVertice()->getRotulo() << endl;
          wNoh->setPai(vNoh);
          wNoh->setNivel(vNoh->getNivel()+1);

          // Se w == r2
          if (wNoh->getVertice()->getRotulo() == r2) {
            // Retorna Distância
            cout << "Término do cálculo da distância..." << endl;
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
          
          // 8. Marcar w
          vetor_vertices.at(i)->setStatus(true);
          
          // 9. Inserir w em Q
          wNoh = new Noh<MatrizVertice>(vetor_vertices.at(i));
          QNoh.push_back(wNoh);
          QIndice.push_back(i);
          // cout << "Inserir " << wNoh->getVertice()->getRotulo() << endl;
          wNoh->setPai(vNoh);
          wNoh->setNivel(vNoh->getNivel()+1);

          // Se w == r2
          if (wNoh->getVertice()->getRotulo() == r2) {
            // Retorna Distância
            cout << "Término do cálculo da distância..." << endl;
            return wNoh->getNivel();
          }
        }
      }
    }
  }

  cout << "Término do cálculo da distância..." << endl;
  cout << "Não há caminho possível entre estes dois vértices!" << endl;
  return -1;
}

// Gera arquivo de saída com árvore geradora BFS
void Matriz::arvoreBFS(int raizRotulo, string arquivoDestino) {
  cout << "Construindo Árvore Geradora (BFS)..." << endl;

  // Busca o endereço do vértice que armazena r1 e seu indice no vetor_vertices
  int indiceRaiz;
  MatrizVertice* raiz = buscaVertical(raizRotulo, &indiceRaiz);
  if (!raiz){
    cout << "Vertice raiz não encontrado." << endl;
    return ;
  }

  // 1. Desmarcar todos os vértices
  for (int i = 0; i < vetor_vertices.size(); i++) {
    vetor_vertices.at(i)->setStatus(false);
  }

  // Inicializa variáveis
  vector<Noh<MatrizVertice>*> QNoh;
  vector<int> QIndice;
  int vIndice;
  Noh<MatrizVertice>* vNoh;
  Noh<MatrizVertice>* wNoh;
  MatrizVertice* w;
  Arvore<MatrizVertice> arvore(raiz);
  Noh<MatrizVertice>* sNoh = arvore.getRaiz();
  
  // Imprimir Cabeçalho
  ofstream outfile(arquivoDestino);
  outfile << "~~ Árvore Geradora (DFS) ~~" << endl << endl;

  // 2. Definir Fila Q vazia
  QNoh = {};
  QIndice = {};

  // 3. Marcar s e inserir s na fila Q
  sNoh->getVertice()->setStatus(true);
  QNoh.push_back(sNoh);
  QIndice.push_back(indiceRaiz);
  // cout << "Inserir " << sNoh->getVertice()->getRotulo() << endl;
  sNoh->setPai(nullptr);
  sNoh->setNivel(0);

  // Imprimir novo vértice (raiz)
  outfile << "Vertice: " << sNoh->getVertice()->getRotulo() << ";\t\t";
  outfile << "Pai: nullptr;\t\t";
  outfile << "Nível: 0" << endl;

  // 4. Enquanto Q não estiver vazia
  while (QNoh.size() > 0) {
  //while (Qint.size() > 0) {
    
    // 5. Retirar v de Q
    vNoh = QNoh.front();
    QNoh.erase(QNoh.begin());
    vIndice = QIndice.front();
    QIndice.erase(QIndice.begin());
    // cout << "Remover " << vNoh->getVertice()->getRotulo() << endl;

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
          wNoh = new Noh<MatrizVertice>(vetor_vertices.at(i));
          QNoh.push_back(wNoh);
          QIndice.push_back(i);
          // cout << "Inserir " << wNoh->getVertice()->getRotulo() << endl;
          wNoh->setPai(vNoh);
          wNoh->setNivel(vNoh->getNivel()+1);

          // Imprimir novo vértice
          outfile << "Vertice: " << wNoh->getVertice()->getRotulo() << ";\t\t";
          outfile << "Pai: " << wNoh->getPai()->getVertice()->getRotulo() << ";\t\t";
          outfile << "Nível: " << wNoh->getNivel()<< endl;
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
          wNoh = new Noh<MatrizVertice>(vetor_vertices.at(i));
          QNoh.push_back(wNoh);
          QIndice.push_back(i);
          // cout << "Inserir " << wNoh->getVertice()->getRotulo() << endl;
          wNoh->setPai(vNoh);
          wNoh->setNivel(vNoh->getNivel()+1);

          // Imprimir novo vértice
          outfile << "Vertice: " << wNoh->getVertice()->getRotulo() << ";\t\t";
          outfile << "Pai: " << wNoh->getPai()->getVertice()->getRotulo() << ";\t\t";
          outfile << "Nível: " << wNoh->getNivel()<< endl;
        }
      }
    }
  }

  cout << "Árvore constuída com sucesso!" << endl;
}

// Retorna o diâmetro do grafo
int Matriz::diametro() {
  cout << "Iniciando cálculo da distância..." << endl;

  // Inicializa variáveis
  vector<Noh<MatrizVertice>*> QNoh;
  vector<int> QIndice;
  int vIndice;
  Noh<MatrizVertice>* vNoh;
  Noh<MatrizVertice>* wNoh;
  Noh<MatrizVertice>* sNoh;
  MatrizVertice* w;
  int maiorDiametro = 0;

  // Para cada vértice
  for (int i = 0; i < vetor_vertices.size(); i++) {

    // 1. Desmarcar todos os vértices
    for (int i = 0; i < vetor_vertices.size(); i++) {
      vetor_vertices.at(i)->setStatus(false);
    }

    // Define raiz inicial
    int indiceRaiz = i;
    MatrizVertice* raiz = vetor_vertices.at(i);
    Arvore<MatrizVertice> arvore(raiz);
    sNoh = arvore.getRaiz();

    // 2. Definir Fila Q vazia
    QNoh = {};
    QIndice = {};

    // 3. Marcar s e inserir s na fila Q
    sNoh->getVertice()->setStatus(true);
    QNoh.push_back(sNoh);
    QIndice.push_back(indiceRaiz);
    // cout << "Inserir " << sNoh->getVertice()->getRotulo() << endl;
    // cout << "Marcar " << sNoh->getVertice()->getRotulo() << endl;
    sNoh->setPai(nullptr);
    sNoh->setNivel(0);

    // 4. Enquanto Q não estiver vazia
    while (QNoh.size() > 0) {
    //while (Qint.size() > 0) {
      
      // 5. Retirar v de Q
      vNoh = QNoh.front();
      QNoh.erase(QNoh.begin());
      vIndice = QIndice.front();
      QIndice.erase(QIndice.begin());
      // cout << "Remover " << vNoh->getVertice()->getRotulo() << endl;

      // 6. Para todo vizinho w de v faça
      // 6.1 Varrer a linha indiceRaiz referente ao rótulo r1
      for (int i = 0; i < vIndice; i++) {
        // 6.2 Se w for vizinho de v
        if (matriz.at(vIndice).at(i)) {

          // 7. Se w não estiver marcado
          if (!vetor_vertices.at(i)->getStatus()) {
            
            // 8. Marcar w
            vetor_vertices.at(i)->setStatus(true);
            // cout << "Marcar " << vetor_vertices.at(i)->getRotulo() << endl;
            
            // 9. Inserir w em Q
            wNoh = new Noh<MatrizVertice>(vetor_vertices.at(i));
            QNoh.push_back(wNoh);
            QIndice.push_back(i);
            // cout << "Inserir " << wNoh->getVertice()->getRotulo() << endl;
            wNoh->setPai(vNoh);
            wNoh->setNivel(vNoh->getNivel()+1);
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
            wNoh = new Noh<MatrizVertice>(vetor_vertices.at(i));
            QNoh.push_back(wNoh);
            QIndice.push_back(i);
            // cout << "Inserir " << wNoh->getVertice()->getRotulo() << endl;
            wNoh->setPai(vNoh);
            wNoh->setNivel(vNoh->getNivel()+1);
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





// Floresta Matriz::BFS(int rotulo) {
//   // cout << "BFS em andamento..." << endl;
//   // cout << "debug" << endl;
//   //1. Desmarca todos os vértices
//   for (int i = 0; i< vetor_vertices.size(); i++) 
//     vetor_vertices.at(i)->setStatus(false);

//   // 2. Define fila descobertos vazia
//   vector<MatrizVertice*> descobertos = {};
//   vector<Noh*> descobertosNoh = {};
  
//   // Define indice do vértice raiz em relação ao rotulo
//   int indice;
//   buscaVertical(rotulo, &indice);
//   MatrizVertice* iterator;
//   Noh* iteratorNoh;
//   Floresta floresta;
//   int indiceFilhos = 0;
  
//   //Info
//   int nA = 0;
//   vector<int> vetor_graus;
//   int grau = 0;
//   int nVe;

//   bool novaComponente = true; // Se true: existem outras componentes conexas a serem exploradas
//   while(novaComponente) {
//     // 3. Marca raiz e insere na fila (Descoberto)
//     vetor_vertices.at(indice)->setStatus(true);
//     descobertos.push_back(vetor_vertices.at(indice));

//     // Cria nova arvore e insere noh raiz // e insere Noh na fila (descoberto)
//     Arvore* arvore = floresta.criaArvoreNova(vetor_vertices.at(indice)->getRotulo());
//     Noh* pai = arvore->getRaiz();
//     pai->setNivel(0);
//     pai->setPai(nullptr);
//     descobertosNoh.push_back(pai);

//     // 4. Enquanto fila não estiver vazia
//     while(descobertos.size() > 0) {
//       // cout << "While(descobertos.size() > 0) {" << indice << endl;
//       // 5. Retira o primeiro vertice V da fila (Explorado)
//       descobertosNoh.erase(descobertosNoh.begin());
//       descobertos.erase(descobertos.begin());
//       buscaVertical(pai->getRotulo(), &indice);

//       //Busca horizontal (linha)
//       for(int i=0; i < indice; i++) {
//         // cout << "for 1" << endl;
//         // Define novo possível vizinho W
//         iterator = vetor_vertices.at(i);
//         // cout << "iterator:" << iterator->getRotulo() << endl;
//         // 6. Para todo vizinho W de V
//         if(matriz.at(indice).at(i) == true){
//           grau++;
//           nA++;
//           // 7. Se W não estiver marcado (caso seja Desconhecido)
//           if (!iterator->getStatus()){
//             // 8. Marca W e insere na fila (Descoberto)
//             nVe++;
//             iterator->setStatus(true);
//             descobertos.push_back(iterator);
//             iteratorNoh = arvore->insereNoh(iterator->getRotulo(), pai);
//             descobertosNoh.push_back(iteratorNoh);
//             iteratorNoh->setPai(pai);
//             iteratorNoh->setNivel(pai->getNivel()+1);
//           }
//         }
//       }

//       // cout << "Debug for 2" << endl;
//       if (indice < vetor_vertices.size()-1) {
//         //Busca Vertical //
//         // cout << "debug" << endl;
//         for(int i = (indice+1); i < vetor_vertices.size(); i++) {
//           // cout << "for 2" << endl;
//           // Define novo possível vizinho W
//           iterator = vetor_vertices.at(i);
//           // cout << "iterator:" << iterator->getRotulo() << endl;
//           // 6. Para todo vizinho W de V
//           if(matriz.at(i).at(indice) == true){
//             grau++;
//             nA++;
//             // 7. Se W não estiver marcado
//             if (!iterator->getStatus()){
//               nVe++;
//               // cout << "if 2" << endl;
//               // 8. Marca W e insere na fila (Descoberto)
//               iterator->setStatus(true);
//               descobertos.push_back(iterator);
//               // cout << "descobertos.size(): " << descobertos.size() << endl;
//               // Cria novo noh, define seu pai e o insere na arvore
//               iteratorNoh = arvore->insereNoh(iterator->getRotulo(), pai);
//               descobertosNoh.push_back(iteratorNoh);
//               iteratorNoh->setPai(pai);
//               iteratorNoh->setNivel(pai->getNivel()+1);
//             }
//           }
//         }
//       }
//       //Atualiza pai como o primeiro vertice da fila
//       if (descobertos.size() > 0)
//         pai = descobertosNoh.at(0);
    
//       vetor_graus.push_back(grau);
//       grau = 0;
//     }
//     // Se todos os vertices estao marcados, novaComponente = false
//     novaComponente = false;
//     int x;
//     for (x = 0; x < vetor_vertices.size(); x++) {
//       if (vetor_vertices.at(x)->getStatus() == false) {
//         indice = x;
//         novaComponente = true;
//         x = vetor_vertices.size();
//       }
//     }
//     arvore->setTamanho(nVe);
//     arvores.push_back(arvore);
//   }

//   //setInfo
//   setNArestas(nA/2);
//   sort(vetor_graus.begin(), vetor_graus.end());
//   setGrauMaximo(vetor_graus.back());
//   setGrauMinimo(vetor_graus.front());
//   setGrauMedio(nA/(double)nVertices);
//   setNComponentes(arvores.size());

//    if (vetor_graus.size() % 2 != 0) 
//       setGrauMediana(vetor_graus.at(vetor_graus.size() / 2));
//     else
//       setGrauMediana((vetor_graus.at((vetor_graus.size()-1)/2) + vetor_graus.at((vetor_graus.size())/2))/2);
//   // cout << "BFS concluída." << endl;

//   return floresta;
// }
    

//   /*
//   int indice;
//   vector<MatrizVertice*> descobertos;
//   MatrizVertice* root = buscaVertical(rotulo, &indice);
//   MatrizVertice* atual = root;
//   MatrizVertice* iterator;
//   descobertos.push_back(atual);
//   atual->setNivel(0);
//   atual->setPai(nullptr);
//   cout << "|   " << atual->getRotulo() << "   | Null |   " << atual->getNivel() << " |" << endl;

  

//   while(descobertos.size() > 0){
    
//     cout << "Atual: " << atual->getRotulo() << endl;
//     cout << "Root: " << root->getRotulo() << endl;
//     cout << "Iterator: " << iterator->getRotulo() << endl;
    
//     for(int i=0; i < matriz.at(indice).size(); i++){
//       iterator = vetor_vertices.at(i);
//       cout << "Iterator: " << iterator->getRotulo() << endl;
      
//       if (matriz.at(indice).at(i) == true) {
//         //Se nao foi explorado && nao foi descoberto
//         if (!iterator->getStatus() && find(descobertos.begin(), descobertos.end(), iterator) == descobertos.end()) {
//           descobertos.push_back(iterator);
//           iterator->setPai(root);
//           iterator->setNivel(root->getNivel()+1);
//           cout << "|   " << iterator->getRotulo() << "   | " << iterator->getPai()->getRotulo() << "    |   " << iterator->getNivel() << "   |" << endl;
//         }
//       }
//     }

//     for(int i = indice+1; i <= vetor_vertices.size()-indice; i++) {
//       iterator = vetor_vertices.at(i);
//       cout << "Iterator: " << iterator->getRotulo() << endl;

//       if (matriz.at(i).at(indice) == true) {//m[1][2:4]
//         //Se nao foi explorado && nao foi descoberto
//         if (!iterator->getStatus() && find(descobertos.begin(), descobertos.end(), iterator) == descobertos.end()) {
//           descobertos.push_back(iterator);
//           iterator->setNivel(root->getNivel()+1);
//           iterator->setPai(root);
//           cout << "|   " << iterator->getRotulo() << "   | " << iterator->getPai()->getRotulo() << "    |   " << iterator->getNivel() << "   |" << endl;
//         }
//       }
//     }

    
    
//     atual->setStatus(true);//Explorado
//     descobertos.erase(descobertos.begin());//Tira atual do descobertos
//     root = atual;
//     atual = descobertos.at(0);
//     cout << "Debug" << endl;
//   }
//   */


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

// void Matriz::buscaEApaga(vector<MatrizVertice*>* vetor, MatrizVertice* vertice)
// {
//   if (vetor->size() < 1)
//   {
//     cout << "vetor vazio." << endl;
//     return ;
//   }
  
//   for (int i = 0; i < vetor->size(); i++) {
//     if (vertice == vetor->at(i)){
//       vetor->erase(vetor->begin()+i);
//       return ;
//     }
//   }

//   return ;
// }

// void Matriz::info() {

//   ofstream outfile("output/Grafo_Info_Matriz.txt");
//   string componentes = "";

//   outfile << "Nº de Vértices: " << getNVertices() << endl;
//   outfile << "Nº de Arestas: " << getNArestas() << endl;
//   outfile << "Grau Máximo: " << getGrauMaximo() << endl;
//   outfile << "Grau Mínimo: " << getGrauMinimo() << endl;
//   outfile << "Grau Médio: " << getGrauMedio() << endl;
//   outfile << "Mediana de Grau: " << getGrauMediana() << endl;
//   outfile << "Nº de Componentes: " << getNComponentes() << endl;

//   sort(arvores.rbegin(), arvores.rend(),
//     [](Arvore* a, Arvore* b){
//       return a->getTamanho() < b->getTamanho();
//     });

//   cout << endl;
//   for (int i=0; i < getArvores().size(); i++) {
//     componentes += "**** Componente " + to_string(i+1) + " ****\n";
//     componentes += infoArvore(getArvore(i)->getRaiz());
//     componentes += "\n";
//   }
  
//   outfile << componentes << endl;
// }

// Arvore* Matriz::criaArvoreNova(int rotuloRaiz) {
//   Arvore* arvoreNova = new Arvore(rotuloRaiz);
//   arvores.push_back(arvoreNova);

//   return arvoreNova;
// }

// Arvore* Matriz::getArvore(int indice) {
//   return arvores.at(indice);
// }

// vector<Arvore*> Matriz::getArvores() {
//   return arvores;
// }

// // void Matriz::infoFLoresta() {
// //   for (int i=0; i<this->getArvores().size(); i++) {
// //   cout << "**** Componente " << i+1 << " ****"<< endl;
// //     this->infoArvore(getArvores().at(i)->getRaiz());
// //     cout << endl; 
// //   }
// // }

// string Matriz::infoArvore(Noh* noh) {
//   string componentes;

//   componentes = "Vértice: " + to_string(noh->getRotulo());
//   componentes += " | Nível: " + to_string(noh->getNivel());
//   componentes += " | Pai: " + to_string((noh->getPai() ? noh->getPai()->getRotulo() : 0)) + "\n" ;
//   vector<Noh*> vetor = noh->getFilhos();
  
//   for (int i=0; i<vetor.size(); i++) {
//     componentes += infoArvore(vetor.at(i));
//   }
//   return componentes;
// }
