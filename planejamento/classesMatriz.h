class Vertice
{
  public:
    Vertice(int);
    ~Vertice();
    
    int getRotulo();
    bool getStatus();
    Vertice* getPai();
    int getNivel();

    void setStatus(bool);
    void setPai(Vertice*);
    void setNivel(int);

  private:
    int rotulo;
    bool statusBusca; //false - Não explorado; true - Explorado;
    Vertice* pai;
    int nivel;
};

class Matriz
{
  
};