#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <cstdlib>
#include <ctime>
using namespace std;

class Grafo
{
    int n;
    vector<vector<int>> adyacentes;
    vector<vector<int>> pesos;

public:
    Grafo(int n){
        this->n = n;
        this->adyacentes.resize(n);
        this->pesos.resize(n);
        for (int i = 0; i < n; ++i) {
            this->adyacentes[i].resize(n);
            this->pesos[i].resize(n);
        }
    }

    void agregar_arista(int u, int v, int peso)
    {
        this->adyacentes[u].push_back(v);
        this->pesos[u][v] = peso;
    }

    vector<int> obtener_adyacentes(int nodo)
    {
        return this->adyacentes[nodo];
    }

    int obtener_peso(int u, int v)
    {
        if(this->pesos[u][v]){
            return this->pesos[u][v];
        }
        return numeric_limits<int>::max();
    }

    int obtener_n()
    {
        return this->n;
    }
};

class Tupla
{
public:
    vector<int> distancias;
    vector<int> previo;
    vector<bool> visitado;

    Tupla(int n)
    {
        this->distancias.resize(n, numeric_limits<int>::max());
        this->previo.resize(n, -1);
        this->visitado.resize(n, false);
    }
};

class ColaPrioridad
{
    typedef pair<int, int> pii;
    priority_queue<pii, vector<pii>, greater<pii>> pq;

public:
    void insertar(int elemento, int prioridad)
    {
        pq.push({prioridad, elemento});
    }

    int extraer_minimo()
    {
        int elemento = pq.top().second;
        pq.pop();
        return elemento;
    }

    void insertar_o_decrementar(int elemento, int nueva_prioridad)
    {
        pq.push({nueva_prioridad, elemento});
    }

    bool vacia()
    {
        return pq.empty();
    }
};

Tupla *Dijkstra(Grafo *G, int origen)
{
    Tupla *solucion = new Tupla(G->obtener_n());

    solucion->distancias[origen] = 0;
    ColaPrioridad *cola_prioridad = new ColaPrioridad();
    cola_prioridad->insertar(origen, 0);

    while (!cola_prioridad->vacia())
    {
        int actual = cola_prioridad->extraer_minimo();
        solucion->visitado[actual] = true;

        for (int vecino : G->obtener_adyacentes(actual))
        {
            if (!solucion->visitado[vecino])
            {
                int costo = G->obtener_peso(actual, vecino);
                int nueva_distancia = solucion->distancias[actual] + costo;

                if (nueva_distancia < solucion->distancias[vecino])
                {
                    solucion->distancias[vecino] = nueva_distancia;
                    solucion->previo[vecino] = actual;
                    cola_prioridad->insertar_o_decrementar(vecino, nueva_distancia);
                }
            }
        }
    }

    delete cola_prioridad;
    return solucion;
}

void insertar_dinamico(int n){
    clock_t start_time = clock(); 
    srand(time(nullptr));
    
    Grafo G = Grafo(n);
    int v = n - 1;
    int nodo_destino = rand( )% (v + 1);
    int peso = rand() % 10 + 1;
    G.agregar_arista(0, nodo_destino, peso);

    for (int i = 0; i < n-1; i++){  
        int nodo_origen = rand() % (v + 1);
        peso = rand() % 10 + 1;
        nodo_destino = rand( )% (v + 1);
        while (nodo_origen == nodo_destino)
        {
            nodo_destino = rand( )% (v + 1);
        }
        G.agregar_arista(nodo_origen, nodo_destino, peso);
    }

    clock_t end_time = clock();
    double elapsed_time = double(end_time - start_time) / CLOCKS_PER_SEC;

    int ORIGEN = 0;
    Tupla *solucion = Dijkstra(&G, ORIGEN);

    cout << "Distancias mínimas desde el nodo " << ORIGEN << ":" << endl;
    for (int i = 0; i < solucion->distancias.size(); ++i)
    {
        cout << "Nodo " << i << ": " << solucion->distancias[i] << endl;
    }

    cout << "Tiempo promedio para n = " << n << ": " << elapsed_time << " segundos" << endl;

    delete solucion;
}

int main()
{
    srand(time(nullptr));
    insertar_dinamico(10);
    return 0;
}
