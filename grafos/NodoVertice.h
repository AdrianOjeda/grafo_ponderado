#pragma once
#include "Ciudad.h"
#include <iostream>
using namespace std;


class NodoArista;


class NodoVertice
{

public:
	Ciudad city;
	NodoArista *headerArista;
	NodoVertice *sigVertice;
	NodoVertice(Ciudad, NodoArista*, NodoVertice*);

};

