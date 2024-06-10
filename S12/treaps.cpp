#include <iostream>
#include<time.h>
#include<cstdlib>
using namespace std;

struct TreapNode{
    int clave;
    int priorida;
    TreapNode* izq;
    TreapNode* der;

    TreapNode(int clave): clave(clave), priorida(rand()), izq(nullptr), der(nullptr) {};
    TreapNode* rightRotate(TreapNode* y);
    TreapNode* leftRotate(TreapNode* x);
    TreapNode* insert(TreapNode* raiz, int clave);
    TreapNode* deleteNode(TreapNode* raiz, int clave);
    void inorder(TreapNode* raiz);
};

TreapNode* TreapNode::rightRotate(TreapNode* y){
    TreapNode* x = y->izq;
    TreapNode* T2 = x->der;
    x->der = y;
    y->izq = T2;
    return x;
}

TreapNode* TreapNode::leftRotate(TreapNode* x){
    TreapNode* y = x->der;
    TreapNode* T2 = y->izq;
    y->izq = x;
    x->der = T2;
    return y;
}

TreapNode* TreapNode::insert(TreapNode* raiz, int clave){
    if (raiz == nullptr){
        return new TreapNode(clave);
    }

    if (clave <= raiz->clave){
        raiz->izq = insert(raiz->izq, clave);
        if (raiz->izq->priorida > raiz->priorida){
            raiz = rightRotate(raiz);
        }
    } else {
        raiz->der = insert(raiz->der, clave);
        if (raiz->der->priorida > raiz->priorida){
            raiz = leftRotate(raiz);
        }
    }
    return raiz;
}

TreapNode* TreapNode::deleteNode(TreapNode* raiz, int clave){
    if (raiz == nullptr){
        return raiz;
    }

    if (clave < raiz->clave){
        raiz->izq = deleteNode(raiz->izq, clave);
    } else if (clave > raiz->clave){
        raiz->der = deleteNode(raiz->der, clave);
    } else if (raiz->izq == nullptr){
        TreapNode* temp = raiz->der;
        delete raiz;
        raiz = temp;
    } else if (raiz->der == nullptr){
        TreapNode* temp = raiz->izq;
        delete raiz;
        raiz = temp;
    } else if (raiz->izq->priorida < raiz->der->priorida){
        raiz = leftRotate(raiz);
        raiz->izq = deleteNode(raiz->izq, clave);
    } else {
        raiz = rightRotate(raiz);
        raiz->der = deleteNode(raiz->der, clave);
    }
    return raiz;
}

void TreapNode::inorder(TreapNode* raiz){
    if (raiz != nullptr){
        inorder(raiz->izq);
        cout << "clave: " << raiz->clave << " | prioridad: " << raiz->priorida << endl;
        inorder(raiz->der);
    }
}

int main()
{
    srand(time(0));
    TreapNode* raiz = nullptr;
    raiz = raiz->insert(raiz, 50);
    raiz = raiz->insert(raiz, 30);
    raiz = raiz->insert(raiz, 20);
    raiz = raiz->insert(raiz, 40);
    raiz = raiz->insert(raiz, 70);
    raiz = raiz->insert(raiz, 60);
    raiz = raiz->insert(raiz, 80);

    cout << "Recorrido inorden del arbol dado" << endl;
    raiz->inorder(raiz);   
    cout << endl;

    raiz = raiz->deleteNode(raiz, 20);
    cout << "Recorrido inorden despues de eliminar 20" << endl;
    raiz->inorder(raiz);   
    cout << endl;

    raiz = raiz->deleteNode(raiz, 30);
    cout << "Recorrido inorden despues de eliminar 30" << endl;
    raiz->inorder(raiz);   
    cout << endl;

    raiz = raiz->deleteNode(raiz, 50);
    cout << "Recorrido inorden despues de eliminar 50" << endl;
    raiz->inorder(raiz);   
    cout << endl;


    return 0;
}
