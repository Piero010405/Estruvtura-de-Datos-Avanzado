#include <iostream>
#include<vector>
const int INICIO_ASCCI = 97;

using namespace std;

class UnionFind {
    private:
        vector<int> parent;
        vector<int> size;
        vector<char> ascii;

    public:
        UnionFind(int n){
            parent.resize(n);
            size.resize(n, 1);
            ascii.resize(n);

            for (int i = 0; i < n; i++)
            {
                parent[i] = i;
                ascii[i] = char(i+INICIO_ASCCI);
            }    
        }

        int find(int x){
            if(parent[x] != x){
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }

        int findAscci(char c) {
    for (int i = 0; i < ascii.size(); i++) {
        if (ascii[i] == c) {
            return i;
        }
    }
    // If character 'c' is not found, return a default value
    return -1; // or any other appropriate default value
}


        void UnionSet(char a, char b){
            int x = findAscci(a);
            int y = findAscci(b);

            int rootX = find(x);
            int rootY = find(y);
            if(rootX == rootY){
                return;
            }

            if(size[rootX] < size[rootY]){
                parent[rootX] = rootY;
                size[rootY] += size[rootX];
            }
            else {
                parent[rootY] = rootX;
                size[rootX] += size[rootY];
            }
            cout << "Union: " << a << " and " << b << endl;
        }
};

void buscarEquivalencia(UnionFind uf,  char c1, char c2){
    cout << "Elemento " << c1 << " y " << c2<< " son equivalentes?? " ;
    int n1 = uf.findAscci(c1);
    int n2 = uf.findAscci(c2);
    if (uf.find(n1) == uf.find(n2)) cout << "SI." << endl;
    else cout << "NO." << endl;

}
int main()
{
    UnionFind uf(16);

    uf.UnionSet('b','a');
    uf.UnionSet('c','a');
    uf.UnionSet('d','c');

    uf.UnionSet('f','a');
    uf.UnionSet('e','f');
    uf.UnionSet('g','f');
    uf.UnionSet('h','g');
    
    uf.UnionSet('j','a');
    uf.UnionSet('i','j');
    uf.UnionSet('k','j');
    uf.UnionSet('l','k');

    uf.UnionSet('n','a');
    uf.UnionSet('m','n');
    uf.UnionSet('o','n');
    uf.UnionSet('p','o');

        // buscarEquivalencia(uf, 'a', 'b');
    // buscarEquivalencia(uf, 'e', 'm');
    // buscarEquivalencia(uf, 'g', 'o');
    // buscarEquivalencia(uf, 'd', 'c');
    // buscarEquivalencia(uf, 'h', 'g');
    // buscarEquivalencia(uf, 'p', 'n');

    return 0;
}


