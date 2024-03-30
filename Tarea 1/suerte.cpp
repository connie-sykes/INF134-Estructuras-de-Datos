#include "suerte.hpp"
#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;
#include <cstring>
#include <sstream>

int tamano_p;


int main(){
    
    //Este primer bloque es fundamental para la recoleccion de informacion desde la entrada estandar.
    
    string entrada;
    getline(cin, entrada);
    tamano_p = (int)entrada[0] - '0';
  
    Persona* array = new Persona[tamano_p];
    
    for (int a=0; a < tamano_p; a++){
        getline(cin, entrada);
        istringstream iss(entrada);
        string nombre;
        char fecha[11];
        bool quiere_intercambiar;
        iss >> nombre >> fecha >> quiere_intercambiar;
        
        array[a].nombre = nombre;
        strcpy(array[a].fecha, fecha);
        array[a].quiere_intercambiar = quiere_intercambiar;
    }
    

    //COUT PARA PROBAR FUNCION UNDIA DESDE ENTRADA ESTANDAR = SUERTE.TXT
        //cout << unDia(array,1) << endl;

    //COUT para probar funcion variosDias DESDE ENTRADA ESTANDAR = SUERTE.TXT
        variosDias(array,2);

    //************************************PRUEBA FUNCION COMPRARTARJETA

    /* 
    string nombre = "Juan";
    int dia = 10;
    int m = nombre.size();
    int* name_array = comprarTarjeta(nombre,dia,m);
    for(int i=0;i<m;i++){
            //cout << name_array[i] << endl; 
    }
    delete [] name_array;
    return 0; 
    */
    
    
    //************************************PRUEBA FUNCION VOID INTERCAMBIAR
    /* 
    // Crear dos objetos de tipo Persona
    Persona p1 = {"Juan", "01/01/2000", 3, new int[3]{1, 2, 3}, true};
    Persona p2 = {"María", "02/02/2001", 4, new int[4]{4, 5, 6, 7}, false};

    // Mostrar las tarjetas de cada persona antes del intercambio
        //cout << "ANTES" << endl;
        //cout << "Tarjeta de " << p1.nombre << ": ";
    for (int i = 0; i < p1.tamanio_tarjeta; i++) {
            //cout << p1.tarjeta[i] << " ";
    }
        //cout << endl;

        //cout << "Tarjeta de " << p2.nombre << ": ";
    for (int i = 0; i < p2.tamanio_tarjeta; i++) {
            //cout << p2.tarjeta[i] << " ";
    }
        //cout << endl;

    // Intercambiar las tarjetas de p1 y p2
    intercambiarTarjeta(&p1, &p2);

    // Mostrar las tarjetas de cada persona después del intercambio
        //cout << endl;
        //cout << "DESPUES" << endl;
        //cout << "Tarjeta de " << p1.nombre << ": ";
    for (int i = 0; i < p1.tamanio_tarjeta; i++) {
            //cout << p1.tarjeta[i] << " ";
    }
        //cout << endl;
        //cout << "Tarjeta de " << p2.nombre << ": ";
    for (int i = 0; i < p2.tamanio_tarjeta; i++) {
            //cout << p2.tarjeta[i] << " ";
    } 
        //cout << endl;

    // Liberar memoria de los arreglos dinámicos
    delete [] p1.tarjeta;
    delete [] p2.tarjeta; */


    /* ************************************PRUEBA FUNCION PUNTAJE
    // Crear un objeto de tipo Persona
    Persona p8 = {"Pepito", "1999-01-12", 9, new int[9]{1,1,0,0,1,1,0,0,1}, true};

    // Calcular el puntaje de la persona
    int puntuacion = puntaje(&p8);

    // Mostrar el puntaje en pantalla
        //cout << "La puntuación de " << p8.nombre << " es: " << puntuacion << endl;

    // Liberar memoria del arreglo dinámico
    delete [] p8.tarjeta; */

    
    delete[] array;
    return 0;
}

