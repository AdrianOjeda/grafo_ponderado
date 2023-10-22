#pragma once


class NodoVertice;

using namespace std;
class NodoArista
{

public:

	int peso;
	NodoVertice* destino;
	NodoArista* sigArista;
	NodoArista();
	NodoArista(int, NodoVertice*, NodoArista*);

};

