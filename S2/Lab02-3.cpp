#include <iostream>
#include <vector>
const int INICIO_ASCCI = 97;

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

    int findAscii(char c)
    {
        int x = static_cast<int>(c) - INICIO_ASCCI;
        return x;
    }

    void UnionSet(char a, char b)
    {
        int rootX = find(findAscii(a));
        int rootY = find(findAscii(b));
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
        cout << "Union: " << a << " and " << b << endl;
    }
};

void buscarEquivalencia(UnionFind uf, char c1, char c2)
{
    cout << "Elemento " << c1 << " y " << c2 << " son equivalentes?? ";

    if (uf.find(uf.findAscii(c1)) == uf.find(uf.findAscii(c2)))
        cout << "SI." << endl;
    else
        cout << "NO." << endl;
}
int main()
{
    UnionFind uf(16);

    uf.UnionSet('b', 'a');
    uf.UnionSet('c', 'a');
    uf.UnionSet('d', 'c');

    uf.UnionSet('e', 'f');
    uf.UnionSet('g', 'f');
    uf.UnionSet('h', 'g');

    uf.UnionSet('i', 'j');
    uf.UnionSet('k', 'j');
    uf.UnionSet('l', 'k');

    uf.UnionSet('m', 'n');
    uf.UnionSet('o', 'n');
    uf.UnionSet('p', 'o');

    buscarEquivalencia(uf, 'a', 'b');
    buscarEquivalencia(uf, 'e', 'm');
    buscarEquivalencia(uf, 'g', 'o');
    buscarEquivalencia(uf, 'd', 'c');
    buscarEquivalencia(uf, 'h', 'g');
    buscarEquivalencia(uf, 'p', 'n');

    return 0;
}
