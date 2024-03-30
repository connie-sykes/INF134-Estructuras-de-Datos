#include <string>
using namespace std;

typedef char tElemLista;

struct tNodo{
 tElemLista info;
 tNodo* sig;
};

class tLista {
private:
    tNodo* head;
    tNodo* tail;
    tNodo* curr;
    unsigned int listSize;
    unsigned int pos;

public:
    tLista();
    ~tLista();
    void insertar(unsigned int i, tElemLista elem);
    void borrar(unsigned int i);
    void intercambiar(unsigned int i, tElemLista elem);
    tElemLista getvalue();
    void moveToStart();
    void next();
    void clear();
    unsigned int getSize();
};