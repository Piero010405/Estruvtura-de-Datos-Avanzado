#include <iostream>
#include <cstdlib>
using namespace std;

struct TreapNode
{
    int clave;
    int prioridad;
    TreapNode *left;
    TreapNode *right;

    TreapNode(int clave) : clave(clave), prioridad(rand()), left(nullptr), right(nullptr){};
    TreapNode *rightRotate(TreapNode *y)
    {
        TreapNode *x = y->left;
        TreapNode *T2 = x->right;
        x->right = y;
        y->left = T2;
    }

    TreapNode *leftRotate(TreapNode *x)
    {
        TreapNode *y = x->right;
        TreapNode *T2 = y->left;
        y->left = x;
        x->right = T2;
    }

    TreapNode *insertar(TreapNode *root, int clave)
    {
        if (root == nullptr)
        {
            return new TreapNode(clave);
        }

        if (clave <= root->clave)
        {
            root->left = insertar(root->left, clave);
            if (root->left->prioridad > root->prioridad)
            {
                root = rightRotate(root);
            }
        }
        else
        {
            root->right = insertar(root->right, clave);
            if (root->right->prioridad > root->prioridad)
            {
                root = leftRotate(root);
            }
        }
        return root;
    }

    TreapNode *eliminar(TreapNode *root, int clave)
    {
        if (root == nullptr)
        {
            return root;
        }

        if (clave < root->clave)
        {
            root->left = eliminar(root->left, clave);
        }
        else if (clave > root->clave)
        {
            root->right = eliminar(root->right, clave);
        }
        else if (root->left == nullptr)
        {
            TreapNode *temp = root->right;
            delete root;
            root = temp;
        }
        else if (root->right == nullptr)
        {
            TreapNode *temp = root->left;
            delete root;
            root = temp;
        }
        else if (root->left->prioridad > root->right->prioridad)
        {
            root = rightRotate(root);
            root->left = eliminar(root->left, clave);
        }
        else
        {
            root = leftRotate(root);
            root->right = eliminar(root->right, clave);
        }
    }
};
int main()
{

    return 0;
}
