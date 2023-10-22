#include "Ciudad.h"
#include <iostream>
using namespace std;

Ciudad::Ciudad() {
	nombre = '\0';
	poblacion = 0;
	coordenadas = '\0';
}
Ciudad::Ciudad(string _nombre, double _poblacion, string _coordenadas) {
	nombre = _nombre;
	poblacion = _poblacion;
	coordenadas = _coordenadas;
}
