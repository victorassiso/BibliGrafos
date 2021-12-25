#include "matrizVertice.h"
#include <iostream>

MatrizVertice::MatrizVertice(int r)
{
  rotulo = r;
  status = false;
}

MatrizVertice::~MatrizVertice() {}

int MatrizVertice::getRotulo() { return rotulo; }

bool MatrizVertice::getStatus() { return status; }
void MatrizVertice::setStatus(bool s) {status = s;}