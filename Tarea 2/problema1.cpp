#include "Secuencia_de_Nucleotidos.hpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){
    int l,k,m,u,j;
    string secuencia_base;
    ifstream f1;
    f1.open ("secuencias-nucleotidos.txt",ios::in);
    if (f1.is_open()){
        f1>>l>>secuencia_base;
        ofstream f2("secuencias-reconstruidas.txt");
        f1>>k;
        for (u=0; u<k;u++){
            tLista lista;
            for (int i=0;i<l;i++){
                lista.insertar(i, secuencia_base[i]);
            }
            f1>>m;
            for (j=0;j<m;j++){
                string mod;
                unsigned int posi;
                char letra;
                f1>>mod>>posi;
                if (mod=="INSERTAR"){
                    f1>>letra;
                    lista.insertar(posi,letra);
                } else if (mod== "INTERCAMBIAR"){
                    f1>>letra;
                    lista.intercambiar(posi,letra);
                } else if (mod=="BORRAR"){
                    lista.borrar(posi);
                }
            }
            lista.moveToStart();
            string result="";
            for (unsigned int i = 0; i < lista.getSize(); i++) {
                result+=lista.getvalue();
                lista.next();
            }
            f2<<result<<endl;
        }
        f1.close();
        f2.close();
    } else{
        cout << "Error al abrir el archivo" << endl;
    }
    return 0;
}