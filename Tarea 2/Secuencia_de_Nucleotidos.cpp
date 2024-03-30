#include "Secuencia_de_Nucleotidos.hpp"
#include <iostream>

tLista::tLista() {
 head = tail = curr = NULL;
 listSize = 0; pos = 0;
}
/*****
* Constructor tLista()
******
* Constructor de la clase tLista el cual inicializa los nodos head, tail y curr en NULL para indicar
que la lista está vacía, además de establecer el tamaño y posición de la lista en 0.
******
* Input:
* Ninguno.
******
* Returns:
* No tiene retorno.
*****/

tLista::~tLista(){
    clear();
}
/*****
* Destructor ~tLista()
******
* Es el destructor de la clase tLista, que se utiliza para liberar la memoria asignada a una instancia 
de la clase cuando se elimina. Se llama a la función clear() de la cual se hablará más adelante.
******
* Input:
* Ninguno
******
* Returns:
* No tiene retorno
*****/

tElemLista tLista::getvalue(){
    return curr->info;
}
/*****
* tElemLista getvalue()
******
* Devuelve el valor de tipo tElemLista almacenado en el nodo actual de la lista. Especificamente 
devuelve la información almacenada en el nodo apuntado por el puntero curr.
******
* Input:
* Ninguno
******
* Returns:
* tElemLista, representa el elemento en el nodo actual de la lista.
*****/

void tLista::moveToStart() { 
    curr = head; pos = 0; 
}
/*****
* void moveToStart()
******
* Establece el cursor curr al inicio de la lista, es decir, hace que el puntero curr apunte al primer nodo 
de la lista, se establece la posición del cursor pos a 0, lo que indica que el cursor está ahora en la primera 
posición de la lista.
******
* Input:
* Ninguno.
******
* Returns:
* No tiene retorno.
*****/

void tLista::next() { 
    if (curr != tail) { 
        curr = curr->sig; 
        pos++; 
    } 
}
/*****
* void next()
******
* Mueve el cursor curr al siguiente nodo de la lista, es decir, hace que el puntero curr 
apunte al nodo siguiente al nodo actual (el nodo apuntado por curr), y actualiza la posición 
del cursor pos en consecuencia. Si curr ya apunta al último nodo de la lista, entonces no se puede 
avanzar más en la lista y la función no hace nada.
******
* Input:
* Ninguno.
******
* Returns:
* No tiene retorno.
*****/

void tLista::clear() {
    tNodo* actual = head;
    while (actual != NULL) {
        tNodo* sig = actual->sig;
        delete actual;
        actual = sig;
    }
    head = NULL;
}
/*****
* void clear()
******
* Libera la memoria asignada a todos los nodos de la lista y establece el puntero head a NULL 
para indicar que la lista está vacía. Se recorre la lista mientras el puntero actual no sea NULL y en cada 
iteración del bucle se crea un puntero sig que apunte al nodo siguiente del actual, se libera la memoria del nodo actual y se actualiza
posteriormente el nodo actual para que apunte al siguiente (sig).
******
* Input:
* Ninguno
* .......
******
* Returns:
* No tiene retorno.
*****/

unsigned int tLista::getSize(){
    return listSize;
}
/*****
* unsigned int getSize()
******
* Retorna el tamaño de la lista.
******
* Input:
* Ninguno.
******
* Returns:
* unsigned int, retorna un entero positivo correspondiente al tamaño de la lista.
*****/

void tLista::insertar(unsigned int i, tElemLista elem) {
    if (i > listSize) {
        return;
    }
    tNodo* aux = new tNodo;
    aux->info=elem;
    if (listSize == 0) {
        head = tail = curr = aux;
        pos=0;
    }
    else if (i == 0) {
        aux->sig = head;
        head = aux;
        curr = aux;
    }
    else if (i == listSize) {
        tail->sig = aux;
        tail = aux;
        curr = aux;
    }
    else {
        moveToStart();
        for (unsigned int j = 0; j < i - 1; j++) {
            next();
        }
        aux->sig =curr->sig;
        curr->sig = aux;
        curr = aux;
    }
    listSize++;
}
/*****
* void insertar()
******
* Inserta un nuevo elemento elem en la lista en la posición i. La posición i se refiere a la posición del elemento 
en la lista, donde el primer elemento se encuentra en la posición 0. Se toman varios casos;
-Si la posición i es mayor que el tamaño actual de la lista listSize, la función no hace nada y se devuelve inmediatamente.
POSTERIORMENTE SE CREA UN NUEVO NODO AUX (auxiliar) Y SE LE ASIGNA EL VALOR ELEM.
-Si la lista está vacía (listSize == 0), se establece el puntero head, tail y curr al nuevo nodo aux, y se establece la posición 
del cursor pos a 0.
-Si i es igual a 0, se inserta el nuevo nodo aux al principio de la lista. Para ello, se establece el puntero sig del nuevo nodo aux 
al puntero head, se actualiza el puntero head para que apunte al nuevo nodo aux, y se establece el cursor curr al nuevo nodo aux.
-Si i es igual a listSize, se inserta el nuevo nodoaux al final de la lista. Para ello, se establece el puntero sig del último nodo tail 
al nuevo nodo aux, se actualiza el puntero tail para que apunte al nuevo nodo aux, y se establece el cursor curr al nuevo nodo aux.
En cualquier otro caso, se busca el nodo en la posición i-1 utilizando la función moveToStart() para establecer el cursor curr al 
principio de la lista, seguida por next() para avanzar en la lista hasta la posición i-1. Luego, se inserta el nuevo nodo aux después 
del nodo curr, actualizando los punteros sig de los nodos correspondientes. Finalmente, se establece el cursor curr al nuevo nodo aux.
Y SE INCREMENTA EL TAMAÑO DE LA LISTA EN UNO.
******
* Input:
* unsigned int i, posición deseada para insertar el nuevo elemento.
tElemLista elem, es el caracter a insertar en la posición i.

******
* Returns:
* No tiene retorno.
*****/

void tLista::borrar(unsigned int i) {
    if (i >= listSize) {
        return;
    }
    if (listSize == 1) {
        delete head;
        head = tail = curr= NULL;
        listSize = 0;
        pos = 0;
        return;
    }
    if (i == 0) {
        curr = head;
        head = head->sig;
    }
    else {
        curr = head;
        pos=0;
        for (unsigned int j = 0; j < i - 1; j++) {
            next();
        }
        if (curr->sig == tail) {
            tail = curr;
        }
        tNodo* aux = curr->sig;
        curr->sig = curr->sig->sig;
        delete aux;
    }
    listSize--;
}
/*****
* void borrar()
******
* Elimina el elemento en la posición i de la lista. Se toman varios casos; Si la posición i es mayor o igual
que el tamaño actual de la lista listSize, la función no hace nada y se devuelve inmediatamente. Si la lista tiene un solo elemento 
(listSize == 1), se elimina el nodo head y se establecen todos los punteros a NULL. A continuación, se actualiza el tamaño de la lista 
listSize a 0 y la posición del cursor pos a 0. Si i es igual a 0, se elimina el primer nodo de la lista. Para ello, se establece el cursor curr 
al primer nodo head, se actualiza el puntero head para que apunte al siguiente nodo head->sig, y se elimina el nodo anterior head, 
liberando la memoria asignada.En cualquier otro caso, se busca el nodo en la posición i-1 utilizando la función moveToStart() para 
establecer el cursor curr al principio de la lista, seguida por next() para avanzar en la lista hasta la posición i-1. Luego, se elimina
elnodo curr->sig (el nodo siguiente al nodo actual curr) actualizando los punteros sig de los nodos correspondientes. Si el 
nodo eliminado es el último de la lista, se actualiza el puntero tail para que apunte al nodo anterior curr. Finalmente, se libera la 
memoria asignada al nodo eliminado utilizando el operador delete. Por último, se reduce el tamaño de la lista listSize en uno.
******
* Input:
* unsigned int i; corresponde a la posición que se desea eliminar, es un entero positivo.
******
* Returns:
* No tiene ningun retorno.
*****/

void tLista::intercambiar(unsigned int i, tElemLista elem) {
    if (i >= listSize) {
        return;
    }
    curr = head;
    for (pos = 0; pos < i; pos++) {
        curr = curr->sig;
    }
    curr->info = elem;
}
/*****
* void intercambiar()
******
*Cambia el valor del elemento en la posición i por el nuevo valor elem, avanzando en la lista hasta la posición i y 
actualizando el valor del campo info del nodo correspondiente. Si la posición i es mayor o igual que el tamaño actual de la lista listSize, la función no hace nada 
y se devuelve inmediatamente. Se establece el cursor curr al primer nodo de la lista (head) y se inicializa la posición del cursor 
pos a 0. Se avanza en la lista con la función next() hasta que se llega al nodo en la posición i. Para ello, se llama a la función 
next() i veces. Se actualiza el valor del elemento en la posición i con el nuevo valor elem, asignándolo al campo info del nodo actual 
curr->info.
******
* Input:
* unsigned int i, posición deseada para instercambiar el nuevo elemento.
* tElemLista elem, es el caracter a intercambiar en la posición i.
******
* Returns:
* No tiene retorno.
*****/