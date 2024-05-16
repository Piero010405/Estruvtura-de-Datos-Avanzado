#include <iostream>
#include <vector>
#include <climits>
#include <iomanip>

using namespace std;

struct Edge{
    int src, dest, weight;
};

struct Graph{
    int V, E;
    vector<Edge> edges;
};

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
                cout << "INF\t";
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
    cout << j << " ";
}

void printSolucion(vector<int>& dist, vector<int>& parent, int src){
    cout << "Nodo\tDistancia\tCamino" << endl;
    for (int i=0; i < dist.size(); i++){
        cout << src << " -> " << i << "\t" << dist[i] << "\t\t\t" << src << " ";
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

int main()
{
    int V = 5;
    int E = 8;
    Graph* graph = createGraph(V, E);

    addEdge(graph, 0, 1, -1, 0);
    addEdge(graph, 0, 2, 4, 1);
    addEdge(graph, 1, 2, 3, 2);
    addEdge(graph, 1, 3, 2, 3);
    addEdge(graph, 1, 4, 2, 4);
    addEdge(graph, 3, 2, 5, 5);
    addEdge(graph, 3, 1, 1, 6);
    addEdge(graph, 4, 3, -3, 7);

    cout <<"Matriz de Adyacencia:" << endl;
    vector<vector<int>> matrix(V, vector<int>(V,INT_MAX));

    for (int i = 0; i < E; i++)
    {
        matrix[graph->edges[i].src][graph->edges[i].dest] = graph->edges[i].weight;
    }

    printMatrix(matrix);

    cout <<"\nResultados de Bellman Ford:\n";
    BellmanFord(graph, 0);
    return 0;
}
