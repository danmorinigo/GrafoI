#include "arista.h"

Arista::Arista(Vertice* destino){
    sig = 0;
    this->destino = destino;
    peso1 = -1;
    peso2 = -1.0;
    cout << "Constructor Arista" << endl;
}
Arista::~Arista(){
    cout << "Destructor Arista" << endl;
}
void Arista::asignarSiguiente(Arista* sig){
    this->sig = sig;
}
void Arista::asignarPeso1(int peso1){
    this->peso1 = peso1;
}
void Arista::asignarPeso2(double peso2){
    this->peso2 = peso2;
}

Arista* Arista::consultarSiguiente(){
    return sig;
}
Vertice* Arista::ConsultarDestino(){
    return destino;
}
int Arista::cunsultarPeso1(){
    return peso1;
}
double Arista::consultarPeso2(){
    return peso2;
}
