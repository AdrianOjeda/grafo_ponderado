#include "Grafo.h"
#include "NodoVertice.h"
#include "NodoArista.h"
#include <fstream>
#include <sstream>

Grafo::Grafo() {
	headerGrafo = nullptr;
}

Grafo::Grafo(NodoVertice* _headerGrafo) {
	headerGrafo = _headerGrafo;

}
bool Grafo::vacio() {
	if (headerGrafo)
		return false;
	else {
		cout << "El grafo esta vacio!" << endl;
		return true;
	}

}

void Grafo::insertarVertice(Ciudad city) {

	NodoVertice *temp = new NodoVertice(city, nullptr, nullptr);

	if (headerGrafo == nullptr) {
		headerGrafo = temp;
	}
	else {
		temp->sigVertice = headerGrafo;
		headerGrafo = temp;
	}
}

NodoVertice* Grafo::buscarVertice(string verticeABuscar) {
	NodoVertice* aux = headerGrafo;
	bool encontrado = false;
	while (aux and !encontrado) {
		if (aux->city.getNombre() == verticeABuscar) {
			encontrado = true;
		}
		else {
			aux = aux->sigVertice;
		}
	}
	return aux;

}

NodoArista* Grafo::buscarArista(string origen, string destino, int peso) {

	NodoVertice* existeOrigen = buscarVertice(origen);
	NodoArista* aux = existeOrigen->headerArista;
	bool aristaEncontrada = false;

	while (aux and !aristaEncontrada) {
		if (aux->destino->city.getNombre() == destino and aux->peso == peso) {
			aristaEncontrada = true;
		}
		else {
			aux = aux->sigArista;
		}
	}
	return aux;
	
}
void Grafo::eliminarArista(string origen, string destino, int peso) {
	NodoVertice* existeOrigen = buscarVertice(origen);

	if (existeOrigen) {
		NodoArista* aux = existeOrigen->headerArista;
		NodoArista* auxAnterior = nullptr;
		bool aristaEliminada = false;

		while (!aristaEliminada) {
			if (aux->destino->city.getNombre() == destino && aux->peso == peso) {
				if (auxAnterior) {
					auxAnterior->sigArista = aux->sigArista;
				}
				else {
					existeOrigen->headerArista = aux->sigArista;
				}
				delete aux;
				aristaEliminada = true;
			}
			else {
				auxAnterior = aux;
				aux = aux->sigArista;
			}	
		}

		if (aristaEliminada) {
			cout << "Ruta (arista) eliminada con exito!" << endl;
		}
		else {
			cout << "No se encontró la ruta (arista)" << endl;
		}
	}
}

void Grafo::insertarArista(string origen, string destino, int peso) {
	NodoVertice* existeOrigen = buscarVertice(origen); 
	NodoVertice* existeDestino = buscarVertice(destino);
	NodoArista* temp = new NodoArista(peso, nullptr, nullptr);

	if (existeOrigen and existeDestino) {
		temp->sigArista = existeOrigen->headerArista;
		existeOrigen->headerArista = temp;
		existeOrigen->headerArista->destino = existeDestino;
	}
	else
		cout << "No se encuentra el origen o el destino" << endl;

}
void Grafo::eliminarVertice(string ciudad) {
	NodoVertice* existeVertice = buscarVertice(ciudad);
	

	if (existeVertice) {

		NodoVertice* auxVertice = headerGrafo; 
		NodoVertice* auxVerticeAnterior = nullptr; 
		NodoArista* auxAristaDeVertice = existeVertice->headerArista; 
		bool verticeEliminada = false;

		while (!verticeEliminada) {
			if (auxVertice->city.getNombre() == ciudad) {
				while (auxAristaDeVertice) {
					NodoArista* temp = auxAristaDeVertice;
					auxAristaDeVertice = auxAristaDeVertice->sigArista;
					delete temp;
				}
				existeVertice->headerArista = nullptr;
				delete auxAristaDeVertice;
				if (auxVerticeAnterior) {
					auxVerticeAnterior->sigVertice = auxVertice->sigVertice;
				}
				else {
					headerGrafo = auxVertice->sigVertice;
				}
				delete auxVertice;
				verticeEliminada = true;

			}
			else {
				auxVerticeAnterior = auxVertice;
				auxVertice = auxVertice->sigVertice;

			}
		}
		if (verticeEliminada)
			cout << "Ciudad (vertice) eliminada con exito!" << endl << endl;
	
	}
	else
		cout << "La ciudad (vertice) que desea eliminar no existe!" << endl << endl;
}
void Grafo::mostrarGrafo() {
	NodoVertice* auxVertice = headerGrafo;
	while (auxVertice) {
		NodoArista* auxArista = auxVertice->headerArista;
		cout << "*** Ciudad (vertice) ***" << endl;
		cout << "Nombre: " << auxVertice->city.getNombre() << " | Coordenadas: " << auxVertice->city.getCoordenadas();
		cout << " | Poblacion: " << auxVertice->city.getPoblacion() << "||" << endl;
		cout << "*** Rutas a (Aristas) ***" << endl;
		while (auxArista) {
			cout << "(Destino: " << auxArista->destino->city.getNombre() << " Peso: " << auxArista->peso << ") ";
			auxArista = auxArista->sigArista;
		}
		cout << endl << "----------------------------------------------------------------------------------" << endl;
		auxVertice = auxVertice->sigVertice;

	}

}

void Grafo::guardarEnArchivo() {

	ofstream fileVertice("archivoVertices.txt", ios::out | ios::app); 
	ofstream fileArista("archivoAristas.txt", ios::out | ios::app); 
	if (!fileVertice.is_open()) { 
		cerr << "No se pudo abrir el archivo vertice" << endl; 
		exit(EXIT_FAILURE); 
	}

	NodoVertice* auxVertice = headerGrafo;
	while (auxVertice) {
		NodoArista* auxArista = auxVertice->headerArista; 
		
		fileVertice << auxVertice->city.getNombre() << "|" << auxVertice->city.getCoordenadas() << "|" << auxVertice->city.getPoblacion() << "\n";
		auxVertice = auxVertice->sigVertice; 
	} 

	fileVertice.close();

	if (!fileArista.is_open()) {
		cerr << "No se pudo abrir el archivo Arista" << endl;
		exit(EXIT_FAILURE);
	}

	NodoVertice* auxVertice2 = headerGrafo; 
	while (auxVertice2) { 
		NodoArista* auxArista = auxVertice2->headerArista; 
		while (auxArista) { 
			fileArista << auxVertice2->city.getNombre()<<"|"<<auxArista->destino->city.getNombre() << "|" << auxArista->peso << "\n";
			auxArista = auxArista->sigArista; 
		}  
		auxVertice2 = auxVertice2->sigVertice;
	}
	fileArista.close();
}

