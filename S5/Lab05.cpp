#include <iostream>
#include <vector>
#include <cctype>
using namespace std;
const int TAMANO_ARREGLO = 26;
const int INICIO_ASCCI = 97;

struct NodoArbolPrefijo
{
    bool esFinal;
    NodoArbolPrefijo *hijos[TAMANO_ARREGLO];
    char c;
};

NodoArbolPrefijo *NuevoNodo(char c)
{
    NodoArbolPrefijo *nodo = new NodoArbolPrefijo();
    nodo->esFinal = false;
    for (int i = 0; i < TAMANO_ARREGLO; i++)
    {
        nodo->hijos[i] = nullptr;
    }
    nodo->c = c;
    return nodo;
}

void Insertar(string palabra, NodoArbolPrefijo *raiz)
{
    NodoArbolPrefijo *nodoActual = raiz;
    for (char c : palabra)
    {
        int indice = static_cast<int>(tolower(c)) - INICIO_ASCCI;
        if (nodoActual->hijos[indice] == nullptr || nodoActual->hijos[indice]->c == ' ')
        {
            nodoActual->hijos[indice] = NuevoNodo(tolower(c));
        }
        nodoActual = nodoActual->hijos[indice];
    }
    nodoActual->esFinal = true;
}

bool Buscar(string palabra, NodoArbolPrefijo *raiz)
{
    NodoArbolPrefijo *nodoActual = raiz;
    for (char c : palabra)
    {
        int indice = static_cast<int>(tolower(c)) - INICIO_ASCCI;
        if (nodoActual->hijos[indice] == nullptr)
        {
            return false;
        }
        nodoActual = nodoActual->hijos[indice];
    }
    return nodoActual != nullptr && nodoActual->esFinal;
}

void BuscarPalabra(string palabra, NodoArbolPrefijo *raiz)
{
    if (Buscar(palabra, raiz))
    {
        cout << "La palabra '" << palabra << "' esta en el arbol de prefijos.";
    }
    else
    {
        cout << "La palabra '" << palabra << "' NO esta en el arbol de prefijos.";
    }
}

void printEnOrder(NodoArbolPrefijo *nodo, int nivel = 0)
{
    if (nodo == nullptr)
        return;

    for (int i = 0; i < TAMANO_ARREGLO; i++)
    {
        if (nodo->hijos[i] != nullptr)
        {
            printEnOrder(nodo->hijos[i], nivel + 1);
        }
    }

    if (nivel > 0)
    {
        for (int i = 0; i < nivel - 1; i++)
        {
            cout << "   ";
        }
        cout << "|--";
    }

    cout << nodo->c << endl;
}

void ImprimirArbol(NodoArbolPrefijo *arbol)
{
    if (arbol == nullptr)
    {
        cout << "Árbol vacío!" << endl;
        return;
    }
    printEnOrder(arbol);
}

int main()
{
    NodoArbolPrefijo *raiz = NuevoNodo(' ');

    // Insertar("hola", raiz);
    // Insertar("adios", raiz);
    // Insertar("hogar", raiz);
    // Insertar("hombre", raiz);
    // Insertar("hora", raiz);
    // Insertar("alamo", raiz);
    // Insertar("arbol", raiz);

    // BuscarPalabra("hola", raiz);
    // BuscarPalabra("adios", raiz);

    // EJERCICIO 1
    // Insertar("Romane", raiz);
    // Insertar("Romanus", raiz);
    // Insertar("Rubens", raiz);
    // Insertar("Ruber", raiz);
    // Insertar("Rubicon", raiz);
    // Insertar("Rubicundus", raiz);

    // EJERCICIO 2
    Insertar("Algo", raiz);
    Insertar("Ala", raiz);
    Insertar("Abeja", raiz);
    Insertar("Trio", raiz);
    Insertar("Trigo", raiz);
    Insertar("Mama", raiz);
    Insertar("Manila", raiz);
    Insertar("Manipular", raiz);
    ImprimirArbol(raiz);
    return 0;
}
