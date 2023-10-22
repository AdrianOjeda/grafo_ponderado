
#include "NodoArista.h"
#include <iostream>
using namespace std;


NodoArista::NodoArista() : peso(0), destino(nullptr), sigArista(nullptr) {

}

NodoArista::NodoArista(int _peso, NodoVertice* _destino, NodoArista* _sigArista)
    : peso(_peso), destino(_destino), sigArista(_sigArista) {
}