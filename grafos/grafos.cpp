// grafos.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Grafo.h"
#include "Ciudad.h"
#include "NodoVertice.h"
#include "NodoArista.h"
#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <sstream>
using namespace std;

int main()
{
    Ciudad city;
    Grafo* miGrafo = new Grafo();
    string nombre, coordenadas, origen, destino, verticeABuscar;
    double poblacion;
    int peso;

    cout << "Hello World!\n";
    city.setNombre("Guadalajara");
    city.setCoordenadas("coordenadas");
    city.setPoblacion(12323);
    miGrafo->insertarVertice(city);
    city.setNombre("Madrid");
    city.setCoordenadas("coordenadas 2");
    city.setPoblacion(347386478);
    miGrafo->insertarVertice(city);
    miGrafo->insertarArista("Guadalajara", "Madrid", 12);
    miGrafo->insertarArista("Madrid", "Guadalajara", 15);

    int resp;
    do{
        cout << "*** Grafo Ponderado ***" << endl << endl;
        cout << "1.- Insertar ciudad (vertice)" << endl;
        cout << "2.- Insertar ruta (arista)" << endl;
        cout << "3.- Eliminar ruta (arista)" << endl;
        cout << "4.- Eliminar ciudad (vertice)" << endl;
        cout << "5.- Mostrar grafo" << endl;
        cout << "6.- Buscar vertice o arista" << endl;
        cout << "7.- Guardar grafo en archivos" << endl;
        cout << "8.- Recuperar informacion del archivo 'grafo.txt'" << endl;
        cout << "9.- Salir" << endl;
        cin >> resp;
        cout << endl;
        switch (resp) {
        case 1: {
            cout << "*** Insertar ciudad ***" << endl << endl;

            cout << "Nombre de la ciudad: ";
            cin.ignore();
            getline(cin, nombre);
            city.setNombre(nombre);

            cout << "Coordenadas de la ciudad: ";
            getline(cin, coordenadas);
            city.setCoordenadas(coordenadas);

            cout << "Poblacion de la ciudad: ";
            cin >> poblacion;
            city.setPoblacion(poblacion);
            NodoVertice* yaExiste= miGrafo->buscarVertice(nombre);
            if (yaExiste) {
                cout << "Ya existe una ciudad (vertice) con ese nombre!" << endl;
            }
            else {
                miGrafo->insertarVertice(city);
                cout << "Ciudad (vertice) insertada con exito!" << endl;
            }
            cout << endl;
            break;
        }case 2: {
            cout << "*** Insertar Arista ***" << endl << endl;

            cout << "Ingrese la ciudad de origen: ";
            cin.ignore();
            getline(cin, origen);

            cout << "Ingrese la ciudad destino: ";
            getline(cin, destino);

            cout << "Ingrese el peso de la arista: ";
            cin >> peso;

            miGrafo->insertarArista(origen, destino, peso);
            cout << endl;
            break;
        }case 3: {
            cout << "*** Eliminar ruta (arista) ***" << endl << endl;

            cout << "Ingrese la ciudad de origen: ";
            cin.ignore();
            getline(cin, origen);

            cout << "Ingrese la ciudad destino: ";
            getline(cin, destino);

            cout << "Ingrese el peso de la arista: ";
            cin >> peso;
            miGrafo->eliminarArista(origen, destino, peso);
            cout << endl;

            break;
        }case 4: {
            cout << "*** Eliminar ciudad (vertice) ***" << endl << endl;
            cout << "Ingrese el nombre de la ciudad (vertice): ";
            cin.ignore();
            getline(cin, verticeABuscar);
            miGrafo->eliminarVertice(verticeABuscar);

            break;
        }case 5: {
            cout << "*** Mostrar Grafo ***" << endl;
            if (miGrafo->vacio());
            else
                miGrafo->mostrarGrafo();

            break;
        }case 6: {
            int option;
            
            cout << "*** Buscar Vertice o Arista ***" << endl;
            cout << "1.- Buscar ciudad (vertice)" << endl;
            cout << "2.- Buscar ruta (arista)" << endl;
            cin >> option;
            if (option == 1) {
                cout << endl << "Inserte el nombre de la ciudad (vertice) ";
                cin.ignore();
                getline(cin, verticeABuscar);
                NodoVertice* existeVertice = miGrafo->buscarVertice(verticeABuscar);
                if (existeVertice) {
                    cout << "Nombre de la ciudad: " << existeVertice->city.getNombre() << " | Coordenadas: " << existeVertice->city.getCoordenadas();
                    cout<<" | Poblacion:"<<existeVertice->city.getPoblacion() << endl;
                }
                else
                    cout << "No existe la ciudad (vertice)!" << endl;

            }
            else if (option == 2) {
                cout << endl << "Ingrese el nombre de la ciudad origen: ";
                cin.ignore();
                getline(cin, verticeABuscar);

                cout << "Ingrese la ciudad destino: ";
                //cin.ignore();
                getline(cin, destino);

                cout << "Ingrese el peso de la arista: ";
                cin >> peso;
                NodoArista* existeArista = miGrafo->buscarArista(verticeABuscar, destino, peso);
                if (existeArista) {
                    cout << endl << "*** Ruta (arista) *** " << endl << endl;
                    cout << "Ciudad de origen: " << verticeABuscar << " | Destino: " << existeArista->destino->city.getNombre();
                    cout << " | Peso: " << existeArista->peso << endl;
                }
                else
                    cout << "No existe la ruta (arista)!" << endl;
            }
            else
                cout << "Entrada no valida!" << endl;
            break;
        }case 7: {
            miGrafo->guardarEnArchivo();
            cout << "Grafo Guardado con exito!" << endl;

            break;
        }case 8: {

            Ciudad city;
            ifstream inputFileVertices("archivoVertices.txt");

            if (!inputFileVertices.is_open()) {
                cerr << "Failed to open the file!" << endl;
                return 1;
            }

            string line;

            while (getline(inputFileVertices, line, '\n')) {
                istringstream iss(line);
                string token;
                double poblacion = 0;
                string nombre;
                string coordenadas;

                int fieldIndex = 0;
                while (getline(iss, token, '|')) {
                    if (fieldIndex == 0) {
                        try {
                            nombre = token;
                            city.setNombre(nombre);
                        }
                        catch (const invalid_argument& e) {
                            cerr << "Error al convertir el nombre: " << e.what() << endl;

                        }

                    }
                    else if (fieldIndex == 1) {
                        try {
                            coordenadas = token;
                            city.setCoordenadas(coordenadas);
                        }
                        catch (const invalid_argument& e) {
                            cerr << "Error al convertir las coordenadas: " << e.what() << endl;

                        }

                    }
                    else if (fieldIndex == 2) {
                        try {
                            poblacion = stod(token);
                            city.setPoblacion(poblacion);
                        }
                        catch (const invalid_argument& e) {
                            cerr << "Error al convertir las páginas: " << e.what() << endl;

                        }

                    }
                   
                    fieldIndex++;
                }

                miGrafo->insertarVertice(city);
            }
            inputFileVertices.close();

            ifstream inputFileAristas("archivoAristas.txt");

            if (!inputFileAristas.is_open()) {
                cerr << "Failed to open the file!" << endl;
                return 1;
            }

            string line2;

            while (getline(inputFileAristas, line2, '\n')) {
                istringstream iss(line2);
                string token;
                int peso;
                string origen;
                string destino;

                int fieldIndex = 0;
                while (getline(iss, token, '|')) {
                    if (fieldIndex == 0) {
                        try {
                            origen = token;
                            
                        }
                        catch (const invalid_argument& e) {
                            cerr << "Error al convertir el origen: " << e.what() << endl;

                        }

                    }
                    else if (fieldIndex == 1) {
                        try {
                            destino = token;
                            
                        }
                        catch (const invalid_argument& e) {
                            cerr << "Error al convertir las coordenadas: " << e.what() << endl;

                        }

                    }
                    else if (fieldIndex == 2) {
                        try {
                            peso = stoi(token);
                            
                        }
                        catch (const invalid_argument& e) {
                            cerr << "Error al convertir el peso: " << e.what() << endl;

                        }

                    }

                    fieldIndex++;
                }

                miGrafo->insertarArista(origen, destino, peso);
            }
            inputFileAristas.close();

            miGrafo->mostrarGrafo();
            cout << "*** Informacion recuperada ***" << endl;

            break;
        }
        
        default: {
            cout << "Ingrese una opcion valida!" << endl;
            break;
        }

        }
    } while (resp != 9);
}

