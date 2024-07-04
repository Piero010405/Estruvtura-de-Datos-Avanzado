#include <iostream>
using namespace std;

struct Node
{
    int clave;
    Node *hijo;
    Node *siguiente;

    Node(int clave) : clave(clave), hijo(nullptr), siguiente(nullptr){};

    Node *meld(Node *heap1, Node *heap2)
    {
        if (heap1 == nullptr)
        {
            return heap2;
        }

        if (heap2 == nullptr)
        {
            return heap1;
        }

        if (heap1->clave < heap2->clave)
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

    Node *insertar(Node *root, int clave)
    {
        Node *nuevo = new Node(clave);
        return meld(root, nuevo);
    }

    Node *meldDosPartes(Node *root)
    {
        if (root == nullptr || root->siguiente == nullptr)
        {
            return root;
        }

        Node *primero = root;
        Node *segundo = root->siguiente;
        Node *otros = root->siguiente->siguiente;
        primero->hijo = nullptr;
        segundo->siguiente = nullptr;
        return meld(meld(primero, segundo), meldDosPartes(otros));
    }

    Node *eliminar(Node *root)
    {
        if (root == nullptr || root->hijo == nullptr)
        {
            return nullptr;
        }

        return meldDosPartes(root->hijo);
    }
};
int main()
{

    return 0;
}
