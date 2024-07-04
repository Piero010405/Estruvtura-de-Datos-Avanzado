#include <iostream>
using namespace std;

struct Node
{
    int clave;
    int nlp;
    Node *der;
    Node *izq;

    Node(int clave) : clave(clave), nlp(0), der(nullptr), izq(nullptr){};

    Node *merge(Node *h1, Node *h2)
    {
        if (h1 == nullptr)
        {
            return h2;
        }

        if (h2 == nullptr)
        {
            return h1;
        }

        if (h1->clave < h2->clave)
        {
            swap(h1, h2);
        }

        h1->der = merge(h1->der, h2);

        if (h1->izq == nullptr || (h1->der != nullptr && h1->izq->nlp < h1->izq->nlp))
        {
            swap(h1->izq, h1->der);
        }

        if (h1->der == nullptr)
        {
            h1->nlp = 0;
        }
        else
        {
            h1->nlp = h1->der->nlp + 1;
        }
        return h1;
    }

    Node *insertar(Node *root, int clave)
    {
        Node *nuevo = new Node(clave);
        return merge(root, nuevo);
    }

    Node *eliminar(Node *root)
    {
        if (root == nullptr)
        {
            return root;
        }
        Node *der = root->der;
        Node *izq = root->izq;
        delete root;
        return merge(izq, der);
    }
};

int main()
{

    return 0;
}
