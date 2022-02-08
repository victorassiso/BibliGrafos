#include "lista.h"

Lista::Lista(string nomeArquivo): ListaEstrutura(nomeArquivo){}
Lista::~Lista(){}

void Lista::info(string arquivoDestino) {

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

string Lista::info2() {
  cout << "Analisando o grafo...\n" << endl;
  // Definir variáveis
    // Info
  string outfile = "";
  vector<vector<ListaVertice*>> componentes;; //Armazena os Vértices por componente
  vector<int> vetor_graus; // Armazena o grau de cada vértice;
  int grau = 0;
  int nA = 0;
  int nComp = 0;
    // BFS
  int i = 0;
  vector<ListaVertice*> Q;
  ListaVertice* v;
  Vizinho* w;
  ListaVertice* s = vetor_vertices.at(0);

  ///////////////////

  // 1. Desmarcar todos os vértices
  for (int i = 0; i < vetor_vertices.size(); i++) {
    vetor_vertices.at(i)->setStatus(false);
  }

  // 2. Definir Fila Q vazia
  Q = {};

  // 3. Marcar s e inserir s na fila Q
  s->setStatus(true);
  //cout << "Marcar " << s->getRotulo() << endl;
  Q.push_back(s);
  //cout << "Inserir " << s->getRotulo() << " na fila Q" << endl;
  
  // [INFO] Insere s na componente nComp
  componentes.push_back({s});
  
  // Para cada Componente Conexa
  bool existeNovaComponenteConexa = true;
  while (existeNovaComponenteConexa) {
    
    // 4. Enquanto Q não estiver vazia
    while (Q.size() > 0) {
      
      // 5.
      v = Q.front();
      Q.erase(Q.begin());
      //cout << "Remover " << v->getRotulo() << " da fila Q" << endl;
      //cout << "Explorar " << v->getRotulo() << endl;

      // 6. Para todo vizinho w de v faça
      w = v->getVizinho();
      while (w) {

        // 7. Se w não estiver marcado
        if (!w->getVertice()->getStatus()) {

          // 8. Marcar w
          w->getVertice()->setStatus(true);
          //cout << "Marcar " << w->getVertice()->getRotulo() << endl;

          // 9. inserir w em Q
          Q.push_back(w->getVertice());
          //cout << "Inserir " << w->getVertice()->getRotulo() << " na fila Q" << endl;

          // [INFO] Inserir w na componente i
          componentes.at(nComp).push_back(w->getVertice());
        }

        // [INFO] Incrementar número de arestas e grau do vertice v 
        nA++;
        grau++;
        w = w->getVizinho();
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
      // 3. Marcar s e inserir s na fila Q
      s = vetor_vertices.at(i);
      s->setStatus(true);
      //cout << "Marcar " << s->getRotulo() << endl;
      Q.push_back(s);
      //cout << "Inserir " << s->getRotulo() << " na fila Q" << endl;

      // Incrementar nComp
      nComp++;
      // [INFO] Insere s na componente nComp
      componentes.push_back({s});

    } else {
      existeNovaComponenteConexa = false;
    }

  }
  ///////////////////

  // [INFO]
  //setInfo
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
}

string Lista::info3(vector<vector<ListaVertice*>>* componentes) {
  cout << "Ordenando componentes...\n" << endl;
  // Cabeçalho
  string outfile = "\n** Componentes Conexas: **\n\n";
  
  vector<vector<ListaVertice*>> Vcomponentes = *componentes;
  
  sort(componentes->rbegin(), componentes->rend(),
    [](vector<ListaVertice*> a, vector<ListaVertice*> b){
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

int Lista::distanciaSemPeso(int r1, int r2) {
  cout << "Iniciando cálculo da distância..." << endl;
  
  // Quando r1 e r2 são iguais a distância é zero
  if (r1 == r2) {
    return 0;
  }

  // Busca o endereço do vértice que armazena r1
  ListaVertice* raiz = buscaVertical(r1);
  if (!raiz){
    cout << "Vertice raiz não encontrado." << endl;
    return -1;
  }

  // 1. Desmarcar todos os vértices
  for (int i = 0; i < vetor_vertices.size(); i++) {
    vetor_vertices.at(i)->setStatus(false);
  }

  // Inicializa variáveis
  vector<Noh<ListaVertice>*> QNoh;
  Noh<ListaVertice>* vNoh;
  Noh<ListaVertice>* wNoh;
  Vizinho* w;
  Arvore<ListaVertice> arvore(raiz);
  Noh<ListaVertice>* sNoh = arvore.getRaiz();

  // 2. Definir Fila Q vazia
  QNoh = {};

  // 3. Marcar s e inserir s na fila Q
  sNoh->getVertice()->setStatus(true);
  QNoh.push_back(sNoh);
  //cout << "Inserir " << sNoh->getVertice()->getRotulo() << " na fila Q" << endl;
  sNoh->setPai(nullptr);
  sNoh->setNivel(0);

  // 4. Enquanto Q não estiver vazia
  while (QNoh.size() > 0) {

    // 5. Retirar v de Q
    vNoh = QNoh.front();
    QNoh.erase(QNoh.begin());
    //cout << "Remover " << vNoh->getVertice()->getRotulo() << " da fila Q" << endl;
    //cout << "Explorar " << vNoh->getVertice()->getRotulo() << endl;

    // 6. Para todo vizinho w de v faça
    w = vNoh->getVertice()->getVizinho();
    while (w) {
      
      // 7. Se w não estiver marcado
      if (!w->getVertice()->getStatus()) {

        // 8. Marcar w
        w->getVertice()->setStatus(true);

        // 9. Inserir w em Q
        wNoh = new Noh<ListaVertice>(w->getVertice());
        QNoh.push_back(wNoh);
        //cout << "Inserir " << wNoh->getVertice()->getRotulo() << " na fila Q" << endl;
        wNoh->setPai(vNoh);
        wNoh->setNivel(vNoh->getNivel()+1);

        // Retorna Distancia caso w == r2
        if (w->getVertice()->getRotulo() == r2) {
          cout << "Término do cálculo da distância..." << endl;
          return wNoh->getNivel();
        }
      }

      w = w->getVizinho();
    }
  }
    
  cout << "Término do cálculo da distância.." << endl;
  cout << "Vértice destino Não encontrado!" << endl;
  return -1;
}

int Lista::diametroSemPeso() {
  cout << "Iniciando cálculo do diametro..." << endl;

  // Inicializar variáveis
  int maiorDiametro = 0;
  ListaVertice* raiz;
  vector<Noh<ListaVertice>*> QNoh;
  Noh<ListaVertice>* vNoh;
  Noh<ListaVertice>* wNoh;
  Vizinho* w;
  Noh<ListaVertice>* sNoh;
  
  // Para cada Componente Conexa
  for (int i = 0; i < vetor_vertices.size(); i++) {
    
    // 0. Desmarcar todos os vértices
    for (int i = 0; i < vetor_vertices.size(); i++) {
      vetor_vertices.at(i)->setStatus(false);
    }

    // 1. Definir raiz s
    raiz = vetor_vertices.at(i);  
    Arvore<ListaVertice> arvore(raiz);
    sNoh = arvore.getRaiz();

    // 2. Definir Fila Q vazia
    QNoh = {};
    
    // 3. Marcar s e inserir s na fila Q
    sNoh->getVertice()->setStatus(true);
    // cout << "Marcar " << sNoh->getVertice()->getRotulo() << endl;
    QNoh.push_back(sNoh);
    // cout << "Inserir " << sNoh->getVertice()->getRotulo() << " na fila Q" << endl;
    sNoh->setPai(nullptr);
    sNoh->setNivel(0);
    
    // 4. Enquanto Q não estiver vazia
    while (QNoh.size() > 0) {

      // 5. Remover v da fila Q
      vNoh = QNoh.front();
      QNoh.erase(QNoh.begin());
      // cout << "Remover " << vNoh->getVertice()->getRotulo() << " da fila Q" << endl;
      // cout << "Explorar " << vNoh->getVertice()->getRotulo() << endl;

      // 6. Para todo vizinho w de v faça
      w = vNoh->getVertice()->getVizinho();
      while (w) {

        // 7. Se w não estiver marcado
        if (!w->getVertice()->getStatus()) {

          // 8. Marcar w
          w->getVertice()->setStatus(true);
          // cout << "Marcar " << w->getVertice()->getRotulo() << endl;

          // 9. inserir w em Q
          wNoh = new Noh<ListaVertice>(w->getVertice());
          QNoh.push_back(wNoh);
          // cout << "Inserir " << wNoh->getVertice()->getRotulo() << " na fila Q" << endl;
          wNoh->setPai(vNoh);
          wNoh->setNivel(vNoh->getNivel()+1);
        }

        w = w->getVizinho();
      }
    }

    // Atualizar maiorDiametro
    if (wNoh->getNivel() > maiorDiametro) {
      maiorDiametro = wNoh->getNivel();
    }

    // Destroir arvore atual
    arvore.~Arvore();
  }
  
  cout << "Diametro calculado com sucesso!" << endl;

  return maiorDiametro;
}

void Lista::arvoreBFS(int raizRotulo, string arquivoDestino) {
  cout << "Construindo Árvore Geradora (BFS)..." << endl;

  // 0. Encontrar o vértice referente ao rótulo informado via parâmetro
  ListaVertice* raiz = this->buscaVertical(raizRotulo);
  if (!raiz){
    cout << "Vértice raiz não encontrado." << endl;
    return ;
  }
  
  // 1. Desmarcar todos os vértices
  for (int i = 0; i < vetor_vertices.size(); i++) {
    vetor_vertices.at(i)->setStatus(false);
  }

  // 2. Definir Fila Q vazia
  vector<Noh<ListaVertice>*> QNoh;
  Noh<ListaVertice>* vNoh;
  Noh<ListaVertice>* wNoh;
  Vizinho* w;
  
  // 3. Marcar s e inserir s na fila Q
  Arvore<ListaVertice> arvore(raiz);
  Noh<ListaVertice>* sNoh = arvore.getRaiz();
  sNoh->getVertice()->setStatus(true);
  //cout << "Marcar " << sNoh->getVertice()->getRotulo() << endl;
  QNoh.push_back(sNoh);
  //cout << "Inserir " << sNoh->getVertice()->getRotulo() << " na fila Q" << endl;
  sNoh->setPai(nullptr);
  sNoh->setNivel(0);
  
  //Imprimir Cabeçalho
  ofstream outfile(arquivoDestino);
  outfile << "~~ Arvore Geradora (BFS) ~~" << endl << endl;
    
    // Imprimir novo vértice (raiz)
    outfile << "Vertice: " << sNoh->getVertice()->getRotulo() << ";\t\t";
    outfile << "Pai: nullptr;\t\t";
    outfile << "Nível: 0" << endl;
    
  // 4. Enquanto Q não estiver vazia
  while (QNoh.size() > 0) {

    // 5.
    vNoh = QNoh.front();
    QNoh.erase(QNoh.begin());
    //cout << "Remover " << vNoh->getVertice()->getRotulo() << " da fila Q" << endl;
    //cout << "Explorar " << vNoh->getVertice()->getRotulo() << endl;

    // 6. Para todo vizinho w de v faça
    w = vNoh->getVertice()->getVizinho();
    while (w) {

      // 7. Se w não estiver marcado
      if (!w->getVertice()->getStatus()) {

        // 8. Marcar w
        w->getVertice()->setStatus(true);

        //cout << "Marcar " << w->getVertice()->getRotulo() << endl;

        // 9. inserir w em Q
        wNoh = new Noh<ListaVertice>(w->getVertice());
        QNoh.push_back(wNoh);
        //cout << "Inserir " << wNoh->getVertice()->getRotulo() << " na fila Q" << endl;
        wNoh->setPai(vNoh);
        wNoh->setNivel(vNoh->getNivel()+1);

        // Imprimir novo vértice
        outfile << "Vertice: " << wNoh->getVertice()->getRotulo() << ";\t\t";
        outfile << "Pai: " << wNoh->getPai()->getVertice()->getRotulo() << ";\t\t";
        outfile << "Nível: " << wNoh->getNivel()<< endl;
      }

      w = w->getVizinho();
    }
  }

  cout << "Árvore construída com sucesso!" << endl << endl;
}

void Lista::arvoreDFS(int raizRotulo, string arquivoDestino) {
  cout << "Construindo Árvore Geradora (DFS)...\n\n" << endl;

  // Encontrar o vértice referente ao rótulo informado via parâmetro
  ListaVertice* raiz = this->buscaVertical(raizRotulo);
  if (!raiz){
    cout << "Vértice raiz não encontrado!\n" << endl;
    return ;
  }

  // Inicializar variáveis
  vector<Noh<ListaVertice>*> pNoh;
  Arvore<ListaVertice> arvore(raiz);
  Noh<ListaVertice>* sNoh = arvore.getRaiz();
  Noh<ListaVertice>* uNoh;
  Noh<ListaVertice>* vNoh;
  Vizinho* v;
  vector<Vizinho*> pVizinho;
  int i = 0;
  
  //Imprimir Cabeçalho
  ofstream outfile(arquivoDestino);
  outfile << "~~ Arvore Geradora (DFS) ~~\n" << endl;

  // 1. DFS(s)
  // ArvoreDFS(raizRotulo, arquivoDestino);

  // 2. Desmarcar todos os vértices
  for (int i = 0; i < vetor_vertices.size(); i++) {
    vetor_vertices.at(i)->setStatus(false);
  }

  // 3. Definir pilha P com um elemento s
  pNoh = {sNoh};
  sNoh->setNivel(0);
  sNoh->setPai(nullptr);
  outfile << "Vertice: " << sNoh->getVertice()->getRotulo() << ";\t Pai: nullptr;\tNível: 0" << endl;

  // /* [DEBUG] */ cout << "Insere " << sNoh->getVertice()->getRotulo();
  // /* [DEBUG] */ cout << ";    P = {1}";
  // /* [DEBUG] */ cout << ";    sNoh =  " << sNoh->getVertice()->getRotulo();
  // /* [DEBUG] */ cout << ";    Pai =  nullptr";
  // /* [DEBUG] */ cout << ";    Nivel = 0" << endl;

  // 4. Enquanto P não estiver vazia
  while (pNoh.size() > 0) {

    // 5. Remover u de P // no topo da pilha
    uNoh = pNoh.back();
    pNoh.pop_back();
    while (!uNoh) {
      if (pNoh.size() < 1) {
        return ;
      }
      sNoh = sNoh->getPai();
      // cout << "Remove nullptr; sNoh = " << sNoh->getVertice()->getRotulo() << endl;
      uNoh = pNoh.back();
      pNoh.pop_back();
      if (pNoh.size() < 1) {
        return ;
      }
    }
    // /* [DEBUG] */ debugDFS("Remove ", uNoh, sNoh, pNoh);
    // 6. Se u não estiver marcado
    if (!uNoh->getVertice()->getStatus()) {
      
      // 7. Marcar u
      uNoh->getVertice()->setStatus(true);

      if (uNoh != arvore.getRaiz()) {
        uNoh->setPai(sNoh);
        uNoh->setNivel(sNoh->getNivel()+1);
        outfile << "Vertice: " << uNoh->getVertice()->getRotulo();
        outfile << ";\t Pai: " << uNoh->getPai()->getVertice()->getRotulo();
        outfile << ";\tNível: " << uNoh->getNivel() << endl;
      }
      sNoh = uNoh;
      // /* [DEBUG] */ debugDFS("Marca ", uNoh, sNoh, pNoh);
      
      // 8. Para cada aresta (u,v) incidente a u
      v = uNoh->getVertice()->getVizinho();
      
      // Inserir v em pVizinho em ordem crescente
      pVizinho = {};
      while (v) {
        pVizinho.push_back(v);
        v = v->getVizinho();
      }

      // 9. Inserir vNoh em PNoh // no topo (em ordem decrescente)
      pNoh.push_back(nullptr);
      i = pVizinho.size()-1;
      while (i >= 0) {
        v = pVizinho.at(i);
        vNoh = new Noh<ListaVertice>(v->getVertice());
        pNoh.push_back(vNoh);
        i--;
        // /* [DEBUG] */ debugDFS("Insere ", vNoh, sNoh, pNoh);
      }
    }
  }  
}

/* [DEBUG_DFS]
void Lista::debugDFS(string acao,Noh* uNoh, Noh* sNoh, vector<Noh*> pNoh) {
  cout << acao << uNoh->getVertice()->getRotulo();
  cout << ";    P = {";
  int tamanho = pNoh.size();

  if (tamanho > 0) {
    for (int i = 0; i < pNoh.size(); i++) {
      if (pNoh.at(i)) {
        cout << pNoh.at(i)->getVertice()->getRotulo() << ", ";
      } else {
        cout << "nullptr, ";
      }
    }
    cout << "}";
  } else {
    cout << "}";
  }

  cout << ";    sNoh =  " << sNoh->getVertice()->getRotulo();
  if (uNoh->getPai()){ 
    cout << ";    Pai =  " << uNoh->getPai()->getVertice()->getRotulo();
  } else {
    cout << ";    Pai = nullptr";
  }
  cout << ";    Nivel = " << uNoh->getNivel() << endl;
}
*/

void Lista::setNArestas(int nA) { nArestas = nA; }
void Lista::setGrauMinimo(int gminimo) { grauMinimo = gminimo; }
void Lista::setGrauMaximo(int gmaximo) { grauMaximo = gmaximo; }
void Lista::setGrauMedio(double gmedio) { grauMedio = gmedio; }
void Lista::setGrauMediana(double gmediana) { grauMediana = gmediana; }
void Lista::setNComponentes(int nComp) { nComponentes = nComp; }

int Lista::getNArestas() { return nArestas; }
int Lista::getGrauMinimo() { return grauMinimo; }
int Lista::getGrauMaximo() { return grauMaximo; }
double Lista::getGrauMedio() { return grauMedio; }
double Lista::getGrauMediana() { return grauMediana; }
int Lista::getNComponentes() { return nComponentes; }
