// La empresa de transportes “Pepito el Rapidín”, inicia operaciones con su flamante 
// flota de camiones. Según el estudio de mercado realizado por la compañía, se debe 
// cubrir las siguientes rutas comerciales:
// • A -> B: 2 horas
// • A -> C: -1 hora
// • B -> C: 3 horas
// • B -> D: 5 horas
// • C -> D: 2 horas
// • C -> E: 4 horas
// • D -> E: 3 horas
// Si cada camión es capaz de transportar 5 Toneladas con un consumo de combustible 
// de S/. 100 por hora de viaje a un costo de flete de S/.50 x Kilo, cual será la 
// rentabilidad máxima y mínima de la compañía por camión, si todos los viajes parten 
// de C. Modificar el programa Bellman-Ford para que resuelva el problema. Mostrar 
// una imagen del grafo resultante
#include <iostream>
#include <vector>
#include <climits>
#include <iomanip>

using namespace std;

const int INICIO_ASCCI = 65;

struct Edge{
    int src, dest, weight;
};

struct Graph{
    int V, E;
    vector<Edge> edges;
};

char calcularLetra(int i){
    char letter = static_cast<char>(i) + INICIO_ASCCI; 
    return letter;
}

Graph* createGraph(int V, int E){
    Graph* graph = new Graph;
    graph->V = V;
    graph->E = E;
    graph->edges.resize(E);
    return graph;
}

void addEdge(Graph* graph, int src, int dest, int weight, int index){
    graph->edges[index].src = src;
    graph->edges[index].dest = dest;
    graph->edges[index].weight = weight;
}

void printMatrix(vector<vector<int>>& matrix){
    for (int i = 0; i <matrix.size(); i++){
        for(int j =0; j< matrix[i].size(); j++){
            if (matrix[i][j] == INT_MAX){
                cout << "INF\t\t";
            } else {
                cout << matrix[i][j] << "\t";
            }
        }
        cout << endl;
    }
}

void printPath(vector<int>& parent, int j){
    if (parent[j] == -1){
        return;
    }
    printPath(parent, parent[j]);
    cout << calcularLetra(j) << " ";
    // cout << j << " ";
}

void printSolucion(vector<int>& dist, vector<int>& parent, int src){
    cout << "Nodo\tDistancia\tCamino" << endl;
    for (int i=0; i < dist.size(); i++){
        cout << calcularLetra(src) << " -> " << calcularLetra(i) << "\t" << dist[i] << "\t\t" << calcularLetra(src) << " ";
        printPath(parent, i);
        cout << endl;
    }
}

void BellmanFord(Graph* graph, int src){
    int V = graph->V;
    int E = graph->E;
    vector<int> dist(V, INT_MAX);
    vector<int> parent(V, -1);
    dist[src] = 0;

    for (int i = 1; i <= V-1; i++){
        for (int j = 0; j < E; j++){
            int u = graph->edges[j].src;
            int v = graph->edges[j].dest;
            int weight = graph->edges[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]){
                dist[v] = dist[u] + weight;
                parent[v] = u;
            }
        }
    }

    for (int i =0; i< E; i++){
            int u = graph->edges[i].src;
            int v = graph->edges[i].dest;
            int weight = graph->edges[i].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]){
                cout << "El grafo contiene un ciclo negativo\n";
                return;
            }
    }
    printSolucion(dist, parent, src);
}

int calcularRentabilidad(int horas){
    int costo_combustible = horas * 100;
    int costo_flete = 50 * (5*1000);
    return costo_combustible + costo_flete;
}

int main()
{
    int V = 5;
    int E = 7;
    Graph* graph = createGraph(V, E);

    addEdge(graph, 0, 1, calcularRentabilidad(2), 0);
    addEdge(graph, 0, 2, calcularRentabilidad(-1), 1);
    addEdge(graph, 1, 2, calcularRentabilidad(3), 2);
    addEdge(graph, 1, 3, calcularRentabilidad(5), 3);
    addEdge(graph, 2, 3, calcularRentabilidad(2), 4);
    addEdge(graph, 2, 4, calcularRentabilidad(4), 5);
    addEdge(graph, 3, 4, calcularRentabilidad(3), 6);
    
    cout <<"Matriz de Adyacencia:" << endl;
    vector<vector<int>> matrix(V, vector<int>(V,INT_MAX));

    for (int i = 0; i < E; i++)
    {
        matrix[graph->edges[i].src][graph->edges[i].dest] = graph->edges[i].weight;
    }

    printMatrix(matrix);

    cout <<"\nResultados de Bellman Ford:\n";
    BellmanFord(graph, 2);
    return 0;
}
