#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#include "vertice.h"
#include "arista.h"

using namespace std;

class Grafo{
private:
    Vertice* primero;
    Vertice* ultimo;
    int tamanio;
public:
    void agregarVertice(string nombre);
    //Vertice* obtenerVertice(string nombre);
    bool existeVertice(string nombre);
    void agregarArista(Vertice* inicio, Vertice* destino, int p1, int p2);
    void eliminarArista(Vertice* inicio, Vertice* destino);
    void eliminarVertice(Vertice* aEliminar);
    int obtenerPeso1(Vertice* inicio, Vertice* destino);
    double obtenerPeso2(Vertice* inicio, Vertice* destino);
    int grandor();
    Vertice* obtenerVertice(string nombre);
    Vertice* obtenerPrimero();
    Grafo();
    ~Grafo();

private:

};

#endif // GRAFO_H_INCLUDED
