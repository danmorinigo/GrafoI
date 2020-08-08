#include "etiqueta.h"

Etiqueta::Etiqueta(Vertice* actual){
    vertice = actual;
    //anterior = 0;
    pesoAcumulado = 0;
    pesoDouble = 0.0;
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
    bool eraPadre = false;
    list<Vertice*>::iterator i;
    i = this->anterior.begin();
    while(!eraPadre && i != this->anterior.end()){
        if(*i == anterior){
            eraPadre = true;
        }
        i++;
    }
    if (!eraPadre){
        this->anterior.push_front(anterior);//aca agrega un nodo a la lista
    }
}
void Etiqueta::setPesoAcumulado(int peso){
    this->pesoAcumulado = peso;
}
void Etiqueta::setPesoDouble(double pesoDouble){
    this->pesoDouble = pesoDouble;
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
double Etiqueta::getPesoDouble(){
    return pesoDouble;
}
int Etiqueta::getIteracion(){
    return iteracion;
}
