#include "vertice.h"

Vertice::Vertice(string nombre){
    cout << "Constructor Vertice " << nombre << endl;
    siguiente = 0;
    arista = 0;
    this->nombre = nombre;
}
Vertice::~Vertice(){
    cout << "Destructor Vertice " << nombre << endl;
}
void Vertice::asignarProxVertice(Vertice* siguiente){
    this->siguiente = siguiente;
}
void Vertice::aliminarArista(Arista* aristaAeliminar){
    if(this->arista == aristaAeliminar){
        this->arista = aristaAeliminar->consultarSiguiente();
        delete aristaAeliminar;
    }else{
        Arista* previa = this->arista;
        Arista* eliminamos = previa->consultarSiguiente();
        while(eliminamos){
            if(eliminamos == aristaAeliminar){
                previa->asignarSiguiente(eliminamos->consultarSiguiente());
                delete eliminamos;
                return;
            }
            previa = eliminamos;
            eliminamos = eliminamos->consultarSiguiente();
        }
    }
}

void Vertice::agregarArista(Arista* nuevaArista){
    Arista* aux = this->arista;
    if(aux == 0){
        this->arista = nuevaArista;
        return;
    }
    while(aux->consultarSiguiente() != 0){
        aux = aux->consultarSiguiente();
    }
    aux->asignarSiguiente(nuevaArista);
}

Vertice* Vertice::obtenerProxVertice(){
    return siguiente;
}
Arista* Vertice::obtenerAristas(){
    return arista;
}
string Vertice::obtenerNombreVertice(){
    return nombre;
}
