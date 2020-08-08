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
    while(!this->anterior.empty()){// aca lo reemplaza
        (this->anterior).pop_front();//Digamos que reemplaza a el o los anteriores
    }
    (this->anterior).push_front(anterior);//inserta este peso
}
void Etiqueta::sumoAnterior(Vertice* anterior){
    this->anterior.push_back(anterior);//aca agrega un nodo a la lista
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
