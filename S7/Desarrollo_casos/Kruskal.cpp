#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;
struct Grafo
{
    int V;
    vector<pair<int, pair<int, int>>> aristas; // Vector de aristas con peso
    Grafo(int V)
    {
        this->V = V;
        aristas = vector<pair<int, pair<int, int>>>();
    }
    void agregar_arista(int u, int v, int w)
    {
        aristas.push_back({w, {u, v}});
    }
    vector<pair<int, pair<int, int>>> obtener_aristas()
    {
        return aristas;
    }
    bool existe_arista(int u, int v)
    {
        for (int i = 0; i < aristas.size(); ++i)
        {
            // Existe una arista entre u y v ?
            if (aristas[i].second.first == u &&
                aristas[i].second.second == v)
            {
                return true;
            }
        }
        return false;
    }
};

struct UnionFind
{
    vector<int> parent, rank;
    UnionFind(int size)
    {
        parent.resize(size);
        for (int i = 0; i < size; i++)
        {
            parent[i] = i;
        }
        rank.resize(size, 0);
    }
    int encontrar(int u)
    {
        if (parent[u] != u)
        {
            parent[u] = encontrar(parent[u]);
        }
        return parent[u];
    }
    void unir(int u, int v)
    {
        int raiz_u, raiz_v;
        raiz_u = encontrar(u);
        raiz_v = encontrar(v);
        // Union por rango
        if (raiz_u != raiz_v)
        {
            if (rank[raiz_u] > rank[raiz_v])
            {
                parent[raiz_v] = raiz_u;
            }
            else if (rank[raiz_u] < rank[raiz_v])
            {
                parent[raiz_u] = raiz_v;
            }
            else
            {
                parent[raiz_v] = raiz_u;
                rank[raiz_u] += 1;
            }
        }
    }
};

// Función para intercambiar dos elementos
void swap(pair<int, pair<int, int>> &a, pair<int, pair<int, int>> &b)
{
    pair<int, pair<int, int>> temp = a;
    a = b;
    b = temp;
}

// Función para la partición del array
int partition(vector<pair<int, pair<int, int>>> &arr, int low, int high)
{
    int pivot = arr[high].first;
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j].first < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// Función QuickSort
void quickSort(vector<pair<int, pair<int, int>>> &arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Función para ordenar las aristas del grafo
vector<pair<int, pair<int, int>>> sorted(Grafo &G)
{
    vector<pair<int, pair<int, int>>> aristas_ordenadas =
        G.obtener_aristas();
    quickSort(aristas_ordenadas, 0, aristas_ordenadas.size() - 1);
    return aristas_ordenadas;
}

// Función para obtener el árbol de expansión mínima (peso, (Nodo origen, Nodo destino))
vector<pair<int, pair<int, int>>> Kruskal(Grafo G)
{
    vector<pair<int, pair<int, int>>> MST, aristas_ordenadas;
    UnionFind uf = UnionFind(G.V);
    aristas_ordenadas = sorted(G);
    for (int i = 0; i < aristas_ordenadas.size(); i++)
    {
        // Accede al elemento segundo del primer segundo de los pares del elemento actual
        int u = aristas_ordenadas[i].second.first;
        // Accede al elemento segundo del primer segundo de los pares del elemento actual
        int v = aristas_ordenadas[i].second.second;
        int temp = uf.encontrar(u);
        int temp2 = uf.encontrar(v);
        if (uf.encontrar(u) != uf.encontrar(v))
        {
            uf.unir(u, v);
            MST.push_back(aristas_ordenadas[i]);
        }
    }
    return MST;
}

int main()
{
    srand(time(0)); // Inicializar la semilla del generador de números aleatorios
    Grafo G(500);
    // Primero, conecta todos los nodos en una línea para garantizar que el grafo sea conexo
    for (int i = 0; i < 499; ++i)
    {
        int numero_aleatorio = rand() % 100 + 1;
        G.agregar_arista(i, i + 1, numero_aleatorio);
    }
    // Luego, agrega las aristas adicionales de manera aleatoria
    for (int i = 0; i < 500; ++i)
    {
        for (int j = 0; j < 4; ++j)
        { // Agrega 4 aristas por nodo
            int x, y;
            do
            {
                x = rand() % 500;
                y = rand() % 500;
            } while (x == y || G.existe_arista(x, y));
            int numero_aleatorio = rand() % 100 + 1;
            // Agrega una arista entre dos nodos aleatorios con un peso aleatorio
            G.agregar_arista(x, y, numero_aleatorio);
        }
    }
    std::vector<pair<int, pair<int, int>>> MST_ = Kruskal(G);
    for (int i = 0; i < MST_.size(); ++i)
    {
        cout << "Nodo origen: " << MST_[i].second.first << " Nodo destino : " << MST_[i].second.second << " Peso : " << MST_[i].first << endl;
    }
    return 0;
}
