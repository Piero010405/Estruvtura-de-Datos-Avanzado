#include <iostream>
using namespace std;
struct Nodo
{
    int valor;
    Nodo *hijo;
    Nodo *siguiente;
    Nodo(int valor)
    {
        this->valor = valor;
        this->hijo = nullptr;
        this->siguiente = nullptr;
    }
};

Nodo *meld(Nodo *heap1, Nodo *heap2)
{
    if (heap1 == nullptr)
    {
        return heap2;
    }
    if (heap2 == nullptr)
    {
        return heap1;
    }
    if (heap1->valor < heap2->valor)
    {
        heap2->siguiente = heap1->hijo;
        heap1->hijo = heap2;
        return heap1;
    }
    else
    {
        heap1->siguiente = heap2->hijo;
        heap2->hijo = heap1;
        return heap2;
    }
}

Nodo *insertar(Nodo *raiz, int valor)
{
    Nodo *nuevo = new Nodo(valor);
    return meld(raiz, nuevo);
}

int encontrarMin(Nodo *raiz)
{
    if (raiz == nullptr)
    {
        throw "El heap esta vacio";
        return -1;
    }
    return raiz->valor;
}

Nodo *meldDosPasos(Nodo *raiz)
{
    if (raiz == nullptr || raiz->siguiente == nullptr)
    {
        return raiz;
    }
    Nodo *primerNodo = raiz;
    Nodo *segundoNodo = raiz->siguiente;
    Nodo *resto = raiz->siguiente->siguiente;
    primerNodo->siguiente = nullptr;
    segundoNodo->siguiente = nullptr;
    return meld(meld(primerNodo, segundoNodo), meldDosPasos(resto));
}

Nodo *eliminarMin(Nodo *raiz)
{
    if (raiz == nullptr)
    {
        cerr << "El heap esta vacio" << endl;
        ;
        return nullptr;
    }
    if (raiz->hijo == nullptr)
        return nullptr;
    return meldDosPasos(raiz->hijo);
}

int main()
{
    try
    {
        Nodo *heap = nullptr;
        heap = insertar(heap, 3);
        heap = insertar(heap, 10);
        heap = insertar(heap, 5);
        cout << "Minimo: " << encontrarMin(heap) << "\n";
        heap = eliminarMin(heap);
        cout << "Minimo despues de eliminacion: "
             << encontrarMin(heap) << "\n";
        heap = eliminarMin(heap);
        cout << "Minimo despues de eliminacion: "
             << encontrarMin(heap) << "\n";
        heap = eliminarMin(heap);
        cout << "Minimo despues de eliminacion: "
             << encontrarMin(heap) << "\n";
    }
    catch (const char *e)
    {
        cout << e;
    }
    return 0;
}