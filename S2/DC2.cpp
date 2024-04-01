#include <iostream>
using namespace std;

void Function(int n){
    int count = 0;  // 1
    for (int i = n/2; i < n; i++) // n/2
    {
        int j = 1; // 1
        while (j + n/2 <= n) // logn
        {
            int k = 1; // 1
            while (k <= n) // n
            {
                count = count + 1; // 1
                k = k *2; // logn
            }
            j = j*2; // 1     
        }
        
    }
    cout << count << endl; // 1
}

// NOTACION ASINTOTICA ==> O(n/2 * (nlogn))
//                         O(n * nlogn)
//                         O(n^2logn)

int main()
{
    Function(20);
    return 0;
}
