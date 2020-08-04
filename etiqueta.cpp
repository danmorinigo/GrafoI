#include "etiqueta.h"

Etiqueta::Etiqueta(Vertice* actual){
    vertice = actual;
    //anterior = 0;
    pesoAcumulado = 0;
    iteracion = 0;
}
Etiqueta::~Etiqueta(){
}

void Etiqueta::setAnterior(Vertice* anterior){
    this->anterior.push_back(anterior);
    //this->anterior = anterior;
}
void Etiqueta::setPesoAcumulado(int peso){
    this->pesoAcumulado = peso;
}
void Etiqueta::setIteracion(int iteracion){
    this->iteracion = iteracion;
}

Vertice* Etiqueta::getVertice(){
    return vertice;
}
list<Vertice*> Etiqueta::getAnterior(){
    return anterior;
}
int Etiqueta::getPesoAcumulado(){
    return pesoAcumulado;
}
int Etiqueta::getIteracion(){
    return iteracion;
}
