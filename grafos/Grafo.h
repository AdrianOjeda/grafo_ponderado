#pragma once
#include "Ciudad.h"
#include <iostream>
using namespace std;

class NodoVertice;
class NodoArista;

class Grafo
{

public:
	NodoVertice* headerGrafo;

	Grafo();
	Grafo(NodoVertice*);

	bool vacio();
	void insertarVertice(Ciudad);
	void insertarArista(string, string, int);
	NodoVertice* buscarVertice(string);
	void mostrarGrafo();
	NodoArista* buscarArista(string, string, int);
	void eliminarVertice(string);
	void eliminarArista(string, string, int);
	void guardarEnArchivo();
	void recuperarArchivo();
};

