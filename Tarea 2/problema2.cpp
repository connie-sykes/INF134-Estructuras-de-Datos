#include "tda.hpp"
#include <stdio.h>
#include <iostream>
#include <fstream>

int main() {       
    tABB arbol;

    string comando;
    int flag = 1;
    while(flag){
        cin >> comando;

        if (comando == "ENCENDER"){
            int entero;
            cin >> entero;
            ENCENDER(entero,arbol);
            cout << endl;

        }
        else if (comando == "CUANTOS_ENCENDER"){
            int num;
            cin >> num;
            CUANTOS_ENCENDER(num,arbol); 
        }
        else if (comando == "PARAR_PROGRAMA"){
            flag = 0;
            PARAR_PROGRAMA(arbol.obtenerRaiz(),arbol);
        }
    }
    
    return 0;
}
