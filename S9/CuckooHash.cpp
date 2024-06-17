#include <iostream>
#include <vector>
using namespace std;

int has1(int clave)
{
    return clave % 11;
}

int has2(int clave)
{
    return (clave / 11) % 11;
}

class CuckooHashTable
{
private:
    vector<int> table1;
    vector<int> table2;
    int size;
    int numElements;

    // Factor de carga umbral para el redimensionamiento
    const double umbralRedimensionamiento = 0.6;

public:
    CuckooHashTable(int size)
    {
        this->size = size;
        this->table1.resize(size, -1);
        this->table2.resize(size, -1);
        this->numElements = 0;
    }

    // Calcular el factor de carga
    double factorDeCarga() const
    {
        return static_cast<double>(numElements) / size;
    }

    void validarRedimensionar()
    {
        if (factorDeCarga() > umbralRedimensionamiento)
        {
            redimensionar();
        }
    }

    // Redimensionar las tablas
    void redimensionar()
    {
        // Calcula el nuevo tamaño
        int newSize = size * 2;

        // Crea nuevas tablas con el nuevo tamaño
        vector<int> newTable1(newSize, -1);
        vector<int> newTable2(newSize, -1);

        // Vuelve a insertar todos los elementos en las nuevas tablas
        for (int i = 0; i < size; ++i)
        {
            if (table1[i] != -1)
            {
                int pos = has1(table1[i]);
                newTable1[pos] = table1[i];
            }
            if (table2[i] != -1)
            {
                int pos = has2(table2[i]);
                newTable2[pos] = table2[i];
            }
        }

        // Actualiza las tablas y el tamaño
        table1 = std::move(newTable1);
        table2 = std::move(newTable2);
        size = newSize;
    }

    void insertar(int clave)
    {
        int pos1 = has1(clave);
        int pos2 = has2(clave);

        if (table1[pos1] == -1)
        {
            table1[pos1] = clave;
            numElements++;
            validarRedimensionar();
            return;
        }

        if (table2[pos2] == -1)
        {
            table2[pos2] = clave;
            numElements++;
            validarRedimensionar();
            return;
        }

        // Manejo de colisiones mediante el método de expulsión
        intercambiar(table1, pos1, clave);
        if (table2[pos2] != -1)
        {
            intercambiar(table2, pos2, clave);
            insertar(clave);
        }
        else
        {
            table2[pos2] = clave;
            numElements++;
            validarRedimensionar();
        }
    }

    void intercambiar(vector<int> &tabla, int pos, int clave)
    {
        if (pos >= 0 && pos < size)
        {
            int temp = tabla[pos];
            tabla[pos] = clave;
            insertar(temp);
        }
    }

    void mostrar()
    {
        cout << "| Tabla 1 |" << endl;
        for (int i = 0; i < this->table1.size(); i++)
        {
            cout << "| Posicion " << i << ": ";
            if (table1[i] != -1)
                cout << table1[i];
            cout << endl;
        }
        cout << endl;

        cout << "| Tabla 2 |" << endl;
        for (int i = 0; i < this->table2.size(); i++)
        {
            cout << "| Posicion " << i << ": ";
            if (table2[i] != -1)
                cout << table2[i];
            cout << endl;
        }
        cout << endl;
    }
};

int main()
{
    CuckooHashTable hashTable(11);
    hashTable.insertar(20);
    hashTable.insertar(50);
    hashTable.insertar(53);
    hashTable.insertar(10);
    hashTable.insertar(90);
    hashTable.insertar(69);
    hashTable.insertar(72);
    hashTable.insertar(13);
    hashTable.insertar(1);
    hashTable.insertar(2);
    hashTable.insertar(3);
    hashTable.insertar(4);
    hashTable.insertar(5);
    hashTable.insertar(6);
    hashTable.insertar(7);
    hashTable.insertar(8);
    hashTable.mostrar();
    return 0;
}
