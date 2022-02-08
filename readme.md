# Em construção...

## A Grafos-lib é uma biblioteca de manipulação de grafos.

### 1. Estrutura de dados:
A Grafos-lib oferece dois tipos de estrutura de dados para se armazenar um grafo:

- Lista de Adjacência
- Matriz de Adjacência

As estruturas são implementadas através de métodos construtores da classe Lista e da classe Matriz.

### 2. Métodos:
Uma vez criada a estrutura do grafo, será possível utilizar diversos métodos para se buscar informações sobre o grafo. Alguns métodos irão gerar um arquivo de saída com o resultado das leituras, outros irão retornar o resultado.

As informações são organizadas da seguinte forma através dos métodos: 

1. info

    Atributos: void\
    Retorno: void

    Gera um arquivo de saída com as seguintes informações:
    - Número de vértices
    - Número de Arestas
    - Grau Mínimo
    - Grau Máximo
    - Grau Médio
    - Mediana de Grau
    - Número de Componentes Conexas
    - Lista de vertices separados por componente conexa (em ordem decrescente de tamanho)
    - Tamanho de cada componente

2. arvoreBFS
    
    Atributos: vértice raiz\
    Retorno: void

    Gera um arquivo de saída com a árvore geradora BFS através de uma Busca em Largura. O arquivo contém uma lista dos vértices da árvore, seus níveis e pais.
    

3. arvoreDFS

    Atributos: vértice raiz\
    Retorno: void

    Gera um arquivo de saída com a árvore geradora DFS. O arquivo contém uma lista dos vértices da árvore, seus níveis e pais.
    

4. distancia

    Atributos: vértice v1, vértice v2\
    Retorno: int distancia

    Retorna a distância entre os vértices v1 e v2.

5. diametro

    Atributos: void
    Retorno: int diametro

    Retorna o diametro do grafo.