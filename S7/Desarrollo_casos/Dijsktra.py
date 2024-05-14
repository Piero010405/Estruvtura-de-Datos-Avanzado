import heapq


class Grafo:
    def __init__(self, n):
        self.n = n
        self.adyacentes = [[] for _ in range(n)]
        self.pesos = {}

    def agregar_arista(self, u, v, peso):
        self.adyacentes[u].append(v)
        self.pesos[(u, v)] = peso

    def obtener_adyacentes(self, nodo):
        return self.adyacentes[nodo]

    def obtener_peso(self, u, v):
        return self.pesos.get((u, v), float('inf'))


class ColaPrioridad:
    def __init__(self):
        self.elementos = []

    def insertar(self, elemento, prioridad):
        heapq.heappush(self.elementos, (prioridad, elemento))

    def extraer_minimo(self):
        return heapq.heappop(self.elementos)[1]

    def insertar_o_decrementar(self, elemento, nueva_prioridad):
        self.eliminar(elemento)
        self.insertar(elemento, nueva_prioridad)

    def eliminar(self, elemento):
        indice = self.encontrar_elemento(elemento)
        if indice != -1:
            self.elementos.pop(indice)
            heapq.heapify(self.elementos)

    def encontrar_elemento(self, elemento):
        for i, (_, elem) in enumerate(self.elementos):
            if elem == elemento:
                return i
        return -1


def dijkstra_code(G: Grafo, origen):
    distancias = [float('inf')] * G.n
    previo = [None] * G.n
    visitado = [False] * G.n

    distancias[origen] = 0
    cola_prioridad = ColaPrioridad()
    cola_prioridad.insertar(origen, 0)

    while cola_prioridad.elementos:
        actual = cola_prioridad.extraer_minimo()
        visitado[actual] = True

        for vecino in G.obtener_adyacentes(actual):
            if visitado[vecino] is False:
                costo = G.obtener_peso(actual, vecino)
                nueva_distancia = distancias[actual] + costo

                if nueva_distancia < distancias[vecino]:
                    distancias[vecino] = nueva_distancia
                    previo[vecino] = actual
                    cola_prioridad.insertar_o_decrementar(
                        vecino, nueva_distancia)
    return distancias, previo


# Crear un grafo de prueba
grafo = Grafo(5)
grafo.agregar_arista(0, 1, 10)
grafo.agregar_arista(0, 2, 5)
grafo.agregar_arista(1, 2, 2)
grafo.agregar_arista(1, 3, 1)
grafo.agregar_arista(2, 1, 3)
grafo.agregar_arista(2, 3, 9)
grafo.agregar_arista(2, 4, 2)
grafo.agregar_arista(3, 4, 4)
grafo.agregar_arista(4, 3, 6)

# Ejecutar el algoritmo de Dijkstra desde el nodo 0
ORIGEN = 0
distancias_1, previo_1 = dijkstra_code(grafo, ORIGEN)

# Imprimir las distancias mínimas desde el nodo de origen a todos los demás nodos
print("Distancias mínimas desde el nodo", ORIGEN, ":")
for j, distancia in enumerate(distancias_1):
    print(f"Nodo {j}: {distancia}")
