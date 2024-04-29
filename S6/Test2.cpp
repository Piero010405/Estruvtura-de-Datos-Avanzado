#include <iostream>
#define rojo false
#define negro true
using namespace std;

struct Nodo
{
    int valor;
    bool color;
    Nodo *izq = nullptr;
    Nodo *der = nullptr;
    Nodo *padre = nullptr;
};

struct Arbol
{
    Nodo *raiz;
};

Nodo *CrearNodo(int valor)
{
    Nodo *nodo = new Nodo();
    nodo->valor = valor;
    nodo->color = rojo;
    nodo->izq = nullptr;
    nodo->der = nullptr;
    nodo->padre = nullptr;
    return nodo;
}

void Insertar(Arbol *arbol, int valor)
{
    Nodo *nodo = CrearNodo(valor);
    if (arbol->raiz == nullptr)
    {
        arbol->raiz = nodo;
    }
    else
    {
        InsertarRecursivamente(arbol->raiz, nodo);
    }
    CambiarColor(nodo, rojo);
    Ajustar(arbol, nodo);
}

void InsertarRecursivamente(Nodo *actual, Nodo *nuevo)
{
    if (nuevo->valor < actual->valor)
    {
        if (actual->izq == nullptr)
        {
            actual->izq = nuevo;
            nuevo->padre = actual;
        }
        else
        {
            InsertarRecursivamente(actual->izq, nuevo);
        }
    }
    else
    {
        if (actual->der == nullptr)
        {
            actual->der = nuevo;
            nuevo->padre = actual;
        }
        else
        {
            InsertarRecursivamente(actual->der, nuevo);
        }
    }
}

void Ajustar(Arbol *arbol, Nodo *nodo)
{
    while (nodo->padre != nullptr && nodo->padre->color == rojo)
    {
        if (nodo->padre == nodo->padre->padre->izq)
        {
            Nodo *tio = nodo->padre->padre->der;
            if (tio != nullptr && tio->color == rojo)
            {
                CambiarColor(nodo->padre, negro);
                CambiarColor(tio, negro);
                CambiarColor(nodo->padre->padre, rojo);
                nodo = nodo->padre->padre;
            }
            else
            {
                if (nodo == nodo->padre->der)
                {
                    nodo = nodo->padre;
                    RotarIzquierda(arbol, nodo);
                }

                CambiarColor(nodo->padre, rojo);
                CambiarColor(nodo->padre->padre, rojo);
                RotarDerecha(arbol, nodo->padre->padre);
            }
        }
        else
        {
            Nodo *tio = nodo->padre->padre->izq;
            if (tio != nullptr && tio->color == rojo)
            {
                CambiarColor(nodo->padre, negro);
                CambiarColor(tio, negro);
                CambiarColor(nodo->padre->padre, rojo);
                nodo = nodo->padre->padre;
            }
            else
            {
                if (nodo == nodo->padre->izq)
                {
                    nodo = nodo->padre;
                    RotarDerecha(arbol, nodo);
                }

                CambiarColor(nodo->padre, rojo);
                CambiarColor(nodo->padre->padre, rojo);
                RotarIzquierda(arbol, nodo->padre->padre);
            }
        }
    }
    CambiarColor(arbol->raiz, negro);
}

void RotarDerecha(Arbol *arbol, Nodo *nodo)
{
    Nodo *izquierdaHijo = nodo->izq;
    nodo->izq = izquierdaHijo->der;

    if (izquierdaHijo->der != nullptr)
    {
        izquierdaHijo->der->padre = nodo;
    }

    izquierdaHijo->padre = nodo->padre;
    if (nodo->padre == nullptr)
    {
        arbol->raiz = izquierdaHijo;
    }
    else if (nodo == nodo->padre->izq)
    {
        nodo->padre->izq = izquierdaHijo;
    }
    else
    {
        nodo->padre->der = izquierdaHijo;
    }

    izquierdaHijo->der = nodo;
    nodo->padre = izquierdaHijo;
}
void RotarIzquierda(Arbol *arbol, Nodo *nodo)
{
    Nodo *derechaHijo = nodo->der;
    nodo->der = derechaHijo->izq;

    if (derechaHijo->izq != nullptr)
    {
        derechaHijo->izq->padre = nodo;
    }

    derechaHijo->padre = nodo->padre;
    if (nodo->padre == nullptr)
    {
        arbol->raiz = derechaHijo;
    }
    else if (nodo == nodo->padre->izq)
    {
        nodo->padre->izq = derechaHijo;
    }
    else
    {
        nodo->padre->der = derechaHijo;
    }

    derechaHijo->izq = nodo;
    nodo->padre = derechaHijo;
}

void CambiarColor(Nodo *nodo, bool color)
{
    nodo->color = color;
}

int main()
{

    return 0;
}
