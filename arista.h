#ifndef ARISTA_H_INCLUDED
#define ARISTA_H_INCLUDED
#include <iostream>
//#include "vertice.h"
using namespace std;

class Vertice;

class Arista{
private:
    Arista* sig;
    Vertice* destino;
    int peso1;
    double peso2;
public:
    Arista(Vertice* destino);
    ~Arista();
    void asignarSiguiente(Arista* sig);
    void asignarPeso1(int peso1);
    void asignarPeso2(double peso2);

    Arista* consultarSiguiente();
    Vertice* ConsultarDestino();
    int cunsultarPeso1();
    double consultarPeso2();

};


#endif // ARISTA_H_INCLUDED
