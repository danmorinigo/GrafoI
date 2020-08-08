#ifndef NODOCOLAPRIORIDAD_H_INCLUDED
#define NODOCOLAPRIORIDAD_H_INCLUDED
#include<iostream>
#include "vertice.h"
const bool MEMORIA = false;
class NodoColaPrioridad{
private:
    Vertice* vertice;
    int prioridad;
    int pesoEntero;
    double pesoDouble;
    NodoColaPrioridad* siguiente;
public:
    NodoColaPrioridad(Vertice* vertice, int prioridad, int pesoEntero, double pesoDouble);
    Vertice* obtenerVertice();
    int getPrioridad();
    int getEntero();
    double getDouble();
    void setSiguiente(NodoColaPrioridad* siguiente);
    NodoColaPrioridad* getSiguiente();
    ~NodoColaPrioridad();
};
#endif // NODOCOLAPRIORIDAD_H_INCLUDED
