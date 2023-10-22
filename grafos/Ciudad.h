#pragma once
#include <iostream>
using namespace std;
class Ciudad
{
private:
	string nombre;
	double poblacion;
	string coordenadas;
public:
	Ciudad();
	Ciudad(string, double, string);

	//Metodos getters
	string getNombre() { return nombre; }
	double getPoblacion() { return poblacion; }
	string getCoordenadas() { return coordenadas; }
	//Metodos setters
	void setPoblacion(double _poblacion) { poblacion = _poblacion; }
	void setNombre(string _nombre) { nombre = _nombre; }
	void setCoordenadas(string _coordenadas) { coordenadas = _coordenadas; }

};

