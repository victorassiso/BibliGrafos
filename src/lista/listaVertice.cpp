#include "listaVertice.h"

ListaVertice::ListaVertice(int r)
{
  rotulo = r;
  vizinho = nullptr;
  statusBusca = 0;
}

ListaVertice::~ListaVertice(){}

void ListaVertice::setVizinho(Vizinho* ptr) { vizinho = ptr; }
void ListaVertice::setStatus(bool s) { statusBusca = s; }

Vizinho* ListaVertice::getVizinho() { return vizinho; }
bool ListaVertice::getStatus() { return statusBusca; }
int ListaVertice::getRotulo() { return rotulo; }
