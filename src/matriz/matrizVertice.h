#ifndef MATRIZVERTICE_H
#define MATRIZVERTICE_H

using namespace std;

// Diz que a classe existe sem inicializá-la
class MatrizVertice
{
  public:
    MatrizVertice(int rotulo);
    ~MatrizVertice();
    
    int getRotulo();
    bool getStatus();

    void setStatus(bool status);
  private:
    int rotulo;
    bool status;
};

#endif