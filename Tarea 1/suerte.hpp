#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;
#include <cstring>
#include <sstream>

/*****
* int* comprarTarjeta
******
*  Retorna un arreglo de enteros de tamaño m, donde en la posición i se encuentra el valor nombre[i] % dia.
******
* Input:
    * string nombre: el nombre de la persona que quiere comprar la tarjeta.
    * int dia: el día en que se compra la tarjeta.
    * int& m: el tamaño del arreglo a retornar.
******
* Returns:
    * int*: un puntero al arreglo de enteros de tamaño m que contiene el resultado del cálculo.
*****/

int* comprarTarjeta(string nombre, int dia, int &m){
    if (dia == 0) {
        dia = 1; 
    }
    int* name_array = new int[m];       //Creo el arreglo de tamanio m
    for (int i=0;i<m;i++){           
        name_array[i] = nombre[i]%dia;  //Asigno a cada posicion su respectivo nombre[i]%dia   
    } 
    return name_array;                  //Retorno dicho arreglo
}


/*****
* void intercambiarTarjeta
******
* Intercambiar las tarjetas (y sus tamanios tambien) entre las dos personas ingresadas.
******
* Input:
    * Persona* p1: Puntero p1 al struct de la primera persona ingresada.
    * Persona* p2: Puntero p2 al struct de la segunda persona ingresada.
******
* Returns:
    * No hay return al ser una funcion void.
*****/
struct Persona {
    string nombre;
    char fecha [11];
    int tamanio_tarjeta;
    int* tarjeta;
    bool quiere_intercambiar;
};

void intercambiarTarjeta(Persona* p1, Persona* p2){
    int* a = p1->tarjeta;
    p1->tarjeta = p2->tarjeta;
    p2->tarjeta = a;

    // INTERCAMBIO LOS TAMANIOS DE TARJETA TAMBIEN
    int b = p1->tamanio_tarjeta;
    p1->tamanio_tarjeta = p2->tamanio_tarjeta;
    p2->tamanio_tarjeta = b;

    p1->quiere_intercambiar = 0;
    p2->quiere_intercambiar = 0;
}


/*****
* int puntaje
******
* Retorna un entero correspondiente al puntaje de la persona ingresada.
******
* Input:
    * Persona* p1: Puntero p1 al struct de la persona ingresada.
******
* Returns:
    * Retorna un entero del puntaje de la persona ingresada.
*****/

int puntaje(Persona* p1) {
    int puntaje = 0;
    for (int i = 0; i < (p1->tamanio_tarjeta); i++) {
        int a = (*p1).tarjeta[i];
        int b = (*p1).fecha[i%10] ;
        puntaje += a*b;
    }
    return puntaje;
}


/*****
* Persona* unDia
******
* Compra una tarjeta a cada persona con el parametro dia, 
  intercambia hasta que no sea posible intercambiar tarjetas. (Orden: 0 -> p-1)

******
* Input:
    * Persona* personas: puntero de tipo Persona al arreglo de personas ingresado
    * int dia: dia que se compra la tarjeta
******
* Returns:
    * Retorna la persona con mayor puntaje (ganadora)
*****/

Persona* unDia(Persona* personas, int dia){

    extern int tamano_p;
    Persona* ganador = nullptr;
    for (int i=0; i < tamano_p; i++){
        int tamano_n = personas[i].nombre.length();
        personas[i].tarjeta = comprarTarjeta(personas[i].nombre,dia,tamano_n);
        personas[i].tamanio_tarjeta = tamano_n;
    }

    for (int h=0; h< tamano_p; h++){
        for (int s=h+1; s< tamano_p; s++){
            if (personas[h].quiere_intercambiar && personas[s].quiere_intercambiar){
                intercambiarTarjeta(&personas[h],&personas[s]);
            }
        }    
    }     
    
    // Calculo puntajes de cada persona LUEGO de intercambio, y voy comparando para obtener la persona con mayor puntaje.
    int puntaje_mayor = 0;
    for (int u=0; u<tamano_p; u++){
        int puntaje_actual = puntaje(&personas[u]);
        if(puntaje_actual >= puntaje_mayor){
            puntaje_mayor = puntaje(&personas[u]);
            ganador = &personas[u];
        }
    }
    if (puntaje_mayor == 0){
        ganador = &personas[0];
    }

    //cout <<  ganador->nombre << " " <<  ganador->fecha << " " << puntaje_mayor << endl;
    return ganador;
}


/*****
* void variosDias
******
* Usando la función "unDia", muestra en pantalla el nombre, fecha de nacimiento y puntaje de la
persona que obtuvo el mayor puntaje ese día.
******
* Input:
    * Persona* persona: Contiene a las personas totales
    * int cant_dias: cantidad de días totales
******
* Returns:
    * No hay return, pero durante la ejecucion imprime dia por dia al ganador, su fecha y su puntaje.
*****/

void variosDias(Persona* persona, int cant_dias){
    int i=1;
    while(i <= cant_dias){
        Persona* p_mayor = unDia(persona, i);
        cout<<"Día: "<<i<< ".\n" <<(*p_mayor).nombre << " " << (*p_mayor).fecha << " " << puntaje(p_mayor)<<endl;
        i++;
    }
}