#ifndef SAIDA_H
#define SAIDA_H

#include "lista.h"
#include <bits/stdc++.h>

class Saida: public Lista
{
  public:
    Saida(string);
    ~Saida();

    int getNumeroDeVertices();
    int getNumeroDeArestas();
    int getGrauMinimo();
    int getGrauMaximo();
    double getGrauMedio();
    int getMedianaDeGrau();

  private:
    int nVertices; //OK
    int nArestas; //OK
    int grauMinimo; //OK
    int grauMaximo; //OK
    double grauMedio; //OK
    int grauMediana; //OK
    
};

#endif