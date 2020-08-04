#include <iostream>
#include <cstdlib>
#include <ctime>
#include <list>
#include <queue>
#include "arista.h"
#include "vertice.h"
#include "grafo.h"
#include "etiqueta.h"

void menu(Grafo* aTrabajar);

using namespace std;

int main()
{
    srand(time(NULL));

    string estaciones[] = {"TIJ", "MTY", "MZT", "BJX", "GDL", "SAN", "TAM", "MEX", "MID", "CUN"};
    Grafo* gra = new Grafo;
    for(int i = 0; i < 10; i++){
        gra->agregarVertice(estaciones[i]);
    }
    gra->agregarArista(gra->obtenerVertice("TIJ"), gra->obtenerVertice("MTY"), 800, 0);
    gra->agregarArista(gra->obtenerVertice("MTY"), gra->obtenerVertice("BJX"), 700, 0);
    gra->agregarArista(gra->obtenerVertice("GDL"), gra->obtenerVertice("MTY"), 450, 0);
    gra->agregarArista(gra->obtenerVertice("MZT"), gra->obtenerVertice("TIJ"), 400, 0);
    gra->agregarArista(gra->obtenerVertice("MZT"), gra->obtenerVertice("BJX"), 300, 0);
    gra->agregarArista(gra->obtenerVertice("GDL"), gra->obtenerVertice("MZT"), 500, 0);
    gra->agregarArista(gra->obtenerVertice("GDL"), gra->obtenerVertice("BJX"), 250, 0);
    gra->agregarArista(gra->obtenerVertice("GDL"), gra->obtenerVertice("MEX"), 500, 0);
    gra->agregarArista(gra->obtenerVertice("CUN"), gra->obtenerVertice("GDL"), 650, 0);
    gra->agregarArista(gra->obtenerVertice("MEX"), gra->obtenerVertice("CUN"), 650, 0);
    gra->agregarArista(gra->obtenerVertice("BJX"), gra->obtenerVertice("MEX"), 350, 0);
    gra->agregarArista(gra->obtenerVertice("BJX"), gra->obtenerVertice("TAM"), 400, 0);
    gra->agregarArista(gra->obtenerVertice("BJX"), gra->obtenerVertice("SAN"), 900, 0);
    gra->agregarArista(gra->obtenerVertice("SAN"), gra->obtenerVertice("MID"), 1200, 0);
    gra->agregarArista(gra->obtenerVertice("TAM"), gra->obtenerVertice("MID"), 450, 0);
    gra->agregarArista(gra->obtenerVertice("MEX"), gra->obtenerVertice("MID"), 450, 0);

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
    cout << "11- Salir\n";
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
            if(aTrabajar->existeVertice(auxDesde) && aTrabajar->existeVertice(auxHasta)){
                int cantVertices = aTrabajar->grandor();
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
                cout << "Etiquetas.." << endl;
                for(itEtiq = etiquetados.begin(); itEtiq != etiquetados.end(); itEtiq++){
                    cout << "Estacion: "<< (*itEtiq).getVertice()->obtenerNombreVertice();
                    cout << " Anterior: ";
                    if((*itEtiq).getAnterior()){
                        cout << (*itEtiq).getAnterior()->obtenerNombreVertice();
                    }else{
                        cout << "NO";
                    }
                    cout << " Acumulado: " << (*itEtiq).getPesoAcumulado();
                    cout << " Iteracion: " << (*itEtiq).getIteracion() << endl;
                }

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
                                if(!auxProximo.getAnterior()){
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
                                        auxProximo.setAnterior(verticeVisitado);
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
                        vistos.push_back(verticeVisitado);
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
                while(!hayCamino && itEtiq != etiquetados.end()){
                    if((*itEtiq).getVertice() == aTrabajar->obtenerVertice(auxHasta)){
                        if((*itEtiq).getAnterior()){
                            hayCamino = true;
                        }
                    }
                    itEtiq++;
                }
                if(hayCamino){
                    cout << "Se encontro camino\n";
                    cout << "Falta mostrarlo de esta lista....\n";
                    cout << "Etiquetas.." << endl;
                    for(itEtiq = etiquetados.begin(); itEtiq != etiquetados.end(); itEtiq++){
                        cout << "Estacion: "<< (*itEtiq).getVertice()->obtenerNombreVertice();
                        cout << " Anterior: ";
                        if((*itEtiq).getAnterior()){
                            cout << (*itEtiq).getAnterior()->obtenerNombreVertice();
                        }else{
                            cout << "NO";
                        }
                        cout << " Acumulado: " << (*itEtiq).getPesoAcumulado();
                        cout << " Iteracion: " << (*itEtiq).getIteracion() << endl;
                    }
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
    }while(opcion != 11);

}
