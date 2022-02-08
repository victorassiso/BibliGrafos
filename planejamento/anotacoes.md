# BFS
```C++
// 1. Desmarcar todos os vértices
  for (int i = 0; i < vetor_vertices.size(); i++) {
    vetor_vertices.at(i)->setStatus(false);
  }

  // 2. Definir Fila Q vazia
  vector<Vertice*> Q;
  Vertice* v;
  Vizinho* w;

  // 3. Marcar s e inserir s na fila Q
  Vertice* s = raiz;
  s->setStatus(true);
  Q.push_back(s);

  // 4. Enquanto Q não estiver vazia
  while (Q.size() > 0) {
    
    // 5. Retirar v de Q
    v = Q.front();
    Q.erase(Q.begin());

    // 6. Para todo vizinho w de v faça
    w = v->getVizinho();
    while (w){

      // 7. Se w não estiver marcado
      if (!w->getVertice()->getStatus()) {

        // 8. Marcar w
        w->getVertice()->setStatus(true);
        
        // 9. Inserir w em Q
        Q.push_back(w->getVertice());
      }
      w = w->getVizinho();
    }
  }
```

# BFS Para Múltiplas Componentes Conexas
```C++
// 1. Desmarcar todos os vértices
  for (int i = 0; i < vetor_vertices.size(); i++) {
    vetor_vertices.at(i)->setStatus(false);
  }

  // 2. Definir Fila Q vazia
  vector<Vertice*> Q;
  Vertice* v;
  Vizinho* w;
  Vertice* s;

  // 3. Marcar s e inserir s na fila Q
  s = raiz;
  s->setStatus(true);
  Q.push_back(s);

  int i = 0;
  bool existeNovaComponenteConexa = true;
  while (existeNovaComponenteConexa) {

    // 4. Enquanto Q não estiver vazia
    while (Q.size() > 0) {
      
      // 5. Retirar v de Q
      v = Q.front();
      Q.erase(Q.begin());

      // 6. Para todo vizinho w de v faça
      w = v->getVizinho();
      while (w){

        // 7. Se w não estiver marcado
        if (!w->getVertice()->getStatus()) {

          // 8. Marcar w
          w->getVertice()->setStatus(true);
          
          // 9. Inserir w em Q
          Q.push_back(w->getVertice());
        }

        w = w->vizinho();
      }
    }

    // Verifica se ainda há vértices desconhecidos, isto é, uma nova componente conexa
    while (vetor_vertices.at(i)->getStatus() && i < vetor_vertices.size()) {
      i++;
    }

    // 3. Marcar s e inserir s na fila Q (Para nova componente Conexa, caso haja uma)
    if (i != vetor_vertices.size()-1) {
      s = vetor_vertices.at(i);
      s->setStatus(true);
      Q.push_back(s);
    } else {
      existeNovaComponenteConexa = false;
    }

  };
```

# Árvore Geradora (BFS) com múltiplas componentes conexas
```C++
cout << "Iniciando Busca em Largura..." << endl;
  cout << "Construindo Árvore Geradora..." << endl;

  // 0. Encontrar o vértice referente ao rótulo informado via parâmetro
  ListaVertice* raiz = this->buscaVertical(raizRotulo);
  if (!raiz){
    cout << "Vertice raiz não encontrado." << endl;
    return ;
  }

  // 1. Desmarcar todos os vértices
  for (int i = 0; i < vetor_vertices.size(); i++) {
    vetor_vertices.at(i)->setStatus(false);
  }

  // 2. Definir Fila Q vazia
  vector<Noh*> QNoh;
  Noh* vNoh;
  Noh* wNoh;
  Vizinho* w;

  // 3. Marcar s e inserir s na fila Q
  Arvore arvore(raiz);
  Noh* sNoh = arvore.getRaiz();
  sNoh->getVertice()->setStatus(true);
  //cout << "Marcar " << sNoh->getVertice()->getRotulo() << endl;
  QNoh.push_back(sNoh);
  //cout << "Inserir " << sNoh->getVertice()->getRotulo() << " na fila Q" << endl;
  sNoh->setPai(nullptr);
  sNoh->setNivel(0);
  
  //Imprimir Cabeçalho
  ofstream outfile("output/ArvoreBFS.txt");
  outfile << "~~Arvore Geradora (BFS)~~\n";

  // Para cada Componente Conexa
  int i = 0;
  int nComponente = 1;
  bool existeNovaComponenteConexa = true;
  while (existeNovaComponenteConexa) {
    
    outfile << "\nComponente : " << to_string(nComponente) << endl;
    // Imprimir novo vértice (raiz)
    outfile << "Vertice: " << to_string(sNoh->getVertice()->getRotulo());
    outfile << "; Nível: " << to_string(sNoh->getNivel()) << endl;
    
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
          wNoh = new Noh(w->getVertice());
          QNoh.push_back(wNoh);
          //cout << "Inserir " << wNoh->getVertice()->getRotulo() << " na fila Q" << endl;
          wNoh->setPai(vNoh);
          wNoh->setNivel(vNoh->getNivel()+1);

          // Imprimir novo vértice
          outfile << "Vertice: " << to_string(wNoh->getVertice()->getRotulo());
          outfile << "; Nível: " << to_string(wNoh->getNivel()) << endl;
        }

        w = w->getVizinho();
      }
    }

    // Verifica se ainda há vértices desconhecidos, isto é, uma nova componente conexa
    while (i < vetor_vertices.size() && vetor_vertices.at(i)->getStatus()) {
      i++;
    }

    // 3. Marcar s e inserir s na fila Q (Para nova componente Conexa, caso haja uma)
    if (i < vetor_vertices.size()) {
      arvore.~Arvore();
      Arvore arvore(vetor_vertices.at(i));
      sNoh = arvore.getRaiz();
      sNoh->getVertice()->setStatus(true);
      //cout << "Marcar " << sNoh->getVertice()->getRotulo() << endl;
      QNoh.push_back(sNoh);
      //cout << "Inserir " << sNoh->getVertice()->getRotulo() << " na fila Q" << endl;
      sNoh->setPai(nullptr);
      sNoh->setNivel(0);
      nComponente++;
    } else {
      existeNovaComponenteConexa = false;
    }

  }
  cout << "Árvore construída com sucesso!" << endl;
```
Arquivo de Saída "info"
  [ ] - Número de vértices
    Definido direto no momento da leitura da primeira linha do arquivo txt em listaEstrutura.cpp

  [ ] - Número de Arestas
    
  [ ] - Grau Mínimo
  [ ] - Grau Máximo
  [ ] - Grau Médio
  [ ] - Mediana de Grau
  [ ] - Número de Componentes Conexas



# Passo a Passo DFS (grafo_DFS)

Insere 1        P = {1}; sNoh = 1; 1.Pai = nullptr; 1.Nivel = 0
Remove 1        P = {};
Marca 1                                       sNoh = 1
Insere nullptr  P = {nullptr}
Insere 5        P = {nullptr, 5}
Insere 2        P = {nullptr, 5,2}
Remove 2        P = {nullptr, 5}
Marca 2                                       2.Pai = 1;    2.Nivel = 1;    sNoh = 2;   
Insere nullptr  P = {nullptr, 5, nullptr}
Insere 1        P = {nullptr, 5, nullptr, 1}
Remove 1        P = {nullptr, 5, nullptr}
Remove nullptr  P = {nullptr, 5}              sNoh = 1;
Remove 5        P = {nullptr}
Marca 5                                       5.Pai = 1;    5.Nivel = 1;    sNoh = 5;
Insere nullptr  P = {nullptr, nullptr}
Insere 7        P = {nullptr, nullptr, 7}
Insere 1        P = {nullptr, nullptr, 7, 1}
Remove 1        P = {nullptr, nullptr, 7}
Remove 7        P = {nullptr, nullptr}
Marca 7                                       7.Pai = 5;    7.Nivel = 2;    sNoh = 7;
Insere nullptr  P = {nullptr, nullptr, nullptr}
Insere 6        P = {nullptr, nullptr, nullptr, 6}
Insere 8        P = {nullptr, nullptr, nullptr, 6, 8}
Insere 5        P = {nullptr, nullptr, nullptr, 6, 8, 5}
Remove 5        P = {nullptr, nullptr, nullptr, 6, 8}
Remove 8        P = {nullptr, nullptr, nullptr, 6}
Marca 8                                       8.Pai = 7;    8.Nivel = 3;    sNoh = 8;
Insere nullptr  P = {nullptr, nullptr, nullptr, 6, nullptr}
Insere 7        P = {nullptr, nullptr, nullptr, 6, nullptr, 7}
Insere 4        P = {nullptr, nullptr, nullptr, 6, nullptr, 7, 4}
Remove 4        P = {nullptr, nullptr, nullptr, 6, nullptr, 7}
Marca 4                                       4.Pai = 8;    4.Nivel = 4;    sNoh = 4;
Insere nullptr  P = {nullptr, nullptr, nullptr, 6, nullptr, 7, nullptr}
Remove nullptr  {nullptr, nullptr, nullptr, 6, nullptr, 7}                  sNoh = 8;
Remove 7        P = {nullptr, nullptr, nullptr, 6, nullptr}
Remove nullptr  P = {nullptr, nullptr, nullptr, 6}                          sNoh = 7;
Remove 6        P = {nullptr, nullptr, nullptr}
Marca 6                                      6.Pai = 7;    6.Nivel = 3;    sNoh = 6;
Insere nullptr  P = {nullptr, nullptr, nullptr, nullptr}
Insere 3        P = {nullptr, nullptr, nullptr, 3}
Insere 7        P = {nullptr, nullptr, nullptr, 3, 7}
Remove 7        P = {nullptr, nullptr, nullptr, 3}
Remove 3        P = {nullptr, nullptr, nullptr}
Marca 3                                      3.Pai = 6;    3.Nivel = 4;    sNoh = 3;
Insere nullptr  P = {nullptr, nullptr, nullptr, nullptr}
Insere 6        P = {nullptr, nullptr, nullptr, nullptr, 6}
Remove 6        P = {nullptr, nullptr, nullptr, nullptr}
Remove nullptr  P = {nullptr, nullptr, nullptr}           sNoh = 6;
Remove nullptr  P = {nullptr, nullptr}           sNoh = 7;
Remove nullptr  P = {nullptr}           sNoh = 5;
Remove nullptr  P = {}           sNoh = 1;


# Função auxiliar de DEBUG da DFS
``` C++
// [DEBUG_DFS]
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
```
