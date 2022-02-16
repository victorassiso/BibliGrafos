# Algoritmo de Dijsktra Otimizado
```C++
// 1. Dijkstra(G, s)
// 2. Para cada vértice v
// 3. dist[v] = infinito
// 4. Define conjunto S = 0 // inicia vazio
// 5. dist[s] = 0
// 6. Enquanto S != V
// 7. Selecione u em V-S, tal que dist[u] é mínima
// 8. Adicione u em S
// 9. Para cada vizinho v de u faça
// 10. Se dist[v] > dist[u] + w(u,v) então
// 11. dist[v] = dist[u] + w(u,v)
// 12.Retorna dist[]

// S é o conjunto dos vértices explorados
// V é o conjunto dos vértices do grafo
// w(u,v) é o peso da aresta (u,v)
// dist[v] é a melhor estimativa da distância de s a v
// Se v é explorado, então dist[v] é a distância de s a v
```

# Algoritmo de Prim
``` C++
// 1.Prim(G,o)
// 2. Para cada vértice v
// 3. custo[v] = infinito
// 4. Define conjunto S = 0 // vazio
// 5. custo[o] = 0
// 6. Enquanto S != V
// 7. Selecione u em V-S, tal que custo[u] é mínimo
// 8. Adicione u em S
// 9. Para cada vizinho v de u faça
// 10. Se custo[v] > w(u,v) então
// 11. custo[v] = w(u,v)
```
