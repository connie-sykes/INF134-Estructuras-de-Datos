#include <iostream>
#include <stdio.h>

using namespace std;

typedef int tElem;

struct tNodoABB{
    tElem pos; 
    tNodoABB* izq;
    tNodoABB* der;
};

class tABB{
    private:
        tNodoABB *raiz;
        int nElems;
    public:
        tABB(){
            raiz = NULL;
            nElems = 0;
        }
        ~tABB(){
            clear();
        }
        tNodoABB* obtenerRaiz();
        void clear();
        void clearHelp(tNodoABB *poste);
        void insert(tElem x);
        bool find(tElem x);
        bool findHelp(tNodoABB *poste, tElem x);
        int lower_bound(tElem x);
};

/*****
* tNodoABB* tABB::obtenerRaiz
******
* Obtiene el puntero a la raíz del árbol
******
* Input:
    * No necesita parametros para ser ejecutado
******
* Returns:
    * Retorna el puntero a la raíz del árbol
*****/
tNodoABB* tABB::obtenerRaiz(){
    return raiz;
}

/*****
* void tABB::clear
******
* Borra el árbol
******
* Input:
    * No necesita parametro.
******
* Returns:
    * No hay retorno al ser función void
*****/
void tABB::clear(){
    clearHelp(raiz); // función auxiliar para eliminar los nodos
    raiz = NULL;
    nElems = 0;
}

/*****
* void tABB::clearHelp
******
* Borra el árbol
******
* Input:
    * tNodoABB *poste: Puntero a la raiz del árbol
******
* Returns:
    * No hay retorno al ser función void
*****/
void tABB::clearHelp(tNodoABB *poste) {
    if (poste == NULL) return; 
    clearHelp(poste->izq); 
    clearHelp(poste->der); 
    delete poste; 
}

/*****
* void tABB::insert
******
* inserta el elemento x en el árbol
******
* Input:
    * tElem x: Elemento de tipo tElem, definido en este caso como entero (int)
******
* Returns:
    * No hay retorno al ser función void
*****/
void tABB::insert(tElem x){
    tNodoABB *actual = raiz;
    while (actual != NULL) {
        if (x == actual->pos) {
            return; // El elemento ya existe, no hacer nada
        } else if (x < actual->pos) {
            actual = actual->izq;
        } else {
            actual = actual->der;
        }
    }
    
    tNodoABB *nuevoPoste = new tNodoABB;
    nuevoPoste->pos = x;
    nuevoPoste->izq = NULL;
    nuevoPoste->der = NULL;

    if(raiz == NULL){
        raiz = nuevoPoste;
    }else{
        tNodoABB *padre = NULL;
        tNodoABB *actual = raiz;
        while(actual != NULL){
            padre = actual;
            if(x <= actual->pos){
                actual = actual->izq;
            }else{
                actual = actual->der;
            }
        }
        if(x <= padre->pos){
            padre->izq = nuevoPoste;
        }else{
            padre->der = nuevoPoste;
        }
    }
    nElems++;
}

/*****
* bool tABB::find
******
* Busca el elemento x en el árbol y retorna un valor verdadero de encontrarse en el árbol
******
* Input:
    * tElem x: Elemento de tipo tElem, definido en este caso como entero (int)
******
* Returns:
    * Retorna el booleano retornado por la función findHelp, correspondiente a si se encontró el elemento en el árbol o no
*****/
bool tABB::find(tElem x){
    return findHelp(raiz, x);
}

/*****
* bool tABB::findHelp
******
* Busca el elemento x y retorna un valor verdadero si x se encuentra en el árbol
******
* Input:
    * tNodoABB *poste: Puntero a la raíz del árbol
    * tElem x: Elemento de tipo tElem, definido en este caso como entero (int)
******
* Returns:
    * Retorna un booleano, falso en caso que x no esté en el árbol y verdadero en caso que x esté en el árbol
*****/
bool tABB::findHelp(tNodoABB *poste, tElem x) {
    if (poste == NULL) return false;
    if (poste->pos == x) return true; 
    if (x < poste->pos){
        return findHelp(poste->izq, x);
    }
    else{
        return findHelp(poste->der, x);
    }
}

/*****
* int tABB::lower_bound
******
* Busca el primer valor menor o igual al elemento x
******
* Input:
    * tElem x: Elemento de tipo tElem, definido en este caso como entero (int)
******
* Returns:
    * Retorna un entero con el primer valor menor o igual a x dentro de la estructura, -1 en caso que no haya resultado
*****/
int tABB::lower_bound(tElem x){
    tNodoABB *actual = raiz;
    tNodoABB *resultado = NULL;
    while(actual != NULL){
        if(actual->pos <= x){
            resultado = actual;
            actual = actual->der;
        }else{
            actual = actual->izq;
        }
    }
    return resultado != NULL ?resultado->pos : -1;
}

/*****
* void ENCENDER
******
* Llama la función insert para introducir al árbol un nodo con un parámetro i
******
* Input:
    * int i: Contiene la posición del poste que se quiere encender
    * tABB& arbol: Dirección de memoria del arbol binario de busqueda
******
* Returns:
    * No hay return al ser función void
*****/
void ENCENDER(int i,tABB& arbol){
    arbol.insert(i);
}

/*****
* int CUANTOS_ENCENDER
******
* Calcula cuántos postes quedan por encender desde la posición i hasta el primer poste encendido con posición <= i
******
* Input:
    * int i: Contiene la posición desde la que se quiere calcular los postes por encender
    * tABB& arbol: Dirección de memoria del arbol binario de busqueda
******
* Returns:
    * Retorna un entero con la cantidad de postes por encender
*****/
int CUANTOS_ENCENDER(int i, tABB& arbol){
    int deben_encender = i - arbol.lower_bound(i); 
    cout << deben_encender << endl;
    cout << endl;
    return deben_encender;
}

/*****
* void inOrdenP
******
* Recorre un árbol en inOrden mientras cuenta los nodos que se han creado
******
* Input:
    * tNodoABB *poste: Puntero a un nodo en especifico dentro del arbol.
    * int &k: variable donde se almacenará la cantidad de nodos del árbol al pasar por referencia
******
* Returns:
    * El return existente es para asegurarse que la función termine
*****/
void inOrdenP(tNodoABB *poste, int &k) {
    if (poste == NULL) return;
    inOrdenP(poste->izq, k); 
    k += 1;
    inOrdenP(poste->der, k); 
}

/*****
* void PARAR_PROGRAMA
******
* Muestra en pantalla la cantidad de postes encendidos, libera la memoria del árbol y termina el programa
******
* Input:
    * tNodoABB *raiz: Puntero a la raíz del árbol
    * tABB& arbol: Dirección de memoria del árbol binario de búsqueda
******
* Returns:
    * No hay return al ser función void
*****/
void PARAR_PROGRAMA (tNodoABB *raiz, tABB& arbol) {
    int k = 0;
    if (raiz != NULL){ 
        inOrdenP(raiz, k);
    }
    cout << k << endl;
    arbol.clear();
    abort();

}