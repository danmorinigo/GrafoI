#ifndef VERTICE_H_INCLUDED
#define VERTICE_H_INCLUDED
#include <iostream>
#include "arista.h"

using namespace std;

class Vertice{
private:
    Vertice* siguiente;
    Arista* arista;
    string nombre;
public:
    Vertice(string nombre);
    ~Vertice();
    void asignarProxVertice(Vertice* siguiente);
    void agregarArista(Arista* nuevaArista);
    void aliminarArista(Arista* aristaAeliminar);

    Vertice* obtenerProxVertice();
    Arista* obtenerAristas();
    string obtenerNombreVertice();
};


#endif // VERTICE_H_INCLUDED
