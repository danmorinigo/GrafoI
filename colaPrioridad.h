#ifndef COLAPRIORIDAD_H_INCLUDED
#define COLAPRIORIDAD_H_INCLUDED
#include "nodoColaPrioridad.h"
//#include "etiqueta.h"
typedef int Dato;
class ColaPrioridad{
private:
    NodoColaPrioridad* primero;
    NodoColaPrioridad* primeroSegunPrioridad;
    NodoColaPrioridad* ultimo;
    int criterioOrden;//1-> pesoEntero / 2-> pesoDouble
public:
    ColaPrioridad(int criterioOrden);
    bool vacia();
    Vertice* topAndPop();
    Vertice* topVertice();
    int topPrioridad();
    int topEntero();
    double topDouble();
    void pop();
    void push(Vertice* evaluado, int pesoEntero, double pesoDouble, int iteracion);
    /*
    void insertar(BSTNode<Aeropuerto*>* aIngresar);
    */
    ~ColaPrioridad();
private:
    //NodoCola* anterior(int posicion);
};


#endif // COLAPRIORIDAD_H_INCLUDED
