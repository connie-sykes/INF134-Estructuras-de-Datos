#include "TDALogin.hpp"
#include <iostream>

TDALogin::TDALogin() {
    tabla = new ranura[M];
    for (int i = 0; i < M; i++) {
        tabla[i].usuario = "";
        tabla[i].clave = "";
    }
    cantidad_elementos=0;
    factor_carga_maximo=0.7;
}
/*****
* Constructor TDALogin()
******
* Constructor de la clase TDALogin el cual asigna memoria dinámica a la tabla que se construirá, inicializa las ranuras vacías, además inicia un contador de los elementos
que se encontrarán dentro de la tabla y le da un valor límite al factor de carga máximo que se puede llegar a obtener.
******
* Input:
* Ninguno.
******
* Returns:
* No tiene retorno.
*****/

TDALogin::~TDALogin() {
    delete[] tabla;
}
/*****
* Destructor ~TDALogin()
******
* Destructor de la clase TDALogin, este elimina la tabla generada y libera la memoria asignada.
******
* Input:
* Ninguno.
******
* Returns:
* No tiene retorno.
*****/

int TDALogin::p(tipoUsser k, int i) {
    return i;
}
/*****
* int p()
******
* Es una función de dispersión que se utiliza para calcular la posición en la tabla hash donde se almacenará el usuario que se le pasa por parámetro.
******
* Input:
* tipoUsser k: corresponde al usuario al cual se le quiere realizar la acción, este forma parte de un struct, los cuales conforman las ranuras de la tabla.
* int i: entero el cual se le suma a la posición inicial del usuario. 
******
* Returns:
* int, retorna un valor entero, el cual es sumado a la posición inicial del tipoUsser usuario.
*****/
int TDALogin::h(string x) {
    int sum;
    unsigned int i;
    for (sum = 0, i = 0; i < x.length(); i++)
        sum += (int) x[i];
    return sum;
}
/*****
* int h()
******
* Es una función de dispersión que se utiliza para convertir una cadena x en un número entero que se utilizará como índice en la tabla hash.
* se recorre cada carácter de la cadena x y se suma su valor numérico al valor acumulado sum. El valor numérico de cada carácter se obtiene 
* mediante la conversión explícita a entero (int) x[i].
******
* Input:
* string x: corresponde al usuario que se quiere consultar.
******
* Returns:
* int, retorna la suma de los valores numéricos de cada carácter.
*****/
void TDALogin::rehash(){
    int nuevoM=M*2;
    ranura *nueva_tabla= new ranura[nuevoM];
    for (int i = 0; i < M; i++) {
        if (tabla[i].usuario != "") {
            int indice = h(tabla[i].usuario) % nuevoM;
            while (nueva_tabla[indice].usuario != "") {
                indice = (indice + 1) % nuevoM;
            }
            nueva_tabla[indice].usuario = tabla[i].usuario;
            nueva_tabla[indice].clave = tabla[i].clave;
        }
    }
    delete [] tabla;
    tabla=nueva_tabla;
    M=nuevoM;
}
/*****
* void rehash()
******
* Es una función la cual crea una nueva tabla duplicando el tamaño de la tabla anterior y copia los valores de la antigua tabla hacia la nueva tabla cuando el factor
* de carga de la tabla original es mayor a 0.7.
******
* Input:
* No tiene parámetros.
******
* Returns:
* No tiene retorno.
*****/
bool TDALogin::iniciar_sesion(string usuario, string clave) {
    int pos = h(usuario);
    int pos_inicial = pos;
    while (tabla[pos].usuario != "") {
        if (tabla[pos].usuario == usuario) {
            if (tabla[pos].clave == clave) {
                cout << "Sesion iniciada con exito" << endl;
                return true;
            } else {
                cout << "La clave ingresada no coincide" << endl;
                return false;
            }
        }
        pos = (pos + p(usuario, 1)) % M;
        if (pos == pos_inicial) break;
    }
    cout << "El usuario no se encuentra registrado" << endl;
    return false;
}
/*****
* bool iniciar_sesion()
******
* Se determina la posición inicial en la tabla hash utilizando una función de dispersión h() que toma como entrada el nombre de usuario -usuario-, se inicia 
* un bucle while que recorre los elementos de la tabla hash a partir de la posición inicial. En cada iteración del bucle, se comprueba si el elemento actual contiene el 
* nombre de usuario -usuario- y la clave -clave- proporcionada. Si se encuentra un elemento que corresponde al nombre de usuario y la clave proporcionados, se muestra 
* un mensaje de éxito y se devuelve true. Si la clave no coincide, se muestra un mensaje de error y se devuelve false. Si no se encuentra un elemento que corresponde al 
* nombre de usuario proporcionado, se muestran un mensaje de error y se devuelve false.
******
* Input:
* string usuario: usuario el cual se quiere consultar, si está registrado, se verificará que su contraseña sea la misma.
* string clase: corresponde a la contraseña que se quiere consultar, si es igual a la registrada, se accede a la sesión.
******
* Returns:
* bool, devuelve true o false dependiendo de lo solicitado, si el usuario está registrado y la contraseña pasada por parametro corresponde, devuelve true, en el caso
* contrario, false.
*****/

bool TDALogin::crear_nuevo_usuario(string usuario, string clave) {
    if (usuario.length()>32) return false;
    int pos = h(usuario);
    int pos_inicial = pos;
    while (tabla[pos].usuario != "") {
        if (tabla[pos].usuario == usuario) {
            cout << "El usuario ya se encuentra registrado" << endl;
            return false;
        }
        pos = (pos + p(usuario, 1)) % M;
        if (pos == pos_inicial) break;
    }
    if (clave.length() < 8) {
        cout << "La clave debe tener al menos 8 caracteres" << endl;
        return false;
    }
    tabla[pos].usuario = usuario;
    tabla[pos].clave = clave;
    cantidad_elementos++;
    float factor_carga= (float) cantidad_elementos/M;
    if (factor_carga > factor_carga_maximo) {
            rehash();
        }
    cout << "Usuario registrado con exito" << endl;
    return true;
}
/*****
* bool crear_nuevo_usuario()
******
* Se verefica que la longitud del usuario no sobrepase los 32 caracteres, si es afirmativo, se retorna false. Posteriormente se determina la posición inicial en la tabla hash 
* utilizando una función de dispersión h() que toma como entrada el nombre de usuario -usuario-. Se inicia un bucle while que recorre los elementos de la tabla hash a partir 
* de la posición inicial. En cada iteración del bucle, se comprueba si el elemento actual contiene el nombre de usuario -usuario-. Si se encuentra un elemento que corresponde 
* al nombre de usuario proporcionado, se muestra un mensaje de error y se devuelve false. Si no se encuentra un elemento que corresponde al nombre de usuario proporcionado, se 
* comprueba  si la longitud de la clave proporcionada es menor que 8 caracteres. En caso afirmativo, se muestra un mensaje  de error y se devuelve false. Si la longitud de la 
* clave es suficiente, se almacena el nombre de usuario y la clave en la tabla hash en la posición correspondiente. También se actualiza la cantidad de elementos en la tabla y 
* se comprueba si el factor de carga de la tabla supera un umbral predeterminado. Si el factor de carga es demasiado alto, se realiza una reorganización de la tabla utilizando 
* la función rehash().
******
* Input:
* string usuario: usuario el cual se quiere consultar, si no está registrado, se registrará en la tabla.
* string clase: corresponde a la contraseña que se quiere consultar, si es superior a 8 caracteres, se registra.
******
* Returns:
* bool, devuelve true o false dependiendo de lo solicitado, si el usuario no estaba registrado, lo registra y devuelve true, en el caso
* contrario, false. Además, si la contraseña no supera los 8 caracteres, devuelve false.
*****/
bool TDALogin::cambiar_clave(string usuario, string nueva_clave) {
    int pos = h(usuario);
    int pos_inicial = pos;
    while (tabla[pos].usuario != "") {
        if (tabla[pos].usuario == usuario) {
            if (nueva_clave.length() < 8) {
                cout << "La clave debe tener al menos 8 caracteres" << endl;
                return false;
            }
            tabla[pos].clave = nueva_clave;
            cout << "Clave actualizada con exito" << endl;
            return true;
        }
        pos = (pos + p(usuario, 1)) % M;
        if (pos == pos_inicial) break;
    }
    cout << "El usuario no se encuentra registrado" << endl;
    return false;
}
/*****
* bool cambiar_clave()
******
* Se determina la posición inicial en la tabla hash utilizando una función de dispersión h() que toma como entrada el nombre de usuario -usuario-. Se inicia un bucle while que 
* recorre los elementos de la tabla hash a partir de la posición inicial. En cada iteración del bucle, se comprueba si el elemento actual contiene el nombre de usuario -usuario-.
* Si se encuentra un elemento que corresponde al nombre de usuario proporcionado, se comprueba si la longitud de la nueva clave es menor que 8 caracteres. En caso afirmativo, se 
* muestra un mensaje de error y se devuelve false. Si la longitud de la nueva clave es suficiente, se actualiza la clave almacenada en la tabla hash en la posición correspondiente y 
* se muestra un mensaje de éxito, devuelve true. Si no se encuentra un elemento que corresponde al nombre de usuario proporcionado, se muestra un mensaje de error y se 
* devuelve false.
******
* Input:
* string usuario: usuario el cual se quiere actualizar, si está registrado, se verificará que la contraseña cumpla con los requisitos.
* string clase: corresponde a la contraseña que se quiere actualizar, si es cumple con los requisitos, se actuliza el la contrasEna del usuario.
******
* Returns:
* bool, devuelve true o false dependiendo de lo solicitado, si el usuario está registrado y la contraseña cumple los requisitos, devuelve true, en el caso
* contrario, false.
*****/