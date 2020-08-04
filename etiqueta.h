#ifndef ETIQUETA_H_INCLUDED
#define ETIQUETA_H_INCLUDED
#include <list>
#include "vertice.h"

class Etiqueta{
private:
    Vertice* vertice;
    //Vertice* anterior;
    list<Vertice*> anterior;
    int pesoAcumulado;
    int iteracion;
public:
    Etiqueta(Vertice* actual);
    ~Etiqueta();

    void setAnterior(Vertice* anterior);
    void sumoAnterior(Vertice* anterior);
    void setPesoAcumulado(int peso);
    void setIteracion(int iteracion);

    Vertice* getVertice();
    list<Vertice*> getAnterior();
    int getPesoAcumulado();
    int getIteracion();
};


#endif // ETIQUETA_H_INCLUDED
