#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Tupla
{
    vector<int> distancias;
    vector<int> previo;

    Tupla();
};
class Nodo
{
};

class Grafo
{
private:
    int n;
    vector<int> adyacentes;
    vector<vector<int>> pesos;

public:
    Grafo(int n)
    {
        this->n = n;
        this->adyacentes.resize(n);
        this->pesos = {};
    }

    void agregar_arista(int u, int v, int peso)
    {
        this->adyacentes[u] = v;
        this->pesos[u][v] = peso;
    }

    int adyacentes(int nodo)
    {
        return this->adyacentes[nodo];
    }

    int peso(int u, int v)
    {
        if (this->pesos[u][v] == NULL)
        {
            return -1;
        }
        else
        {
            return this->pesos[u][v];
        }
    }
};

// class ColaPrioridad
// {
// private:
// // vector<Nodo*> elementos;
// vector<int> elementos;

// public:
// void insertar(int elemento, int prioridad){
// heapq.push(elemento, prioridad);
// }
// };

Tupla *Dijkstra(Grafo g, Nodo origen)
{
    Tupla *solucion = new Tupla();
    solucion->distancias[n] = -1;
}

int main()
{

    return 0;
}