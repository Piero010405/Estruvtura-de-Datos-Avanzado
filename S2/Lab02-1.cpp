#include <iostream>
#include <vector>

using namespace std;

class UnionFind
{
private:
    vector<int> parent;
    vector<int> size;

public:
    UnionFind(int n)
    {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }

    int find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void UnionSet(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX == rootY)
        {
            return;
        }

        if (size[rootX] < size[rootY])
        {
            parent[rootX] = rootY;
            size[rootY] += size[rootX];
        }
        else
        {
            parent[rootY] = rootX;
            size[rootX] += size[rootY];
        }
        cout << "Union: " << x << " and " << y << endl;
    }
};

void buscarEquivalencia(UnionFind uf, int n1, int n2)
{
    cout << "Elemento " << n1 << " y " << n2 << " son equivalentes?? ";
    if (uf.find(n1) == uf.find(n2))
        cout << "SI." << endl;
    else
        cout << "NO." << endl;
}
int main()
{
    // UnionFind uf(12);

    // uf.UnionSet(1, 0);
    // uf.UnionSet(2, 0);
    // uf.UnionSet(3, 2);

    // uf.UnionSet(5, 4);
    // uf.UnionSet(6, 4);
    // uf.UnionSet(7, 6);

    // uf.UnionSet(9, 8);
    // uf.UnionSet(10, 8);
    // uf.UnionSet(11, 10);

    // buscarEquivalencia(uf, 1, 3);
    // buscarEquivalencia(uf, 2, 9);
    // buscarEquivalencia(uf, 4, 7);

    UnionFind uf(16);

    uf.UnionSet(1, 0);
    uf.UnionSet(2, 0);
    uf.UnionSet(3, 2);

    uf.UnionSet(5, 4);
    uf.UnionSet(6, 4);
    uf.UnionSet(7, 6);

    uf.UnionSet(9, 8);
    uf.UnionSet(10, 8);
    uf.UnionSet(11, 10);

    uf.UnionSet(13, 12);
    uf.UnionSet(14, 12);
    uf.UnionSet(15, 14);

    buscarEquivalencia(uf, 0, 1);
    buscarEquivalencia(uf, 5, 13);
    buscarEquivalencia(uf, 6, 14);
    buscarEquivalencia(uf, 3, 2);
    buscarEquivalencia(uf, 7, 6);
    buscarEquivalencia(uf, 15, 12);

    return 0;
}
