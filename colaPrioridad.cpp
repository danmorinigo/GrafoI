#include "colaPrioridad.h"
ColaPrioridad::ColaPrioridad(int criterioOrden){
    primero = 0;
    primeroSegunPrioridad = 0;
    ultimo = 0;
    this->criterioOrden = criterioOrden;
    if(MEMORIA) std::cout << "Constructor ColaPrioridad (" << this << ")\n";
}
void ColaPrioridad::push(Vertice* evaluado, int pesoEntero, double pesoDouble, int iteracion){
    if(!primero){//cola vacia
        primero = new NodoColaPrioridad(evaluado, iteracion, pesoEntero, pesoDouble);
        primeroSegunPrioridad = primero;
        ultimo = primero;
    }else{//habia elementos en la cola
        int prioridadActual = primeroSegunPrioridad->getPrioridad();
        if(iteracion > prioridadActual){//nueva iteracion - inserta al final
            NodoColaPrioridad* aux = new NodoColaPrioridad(evaluado, iteracion, pesoEntero, pesoDouble);
            ultimo->setSiguiente(aux);
            ultimo = aux;
            primeroSegunPrioridad = aux;
        }else if(iteracion == prioridadActual){//hay que ordenar...
            NodoColaPrioridad* aux = new NodoColaPrioridad(evaluado, iteracion, pesoEntero, pesoDouble);
            //mayor que el ultimo, inserta al final de cola
            if(((criterioOrden == 1) && (pesoEntero >= ultimo->getEntero())) || ((criterioOrden == 2) && (pesoDouble >= ultimo->getDouble()))){
                ultimo->setSiguiente(aux);
                ultimo = aux;
            }else{
                //menor que el primero en esta prioridad
                if(((criterioOrden == 1) && (pesoEntero < primeroSegunPrioridad->getEntero())) || ((criterioOrden == 2) && (pesoDouble < primeroSegunPrioridad->getDouble()))){
                    //primero en cola y primero segun prioridad apuntando al mismo lugar
                    if(primero == primeroSegunPrioridad){
                        aux->setSiguiente(primero);
                        this->primero = aux;
                        this->primeroSegunPrioridad = aux;
                    }else{
                        //primero segun prioridad apuntando luego del principio
                        NodoColaPrioridad* auxPrimero = primero;
                        while(auxPrimero->getSiguiente() != primeroSegunPrioridad){
                            auxPrimero = auxPrimero->getSiguiente();
                        }
                        aux->setSiguiente(primeroSegunPrioridad);
                        auxPrimero->setSiguiente(aux);
                        primeroSegunPrioridad = aux;
                    }
                }else{//esta en medio de esta prioridad, pero no al final ni al principio
                    NodoColaPrioridad* auxPrioridadActual = primeroSegunPrioridad;
                    bool hecho = false;
                    while(auxPrioridadActual->getSiguiente() && !hecho){
                        if(((criterioOrden == 1) && (pesoEntero <= auxPrioridadActual->getSiguiente()->getEntero())) || ((criterioOrden == 2) && (pesoDouble <= auxPrioridadActual->getSiguiente()->getDouble()))){
                            aux->setSiguiente(auxPrioridadActual->getSiguiente());
                            auxPrioridadActual->setSiguiente(aux);
                            hecho= true;
                        }
                        auxPrioridadActual = auxPrioridadActual->getSiguiente();
                    }
                    if(!hecho){
                        cout << "Ha ocurrido un error ordenando dentro de la prioridad " << this->primeroSegunPrioridad->getPrioridad() << endl;
                        cin.get();
                    }
                }
            }
        }else{
            cout << "ERROR - Iteracion no permitida" << endl;
            cin.get();
        }

    }
}
bool ColaPrioridad::vacia(){
    return (primero == 0);
}
int ColaPrioridad::topPrioridad(){
    return this->primero->getPrioridad();
}
int ColaPrioridad::topEntero(){
    return this->primero->getEntero();
}
double ColaPrioridad::topDouble(){
    return this->primero->getDouble();
}
Vertice* ColaPrioridad::topVertice(){
    return this->primero->obtenerVertice();
}
void ColaPrioridad::pop(){
    NodoColaPrioridad* auxNodo = primero;
    this->primero = auxNodo->getSiguiente();
    if (primeroSegunPrioridad == auxNodo){
        primeroSegunPrioridad = primero;
    }
    if(!primero){
        ultimo = 0;
    }
    delete auxNodo;
}
Vertice* ColaPrioridad::topAndPop(){
    NodoColaPrioridad* auxNodo = primero;
    Vertice* aux = primero->obtenerVertice();
    this->primero = auxNodo->getSiguiente();
    if (primeroSegunPrioridad == auxNodo){
        primeroSegunPrioridad = primero;
    }
    if(!primero){
        ultimo = 0;
    }
    delete auxNodo;
    return aux;
}

ColaPrioridad::~ColaPrioridad(){
    while(!vacia()){
        this->pop();
    }
    if(MEMORIA) std::cout << "Destructor ColaPrioridad (" << this << ")\n";
}
