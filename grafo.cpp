#include "grafo.h"

Grafo::Grafo(){
    cout << "Contructor Grafo\n";
    primero = 0;
    ultimo = 0;
    tamanio = 0;
}
void Grafo::agregarArista(Vertice* inicio, Vertice* destino, int p1, double p2){
    if(!inicio || !destino){
        cout << "Error salida / llegada\n";
        return;
    }
    Arista* nuevaArista = new Arista(destino);
    nuevaArista->asignarPeso1(p1);
    nuevaArista->asignarPeso2(p2);
    inicio->agregarArista(nuevaArista);
}
Vertice* Grafo::obtenerPrimero(){
    return this->primero;
}
void Grafo::agregarVertice(string nombre){
    Vertice* ingresante = new Vertice(nombre);
    if (!primero){
        primero = ingresante;
        ultimo = ingresante;
        tamanio++;
        return;
    }
    Vertice* aux = primero;
    while(aux->obtenerProxVertice() != 0){
        aux = aux->obtenerProxVertice();
    }
    aux->asignarProxVertice(ingresante);
    ultimo = ingresante;
    tamanio++;
}
int Grafo::obtenerPeso1(Vertice* inicio, Vertice* destino){
    if(!inicio || !destino){
        cout << "Error salida / llegada\n";
        return 0;
    }
    Arista* aux1 = inicio->obtenerAristas();
    while(aux1){
        if(aux1->ConsultarDestino() == destino){
            return aux1->cunsultarPeso1();
        }
        aux1 = aux1->consultarSiguiente();
    }
    return -1;
}
double Grafo::obtenerPeso2(Vertice* inicio, Vertice* destino){
    if(!inicio || !destino){
        cout << "Error salida / llegada\n";
        return 0;
    }
    Arista* aux1 = inicio->obtenerAristas();
    while(aux1){
        if(aux1->ConsultarDestino() == destino){
            return aux1->consultarPeso2();
        }
        aux1 = aux1->consultarSiguiente();
    }
    return -1;
}
void Grafo::eliminarVertice(Vertice* aEliminar){
    if(!aEliminar){
        cout << "No existe vertice\n";
    }else{
        Arista* auxArista1 = aEliminar->obtenerAristas(), *auxArista2;
        while(auxArista1){//libero todas sus aristas
            auxArista2 = auxArista1;
            auxArista1 = auxArista1->consultarSiguiente();
            aEliminar->aliminarArista(auxArista2);
        }
        cout << "aEliminar quedo con aristas: " << (aEliminar->obtenerAristas() != 0)<< endl;
        cout << "Limpio todas las otras aristas" << endl;
        Vertice* auxVertice = this->primero;
        cout << "Cantidad de vertices: "<< this->tamanio << endl;
        for(int i = 0; i < tamanio; i++){
            cout << "Vertice: " << auxVertice->obtenerNombreVertice() << endl;
            auxArista1 = auxVertice->obtenerAristas();
            auxArista2 = auxArista1;
            while(auxArista2){
                cout << "Destino " << auxArista1->ConsultarDestino()->obtenerNombreVertice() << endl;
                auxArista2 = auxArista1->consultarSiguiente();
                if(auxArista1->ConsultarDestino() == aEliminar){
                    cout << "Elimino una arista" << endl;
                    auxVertice->aliminarArista(auxArista1);
                }
                auxArista1 = auxArista2;
            }
            auxVertice = auxVertice->obtenerProxVertice();
        }

        if(this->primero == aEliminar){
            cout << "Elimino el primero\n";
            Vertice* auxiliar = this->primero;
            this->primero = auxiliar->obtenerProxVertice();
            tamanio--;
            delete auxiliar;
        }else{
            bool fueBorrado = false;
            Vertice* anterior = this->primero;
            Vertice* porSerBorrado = anterior->obtenerProxVertice();
            while(porSerBorrado && !fueBorrado){
                if(porSerBorrado == aEliminar){
                    anterior->asignarProxVertice(porSerBorrado->obtenerProxVertice());
                    delete porSerBorrado;
                    tamanio--;
                    fueBorrado = true;
                }
                if(!fueBorrado){
                    anterior = porSerBorrado;
                    porSerBorrado = porSerBorrado->obtenerProxVertice();
                }
            }
        }
    }

}
void Grafo::eliminarArista(Vertice* inicio, Vertice* destino){
    if(!inicio || !destino){
        cout << "Error salida / llegada\n";
        return;
    }
    Arista* aux1 = inicio->obtenerAristas();
    while(aux1){
        cout << "Consulto Arista eliminar\n";
        if(aux1->ConsultarDestino() == destino){
            cout << "ELIMINO\n";
            inicio->aliminarArista(aux1);
            return;
        }
        aux1 = aux1->consultarSiguiente();
    }
}
bool Grafo::existeVertice(string nombre){
    return (obtenerVertice(nombre) != 0);
}
Vertice* Grafo::obtenerVertice(string nombre){
    Vertice* aux = primero;
    for(int i = 0; i < tamanio; i++){
        if(aux->obtenerNombreVertice() == nombre){
            return aux;
        }
        aux = aux->obtenerProxVertice();
    }
    return 0;
}
int Grafo::grandor(){
    return this->tamanio;
}
Grafo::~Grafo(){
    Vertice* aux = primero, *prev;
    Arista* auxArista;
    Arista* auxAristaBorrar;
    while(tamanio){
        auxArista = aux->obtenerAristas();
        while(auxArista){
            auxAristaBorrar = auxArista;
            auxArista = auxArista->consultarSiguiente();
            delete auxAristaBorrar;
        }
        prev = aux;
        aux = aux->obtenerProxVertice();
        delete prev;
        tamanio--;
    }
    cout << "Destructor Grafo\n";
}
