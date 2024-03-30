#include <string>
#include <iostream>

using namespace std;

typedef string tipoUsser;
typedef string tipoClave; 

struct ranura {
 tipoClave clave;
 tipoUsser usuario;
};

class TDALogin{
    private:
        ranura* tabla;
        int M=32;
        int h(string clave);
        int p(tipoUsser k, int i);
        int cantidad_elementos;
        float factor_carga_maximo;
        void rehash();
    public:
        TDALogin();
        ~TDALogin();
        bool iniciar_sesion(string usuario, string clave);
        bool crear_nuevo_usuario(string usuario, string clave);
        bool cambiar_clave(string usuario, string nueva_clave);

};
