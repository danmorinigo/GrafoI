#include <iostream>
#include <cstdlib>
#include <ctime>
#include <list>
#include <queue>
#include <stack>
#include "arista.h"
#include "vertice.h"
#include "grafo.h"
#include "etiqueta.h"
#include "colaPrioridad.h"
using namespace std;

void menu(Grafo* aTrabajar);
void mostrarRuta(list<Vertice*> anteriores, list<Etiqueta> lista, stack<Vertice*> pila, Vertice* actual, Vertice* inicio);

//Necesito....
//  Lista etiquetados**
//  vertice inicio (una lista de vertices)**
//  vertice destino**
//  pila<tuplas> (vertice, costo acumulado)**
//  booleano primeraPasada
struct Tupla{
    Vertice* vertice = 0;
    int pesoAcumulado = 0;
};


void mostrarVer2(list<Etiqueta> etiquetados, list<Vertice*> recorriendoDesde, Vertice* destino, stack<Tupla> caminoRecorrido, bool primeraPasada);
void mostrarPilaTuplas(stack<Tupla> aMostrar);

//************************
struct TuplaCompleta{
    Vertice* vertice = 0;
    int pesoAcumulado = 0;
    double pesoDouble = 0.0;
};
void mostrarVer3(list<Etiqueta> etiquetados, Vertice* recorriendoDesde, Vertice* destino, stack<TuplaCompleta> caminoRecorrido, bool primeraPasada, int criterio, Grafo* gra);
void mostrarPila(stack<TuplaCompleta> aMostrar, int criterio);
//***********************
int main()
{


    srand(time(NULL));

    string estaciones[] = {"TIJ", "MTY", "MZT", "BJX", "GDL", "SAN", "TAM", "MEX", "MID", "CUN", "FAN", "CIF"};
    Grafo* gra = new Grafo;
    for(int i = 0; i < 12; i++){
        gra->agregarVertice(estaciones[i]);
    }
    /*
    ColaPrioridad testCola(2);
    testCola.push(gra->obtenerVertice("TIJ"), 8,2.3,1);
    testCola.push(gra->obtenerVertice("MTY"), 7,5.8,1);
    testCola.push(gra->obtenerVertice("MZT"), 3,3.33,1);
    testCola.push(gra->obtenerVertice("BJX"), 5,1.9,1);
    testCola.push(gra->obtenerVertice("SAN"), 1,0.1,2);
    while(!testCola.vacia()){
        cout << testCola.topVertice()->obtenerNombreVertice() << " peso2: ";
        cout << testCola.topDouble() << " iteracion : " << testCola.topPrioridad() << endl;
        testCola.pop();
    }
    return 0;
    */
    gra->agregarArista(gra->obtenerVertice("TIJ"), gra->obtenerVertice("MTY"), 30, 1.5);//800
    gra->agregarArista(gra->obtenerVertice("MTY"), gra->obtenerVertice("BJX"), 125, 2.9);//700
    gra->agregarArista(gra->obtenerVertice("GDL"), gra->obtenerVertice("MTY"), 125, 10.5);//450
    gra->agregarArista(gra->obtenerVertice("MZT"), gra->obtenerVertice("TIJ"), 20, 6.6);//400
    gra->agregarArista(gra->obtenerVertice("MZT"), gra->obtenerVertice("BJX"), 300, 7.61);
    gra->agregarArista(gra->obtenerVertice("GDL"), gra->obtenerVertice("MZT"), 200, 10.36);//500
    gra->agregarArista(gra->obtenerVertice("GDL"), gra->obtenerVertice("BJX"), 250, 45.36);
    gra->agregarArista(gra->obtenerVertice("GDL"), gra->obtenerVertice("MEX"), 500, 111.9);
    gra->agregarArista(gra->obtenerVertice("CUN"), gra->obtenerVertice("GDL"), 650, 10.97);
    gra->agregarArista(gra->obtenerVertice("MEX"), gra->obtenerVertice("CUN"), 650, 26.65);
    gra->agregarArista(gra->obtenerVertice("BJX"), gra->obtenerVertice("MEX"), 500, 15.64);//350
    gra->agregarArista(gra->obtenerVertice("BJX"), gra->obtenerVertice("TAM"), 350, 3.36);//400
    gra->agregarArista(gra->obtenerVertice("BJX"), gra->obtenerVertice("SAN"), 400, 29.9);//900
    gra->agregarArista(gra->obtenerVertice("SAN"), gra->obtenerVertice("MID"), 450, 11.56);//1200
    gra->agregarArista(gra->obtenerVertice("TAM"), gra->obtenerVertice("MID"), 500, 78.2);//450
    gra->agregarArista(gra->obtenerVertice("MEX"), gra->obtenerVertice("MID"), 5000, 18.25);//450
    gra->agregarArista(gra->obtenerVertice("MID"), gra->obtenerVertice("FAN"), 630, 26.33);
    gra->agregarArista(gra->obtenerVertice("MID"), gra->obtenerVertice("CIF"), 350, 4.66);

    menu(gra);
    cout << "FIN" << endl;
    delete gra;
    return 0;
}

void menu(Grafo* aTrabajar){
    int opcion = 0;
    do{
    cout << "1- Ver todos los vertices\n";
    cout << "2- Ver cantidad vertices\n";
    cout << "3- Ver destinos directos de una estacion\n";
    cout << "4- Eliminar un trayecto\n";
    cout << "5- Eliminar una estacion\n";
    cout << "6- Agregar estacion\n";
    cout << "7- Agregar recorrido\n";
    cout << "8- Lista Adyacencia\n";
    cout << "9- Matriz Adyacencias y costos\n";
    cout << "10- Recorridos menor costo\n";
    cout << "11- Recorridos menor costo (ver II)\n";
    cout << "12- Recorridos menor costo (ver III)\n";
    cout << "13- Salir\n";
    cout << "Opcion: ";
    cin >> opcion;
    switch(opcion){
        case 1:
        {
            cout << "Listado de estaciones\n";
            Vertice* aux = aTrabajar->obtenerPrimero();
            for(int i = 0; i < aTrabajar->grandor(); i++){
                cout << "\t" << i << "- " << aux->obtenerNombreVertice() << endl;
                aux = aux->obtenerProxVertice();
            }
            cin.get();
            break;
        }
        case 2:{
            cout << "Cantidad de estacioens\n";
            cout << "\t" << aTrabajar->grandor() << endl;
            cin.get();
            break;
            }
        case 3:{
            string aux;
            cout << "Destinos directos desde:\n";
            cout << "Ingrese estacion salida: ";
            cin >> aux;
            if(aTrabajar->existeVertice(aux)){
                Arista* auxAristas = aTrabajar->obtenerVertice(aux)->obtenerAristas();
                while (auxAristas){
                    cout << "\t" << auxAristas->ConsultarDestino()->obtenerNombreVertice() << endl;
                    auxAristas = auxAristas->consultarSiguiente();
                }
            }else{
                cout << "No existe tal estacion\n";
            }
            cin.get();
            break;
        }
        case 4:{
            string aux1, aux2;
            cout << "Eliminar una ruta\n";
            cout << "Salida: ";
            cin >> aux1;
            cout << "Llegada: ";
            cin >> aux2;
            if(aTrabajar->existeVertice(aux1) && aTrabajar->existeVertice(aux2)){
                aTrabajar->eliminarArista(aTrabajar->obtenerVertice(aux1), aTrabajar->obtenerVertice(aux2));
            }else{
                cout << "No existe alguna de las estaciones proporcionadas\n";
            }
            cin.get();
            break;
        }
        case 5:{
            string aux;
            cout << "ELIMINAR ESTACION\n";
            cout << "Estacion: ";
            cin >> aux;
            if(aTrabajar->existeVertice(aux)){
                aTrabajar->eliminarVertice(aTrabajar->obtenerVertice(aux));
            }else{
                cout << "No existe esa estacion\n";
            }
            cin.get();
            break;
        }
        case 6:{
            string aux;
            cout << "AGREGAR ESTACION\n";
            cout << "Estacion: ";
            cin >> aux;
            aTrabajar->agregarVertice(aux);
            break;
        }
        case 7:{
            string aux1, aux2;
            cout << "AGREGAR RECORRIDO\n";
            cout << "Estacion salida: ";
            cin >> aux1;
            cout << "Estacion llegada: ";
            cin >> aux2;
            if(aTrabajar->existeVertice(aux1) && aTrabajar->existeVertice(aux1)){
                int aux3, aux4;
                cout << "Precio 1: ";
                cin >> aux3;
                cout << "Precio 2: ";
                cin >> aux4;
                aTrabajar->agregarArista(aTrabajar->obtenerVertice(aux1), aTrabajar->obtenerVertice(aux2), aux3, aux4);
            }else{
                cout << "No existe alguna de las estaciones proporcionadas\n";
            }
            break;
        }
        case 8:{
            cout << "LISTA ADYACENCIA\n";
            Vertice* aux = aTrabajar->obtenerPrimero();
            Arista* auxAri;
            for(int i = 0; i < aTrabajar->grandor(); i++){
                cout << aux->obtenerNombreVertice() << "-->";
                auxAri = aux->obtenerAristas();
                while(auxAri){
                    cout << auxAri->ConsultarDestino()->obtenerNombreVertice();
                    if (auxAri->consultarSiguiente()){
                        cout << "->";
                    }
                    auxAri = auxAri->consultarSiguiente();
                }
                aux = aux->obtenerProxVertice();
                cout << endl;
            }
            cin.get();
            break;
        }
        case 9:{
            cout << "MATRICES ADYACENCIA Y COSTOS\n";
            cout << "+-";
            int matriz1[aTrabajar->grandor()][aTrabajar->grandor()];
            int matriz2[aTrabajar->grandor()][aTrabajar->grandor()];
            for(int j = 0; j < aTrabajar->grandor(); j++){
                cout << "-";
            }
            cout << "+" << endl;
            cout << "|-";
            for(int j = 0; j < aTrabajar->grandor(); j++){
                cout << j;
            }
            cout << "|" << endl;
            Vertice* auxEstacion = aTrabajar->obtenerPrimero(), *auxLlegada;
            Arista* auxArista, *auxAristaInicio;
            bool encontrado = false;
            for(int i = 0; i < aTrabajar->grandor(); i++){//para las filas
                auxLlegada = aTrabajar->obtenerPrimero();
                auxArista = auxEstacion->obtenerAristas();
                auxAristaInicio = auxArista;
                cout << "|" << i;
                for(int j = 0; j < aTrabajar->grandor(); j++){//para las columnas
                    auxArista = auxAristaInicio;
                    while(auxArista && !encontrado){
                        if(auxArista->ConsultarDestino() == auxLlegada){
                            matriz1[i][j] = auxArista->cunsultarPeso1();
                            matriz2[i][j] = auxArista->consultarPeso2();
                            encontrado = true;
                        }
                        auxArista = auxArista->consultarSiguiente();
                    }
                    if(encontrado){
                        cout << "1";
                    }else{
                        matriz1[i][j] = -1;
                        matriz2[i][j] = -1;
                        cout << "0";
                    }
                    encontrado = false;
                    auxLlegada = auxLlegada->obtenerProxVertice();
                }
                cout << "|" << endl;
                auxEstacion = auxEstacion->obtenerProxVertice();
            }

            cout << "+-";
            for(int j = 0; j < aTrabajar->grandor(); j++){
                cout << "-";
            }
            cout << "+" << endl;

            cout << "COSTOS1" << endl;
            for(int i = 0; i < aTrabajar->grandor(); i++){
                for(int j = 0; j < aTrabajar->grandor(); j++){
                    cout << matriz1[i][j] << "|";
                }
                cout << endl;
            }
            cout << "COSTOS2" << endl;
            for(int i = 0; i < aTrabajar->grandor(); i++){
                for(int j = 0; j < aTrabajar->grandor(); j++){
                    cout << matriz2[i][j] << "|";
                }
                cout << endl;
            }
            cin.get();
            cin.get();
            break;
        }
        case 10:{
            string auxDesde, auxHasta;
            cout << "VIAJE MENOR COSTO\n";
            cout << "Desde: ";
            cin >> auxDesde;
            cout << "Hasta:";
            cin >> auxHasta;
            bool primeraEntrada = true;
            if(aTrabajar->existeVertice(auxDesde) && aTrabajar->existeVertice(auxHasta)){
                //int cantVertices = aTrabajar->grandor();
                int verticesVisitados = 0;

                queue<Vertice*> colaMaestra;
                colaMaestra.push(aTrabajar->obtenerVertice(auxDesde));
                queue<Vertice*> colaAuxiliar;
                list<Vertice*> auxParaCola;
                list<Vertice*>::iterator iTauxParaCola;

                Arista* auxAristas;
                Vertice* verticeVisitado;

                list<Vertice*> vistos;
                list<Vertice*>::iterator Viterator;

                list<Etiqueta> etiquetados;
                list<Etiqueta>::iterator itEtiq;
                Vertice* auxParaEt = aTrabajar->obtenerPrimero();
                while(auxParaEt){
                    Etiqueta perdidos(auxParaEt);
                    etiquetados.push_back(perdidos);
                    auxParaEt = auxParaEt->obtenerProxVertice();
                }
                /*
                cout << "Etiquetas.." << endl;
                for(itEtiq = etiquetados.begin(); itEtiq != etiquetados.end(); itEtiq++){
                    cout << "Estacion: "<< (*itEtiq).getVertice()->obtenerNombreVertice();
                    cout << " Anterior(es): ";

                    if(!(*itEtiq).getAnterior().empty()){
                        list<Vertice*> auxVerticesAnteriores = (*itEtiq).getAnterior();
                        list<Vertice*>::iterator i;
                        for(i = auxVerticesAnteriores.begin(); i != auxVerticesAnteriores.end(); i++){
                            cout << (*i)->obtenerNombreVertice() << "-";
                        }
                    }else{
                        cout << "NO";
                    }

                    cout << " Acumulado: " << (*itEtiq).getPesoAcumulado();
                    cout << " Iteracion: " << (*itEtiq).getIteracion() << endl;
                }
                */

                while(!colaMaestra.empty()){
                    verticeVisitado = colaMaestra.front();
                    colaMaestra.pop();
                    bool fueVisitadoAntes = false;
                    Viterator = vistos.begin();
                    while(Viterator != vistos.end() && !fueVisitadoAntes){
                        if(*Viterator == verticeVisitado){
                            fueVisitadoAntes = true;
                        }
                        Viterator++;
                    }
                    if(!fueVisitadoAntes){
                        auxAristas = verticeVisitado->obtenerAristas();
                        while(auxAristas){
                            fueVisitadoAntes = false;
                            Viterator = vistos.begin();
                            while(Viterator != vistos.end() && !fueVisitadoAntes){
                                if(*Viterator == auxAristas->ConsultarDestino()){
                                    fueVisitadoAntes = true;
                                }
                                Viterator++;
                            }
                            if(!fueVisitadoAntes){
                                //PRIMERO
                                //Hacer lista ordenada (por peso) los vert adyacentes
                                //Peso desde donde estoy parado hasta prox vertice
                                //Menor peso al principio de lista
                                //Pasar la lista a Cola maestra, comenzando por el principio

                                //tomo nota de los nodos que luego seran visitados
                                //luego los ordeno en una lista y los paso a la cola maestra
                                colaAuxiliar.push(auxAristas->ConsultarDestino());


                                //SEGUNDO - ASIGNARLES PESO ACUMULADO
                                //Consultar Peso Acumulado de donde estoy parado
                                //sumarle arista
                                //usar la lista de etiquetados
                                Etiqueta auxActual(verticeVisitado), auxProximo(auxAristas->ConsultarDestino());
                                itEtiq = etiquetados.begin();
                                int losDos = 0;
                                while(losDos != 2){
                                    if((*itEtiq).getVertice() == verticeVisitado){
                                        auxActual = *itEtiq;
                                        losDos++;
                                    }
                                    if((*itEtiq).getVertice() == auxAristas->ConsultarDestino()){
                                        auxProximo = *itEtiq;
                                        losDos++;
                                    }
                                    itEtiq++;
                                }
                                //Consultar si tiene ANTERIOR
                                int miPeso, pesoArista, pesoTotal;
                                miPeso = auxActual.getPesoAcumulado();
                                pesoArista = aTrabajar->obtenerPeso1(verticeVisitado, auxProximo.getVertice());
                                pesoTotal = miPeso + pesoArista;
                                if(auxProximo.getAnterior().empty()){
                                    auxProximo.setAnterior(verticeVisitado);
                                    auxProximo.setPesoAcumulado(miPeso + pesoArista);
                                    auxProximo.setIteracion(verticesVisitados + 1);
                                }else{
                                    int suPeso;
                                    suPeso = auxProximo.getPesoAcumulado();
                                    if(pesoTotal < suPeso){
                                        auxProximo.setAnterior(verticeVisitado);
                                        auxProximo.setPesoAcumulado(miPeso + pesoArista);
                                        auxProximo.setIteracion(verticesVisitados + 1);
                                    }else if(pesoTotal == suPeso){
                                        auxProximo.sumoAnterior(verticeVisitado);
                                    }
                                }

                                itEtiq = etiquetados.begin();
                                bool hecho = false;
                                while(!hecho){
                                    if((*itEtiq).getVertice() == auxProximo.getVertice()){
                                        *itEtiq = auxProximo;
                                        hecho = true;
                                    }
                                    itEtiq++;
                                }
                                //NO -> Le asigno Peso de donde estoy parado + peso arista
                                //      Donde estoy parado es su anterior
                                //SI->  Consultar su Peso Acumulado
                                //      Hacer suma del Peso donde estoy parado + Peso Arista
                                //      Si su peso acumulado es menor que la suma
                                //          No hacer nada
                                //      Si su peso acumulado es igual que la suma
                                //          Donde estoy parado TAMBIEN es su anterior
                                //      Si su peso acumulado es mayor que la suma
                                //          Le asigno Peso de donde estoy parado + peso arista
                                //          Donde estoy parado es su anterior

                            }
                            auxAristas = auxAristas->consultarSiguiente();
                        }
                        //aca tengo que cargar colaMaestra
                        while(!colaAuxiliar.empty()){
                            //tengo que ordenar....
                            if(auxParaCola.empty()){
                                auxParaCola.push_front(colaAuxiliar.front());
                                colaAuxiliar.pop();
                            }else{
                                bool agregado = false;
                                int aristaEnLista, aristaNueva;
                                Vertice* verticeEnLista;
                                iTauxParaCola = auxParaCola.begin();
                                while(!agregado && iTauxParaCola != auxParaCola.end()){
                                    verticeEnLista = *iTauxParaCola;
                                    aristaEnLista = aTrabajar->obtenerPeso1(verticeVisitado, verticeEnLista);
                                    aristaNueva = aTrabajar->obtenerPeso1(verticeVisitado, colaAuxiliar.front());
                                    if(aristaEnLista <= aristaNueva){
                                        auxParaCola.insert(iTauxParaCola, colaAuxiliar.front());
                                        colaAuxiliar.pop();
                                        agregado = true;
                                    }
                                    iTauxParaCola++;
                                }
                                if(!agregado){
                                    auxParaCola.push_back(colaAuxiliar.front());
                                    colaAuxiliar.pop();
                                }
                            }
                        }

                        //tendria que tener la lista ordenada
                        //paso a la cola maestra
                        iTauxParaCola = auxParaCola.begin();
                        while(!auxParaCola.empty()){
                            colaMaestra.push(auxParaCola.front());
                            auxParaCola.pop_front();
                        }
                        if(auxDesde == auxHasta){
                            if(primeraEntrada){
                                primeraEntrada = false;
                            }else{
                                vistos.push_back(verticeVisitado);
                            }
                        }else{
                            vistos.push_back(verticeVisitado);
                        }
                        verticesVisitados++;
                    }
                }

                Vertice* auxilio;
                cout << "VERTICES MARCADOS" << endl;
                for(Viterator = vistos.begin(); Viterator != vistos.end(); Viterator++){
                    auxilio = *Viterator;
                    cout << auxilio->obtenerNombreVertice() << endl;
                }
                itEtiq = etiquetados.begin();
                bool hayCamino = false;
                list<Vertice*> comienzoDelCamino;
                while(!hayCamino && itEtiq != etiquetados.end()){
                    list<Vertice*> auxVerticesAnteriores = (*itEtiq).getAnterior();
                    list<Vertice*>::iterator i;
                    i = auxVerticesAnteriores.begin();
                    while(!hayCamino && i != auxVerticesAnteriores.end()){
                        if((*itEtiq).getVertice() == aTrabajar->obtenerVertice(auxHasta)){
                            if (!(*itEtiq).getAnterior().empty()){
                                comienzoDelCamino = (*itEtiq).getAnterior();
                                hayCamino = true;
                            }
                        }
                        i++;
                    }
                    itEtiq++;
                }
                if(hayCamino){
                    cout << "Se encontro camino\n";
                    cout << "Etiquetas.." << endl;
                    for(itEtiq = etiquetados.begin(); itEtiq != etiquetados.end(); itEtiq++){
                        cout << "Estacion: "<< (*itEtiq).getVertice()->obtenerNombreVertice();
                        cout << " Anterior(es): ";

                        if(!(*itEtiq).getAnterior().empty()){
                            list<Vertice*> auxVerticesAnteriores = (*itEtiq).getAnterior();
                            list<Vertice*>::iterator i;
                            for(i = auxVerticesAnteriores.begin(); i != auxVerticesAnteriores.end(); i++){
                                cout << (*i)->obtenerNombreVertice() << "-";
                            }
                        }else{
                        cout << "NO";
                        }
                        cout << " Acumulado: " << (*itEtiq).getPesoAcumulado();
                        cout << " Iteracion: " << (*itEtiq).getIteracion() << endl;
                    }
                    stack<Vertice*> pilaInicial;
                    pilaInicial.push(aTrabajar->obtenerVertice(auxHasta));
                    //anteriores de Llegada
                    mostrarRuta(comienzoDelCamino, etiquetados, pilaInicial, aTrabajar->obtenerVertice(auxHasta), aTrabajar->obtenerVertice(auxDesde));
                }else{
                    cout << "No hay conexion\n";
                }
            }else{
                cout << "No existe DESDE o HASTA\n";
            }
            cin.get();
            cin.get();

            break;
        }
        case 11:{
            //Se ve??
            //primero muestro que funciona
            //Si esta bien faltaria modulizar / modular
            //Uso un struct Tupla(Vertice* , int peso)

            string auxDesde, auxHasta;
            cout << "VIAJE MENOR COSTO (Ver II)\n";
            cout << "Desde: ";
            cin >> auxDesde;
            cout << "Hasta:";
            cin >> auxHasta;
            bool primeraEntrada = true; //Lo uso para el caso en que la salida y la
                                        //llegada sea la misma
            bool existeDesde = aTrabajar->existeVertice(auxDesde);
            bool existeHasta = aTrabajar->existeVertice(auxHasta);
            if(existeDesde && existeHasta){
                int iteracion = 1;

                queue<Vertice*> colaMaestra;    //En cada iteracion se suman, ordenados,
                                                //(primero el de menor peso1)
                                                //los vertices a los cuales debe visitar
                colaMaestra.push(aTrabajar->obtenerVertice(auxDesde));  //Comienza desde
                                                                        //la salida
                                                                        //si prueba y error y viendo
                                                                        //pseudocodigos en youtube
                queue<Vertice*> colaAuxiliar;   //En cada iteracion guardo los
                                                //vertices que hay que visitar
                                                //en la siguiente iteracion
                                                //pero no estan ordenados.
                list<Vertice*> auxParaCola;     //En la lista los ordeno de menor a mayor
                                                //para luego pasarselos a colaMaestra
                list<Vertice*> vistos;  //Aca van los vertices ya visitados (marcados)

                list<Etiqueta> etiquetados;
                list<Etiqueta>::iterator itEtiq;    //Iterador lo uso en todo lo que sigue

                //------------------------------------------------------
                //Armo la lista de etiquetas con todos los vertices del grafo
                //Todos los etiquetas (vertices) tendran peso e iteracion = 0
                //Hice ua clase etiquetas
                //Ahi tipo voy guardando los nodos, sus ancestros,
                //pero bueno ahi escribi mas o menos
                //Si entran todos los vertices
                //Sin peso ni antecesores
                Vertice* verticeEnGrafo = aTrabajar->obtenerPrimero();
                while(verticeEnGrafo){
                    Etiqueta ingresante(verticeEnGrafo);
                    etiquetados.push_back(ingresante);
                    verticeEnGrafo = verticeEnGrafo->obtenerProxVertice();
                }
                //------------------------------------------------------
                Vertice* verticeVisitado;
                //Unico vertice en la cola, al entrar, es el vertice de partida
                //
                //claro si
                while(!colaMaestra.empty()){
                    verticeVisitado = colaMaestra.front();
                    colaMaestra.pop();  //elimino de la cola vertice que estoy visitando

                    //-------------------------------------------------------------------
                    bool fueVisitadoAntes = false;
                    list<Vertice*>::iterator i;
                    i = vistos.begin();
                    //Si el vertice que quiero visitar ya fue marcado como visitado
                    //no lo evalua
                    while(i != vistos.end() && !fueVisitadoAntes){
                        if(*i == verticeVisitado){
                            fueVisitadoAntes = true;
                        }
                        i++;
                    }
                    //-------------------------------------------------------------------

                    Arista* auxAristas;
                    //Si fue visitado saltea este if, y retorna al comienzo del while
                    if(!fueVisitadoAntes){
                        auxAristas = verticeVisitado->obtenerAristas();
                        while(auxAristas){
                            //-------------------------------------------------------------------
                            //Verifico que los destinos de cada arista del vertice evaluado
                            //no estan marcados como visitados
                            fueVisitadoAntes = false;
                            list<Vertice*>::iterator i;
                            i = vistos.begin();
                            while(i != vistos.end() && !fueVisitadoAntes){
                                if(*i == auxAristas->ConsultarDestino()){
                                    fueVisitadoAntes = true;
                                }
                                i++;
                            }
                            //-------------------------------------------------------------------
                            //Si fue visitado saltea este if, y continua con la siguiente arista
                            if(!fueVisitadoAntes){
                                //Comienzo a armar lista para agregar a colaMaestra
                                colaAuxiliar.push(auxAristas->ConsultarDestino());
                                //Dos etiquetas auxiliares, uno apuntando al vertice visitado
                                //el otro apuntando al vertice destino de la arista
                                Etiqueta auxActual(verticeVisitado), auxDestino(auxAristas->ConsultarDestino());
                                //Busco dentro de la lista de etiquetas a las que apuntan al mismo vertice
                                //de las etiquetas auxiliares, y copio sus datos (vertices anteriores,
                                //peso acumulado e iteracion)
                                itEtiq = etiquetados.begin();
                                int losDos = 0;
                                while(losDos != 2){
                                    if((*itEtiq).getVertice() == verticeVisitado){
                                        auxActual = *itEtiq;
                                        losDos++;
                                    }
                                    if((*itEtiq).getVertice() == auxAristas->ConsultarDestino()){
                                        auxDestino = *itEtiq;
                                        losDos++;
                                    }
                                    itEtiq++;
                                }
                                //Verifico si cambio o no el peso total del vertice destino de la arista
                                int miPeso, pesoArista, pesoTotal;
                                miPeso = auxActual.getPesoAcumulado();
                                //Trabajando con el peso1
                                pesoArista = aTrabajar->obtenerPeso1(verticeVisitado, auxDestino.getVertice());
                                pesoTotal = miPeso + pesoArista;
                                if(auxDestino.getAnterior().empty()){   //Si no tiene predecesor no tiene peso
                                                                        //Asigno anterior a el vertice que
                                                                        //estoy visitando, peso = al peso
                                                                        //del vertice que estoy visitando+peso
                                                                        //de la arista
                                    cout << "No habia nada dentro" << endl;
                                    auxDestino.setAnterior(verticeVisitado);
                                    auxDestino.setPesoAcumulado(miPeso + pesoArista);
                                    auxDestino.setIteracion(iteracion);
                                }else{  //tiene peso acumulado
                                    cout << "habia nada dentro" << endl;
                                    int suPeso;
                                    suPeso = auxDestino.getPesoAcumulado();
                                    //Si peso total (acumulado del vertice visitado + arista) menor
                                    //al peso acumulado del vertice destino de la arista
                                    //Cambio su anterior, su peso acumulado e iteracion
                                    //Del vertice que estoy mirando seria, o sea el vertice destino de la arista
                                    if(pesoTotal < suPeso){ //Te muestro los metodos
                                        auxDestino.setAnterior(verticeVisitado);
                                        auxDestino.setPesoAcumulado(miPeso + pesoArista);
                                        auxDestino.setIteracion(iteracion);
                                    }else if(pesoTotal == suPeso){  //Si es igual, agrego un nuevo anterior
                                                                    //y cambio iteracion
                                                                    //iteracion nada, lo saque de no se que clase
                                                                    //per no le encontre utilidad hasta ahora
                                        auxDestino.sumoAnterior(verticeVisitado);
                                        auxDestino.setIteracion(iteracion);
                                    }
                                }
                                //----------------------------
                                //Reeplazo datos del vertice destino en la lista de etiquetas
                                itEtiq = etiquetados.begin();
                                bool hecho = false;
                                while(!hecho){
                                    if((*itEtiq).getVertice() == auxDestino.getVertice()){
                                        *itEtiq = auxDestino;
                                        hecho = true;
                                    }
                                    itEtiq++;
                                }
                                //----------------------------
                            }
                            auxAristas = auxAristas->consultarSiguiente();
                        }

                        //Comienzo a ordenar vertices para que vayan en orden a colaMaestra

                        //colaAuxiliar tiene los vertices evaluados arriba.
                        //auxParaCola es una lista, la lista fue lo que se me ocurrio para poder ordenar
                        //los vertices segun su peso acumulado.
                        //si va bien
                        //Lo unico en el codigo
                        //lo que sigue, la forma en que ordeno no se si esta bien
                        //uso una lista

                        while(!colaAuxiliar.empty()){
                            //Lista vacia, agrego elemento de la colaAuxiliar, luego lo retiro de la cola
                            //Esto ocurre solo la primera iteracion
                            if(auxParaCola.empty()){
                                auxParaCola.push_front(colaAuxiliar.front());
                                colaAuxiliar.pop();
                            }else{
                                bool agregado = false;
                                //->pesoEnLista se refiere al peso de la arista que une al vertice que estoy
                                //visitando hasta el vertice que esta en la lista auxParaCola
                                //->pesoNuevo desde vertice que estoy visitando hasta vertice que quedo en
                                //colaAuxiliar
                                int pesoEnLista, pesoNuevo;
                                Vertice* verticeEnLista;
                                list<Vertice*>::iterator i;
                                i = auxParaCola.begin();
                                while(!agregado && i != auxParaCola.end()){
                                    verticeEnLista = *i;
                                    pesoEnLista = aTrabajar->obtenerPeso1(verticeVisitado, verticeEnLista);
                                    pesoNuevo = aTrabajar->obtenerPeso1(verticeVisitado, colaAuxiliar.front());
                                    //Si pesoNuevo es menor o igual a pesoLista inserto en esa posicion
                                    //de la lista el vertice que esta en la colaAuxiliar, y lo retiro de
                                    //la cola
                                    //La cola auxiliar tiene los vertices que revise recien pero no estan ordenados
                                    //y los quiero ordenar del menor a mayor peso
                                    //para pasarlo a la cola maestra ya ordenados

                                    if(pesoNuevo <= pesoEnLista){
                                    //if(pesoEnLista <= pesoNuevo){
                                        auxParaCola.insert(i, colaAuxiliar.front());
                                        colaAuxiliar.pop();
                                        agregado = true;
                                    }
                                    i++;
                                }
                                //Si no fue agregado es porque el pesoNuevo es mayor que los que estan en
                                //la lista, si inserta al final el vertice que esta en la colaAuxiliar,
                                //y lo retiro de la cola
                                if(!agregado){
                                    auxParaCola.push_back(colaAuxiliar.front());
                                    colaAuxiliar.pop();
                                }
                            }
                        }

                        //Tengo la lista ordenada, de menor a mayor segun su peso (peso de arista)
                        //y paso los vertices a la colaMaestra
                        //si listas pilas y colas
                        //mostrar ahi te muestro
                        while(!auxParaCola.empty()){
                            colaMaestra.push(auxParaCola.front());
                            auxParaCola.pop_front();
                        }

                        //Este condicional lo puse para el caso de que inicio y fin del viaje sea el mismo
                        //De esta forma no marco el vertice de salida como visitado si es la primera iteracion
                        if(auxDesde == auxHasta){
                            if(primeraEntrada){
                                primeraEntrada = false;
                            }else{
                                vistos.push_back(verticeVisitado);
                            }
                        }else{
                            vistos.push_back(verticeVisitado);
                        }
                        iteracion++;
                    }
                }
                //------------------------------------------------------
                //Solo muestro el orden en que fueron recorridos los vertices
                Vertice* auxilio;
                cout << "----------------------------" << endl;
                cout << "VERTICES MARCADOS (EN ORDEN)" << endl;
                cout << "----------------------------" << endl;
                list<Vertice*>::iterator i;
                for(i = vistos.begin(); i != vistos.end(); i++){
                    auxilio = *i;
                    cout << auxilio->obtenerNombreVertice() << endl;
                }
                //------------------------------------------------------
                itEtiq = etiquetados.begin();
                bool hayCamino = false;
                list<Vertice*> comienzoDelCamino;
                while(!hayCamino && itEtiq != etiquetados.end()){
                    if((*itEtiq).getVertice() == aTrabajar->obtenerVertice(auxHasta)){
                        if (!(*itEtiq).getAnterior().empty()){
                            comienzoDelCamino = (*itEtiq).getAnterior();
                            hayCamino = true;
                        }
                    }
                    itEtiq++;
                }
                if(hayCamino){
                    cout << "------------------" << endl;
                    cout << "Se encontro camino\n";
                    cout << "------------------" << endl;
                    //-----------------------------------------------------------------
                    //Solo muestro etiquetas finales
                    cout << "----------------" << endl;
                    cout << "ETIQUETADO FINAL" << endl;
                    cout << "----------------" << endl;
                    for(itEtiq = etiquetados.begin(); itEtiq != etiquetados.end(); itEtiq++){
                        cout << "Estacion: "<< (*itEtiq).getVertice()->obtenerNombreVertice();
                        cout << " Anterior(es): ";

                        if(!(*itEtiq).getAnterior().empty()){
                            list<Vertice*> auxVerticesAnteriores = (*itEtiq).getAnterior();
                            list<Vertice*>::iterator i;
                            for(i = auxVerticesAnteriores.begin(); i != auxVerticesAnteriores.end(); i++){
                                cout << (*i)->obtenerNombreVertice() << "-";
                            }
                        }else{
                        cout << "NO";
                        }
                        cout << " Acumulado: " << (*itEtiq).getPesoAcumulado();
                        cout << " Iteracion: " << (*itEtiq).getIteracion() << endl;
                    }
                    //-----------------------------------------------------------------

                    stack<Vertice*> pilaInicial;
                    pilaInicial.push(aTrabajar->obtenerVertice(auxHasta));
                    //Falta comentar y mejorar
                    //mostrarRuta(comienzoDelCamino, etiquetados, pilaInicial, aTrabajar->obtenerVertice(auxHasta), aTrabajar->obtenerVertice(auxDesde));
                    //-----------------------------------------------------
                    //Necesito....
                    //  Lista etiquetados
                    //  vertice inicio (una lista de vertices)**
                    //  vertice destino**
                    //  pila<tuplas> (vertice, costo acumulado)**
                    //  booleano primeraPasada
                    list<Vertice*> inicioRecorrido;
                    inicioRecorrido.push_front(aTrabajar->obtenerVertice(auxHasta));
                    stack<Tupla> pilaTuplas;
                    bool primerLlamado = true;

                    mostrarVer2(etiquetados, inicioRecorrido, aTrabajar->obtenerVertice(auxDesde), pilaTuplas, primerLlamado);
                    //-----------------------------------------------------
                    cout << "-------------------------------------------------\n";
                }else{
                    cout << "No hay conexion\n";
                }
            }else{
                cout << "No existe DESDE o HASTA\n";
            }
            cin.get();
            cin.get();
            break;
        }
        case 12:{
            int modo; //1 para INT, 2 para DOUBLE
            string auxDesde, auxHasta;
            cout << "VIAJE MENOR COSTO (Ver III)\n";
            cout << "Desde: ";
            cin >> auxDesde;
            cout << "Hasta:";
            cin >> auxHasta;
            bool primeraEntrada = true; //Lo uso para el caso en que la salida y la
                                        //llegada sea la misma
            bool existeDesde = aTrabajar->existeVertice(auxDesde);
            bool existeHasta = aTrabajar->existeVertice(auxHasta);

            //PRIMERO ARREGLO LO DE LA COLA PRIORIDAD(LISTO!!)
            //SEGUNDO PADRES PROBANDO....

            if(existeDesde && existeHasta){
                cout << "Modo [1-Enteros / 2-Double]: ";
                cin >> modo;
                int iteracion = 1;

                ColaPrioridad cola(modo);
                cola.push(aTrabajar->obtenerVertice(auxDesde), 0, 0.0, iteracion);

                list<Vertice*> vistos;  //Aca van los vertices ya visitados (marcados)

                list<Etiqueta> etiquetados;
                list<Etiqueta>::iterator itEtiq;    //Iterador lo uso en todo lo que sigue

                //------------------------------------------------------
                //VA EN METODO CREAR_ETIQUETADOS
                //Armo la lista de etiquetas con todos los vertices del grafo
                //Todos los etiquetas (vertices) tendran peso e iteracion = 0
                //Hice ua clase etiquetas
                //Ahi tipo voy guardando los nodos, sus ancestros,
                //pero bueno ahi escribi mas o menos
                //Si entran todos los vertices
                //Sin peso ni antecesores
                Vertice* verticeEnGrafo = aTrabajar->obtenerPrimero();
                while(verticeEnGrafo){
                    Etiqueta ingresante(verticeEnGrafo);
                    etiquetados.push_back(ingresante);
                    verticeEnGrafo = verticeEnGrafo->obtenerProxVertice();
                }
                //------------------------------------------------------

                Vertice* verticeVisitado;
                //Unico vertice en la cola, al entrar, es el vertice de partida
                while(!cola.vacia()){
                    verticeVisitado = cola.topAndPop();
                    bool fueVisitadoAntes = false;
                    list<Vertice*>::iterator i;
                    i = vistos.begin();
                    //Si el vertice que quiero visitar ya fue marcado como visitado
                    //no lo evalua
                    while(i != vistos.end() && !fueVisitadoAntes){
                        if(*i == verticeVisitado){
                            fueVisitadoAntes = true;
                        }
                        i++;
                    }
                    //-------------------------------------------------------------------

                    Arista* auxAristas;
                    if(!fueVisitadoAntes){
                        auxAristas = verticeVisitado->obtenerAristas();
                        while(auxAristas){

                            //-------------------------------------------------------------------
                            //Verifico que los destinos de cada arista del vertice evaluado
                            //no estan marcados como visitados
                            fueVisitadoAntes = false;
                            list<Vertice*>::iterator i;
                            i = vistos.begin();
                            while(i != vistos.end() && !fueVisitadoAntes){
                                if(*i == auxAristas->ConsultarDestino()){
                                    fueVisitadoAntes = true;
                                }
                                i++;
                            }
                            //-------------------------------------------------------------------
                            //Si fue visitado saltea este if, y continua con la siguiente arista
                            if(!fueVisitadoAntes){
                                int pesoEntero = aTrabajar->obtenerPeso1(verticeVisitado, auxAristas->ConsultarDestino());
                                int pesoDouble = aTrabajar->obtenerPeso2(verticeVisitado, auxAristas->ConsultarDestino());
                                cola.push(auxAristas->ConsultarDestino(), pesoEntero, pesoDouble, iteracion);

                                //Dos etiquetas auxiliares, uno apuntando al vertice visitado
                                //el otro apuntando al vertice destino de la arista
                                Etiqueta auxActual(verticeVisitado), auxDestino(auxAristas->ConsultarDestino());
                                //Busco etiquetas correspondientes y copio sus datos
                                itEtiq = etiquetados.begin();
                                int losDos = 0;
                                while(losDos != 2){
                                    if((*itEtiq).getVertice() == verticeVisitado){
                                        auxActual = *itEtiq;
                                        losDos++;
                                    }
                                    if((*itEtiq).getVertice() == auxAristas->ConsultarDestino()){
                                        auxDestino = *itEtiq;
                                        losDos++;
                                    }
                                    itEtiq++;
                                }
                                //CAMBIO O NO ETIQUETA DE VERTICES DESTINO DE LA ACTUAL ARISTA???
                                //---------------------------------------------------------------
                                int miPeso, pesoArista, pesoTotal;
                                double miPesoDouble, pesoAristaDouble, pesoTotalDouble;
                                miPeso = auxActual.getPesoAcumulado();
                                miPesoDouble = auxActual.getPesoDouble();
                                pesoAristaDouble = aTrabajar->obtenerPeso2(verticeVisitado, auxDestino.getVertice());
                                pesoArista = aTrabajar->obtenerPeso1(verticeVisitado, auxDestino.getVertice());
                                pesoTotal = miPeso + pesoArista;
                                pesoTotalDouble = miPesoDouble + pesoAristaDouble;
                                if(auxDestino.getAnterior().empty()){   //Si no tiene predecesor no tiene peso
                                                                        //Asigno anterior a el vertice que
                                                                        //estoy visitando, peso = al peso
                                                                        //del vertice que estoy visitando+peso
                                                                        //de la arista
                                    auxDestino.setPesoAcumulado(pesoTotal);
                                    auxDestino.setPesoDouble(pesoTotalDouble);
                                    auxDestino.setIteracion(iteracion);
                                }else{  //tiene peso acumulado
                                    int suPeso;
                                    double suPesoDouble;
                                    suPeso = auxDestino.getPesoAcumulado();
                                    suPesoDouble = auxDestino.getPesoDouble();
                                    //Si peso total (acumulado del vertice visitado + arista) menor
                                    //al peso acumulado del vertice destino de la arista
                                    if(((modo == 1) && (pesoTotal < suPeso)) || ((modo == 2) && (pesoTotalDouble < suPesoDouble))){
                                        auxDestino.setPesoAcumulado(pesoTotal);
                                        auxDestino.setPesoDouble(pesoTotalDouble);
                                        auxDestino.setIteracion(iteracion);
                                    }else if(pesoTotal == suPeso){  //Si es igual, agrego un nuevo anterior
                                                                    //y cambio iteracion
                                                                    //iteracion nada, lo saque de no se que clase
                                                                    //per no le encontre utilidad hasta ahora
                                        auxDestino.setIteracion(iteracion);
                                    }
                                }
                                //----------------------------
                                //Reeplazo datos del vertice destino en la lista de etiquetas
                                itEtiq = etiquetados.begin();
                                bool hecho = false;
                                while(!hecho){
                                    if((*itEtiq).getVertice() == auxDestino.getVertice()){
                                        *itEtiq = auxDestino;
                                        hecho = true;
                                    }
                                    itEtiq++;
                                }
                                //----------------------------
                            }
                            itEtiq = etiquetados.begin();
                            bool agregado = false;
                            while(!agregado && itEtiq != etiquetados.end()){
                                if((*itEtiq).getVertice() == auxAristas->ConsultarDestino()){
                                    (*itEtiq).sumoAnterior(verticeVisitado);
                                    agregado = true;
                                }
                                itEtiq++;
                            }
                            if (!agregado){
                                cout << "Error queriendo agregar padre" << endl;
                                cin.get();
                            }
                            auxAristas = auxAristas->consultarSiguiente();
                        }

                        //Este condicional lo puse para el caso de que inicio y fin del viaje sea el mismo
                        //De esta forma no marco el vertice de salida como visitado si es la primera iteracion
                        if(auxDesde == auxHasta){
                            if(primeraEntrada){
                                primeraEntrada = false;
                            }else{
                                vistos.push_back(verticeVisitado);
                            }
                        }else{
                            vistos.push_back(verticeVisitado);
                        }
                        iteracion++;
                    }
                }
                //------------------------------------------------------
                //HACER METODO APARTE
                //Solo muestro el orden en que fueron recorridos los vertices
                Vertice* auxilio;
                cout << "----------------------------" << endl;
                cout << "VERTICES MARCADOS (EN ORDEN)" << endl;
                cout << "----------------------------" << endl;
                list<Vertice*>::iterator i;
                for(i = vistos.begin(); i != vistos.end(); i++){
                    auxilio = *i;
                    cout << auxilio->obtenerNombreVertice() << endl;
                }
                //------------------------------------------------------
                //-------------------------------------------------
                //metodo aparte HAY CAMINO??
                itEtiq = etiquetados.begin();
                bool hayCamino = false;
                list<Vertice*> comienzoDelCamino;
                while(!hayCamino && itEtiq != etiquetados.end()){
                    if((*itEtiq).getVertice() == aTrabajar->obtenerVertice(auxHasta)){
                        if (!(*itEtiq).getAnterior().empty()){
                            comienzoDelCamino = (*itEtiq).getAnterior();
                            hayCamino = true;
                        }
                    }
                    itEtiq++;
                }
                //------------------------------------------------
                if(hayCamino){
                    cout << "------------------" << endl;
                    cout << "Se encontro camino\n";
                    cout << "------------------" << endl;
                    //-----------------------------------------------------------------
                    //Solo muestro etiquetas finales
                    cout << "----------------" << endl;
                    cout << "ETIQUETADO FINAL" << endl;
                    cout << "----------------" << endl;
                    for(itEtiq = etiquetados.begin(); itEtiq != etiquetados.end(); itEtiq++){
                        cout << "Estacion: "<< (*itEtiq).getVertice()->obtenerNombreVertice();
                        cout << " Anterior(es): ";

                        if(!(*itEtiq).getAnterior().empty()){
                            list<Vertice*> auxVerticesAnteriores = (*itEtiq).getAnterior();
                            list<Vertice*>::iterator i;
                            for(i = auxVerticesAnteriores.begin(); i != auxVerticesAnteriores.end(); i++){
                                cout << (*i)->obtenerNombreVertice() << "-";
                            }
                        }else{
                        cout << "NO";
                        }
                        cout << " Acumulado: " << (*itEtiq).getPesoAcumulado();
                        cout << " Double: " << (*itEtiq).getPesoDouble();
                        cout << " It: " << (*itEtiq).getIteracion() << endl;
                    }
                    //-----------------------------------------------------------------

                    //-----------------------------------------------------
                    Vertice* inicioRecorrido = aTrabajar->obtenerVertice(auxHasta);
                    stack<TuplaCompleta> pilaTuplas;
                    bool primerLlamado = true;
                    mostrarVer3(etiquetados, inicioRecorrido, aTrabajar->obtenerVertice(auxDesde), pilaTuplas, primerLlamado, modo, aTrabajar);
                    //-----------------------------------------------------
                    cout << "-------------------------------------------------\n";
                }else{
                    cout << "No hay conexion\n";
                }
            }else{
                cout << "No existe DESDE o HASTA\n";
            }
            cin.get();
            cin.get();
            break;
        }
        default:
            break;
    }
    }while(opcion != 13);

}

//Listado Vertices anteriores (de donde vengo)
//Listado etiquetas para referencia(no se modifica nunca)
//Cola relativa, una vez que llegue al comienzo tienen que imprimir
//Vertice donde estoy parado
//vertice de llegada (seria el comienzo del camino)
//uso en el main
//mostrarRuta("anteriores del final" , "etiquetados", "cola vacia", "Vertice* llegada", "Vertice* inicio")

void mostrarRuta(list<Vertice*> anteriores, list<Etiqueta> etiquetas, stack<Vertice*> pila, Vertice* actual, Vertice* inicio){
    list<Vertice*> anterioresActual = anteriores;
    stack<Vertice*> pilaActual = pila;
    if(anterioresActual.size() == 1){//la lista de anteriores tiene un solo elemento
        pilaActual.push(anterioresActual.front());
        anterioresActual.pop_front();
        int costoTrayecto = 0, costoAcumulado = 0;
        if(pilaActual.top() == inicio){
            cout << "----------------------------\n";
            cout << "Recorrido minimo encontrado:\n";
            cout << "----------------------------\n";
            bool comienzoTramo = true;
            while(!pilaActual.empty()){
                cout << pilaActual.top()->obtenerNombreVertice();
                //cout << "-(";
                if(comienzoTramo){
                    cout << "-(+";
                    comienzoTramo = false;
                    pilaActual.pop();
                    list<Etiqueta>:: iterator i;
                    i = etiquetas.begin();
                    bool encontrado = false;
                    while(!encontrado && i != etiquetas.end()){
                        if((*i).getVertice() == pilaActual.top()){
                            costoAcumulado = (*i).getPesoAcumulado();
                            encontrado = true;
                        }
                        i++;
                    }
                    cout << costoAcumulado << ")->";
                    costoTrayecto = costoAcumulado;
                }else{
                    pilaActual.pop();
                    list<Etiqueta>:: iterator i;
                    i = etiquetas.begin();
                    bool encontrado = false;
                    while(!pilaActual.empty() && (!encontrado && i != etiquetas.end())){
                        if((*i).getVertice() == pilaActual.top()){
                            costoAcumulado = (*i).getPesoAcumulado();
                            encontrado = true;
                        }
                        i++;
                    }
                    //pilaActual.pop();
                    if(!pilaActual.empty()){
                        cout << "-(+";
                        cout << costoAcumulado - costoTrayecto << ")->";
                        costoTrayecto = costoAcumulado;
                    }else{
                        cout << "[" << costoAcumulado << "]";
                    }
                }
            }
            cout << endl;
            return;
        }else{
            //buscar los anteriores del que esta sobre la cola
            list<Etiqueta>:: iterator i;
            i = etiquetas.begin();
            bool encontrado = false;
            while(!encontrado && i != etiquetas.end()){
                if((*i).getVertice() == pilaActual.top()){
                    anterioresActual = (*i).getAnterior();
                    encontrado = true;
                    mostrarRuta(anterioresActual, etiquetas, pilaActual, anterioresActual.front(), inicio);
                }
                i++;
            }
            return;
        }
    }else{
        cout << "--------------------------\n";
        cout << "VARIOS CAMINOS MISMO COSTO" << endl;
        cout << "--------------------------\n";
        list<Vertice*> unoDeVariosAnteriores;
        while(!anterioresActual.empty()){
            unoDeVariosAnteriores.push_front(anterioresActual.front());
            mostrarRuta(unoDeVariosAnteriores, etiquetas, pilaActual, actual, inicio);
            anterioresActual.pop_front();
            unoDeVariosAnteriores.pop_front();
        }
        return;
    }
}

//Pasos que debe realizar metodo:
    // hago pila local
    // aux Vertice*
    // recorriendoDsd longitud 1
    //          de recorriendoDsd retiro el vertice
    //          tupla aux, peso acumulado aux
    //      recorriendoDsd == lugarDePartida y no es el primer llamado al metodo
    //          apilo tupla (en pila local)
    //          imprime pila
    //          RETURN
    //      sino
    //          apilo tupla (en pila local)
    //          consulto antecesores de aux
    //          coloco booleano en falso
    //          llamo de nuevo a mostrar
    //          RETURN
    // recorriendoDsd longitud mayor 1 (varios caminos)
    //      mientras recorriendoDsd no este vacio
    //          aux Vertice*
    //          consulto 1 elemento de recorriendoDsd (en aux)
    //          retiro dicho elemento de recorriendoDsd (de la lista)
    //          apilo tupla aux, peso acumulado aux (en pila local)
    //          consulto antecesores de aux
    //          coloco booleano en falso
    //          llamo de nuevo a mostrar
    //          retiro tupla aux, peso acumulado aux (de pila local)
    //      RETURN
    // inicio longitud 0 no puede pasar!!
    //      Cartel mostrando un error
void mostrarVer2(list<Etiqueta> etiquetados, list<Vertice*> recorriendoDesde, Vertice* destino, stack<Tupla> caminoRecorrido, bool primeraPasada){
    //creo que no

    stack<Tupla> PilaLocal = caminoRecorrido;//entra vacio
    Tupla tuplaLocal;
    Vertice* aux;
    if(recorriendoDesde.size() == 1){
        aux = recorriendoDesde.front();
        tuplaLocal.vertice = aux;
        list<Etiqueta>::iterator i;
        i = etiquetados.begin();
        bool encontrado = false;
        while(!encontrado && i != etiquetados.end()){
            if((*i).getVertice() == aux){
                tuplaLocal.pesoAcumulado = (*i).getPesoAcumulado();
                encontrado = true;
            }
            i++;
        }
        if((aux == destino) && !primeraPasada){
            PilaLocal.push(tuplaLocal);
            cout << "-------------------------" << endl;
            cout << "MOSTRAR TODO EL RECORRIDO" << endl;
            cout << "-------------------------" << endl;
            mostrarPilaTuplas(PilaLocal);
            return;
        }else{
            PilaLocal.push(tuplaLocal);
            list<Vertice*> recorriendoDesdeLocal;
            i = etiquetados.begin();
            bool encontrado = false;
            while(!encontrado && i != etiquetados.end()){
                if((*i).getVertice() == aux){
                    recorriendoDesdeLocal = (*i).getAnterior();
                    encontrado = true;
                }
                i++;
            }
            bool primerRecorrido = false;
            mostrarVer2(etiquetados, recorriendoDesdeLocal, destino, PilaLocal, primerRecorrido);
            return;
        }
    }else if(recorriendoDesde.size() > 1){
        while(!recorriendoDesde.empty()){
            aux = recorriendoDesde.front();
            recorriendoDesde.pop_front();
            tuplaLocal.vertice = aux;
            list<Etiqueta>::iterator i;
            i = etiquetados.begin();
            bool encontrado = false;
            list<Vertice*> recorriendoDesdeLocal;
            while(!encontrado && i != etiquetados.end()){
                if((*i).getVertice() == aux){
                    tuplaLocal.pesoAcumulado = (*i).getPesoAcumulado();
                    recorriendoDesdeLocal = (*i).getAnterior();
                    encontrado = true;
                }
                i++;
            }
            PilaLocal.push(tuplaLocal);
            bool primerRecorrido = false;
            mostrarVer2(etiquetados, recorriendoDesdeLocal, destino, PilaLocal, primerRecorrido);
            PilaLocal.pop();
        }
        return;
    }else{
        cout << "---------------------------" << endl;
        cout << "NO TIENE ANTECESORES, ERROR!" << endl;
        cout << "---------------------------" << endl;
        return;
    }
}
void mostrarPilaTuplas(stack<Tupla> aMostrar){
    Tupla mostrando;
    int pesoTotal = 0, pesoAnterior = 0, pesoArista = 0;
    bool primerVertice = true;
    while(!aMostrar.empty()){
        mostrando = aMostrar.top();
        if(primerVertice){
            cout << (mostrando.vertice)->obtenerNombreVertice();
            primerVertice = false;
        }else{
            pesoTotal = mostrando.pesoAcumulado;
            pesoArista = pesoTotal - pesoAnterior;
            cout << "-(+" << pesoArista << ")->" << (mostrando.vertice)->obtenerNombreVertice();
            pesoAnterior = pesoTotal;
        }
        aMostrar.pop();
    }
    cout << "[" << pesoTotal << "]" << endl;
}

void mostrarVer3(list<Etiqueta> etiquetados, Vertice* recorriendoDesde, Vertice* destino, stack<TuplaCompleta> caminoRecorrido, bool primeraPasada, int criterio, Grafo* gra){
    stack<TuplaCompleta> PilaLocal = caminoRecorrido;//entra vacio

    TuplaCompleta tuplaLocal;
    Vertice* aux;

    if(recorriendoDesde){
        tuplaLocal.vertice = recorriendoDesde;
        aux = recorriendoDesde;
        list<Etiqueta>::iterator i;
        i = etiquetados.begin();
        bool encontrado = false;
        while(!encontrado && i != etiquetados.end()){
            if((*i).getVertice() == aux){
                tuplaLocal.pesoAcumulado = (*i).getPesoAcumulado();
                tuplaLocal.pesoDouble = (*i).getPesoDouble();
                encontrado = true;
            }
            i++;
        }
        if((recorriendoDesde == destino) && !primeraPasada){
            PilaLocal.push(tuplaLocal);
            cout << "+-------------------------+" << endl;
            cout << "|MOSTRAR TODO EL RECORRIDO|" << endl;
            cout << "+-------------------------+" << endl;
            mostrarPila(PilaLocal, criterio);
            return;
        }else{
            PilaLocal.push(tuplaLocal);
            list<Vertice*> antecesores;
            i = etiquetados.begin();
            bool encontrado = false;
            while(!encontrado && i != etiquetados.end()){
                if((*i).getVertice() == recorriendoDesde){
                    antecesores = (*i).getAnterior();
                    encontrado = true;
                }
                i++;
            }
            Vertice* recorriendoDesdeLocal;
            if(antecesores.size() > 1){
                while(!antecesores.empty()){
                    recorriendoDesdeLocal = antecesores.front();
                    antecesores.pop_front();
                    if(recorriendoDesdeLocal == destino){
                        bool primerRecorrido = false;
                        mostrarVer3(etiquetados, recorriendoDesdeLocal, destino, PilaLocal, primerRecorrido, criterio, gra);
                    }else{
                        int pesoEntero = 0;
                        double pesoDouble = 0.0;
                        pesoEntero = gra->obtenerPeso1(recorriendoDesdeLocal, recorriendoDesde);
                        pesoDouble = gra->obtenerPeso2(recorriendoDesdeLocal, recorriendoDesde);
                        int pesoQueTraiaElOtro = tuplaLocal.pesoAcumulado;
                        double pesoQueTraiaDouble = tuplaLocal.pesoDouble;
                        int anteriorDebeAcumular = pesoQueTraiaElOtro - pesoEntero;
                        double anteriorDebeDouble = pesoQueTraiaDouble - pesoDouble;
                        int anteriorAcumula;
                        double anteriorAcumulaDouble;
                        list<Etiqueta>::iterator i;
                        i = etiquetados.begin();
                        bool hecho = false;
                        while(!hecho && i != etiquetados.end()){
                            if((*i).getVertice() == recorriendoDesdeLocal){
                                anteriorAcumula = (*i).getPesoAcumulado();
                                anteriorAcumulaDouble = (*i).getPesoDouble();
                                hecho = true;
                            }
                            i++;
                        }
                        if(((criterio == 1) && (anteriorAcumula == anteriorDebeAcumular)) || ((criterio == 2) && (anteriorAcumulaDouble == anteriorDebeDouble))){
                            bool primerRecorrido = false;
                            mostrarVer3(etiquetados, recorriendoDesdeLocal, destino, PilaLocal, primerRecorrido, criterio, gra);
                        }
                    }
                }
                return;
            }else{
                recorriendoDesdeLocal = antecesores.front();
                bool primerRecorrido = false;
                mostrarVer3(etiquetados, recorriendoDesdeLocal, destino, PilaLocal, primerRecorrido, criterio, gra);
                return;
            }
        }
    }else{
        cout << "-------------------------------------" << endl;
        cout << "        ERROR - ERROR - ERROR!" << endl;
        cout << "(ARMANDO PILA PARA MOSTRAR RECORRIDO)" << endl;
        cout << "-------------------------------------" << endl;
        return;
    }
}
void mostrarPila(stack<TuplaCompleta> aMostrar, int criterio){
    TuplaCompleta mostrando;
    int pesoTotal = 0, pesoAnterior = 0, pesoArista = 0;
    double pesoTotalDouble = 0, pesoAnteriorDouble = 0, pesoAristaDouble = 0;
    bool primerVertice = true;
    while(!aMostrar.empty()){
        mostrando = aMostrar.top();
        if(primerVertice){
            cout << (mostrando.vertice)->obtenerNombreVertice();
            primerVertice = false;
        }else{
            if (criterio == 1){
                pesoTotal = mostrando.pesoAcumulado;
                pesoArista = pesoTotal - pesoAnterior;
                cout << "-(+" << pesoArista << ")->" << (mostrando.vertice)->obtenerNombreVertice();
                pesoAnterior = pesoTotal;
            }else if(criterio == 2){
                pesoTotalDouble = mostrando.pesoDouble;
                pesoAristaDouble = pesoTotalDouble - pesoAnteriorDouble;
                cout << "-(+" << pesoAristaDouble << ")->" << (mostrando.vertice)->obtenerNombreVertice();
                pesoAnteriorDouble = pesoTotalDouble;
            }
        }
        aMostrar.pop();
    }
    if (criterio == 1){
        cout << "[" << pesoTotal << "]" << endl;
    }else if(criterio == 2){
        cout << "[" << pesoTotalDouble << "]" << endl;
    }

}
