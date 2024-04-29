#include <iostream>
#include <vector>
#define rojo false
#define negro true
using namespace std;

struct Nodo
{
    int valor;
    bool color; // falso negro, verdadero rojo
    Nodo *izquierda = nullptr;
    Nodo *derecha = nullptr;
    Nodo *padre = nullptr;
};

struct Arbol
{
    Nodo *raiz;
};

void InsertarRecursivamente(Nodo *nodoActual, Nodo *nuevoNodo);
void Insertar(Arbol *arbol, int valor);
void Ajustar(Arbol *arbol, Nodo *nodo);
Nodo *Buscar(Arbol *arbol, int valor);
Nodo *Eliminar(Arbol *arbol, int valor);
Nodo *ObtenerSiguiente(Nodo *nodo);
void AjustarEliminacion(Arbol *arbol, Nodo *nodo);
Nodo *CrearNodo(int valor);
void RotarIzquierda(Arbol *arbol, Nodo *nodo);
void RotarDerecha(Arbol *arbol, Nodo *nodo);
void CambiarColor(Nodo *nodo, bool color);
bool ColorDeNodo(Nodo *nodo);
void printEnOrder(Nodo *n, int space);
void printTree(Arbol *arbol);
bool ColorDeNodo(Nodo *nodo);
void insertarVector(Arbol *arbol, vector<int> v);

Nodo *CrearNodo(int valor)
{
    Nodo *nodo = new Nodo();
    nodo->valor = valor;
    nodo->color = rojo; // Un nodo nuevo del árbol presenta color rojo
    nodo->izquierda = nullptr;
    nodo->derecha = nullptr;
    nodo->padre = nullptr;
    return nodo;
}

void Insertar(Arbol *arbol, int valor)
{
    Nodo *nuevoNodo = CrearNodo(valor);

    if (arbol->raiz == nullptr)
    { // significaria que el arbol esta vacios
        // std::cout<<"Ingrese en el arbol nuevo"<<std::endl;
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

void InsertarRecursivamente(Nodo *nodoActual, Nodo *nuevoNodo)
{
    if (nuevoNodo->valor < nodoActual->valor)
    {
        if (nodoActual->izquierda == nullptr)
        {
            nodoActual->izquierda = nuevoNodo;
            nuevoNodo->padre = nodoActual;
        }
        else
        {
            InsertarRecursivamente(nodoActual->izquierda, nuevoNodo);
        }
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

void Ajustar(Arbol *arbol, Nodo *nodo)
{
    while (nodo->padre != nullptr && nodo->padre->color == rojo)
    {
        // SI PADRE ES HIJO IZQ
        if (nodo->padre == nodo->padre->padre->izquierda)
        {
            Nodo *tio = nodo->padre->padre->derecha;
            if (tio != nullptr && tio->color == rojo)
            {
                CambiarColor(nodo->padre, negro);
                CambiarColor(tio, negro);
                CambiarColor(nodo->padre->padre, rojo);
                nodo = nodo->padre->padre;
            }
            else
            {
                // SI HIJO ES DER
                if (nodo == nodo->padre->derecha)
                {
                    nodo = nodo->padre;
                    RotarIzquierda(arbol, nodo);
                }
                CambiarColor(nodo->padre, negro);
                CambiarColor(nodo->padre->padre, rojo);
                RotarDerecha(arbol, nodo->padre->padre);
            }
        }
        // SI PADRE ES HIJO DER
        else
        {
            Nodo *tio = nodo->padre->padre->izquierda;
            if (tio != nullptr && tio->color == rojo)
            {
                CambiarColor(nodo->padre, negro);
                CambiarColor(tio, negro);
                CambiarColor(nodo->padre->padre, rojo);
                nodo = nodo->padre->padre;
            }
            else
            {
                // SI HIJO ES IZQ
                if (nodo == nodo->padre->izquierda)
                {
                    nodo = nodo->padre;
                    RotarDerecha(arbol, nodo);
                }
                CambiarColor(nodo->padre, negro);
                CambiarColor(nodo->padre->padre, rojo);
                RotarIzquierda(arbol, nodo->padre->padre);
            }
        }
    }
    CambiarColor(arbol->raiz, negro);
}

Nodo *Buscar(Arbol *arbol, int valor)
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

Nodo *Eliminar(Arbol *arbol, int valor)
{
    Nodo *hijoReemplazo = nullptr;
    Nodo *nodoReemplazo = nullptr;
    Nodo *nodoEliminar = Buscar(arbol, valor);
    if (nodoEliminar == nullptr)
    {
        cout << "No se pudo encontrar el valor especificado" << endl;
        return nullptr;
    }

    // Obtener Nodo Remplazo
    if (nodoEliminar->izquierda == nullptr || nodoEliminar->derecha == nullptr)
    {
        nodoReemplazo = nodoEliminar;
    }
    else
    {
        nodoReemplazo = ObtenerSiguiente(nodoEliminar);
    }

    // Obtener Hijo Remplazo
    if (nodoReemplazo->izquierda != nullptr)
    {
        hijoReemplazo = nodoReemplazo->izquierda;
    }
    else
    {
        hijoReemplazo = nodoReemplazo->derecha;
    }

    // PADRE DEL HIJO REMPLAZO
    if (hijoReemplazo != nullptr)
    {
        hijoReemplazo->padre = nodoReemplazo->padre;
    }

    // SI ES RAIZ
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

        if (nodoReemplazo != nodoEliminar)
        {
            nodoEliminar->valor = nodoReemplazo->valor;
        }

        if (nodoReemplazo->color == negro)
        {
            AjustarEliminacion(arbol, hijoReemplazo);
        }
    }
    return nodoReemplazo;
}

Nodo *ObtenerSiguiente(Nodo *nodo)
{
    if (nodo->derecha != nullptr)
    {
        nodo = nodo->derecha;
    }
    while (nodo->izquierda != nullptr)
    {
        nodo = nodo->izquierda;
    }
    return nodo;
}

void AjustarEliminacion(Arbol *arbol, Nodo *nodo)
{
    while (nodo != arbol->raiz && ColorDeNodo(nodo) == negro)
    {
        // Si NODO ES IZQ
        if (nodo == nodo->padre->izquierda)
        {
            Nodo *hermano = nodo->padre->izquierda;
            if (ColorDeNodo(hermano) == rojo)
            {
                CambiarColor(hermano, negro);
                CambiarColor(nodo->padre, rojo);
                RotarIzquierda(arbol, nodo->padre);
                hermano = nodo->padre->derecha;
            }
            if (ColorDeNodo(hermano->izquierda) == negro && ColorDeNodo(hermano->derecha) == negro)
            {
                CambiarColor(hermano, rojo);
                nodo = nodo->padre;
            }
            else
            {
                if (ColorDeNodo(hermano->derecha) == negro)
                {
                    CambiarColor(hermano->izquierda, negro);
                    CambiarColor(hermano, rojo);
                    RotarDerecha(arbol, hermano);
                    hermano = nodo->padre->derecha;
                }
                CambiarColor(hermano, ColorDeNodo(nodo->padre));
                CambiarColor(nodo->padre, negro);
                CambiarColor(hermano->derecha, negro);
                RotarIzquierda(arbol, nodo->padre);
                nodo = arbol->raiz;
            }
        }
        else
        {
            Nodo *hermano = nodo->padre->izquierda;
            if (ColorDeNodo(hermano) == rojo)
            {
                CambiarColor(hermano, negro);
                CambiarColor(nodo->padre, rojo);
                RotarDerecha(arbol, nodo->padre);
                hermano = nodo->padre->izquierda;
            }
            if (ColorDeNodo(hermano->derecha) == negro && ColorDeNodo(hermano->izquierda) == negro)
            {
                CambiarColor(hermano, rojo);
                nodo = nodo->padre;
            }
            else
            {
                if (ColorDeNodo(hermano->izquierda) == negro)
                {
                    CambiarColor(hermano->derecha, negro);
                    CambiarColor(hermano, rojo);
                    RotarIzquierda(arbol, hermano);
                }
                CambiarColor(hermano, ColorDeNodo(nodo->padre));
                CambiarColor(nodo->padre, negro);
                CambiarColor(hermano->izquierda, negro);
                RotarDerecha(arbol, nodo->padre);
                nodo = arbol->raiz;
            }
        }
    }
    CambiarColor(nodo, negro);
}

void RotarIzquierda(Arbol *arbol, Nodo *nodo)
{
    Nodo *derechaHijo = nodo->derecha;
    nodo->derecha = derechaHijo->izquierda;
    // VERIFICAR SI ESTA VACIO
    if (derechaHijo->izquierda != nullptr)
    {
        derechaHijo->izquierda->padre = nodo;
    }

    // PARTE DEL PADRE
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

    // PARTE ENTRE CAMBIO DE POS
    derechaHijo->izquierda = nodo;
    nodo->padre = derechaHijo;
}

void RotarDerecha(Arbol *arbol, Nodo *nodo)
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

void CambiarColor(Nodo *nodo, bool color)
{
    nodo->color = color;
}

bool ColorDeNodo(Nodo *nodo)
{
    if (nodo == nullptr)
    {
        return negro;
    }
    return nodo->color;
}

// extra

string ImprimirColor(bool color)
{
    if (color)
    {
        return "Negro";
    }
    return "Rojo";
}

void printEnOrder(Nodo *nodo, int space)
{
    if (nodo == nullptr)
        return;
    space += 10;
    // Imprimir el subárbol derecho
    printEnOrder(nodo->derecha, space);

    // Imprimir el nodo actual
    cout << endl;
    for (int i = 10; i < space; i++)
        cout << " ";
    if (nodo->padre != nullptr)
    {
        if (nodo == nodo->padre->izquierda)
            cout << "|----" << nodo->valor << "(" << ImprimirColor(nodo->color) << ")";
        else
            cout << "|----" << nodo->valor << "(" << ImprimirColor(nodo->color) << ")";
    }
    else
    {
        cout << nodo->valor << "(" << ImprimirColor(nodo->color) << ")";
    }

    // Imprimir el subárbol izquierdo
    printEnOrder(nodo->izquierda, space);
}

void printTree(Arbol *arbol)
{
    if (arbol == nullptr || arbol->raiz == nullptr)
    {
        cout << "Árbol vacío!" << endl;
        return;
    }
    // Llamar a la función de impresión con el nodo raíz y el espacio inicial
    printEnOrder(arbol->raiz, 0);
    cout << endl;
}

void insertarVector(Arbol *arbol, vector<int> v)
{
    for (int i = 0; i < v.size(); i++)
    {
        Insertar(arbol, v[i]);
    }
}

int main()
{
    Arbol *arbol = new Arbol();
    arbol->raiz = nullptr;
    vector<int> v = {50, 70, 40, 30, 65, 35, 85, 20, 90, 10, 80, 5, 15, 60, 55};
    insertarVector(arbol, v);
    cout << "Arbol B: Raiz -> " << arbol->raiz->valor << ImprimirColor(arbol->raiz->color) << "\n Estructura completa: ";
    printTree(arbol);
    cout << endl;

    // Pregunta 4
    // vector<int> v4 = { 12,5,15,3,10,13,17,4,7,11,14,6,8};
    // insertarVector(arbol, v4);
    // Nodo * n = Eliminar(arbol, 5);
    // cout << "Arbol B: Raiz -> " << arbol->raiz->valor << ImprimirColor(arbol->raiz->color) << "\n Estructura completa: ";
    // printTree(arbol);
    // cout << endl;

    // Pregunta 3
    // vector<int> v3 = {13,8,1,6,11,17,15,25,22,27};
    // insertarVector(arbol, v3);
    // Insertar(arbol, 5);
    // cout << "Arbol B: Raiz -> " << arbol->raiz->valor << ImprimirColor(arbol->raiz->color) << "\n Estructura completa: ";
    // printTree(arbol);
    // cout << endl;

    // Pregunta 2
    // vector<int> v2 = {7,2,11,1,5,4,8,14,15};
    // insertarVector(arbol, v2);
    // Nodo * n = Eliminar(arbol, 14);
    // cout << "Arbol B: Raiz -> " << arbol->raiz->valor << ImprimirColor(arbol->raiz->color) << "\n Estructura completa: ";
    // printTree(arbol);
    // cout << endl;

    return 0;
}
