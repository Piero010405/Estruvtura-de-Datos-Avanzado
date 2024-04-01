#include <iostream>
#include <cstdlib> 
#include <chrono>
#include <math.h>

using namespace std;
using namespace std::chrono;
const int TAMANO_MAX = 100000;

void fun(int n){
    time_point<std::chrono::system_clock> inicio, fin;
    // int n = 0;
    // cout << "Ingrese la cantidad de valores a ingresar en el arreglo: ";
    // cin >> n;

    if (n == 0 || n > TAMANO_MAX){
        cout << "La cantidad ingresada no es valida" << endl;
        return;
    } else {
        int array[TAMANO_MAX];
        int i = 0;
        inicio = system_clock::now();
        srand(time(0));

        while(i < n ){
            int numero = rand() % 100;
            array[i] = numero;
            i++;
        }

        i = 0;
        cout << "Valores generados para " << n << " valores : " << endl;

        while(i < n ){
            cout << array[i] << endl ;
            i++;
        }
        fin = system_clock::now();

        duration<double> tiempo = fin - inicio;

        cout << "El tiempo de ejecucion es: " << tiempo.count() << endl;
    }
}

int main()
{
    int entrada_datos = 100;
    // for (int i = 1; i <= 5; i++){
    //     cout << pow(entrada_datos, i) << " datos de entrada: " << endl;
    //     fun(pow(entrada_datos, i));
    //     cout << endl;
    // }
    fun(entrada_datos);
    
    return 0;
}
