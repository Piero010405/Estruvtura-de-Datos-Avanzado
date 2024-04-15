#include <iostream>
using namespace std;

const string ROJO = "Rojo";
const string NEGRO = "Negro";

struct Nodo
{
    int valor;
    string color;
    Nodo *izquierda;
    Nodo *derecha;
    Nodo *padre;
    Nodo *raiz;

    Nodo() : valor(0), color(""), izquierda(nullptr), derecha(nullptr), padre(nullptr), raiz(nullptr) {}
};

// Prototipos de funciones
Nodo *CrearNodo(int valor);
void Insertar(Nodo *&arbol, int valor);
void InsertarRecursivamente(Nodo *&nodoActual, Nodo *nuevoNodo);
void Ajustar(Nodo *&arbol, Nodo *nodo);
void RotarIzquierda(Nodo *&arbol, Nodo *nodo);
void RotarDerecha(Nodo *&arbol, Nodo *nodo);
void CambiarColor(Nodo *nodo, const string color);
string ColorDeNodo(Nodo *nodo);
Nodo *Buscar(Nodo *arbol, int valor);
Nodo *Eliminar(Nodo *&arbol, int valor);
Nodo *ObtenerSiguiente(Nodo *nodo);
void AjustarEliminacion(Nodo *&arbol, Nodo *nodo);
void ImprimirArbol(Nodo *arbol);
void ImprimirNodo(Nodo *nodo);

Nodo *CrearNodo(int valor)
{
    Nodo *nodo = new Nodo();
    nodo->valor = valor;
    nodo->color = ROJO;
    nodo->izquierda = nullptr;
    nodo->derecha = nullptr;
    nodo->padre = nullptr;
    nodo->raiz = nullptr;

    return nodo;
}

void Insertar(Nodo *&arbol, int valor)
{
    Nodo *nuevoNodo = CrearNodo(valor);
    if (arbol == nullptr)
    {
        arbol = nuevoNodo;
        arbol->raiz = nuevoNodo;
    }
    else
    {
        InsertarRecursivamente(arbol, nuevoNodo);
    }

    CambiarColor(nuevoNodo, ROJO);
    Ajustar(arbol, nuevoNodo);
}

void InsertarRecursivamente(Nodo *&nodoActual, Nodo *nuevoNodo)
{
    if (nuevoNodo->valor < nodoActual->valor)
    {
        if (nodoActual->izquierda == nullptr)
        {
            nodoActual->izquierda = nuevoNodo;
            nuevoNodo->padre = nodoActual;
        }
        else
            InsertarRecursivamente(nodoActual->izquierda, nuevoNodo);
    }
    else
    {
        if (nodoActual->derecha == nullptr)
        {
            nodoActual->derecha = nuevoNodo;
            nuevoNodo->padre = nodoActual;
        }
        else
        {
            InsertarRecursivamente(nodoActual->derecha, nuevoNodo);
        }
    }
}

void Ajustar(Nodo *&arbol, Nodo *nodo)
{
    while (nodo->padre->color == ROJO)
    {
        if (nodo->padre == nodo->padre->izquierda->padre)
        {
            Nodo *tio = nodo->padre->padre->derecha;
            if (tio->color == ROJO)
            {
                CambiarColor(nodo->padre, NEGRO);
                CambiarColor(tio, NEGRO);
                CambiarColor(nodo->padre->padre, ROJO);
                nodo = nodo->padre->padre;
            }
            else
            {
                if (nodo == nodo->padre->derecha)
                {
                    nodo = nodo->padre;
                    RotarIzquierda(arbol, nodo);
                }
                CambiarColor(nodo->padre, NEGRO);
                CambiarColor(nodo->padre->padre, ROJO);
                RotarDerecha(arbol, nodo->padre->padre);
            }
        }
        else
        {
            Nodo *tio = nodo->padre->padre->izquierda;
            if (tio->color == ROJO)
            {
                CambiarColor(nodo->padre, NEGRO);
                CambiarColor(tio, NEGRO);
                CambiarColor(nodo->padre->padre, ROJO);
                nodo = nodo->padre->padre;
            }
            else
            {
                if (nodo == nodo->padre->izquierda)
                {
                    nodo = nodo->padre;
                    RotarDerecha(arbol, nodo);
                }
                CambiarColor(nodo->padre, NEGRO);
                CambiarColor(nodo->padre->padre, ROJO);
                RotarIzquierda(arbol, nodo->padre->padre);
            }
        }
    }
    CambiarColor(arbol->raiz, NEGRO);
}

Nodo *Buscar(Nodo *arbol, int valor)
{
    Nodo *nodoActual = arbol->raiz;
    while (nodoActual != nullptr && nodoActual->valor != valor)
    {
        if (valor < nodoActual->valor)
        {
            nodoActual = nodoActual->izquierda;
        }
        else
        {
            nodoActual = nodoActual->derecha;
        }
    }
    return nodoActual;
}

Nodo *Eliminar(Nodo *&arbol, int valor)
{
    Nodo *nodoAEliminar = Buscar(arbol, valor);
    Nodo *nodoReemplazo;
    Nodo *hijoReemplazo;

    if (nodoAEliminar == nullptr)
    {
        return nullptr;
    }

    if (nodoAEliminar->izquierda == nullptr || nodoAEliminar->derecha == nullptr)
    {
        nodoReemplazo = nodoAEliminar;
    }
    else
    {
        nodoReemplazo = ObtenerSiguiente(nodoAEliminar);
    }

    if (nodoReemplazo->izquierda != nullptr)
    {
        hijoReemplazo = nodoReemplazo->izquierda;
    }
    else
    {
        hijoReemplazo = nodoReemplazo->derecha;
    }

    if (hijoReemplazo != nullptr)
    {
        hijoReemplazo->padre = nodoReemplazo->padre;
    }

    if (nodoReemplazo->padre == nullptr)
    {
        arbol->raiz = hijoReemplazo;
    }
    else
    {
        if (nodoReemplazo == nodoReemplazo->padre->izquierda)
        {
            nodoReemplazo->padre->izquierda = hijoReemplazo;
        }
        else
        {
            nodoReemplazo->padre->derecha = hijoReemplazo;
        }
    }

    if (nodoReemplazo != nodoAEliminar)
    {
        nodoAEliminar->valor = nodoReemplazo->valor;
    }

    if (nodoReemplazo->color == NEGRO)
    {
        AjustarEliminacion(arbol, hijoReemplazo);
    }

    return nodoReemplazo;
}

Nodo *ObtenerSiguiente(Nodo *nodo)
{
    if (nodo->derecha != nullptr)
    {
        nodo = nodo->derecha;
        while (nodo->izquierda != nullptr)
        {
            nodo = nodo->izquierda;
        }
    }
    return nodo;
}

void AjustarEliminacion(Nodo *&arbol, Nodo *nodo)
{
    while (nodo != arbol->raiz && ColorDeNodo(nodo) == NEGRO)
    {
        Nodo *hermano;
        if (nodo == nodo->padre->izquierda)
        {
            hermano = nodo->padre->derecha;
            if (ColorDeNodo(hermano) == ROJO)
            {
                CambiarColor(hermano, NEGRO);
                CambiarColor(nodo->padre, ROJO);
                RotarIzquierda(arbol, nodo->padre);
                hermano = nodo->padre->derecha;
            }

            if (ColorDeNodo(hermano->izquierda) == NEGRO && ColorDeNodo(hermano->derecha) == NEGRO)
            {
                CambiarColor(hermano, ROJO);
                nodo = nodo->padre;
            }
            else
            {
                if (ColorDeNodo(hermano->derecha) == NEGRO)
                {
                    CambiarColor(hermano->izquierda, NEGRO);
                    CambiarColor(hermano, ROJO);
                    RotarDerecha(arbol, hermano);
                    hermano = nodo->padre->derecha;
                }
                CambiarColor(hermano, ColorDeNodo(nodo->padre));
                CambiarColor(nodo->padre, NEGRO);
                CambiarColor(hermano->derecha, NEGRO);
                RotarIzquierda(arbol, nodo->padre);
                nodo = arbol->raiz;
            }
        }
        else
        {
            hermano = nodo->padre->izquierda;
            if (ColorDeNodo(hermano) == ROJO)
            {
                CambiarColor(hermano, NEGRO);
                CambiarColor(nodo->padre, ROJO);
                RotarDerecha(arbol, nodo->padre);
                hermano = nodo->padre->izquierda;
            }

            if (ColorDeNodo(hermano->izquierda) == NEGRO && ColorDeNodo(hermano->izquierda) == NEGRO)
            {
                CambiarColor(hermano, ROJO);
                nodo = nodo->padre;
            }
            else
            {
                if (ColorDeNodo(hermano->izquierda) == NEGRO)
                {
                    CambiarColor(hermano->derecha, NEGRO);
                    CambiarColor(hermano, ROJO);
                    RotarIzquierda(arbol, hermano);
                    hermano = nodo->padre->izquierda;
                }
                CambiarColor(hermano, ColorDeNodo(nodo->padre));
                CambiarColor(nodo->padre, NEGRO);
                CambiarColor(hermano->izquierda, NEGRO);
                RotarDerecha(arbol, nodo->padre);
                nodo = arbol->raiz;
            }
        }
    }
    CambiarColor(nodo, NEGRO);
}

void RotarIzquierda(Nodo *&arbol, Nodo *nodo)
{
    Nodo *derechaHijo = nodo->derecha;
    nodo->derecha = derechaHijo->izquierda;

    if (derechaHijo->izquierda != nullptr)
    {
        derechaHijo->izquierda->padre = nodo;
    }
    derechaHijo->padre = nodo->padre;

    if (nodo->padre == nullptr)
    {
        arbol->raiz = derechaHijo;
    }
    else if (nodo == nodo->padre->izquierda)
    {
        nodo->padre->izquierda = derechaHijo;
    }
    else
    {
        nodo->padre->derecha = derechaHijo;
    }
    derechaHijo->izquierda = nodo;
    nodo->padre = derechaHijo;
}

void RotarDerecha(Nodo *&arbol, Nodo *nodo)
{
    Nodo *izquierdaHijo = nodo->izquierda;
    nodo->izquierda = izquierdaHijo->derecha;

    if (izquierdaHijo->derecha != nullptr)
    {
        izquierdaHijo->derecha->padre = nodo;
    }
    izquierdaHijo->padre = nodo->padre;

    if (nodo->padre == nullptr)
    {
        arbol->raiz = izquierdaHijo;
    }
    else if (nodo == nodo->padre->derecha)
    {
        nodo->padre->derecha = izquierdaHijo;
    }
    else
    {
        nodo->padre->izquierda = izquierdaHijo;
    }
    izquierdaHijo->derecha = nodo;
    nodo->padre = izquierdaHijo;
}

void CambiarColor(Nodo *nodo, string color)
{
    nodo->color = color;
}

string ColorDeNodo(Nodo *nodo)
{
    if (nodo == nullptr)
    {
        return NEGRO;
    }

    return nodo->color;
}

void ImprimirArbol(Nodo *arbol)
{
    if (arbol == nullptr)
    {
        cout << "Árbol vacío" << endl;
        return;
    }

    ImprimirNodo(arbol);
}

void ImprimirNodo(Nodo *nodo)
{
    if (nodo != nullptr)
    {
        ImprimirNodo(nodo->derecha);
        cout << "Valor: " << nodo->valor << ", Color: " << nodo->color << endl;
        ImprimirNodo(nodo->izquierda);
    }
}

int main()
{
    Nodo *arbol = nullptr;

    Insertar(arbol, 50);
    Insertar(arbol, 70);
    Insertar(arbol, 40);
    Insertar(arbol, 30);
    Insertar(arbol, 65);
    Insertar(arbol, 35);
    Insertar(arbol, 85);
    Insertar(arbol, 20);
    Insertar(arbol, 90);
    Insertar(arbol, 10);
    Insertar(arbol, 80);
    Insertar(arbol, 5);
    Insertar(arbol, 15);
    Insertar(arbol, 60);
    Insertar(arbol, 55);

    // Imprimir árbol
    cout << "Árbol:" << endl;
    cout << "Nodo Raiz: " << arbol->raiz->valor << ", Color: " << arbol->raiz->color << endl;
    ImprimirArbol(arbol);

    return 0;
}
