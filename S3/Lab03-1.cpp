#include <iostream>
#include <vector>
using namespace std;

class BTreeNode
{
    int t, n; // t = orden & n = numero de elementos actuales en la tupla
    bool leaf;
    vector<int> keys;             // tupla
    vector<BTreeNode *> children; // subarboles

public:
    BTreeNode(int _t, bool _leaf)
    {
        this->t = _t;
        this->leaf = _leaf;
        n = 0;
        keys.resize(2 * (t - 1));
        children.resize(2 * t);
    }

    // Imprimir el arbol
    void traverse()
    {
        int i = 0;
        while (i < n)
        {
            if (!leaf)
            {
                children[i]->traverse();
            }
            cout << " " << keys[i];
            i++;
        }

        // Imprimir raiz
        if (!leaf)
        {
            children[i]->traverse();
        }
    }

    // Inserccion BINARIA
    void insertNonFull(int k)
    {
        int i = n - 1;
        if (leaf)
        {
            while (i >= 0 && keys[i] > k)
            {
                // Le abres espacio dentro de la tupla para que el elemento K sea incertado en su sitio
                keys[i + 1] = keys[i];
                i--;
            }

            // Insertar el elemento K en la tupla
            keys[i + 1] = k;
            n++;
        }
        else // en la RAIZ
        {
            while (i >= 0 && keys[i] > k)
            {
                // Obtener la posicion en donde k puede ser insertado dentro de la RAIZ
                i--;
            }

            // En caso que el subarbol siguiente posterior este lleno
            if (children[i + 1]->n == 2 * (t - 1))
            {
                // Division Celular
                splitChild(i + 1, children[i + 1]);
                // Decidir en que subarbol ponerlo luego de la DIVISION CELULAR
                if (keys[i + 1] < k)
                {
                    i++;
                }
            }
            // Insertamos el elemento K en el subarbol siguiente posterior
            children[i + 1]->insertNonFull(k);
        }
    }

    // DIVISION CELULAR => i = índice del hijo que está lleno
    void splitChild(int i, BTreeNode *y)
    {
        BTreeNode *z = new BTreeNode(y->t, y->leaf);
        z->n = t - 1; // minimo
        for (int j = 0; j < t - 1; j++)
        {
            z->keys[j] = y->keys[j + t];
        }

        // En caso sea ROOT tmb tenemos que copiar los hijos
        if (!y->leaf)
        {
            for (int j = 0; j < t; j++)
            {
                z->children[j] = y->children[j + t];
            }
        }

        y->n = t - 1;

        // Este bucle mueve los punteros de los hijos de y hacia la derecha para hacer espacio para el nuevo hijo z
        for (int j = n; j >= i + 1; j--)
        {
            children[j + 1] = children[j];
        }

        // Se inserta el puntero al nuevo hijo z en la posición correcta en el arreglo de punteros a hijos.
        children[i + 1] = z;

        // Este bucle mueve las claves en el nodo actual hacia la derecha para hacer espacio para la nueva clave que se moverá desde y al nodo actual.
        for (int j = n - 1; j >= i; j--)
        {
            keys[j + 1] = keys[j];
        }

        // Finalmente, se inserta la clave adecuada de y en la posición i del nodo actual, y se incrementa el número de claves en el nodo actual.
        keys[i] = y->keys[t - 1];
        n = n + 1;
    }
    friend class BTree;
};

class BTree
{
    BTreeNode *root;
    int t;

public:
    BTree(int _t)
    {
        root = nullptr;
        this->t = _t;
    }

    void traverse()
    {
        if (root != nullptr)
        {
            root->traverse();
        }
    }

    void insert(int k)
    {
        if (root == nullptr)
        {
            root = new BTreeNode(t, true);
            root->keys[0] = k;
            root->n = 1;
        }
        else
        {
            // En caso de que la raiz este llena
            if (root->n == 2 * (t - 1))
            {
                // Crear una raiz
                BTreeNode *s = new BTreeNode(t, false);
                s->children[0] = root;
                s->splitChild(0, root);
                int i = 0;
                if (s->keys[0] < k)
                {
                    i++;
                }

                s->children[i]->insertNonFull(k);
                root = s;
            }
            else
            {
                root->insertNonFull(k);
            }
        }
    }
};

int main()
{
    BTree t(4);

    t.insert(70);
    t.insert(50);
    t.insert(30);
    t.insert(40);
    t.insert(20);
    t.insert(80);
    t.insert(25);
    t.insert(90);
    t.insert(75);
    t.insert(10);
    t.insert(15);

    cout << "El recorrido del arbol construido es: \n";
    t.traverse();
    cout << "\n";

    return 0;
}
