#include <iostream>
#include <vector>
#include<cctype>
using namespace std;
const int TAMANO_ARREGLO = 26;
const int INICIO_ASCCI = 97;

struct NodoArbolPrefijo{
    bool esFinal;
    NodoArbolPrefijo* hijos[TAMANO_ARREGLO];
};

NodoArbolPrefijo* NuevoNodo(){
    NodoArbolPrefijo* nodo = new NodoArbolPrefijo();
    nodo->esFinal = false;
    for (int i = 0; i < TAMANO_ARREGLO; i++) {
        nodo->hijos[i] = nullptr; 
    }
    return nodo;
}

void Insertar(string palabra, NodoArbolPrefijo *raiz){
    NodoArbolPrefijo* nodoActual = raiz;
    for (char c: palabra){
        int indice = static_cast<int>(tolower(c)) - INICIO_ASCCI;
        if (nodoActual->hijos[indice] == nullptr){
            nodoActual->hijos[indice] = NuevoNodo();
        }
        nodoActual = nodoActual->hijos[indice];
    }
    nodoActual->esFinal = true;
}

bool Buscar(string palabra, NodoArbolPrefijo* raiz){
    NodoArbolPrefijo* nodoActual = raiz;
    for (char c: palabra){
        int indice = static_cast<int>(tolower(c)) - INICIO_ASCCI;
        if (nodoActual->hijos[indice] == nullptr){
            return false;
        }
        nodoActual = nodoActual->hijos[indice];
    }
    return nodoActual != nullptr && nodoActual->esFinal;
}

void BuscarPalabra(string palabra, NodoArbolPrefijo* raiz){
    if (Buscar(palabra, raiz)){
        cout << "La palabra '" << palabra << "' esta en el arbol de prefijos.";
    } else {
        cout << "La palabra '" << palabra << "' NO esta en el arbol de prefijos.";
    }
}

int main()
{
    NodoArbolPrefijo* raiz = NuevoNodo();

    Insertar("hola", raiz);
    Insertar("adios", raiz);
    Insertar("hogar", raiz);
    Insertar("hombre", raiz);
    Insertar("hora", raiz);
    Insertar("alamo", raiz);
    Insertar("arbol", raiz);

    BuscarPalabra("hola", raiz);
    BuscarPalabra("adios", raiz);
    
    return 0;
}
