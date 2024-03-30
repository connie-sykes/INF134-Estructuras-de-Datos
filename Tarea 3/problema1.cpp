#include <iostream>
#include <string>
#include "TDALogin.hpp"

using namespace std;

int main() {
    TDALogin login;
    string operacion, usuario, contrasena;
    bool flag=true;

    while (flag) {
        cin >> operacion;
        if (operacion == "INICIAR_SESION") {
            cin >> usuario >> contrasena;
            login.iniciar_sesion(usuario,contrasena);
        } else if (operacion == "REGISTRAR") {
            cin >> usuario >> contrasena;
            login.crear_nuevo_usuario(usuario,contrasena);
        } else if (operacion == "ACTUALIZAR") {
            cin >> usuario >> contrasena;
            login.cambiar_clave(usuario,contrasena);
        } else if (operacion == "FINALIZAR") {
            flag=false;
        }
    }

    return 0;
}