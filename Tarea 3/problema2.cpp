#include <iostream>
#include <string>
#include <stdio.h>
#include "TDAHEAP.hpp"

using namespace std;

int main() {
    tColaP colaP;
    int i = 0;
    int j = 0;

    string entrada;
    int flag = 1;
    while(flag){
        cin >> entrada;

        if (entrada == "PUSHCOMMAND") {
            string ID;
            int prio;
            string comando;
            getline(cin >> ID >> prio >>ws, comando);
            PUSHCOMMAND(prio, ID, comando);

            j += 1;
        }
        else if (entrada == "GET") {
            int entero;
            cin >> entero;
            GET(entero, i);

        }
        else if (entrada == "TERMINATE") {
            flag = 0;
            TERMINATE(i, j);
        }
    }


}
