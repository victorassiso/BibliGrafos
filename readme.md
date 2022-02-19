# BibliGrafos

## Biblioteca de manipulação de grafos.

A BibliGrafos oferece estruturas de dados para o armazenamento e manipulação de grafos não-direcionados, com pesos positivos ou sem pesos.

Esta biblioteca é a implementação do trabalho da disciplina Teoria dos Grafos, realizada pelos alunos de Engenharia:
- Victor Assis
- Nayara Gomes

### 1. Estruturas de dados:
A BibliGrafos oferece dois tipos de estrutura de dados para se armazenar um grafo:

- Lista de Adjacência
- Matriz de Adjacência

### 2. Métodos:
Uma vez criada a estrutura do grafo, será possível utilizar diversos métodos para se buscar informações sobre o mesmo. Alguns métodos irão gerar um arquivo de saída com o resultado das leituras, outros irão retornar o resultado, outros farão os dois.

A seguir, a lista de métodos e suas funcionalidades:

**1. info**

**Atributos:** [nome_do_arquivo_de_saída]\
**Retorno:** void

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

**2. arvoreBFS**
    
**Atributos:** [rótulo_raiz], [nome_do_arquivo_de_saída]\
**Retorno:** void

Gera um arquivo de saída com uma árvore geradora através da Busca em Largura. O arquivo contém uma lista dos vértices da árvore, seus níveis e pais.
    

**3. arvoreDFS**

**Atributos:** [rótulo_raiz], [nome_do_arquivo_de_saída]\
**Retorno:** void

Gera um arquivo de saída com a árvore geradora DFS. O arquivo contém uma lista dos vértices da árvore, seus níveis e pais.
    

**4. distanciaBFS**

**Atributos:** [rótulo_v1], [rótulo_v2]\
**Retorno:** [distancia]

Retorna um valor inteiro representando a distância entre os vértices v1 e v2.

**5. diametroBFS**

**Atributos:** void
**Retorno:** [distancia]

Retorna um valor inteiro representando o diâmetro do grafo. Ou seja, a distância do maior caminho mínimo do grafo.

**6. arvoreMST**

**Atributos:** [rótulo_raiz], [nome_do_arquivo_de_saída]\
**Retorno:** [custo]

Gera um arquivo de saída com uma árvore geradora através do algoritmo Prim e retorna o custo total da árvore. Isto é, a soma do peso de todas as arestas da árvore.

**7. caminhoMinimo**

**Sobrecarga 1:**

**Atributos:** [rótulo_v1], [nome_do_arquivo_de_saída]\
**Retorno:** void

Gera um arquivo de saída contendo o caminho mínimo entre o vértice v1 e todos os demais vértices, bem como a distância de tais caminhos.

**Sobrecarga 2:**

**Atributos:** [rótulo_v1], [rótulo_v2], [nome_do_arquivo_de_saída]\
**Retorno:** void

Gera um arquivo de saída contendo o caminho mínimo entre o vértice v1 e o vértice v2, bem como a distância entre os dois vértices.