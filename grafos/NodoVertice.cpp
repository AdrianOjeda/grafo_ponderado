#include "NodoVertice.h"

#include <iostream>
using namespace std;


NodoVertice::NodoVertice(Ciudad _city, NodoArista* _headerArista, NodoVertice* _sigVertice) {
	city = _city;
	headerArista = _headerArista;
	sigVertice = _sigVertice;

}
