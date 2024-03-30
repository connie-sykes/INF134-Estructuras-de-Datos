#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

struct HeapStruct {
    int prioridad;
    string ID;
    string comando;

    HeapStruct() : prioridad(0), ID(""), comando("") {}

    HeapStruct(int p, const string& id, const string& cmd)
        : prioridad(p), ID(id), comando(cmd) {}
};

class tColaP {
    private:
        HeapStruct* heap;
        int capacidad;
        int size;
    
    /*****
    * void resize
    ******
    * Se utiliza cuando se quieren insertar mas elementos al heap que el tamaño permite, copiando la informacion del heap a uno nuevo con una capacidad suficiente
      para almacenar los datos faltantes, eliminando el anterior y reasignando las variables heap y capacidad al nuevo heap y al nuevo tamano respectvamente
    ******
    * Input:
        * int newcapacidad: Numero entero de la nueva capacidad que se quiere del heap.
    ******
    * Returns:
        * No hay return por ser funcion void
    *****/
    void resize(int newcapacidad) {
        HeapStruct* newHeap = new HeapStruct[newcapacidad];
        for (int i = 0; i < size; i++) {
           newHeap[i] = heap[i];
       }
        delete[] heap;
        heap = newHeap;
        capacidad = newcapacidad;
        }


    /*****
    * void heapflotar
    ******
    * El elemento siendo menor que el padre se intercambian, hasta que se cumpla la propiedad del monticulo, es decir, que 
      el padre sea menor que los hijos.
    ******
    * Input:
        * int index: Entero de la prioridad respectiva del elemento
    ******
    * Returns:
        * No hay return por ser funcion void
    *****/
    void heapflotar(int index) {
        int parentIndex = (index - 1) / 2;

        while (index > 0 && heap[parentIndex].prioridad > heap[index].prioridad) {
            swap(heap[parentIndex], heap[index]);

            index = parentIndex;
            parentIndex = (index - 1) / 2;
        }
    }

    /*****
    * void heaphundir
    ******
    * El elemento, siendo mayor que sus hijos, se intercambia con el hijo menor repetidamente hasta que se cumpla la propiedad del monticulo, es decir,
      que el padre sea menor que los hijos.
    ******
    * Input:
        * int index: Entero de la prioridad respectiva del elemento
    ******
    * Returns:
        * No hay return por ser funcion void
    *****/
    void heaphundir(int index) {
        int menor = index;
        int hijo_izq = 2 * index + 1;
        int hijo_der = 2 * index + 2;

        if (hijo_izq < size && heap[hijo_izq].prioridad < heap[menor].prioridad)
            menor = hijo_izq;

        if (hijo_der < size && heap[hijo_der].prioridad < heap[menor].prioridad)
            menor = hijo_der;

        if (menor != index) {
            swap(heap[index], heap[menor]);

            heaphundir(menor);
        }
    }

public:
    tColaP() : capacidad(10), size(0) {
        heap = new HeapStruct[capacidad];
    }

    ~tColaP() {
        delete[] heap;
    }
    
    /*****
    * int sizeColaP
    ******
    * Obtiene el entero de la cantidad de elementos en la cola de prioridad
    ******
    * Input:
        * No necesita parametros para ser ejecutado
    ******
    * Returns:
        * Retorna la cantidad de elementos en la cola de prioridad
    *****/
    int sizeColaP() {
        return size;
    }
    
    /*****
    * void insertColaP
    ******
    * Inserta un elemento al heap respetando la propiedad del monticulo con la funcion heapflotar. En el caso que la cantidad de elementos sea igual a la capacidad, se llama
      a la funcion resize con el doble de la capacidad.
    ******
    * Input:
        * int p: Numero entero asociado a la prioridad a insertar en el heap
        * const string& id: String asociado al id del elemento a insertar en el heap
        * const string& cmd: String asociado al comando del elemento a insertar en el heap
    ******
    * Returns:
        * No hay retorno al ser funcion void
    *****/
    void insertColaP(int p, const string& id, const string& cmd) {
        if (size == capacidad) {
            resize(capacidad * 2);
        }

        heap[size] = HeapStruct(p, id, cmd);
        heapflotar(size);
        size++;
    }

    /*****
    * int findMin
    ******
    * Obtiene el entero a la raiz del heap
    ******
    * Input:
        * No necesita parametros para ser ejecutado
    ******
    * Returns:
        * Retorna la raiz del heap (el valor minimo)
    *****/
    int findMin() {
        if (size == 0)
            return -1;

        return heap[0].prioridad;
    }

    /*****
    * void pop
    ******
    * Elimina la raiz del heap (el primer elemento), y en caso que al eliminar elementos la cantidad de elementos sea menor a un cuarto de la capacidad del heap, se
      llama a la funcion resize con la mitad de la capacidad.
    ******
    * Input:
        * No necesita parametros para ser ejecutado
    ******
    * Returns:
        * No retorna nada al ser funcion void
    *****/
    void pop() {
        if (size == 0)
            return;

        heap[0] = heap[size - 1];
        size--;
        heaphundir(0);

        if (size < capacidad / 4 && capacidad > 10) {
            resize(capacidad / 2);
        }
    }

    /*****
    * void clearcolaP
    ******
    * Reinicializa el heap eliminandolo y creando uno nuevo
    ******
    * Input:
        * No necesita parametros para ser ejecutado
    ******
    * Returns:
        * No hay return al ser funcion void
    *****/
    void clearcolaP() {
        delete[] heap;
        capacidad = 10;
        size = 0;
        heap = new HeapStruct[capacidad];
    }

    /*****
    * void removeMin
    ******
    * Es una funcion auxiliar; llama a la funcion pop
    ******
    * Input:
        * No necesita parametros para ser ejecutado
    ******
    * Returns:
        * No hay return al ser funcion void
    *****/
    void removeMin() {
        pop();
    }

    /*****
    * string& getID(int index)
    ******
    * Obtiene el ID del elemento en ese indice
    ******
    * Input:
        * int index: Índice del elemento a consultar
    ******
    * Returns:
        * Retorna el ID del elemento
    *****/
    string& getID(int index) {
        return heap[index].ID;
    }

    /*****
    * string& getComando(int index)
    ******
    * Obtiene el comando del elemento en ese indice
    ******
    * Input:
        * int index: Índice del elemento a consultar
    ******
    * Returns:
        * Retorna el comando del elemento
    *****/
    string& getComando(int index) {
        return heap[index].comando;
    }

    /*****
    * int getPrioridad
    ******
    * Obtiene la prioridad del elemento en ese indice
    ******
    * Input:
        * int index: Índice del elemento a consultar
    ******
    * Returns:
        * Retorna la prioridad del elemento
    *****/
    int getPrioridad(int index) {
        return heap[index].prioridad;
    }

};
tColaP colaP;
tColaP auxcolaP;

/*****
* void PUSHCOMMAND
******
* Inserta un elemento al heap
******
* Input:
    * int prioridad: Numero entero de la prioridad del elemento
    * string ID : ID del elemento 
    * string comando: Comando del elemento
******
* Returns:
    * No hay return por ser funcion void
*****/
void PUSHCOMMAND(int prioridad, string ID, string comando) {
    colaP.insertColaP(prioridad, ID, comando);
    cout << colaP.sizeColaP() << " PENDING" << endl;
}

/*****
* void GET
******
* Obtiene y remueve las id solicitadas del auxiliar del heap y después obtiene y remueve los comandos solicitados del heap
******
* Input:
    * int N : Cantidad de comandos a solicitar
    * int &SENT : Referencia a un contador de la cantidad de comandos impresos
******
* Returns:
    * No hay return por ser funcion void
*****/
void GET(int N, int &SENT) {

    if (colaP.findMin() == -1) {
        cout << "0" << endl;
        return;
    }
    int c = 0;
    auxcolaP.clearcolaP();
    
    while (colaP.sizeColaP() > auxcolaP.sizeColaP()) {
        auxcolaP.insertColaP(colaP.getPrioridad(c), colaP.getID(c), colaP.getComando(c));
        c+=1;
    }

    c = 0;
    int h = 0;

    cout << N;
    if (colaP.sizeColaP() < N) {
        while (c < colaP.sizeColaP()) {
            cout << " " << auxcolaP.getID(0);
            auxcolaP.removeMin();
            h+=1;
            c+=1;
        }
    }
    else if (colaP.sizeColaP() >= N) {
        while (c < N) {
            cout << " " << auxcolaP.getID(0);
            auxcolaP.removeMin();
            c+=1;
        }
        h = N;
    }
    cout <<" \n";

    int saltos_extra = N-h;
    c = 0;
    if (saltos_extra > 0) {
        while (c < h) {
            cout << colaP.getComando(0) << endl;
            colaP.removeMin();
            c+=1;
        }
        while (saltos_extra > 0) {
            cout <<'\n';
            saltos_extra-=1;
        }
        SENT += h;
    }
    else if (saltos_extra == 0) {
        while (c < N) {
            cout << colaP.getComando(0) << endl;
            colaP.removeMin();
            SENT+=1;
            c += 1;
        }
    }
}

/*****
* void TERMINATE
******
* Imprime la cantidad de comandos impresos seguido de los comandos que ingresaron en total, para luego finalizar el programa.
******
* Input:
    * int i: Entero de la cantidad de comandos impresos en total
    * int j: Entero de la cantidad de comandos ingresados en total
******
* Returns:
    * No hay return al ser funcion void
*****/
void TERMINATE(int i, int j) {
    cout << i << " sent " << j << " created" << endl;
    auxcolaP.~tColaP();
    colaP.~tColaP();
    abort();

}
