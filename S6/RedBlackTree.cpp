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
    Nodo *nuevoNodo = CrearNodo(valor);

    if (arbol->raiz == nullptr)
    {
        arbol->raiz = nuevoNodo;
    }
    else
    {
        // std::cout<<"Insertando recursivamente"<<std::endl;
        InsertarRecursivamente(arbol->raiz, nuevoNodo);
    }
    CambiarColor(nuevoNodo, rojo);
    Ajustar(arbol, nuevoNodo);
}

void InsertarRecursivamente(Nodo *nodoActual, Nodo *nodoNuevo)
{
    if (nodoNuevo->valor < nodoActual->valor)
    {
        if (nodoActual->izq == nullptr)
        {
            nodoActual->izq = nodoNuevo;
            nodoNuevo->padre = nodoActual;
        }
        else
        {
            InsertarRecursivamente(nodoActual->izq, nodoNuevo);
        }
    }
    else
    {
        if (nodoActual->der == nullptr)
        {
            nodoActual->izq = nodoNuevo;
            nodoNuevo->padre = nodoActual;
        }
        else
        {
            InsertarRecursivamente(nodoActual->izq, nodoNuevo);
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
    else if (nodo = nodo->padre->izq)
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

Nodo *Buscar(Arbol *arbol, int valor)
{
    Nodo *actual = arbol->raiz;
    while (actual != nullptr && actual->valor != valor)
    {
        if (actual->valor > valor)
        {
            actual = actual->izq;
        }
        else
        {
            actual = actual->der;
        }
    }
    return actual;
}

Nodo *ObtenerSiguiente(Nodo *nodo)
{
    if (nodo->der != nullptr)
    {
        nodo = nodo->der;
    }

    while (nodo->izq != nullptr)
    {
        nodo = nodo->izq;
    }
    return nodo;
}

Nodo *Eliminar(Arbol *arbol, int valor)
{
    Nodo *hijoRemplazo = nullptr;
    Nodo *nodoRemplazo = nullptr;
    Nodo *nodoElimianr = Buscar(arbol, valor);

    if (nodoElimianr == nullptr)
    {
        return nullptr;
    }

    if (nodoElimianr->izq == nullptr || nodoElimianr->der == nullptr)
    {
        nodoRemplazo = nodoElimianr;
    }
    else
    {
        nodoRemplazo = ObtenerSiguiente(nodoElimianr);
    }

    if (nodoRemplazo->izq != nullptr)
    {
        hijoRemplazo = nodoRemplazo->izq;
    }
    else
    {
        hijoRemplazo = nodoRemplazo->der;
    }

    if (hijoRemplazo != nullptr)
    {
        hijoRemplazo->padre = nodoRemplazo->padre;
    }

    if (nodoRemplazo->padre == nullptr)
    {
        arbol->raiz = hijoRemplazo;
    }
    else
    {
        if (nodoRemplazo == nodoRemplazo->padre->izq)
        {
            nodoRemplazo->padre->izq = hijoRemplazo;
        }
        else
        {
            nodoRemplazo->padre->der = hijoRemplazo;
        }

        if (nodoRemplazo != nodoElimianr)
        {
            nodoElimianr->valor = nodoRemplazo->valor;
        }

        if (nodoRemplazo->color == negro)
        {
            AjustarEliminacion(arbol, hijoRemplazo);
        }
    }
    return nodoRemplazo;
}

void AjustarEliminacion(Arbol *arbol, Nodo *nodo)
{
}

void CambiarColor(Nodo *nodo, bool color)
{
    nodo->color = color;
}

int main()
{

    return 0;
}
