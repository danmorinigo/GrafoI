#ifndef ETIQUETA_H_INCLUDED
#define ETIQUETA_H_INCLUDED

#include "vertice.h"

class Etiqueta{
private:
    Vertice* vertice;
    Vertice* anterior;
    int pesoAcumulado;
    int iteracion;
public:
    Etiqueta(Vertice* actual);
    ~Etiqueta();

    void setAnterior(Vertice* anterior);
    void setPesoAcumulado(int peso);
    void setIteracion(int iteracion);

    Vertice* getVertice();
    Vertice* getAnterior();
    int getPesoAcumulado();
    int getIteracion();
};


#endif // ETIQUETA_H_INCLUDED
