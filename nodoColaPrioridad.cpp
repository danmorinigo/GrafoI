#include "nodoColaPrioridad.h"
NodoColaPrioridad::NodoColaPrioridad (Vertice* vertice, int prioridad, int pesoEntero, double pesoDouble){
    if(MEMORIA) std::cout << "Constructor NodoColaPrioridad (" << this << ")\n";
    this->vertice = vertice;
    this->prioridad = prioridad;
    this->pesoEntero = pesoEntero;
    this->pesoDouble = pesoDouble;
    this->siguiente = 0;
}
Vertice* NodoColaPrioridad::obtenerVertice(){
    return this->vertice;
}
int NodoColaPrioridad::getPrioridad(){
    return this->prioridad;
}
int NodoColaPrioridad::getEntero(){
    return this->pesoEntero;
}
double NodoColaPrioridad::getDouble(){
    return this->pesoDouble;
}
void NodoColaPrioridad::setSiguiente(NodoColaPrioridad* siguiente){
    this->siguiente = siguiente;
}

NodoColaPrioridad* NodoColaPrioridad::getSiguiente(){
    return this->siguiente;
}


NodoColaPrioridad::~NodoColaPrioridad(){
    if(MEMORIA) std::cout << "Destructor NodoColaPrioridad (" << this << ")\n";
}
