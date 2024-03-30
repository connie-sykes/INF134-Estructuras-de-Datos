#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;
//Datos del problema a resolver:
int const SERV_DESAYUNO = 0;
int const SERV_ALMUERZO = 1;
int const SERV_ONCE = 2;
int const SERV_CENA = 3;

struct SaldoColaborador {//Struct correspondiente a cada colaborador
    char rut [11];
    int saldo_desayuno ;
    int saldo_almuerzo ;
    int saldo_once ;
    int saldo_cena ;
};
/*****
* bool puedeConsumir
******
* Esta función permite recorrer dos archivos, uno ASCII y el otro binario, los cuales contienen el rut, consumos diarios y saldos
  de cada colaborador respectivamente, el programa verifica si el rut que pasan por parámetro existe dentro de saldos.bin, si existe, 
  se devuelve el rut, en caso contrario, se devuelce un string vacío y automaticamente la transacción es rechazada.
  Al recorrer consumos_dia, analiza cada consumo hecho por los colaboradores y en el caso de que estos coincidan con sus parametros 
  entregados, guarda en una variable cada ticket (desayuno, almuerzo, once o cena) ya utilizado. 
  Posteriormente, utilizando saldos.bin, consulta el saldo de cada colaborador y verifica si este es capaz de consumir lo que está 
  solicitando, si su saldo es mayor a la cantidad de tickets ya consumidos, podrá obtener un nuevo ticket, en el caso contrario, se 
  le niega. Si la transacción es completada efectivamente, a consumos.txt se le agregará su rut y el nuevo consumo.
******
* Input:
* char* rut: Un string con el rut del colaborador a evaluar, en formato NNNNNNNN-D con cada N siendo un número del
* 0 al 9 y D un número del 0 al 9 o la letra k
* int servicio: un entero del 0 al 3 correspondiente a una de las constantes asociadas a cada consumo (desayuno, almuerzo, once y cena)
* string consunos_dia: Un string con el nombre del archivo que contiene los consumos realizados por cada colaborador.
******
* Returns:
* bool resultado: retorna falso en el caso de que la transacción se haya rechazado y true en el caso contrario. Si su saldo
* es mayor a la cantidad de tickets ya consumidos, relsutado=true, en el caso contrario o que no exista registro del rut consultado, 
* resultado=false.
*****/

bool puedeConsumir(char* rut, int servicio, string consumos_dia){
    bool resultado=false;
    bool encontrado= false;
    string servicio_selec;
    if (servicio==0){
        servicio_selec="DESAYUNO";
    } else if (servicio == 1){
        servicio_selec="ALMUERZO";
    } else if (servicio==2){
        servicio_selec="ONCE";
    } else if(servicio==3){
        servicio_selec="CENA";
    }int n,i;
    ifstream f1;
    f1.open("saldos.bin",ios::binary);
    f1.read((char*)&n,sizeof(int));
    SaldoColaborador *colaborador= new SaldoColaborador[n];
    int saldo;
    string rut_consumidor, servicio_consumidor;
    fstream f2;
    f2.open(consumos_dia,ios::in|ios::app);
    int cantidad_consumos=0;
    while (f2 >> rut_consumidor >> servicio_consumidor) {
        if(rut_consumidor==rut && servicio_consumidor==servicio_selec){
            cantidad_consumos++;
        }
    }
    for (i=0;i<n; i++){
        f1.read((char*)&colaborador[i],sizeof(SaldoColaborador));
        if (strcmp(colaborador[i].rut,rut)==0){
            encontrado=true;
            if(servicio==0){
                saldo= colaborador[i].saldo_desayuno;
            }else if(servicio==1){
                saldo= colaborador[i].saldo_almuerzo;
            }else if(servicio==2){
                saldo= colaborador[i].saldo_once;
            }else if(servicio==3){
                saldo= colaborador[i].saldo_cena;
            }
            break;
        }
    }
    if(encontrado==true){
        cout<<rut<<endl;
    }else{
        cout<<" "<<endl;
        return false;
    }
    if(cantidad_consumos>=saldo){
        resultado= false;
    }else{
        ofstream consumo_salida_out(consumos_dia,ios::app);
        consumo_salida_out<< rut <<' '<<servicio_selec<<endl;
        resultado= true;
        consumo_salida_out.close(); 
    }               
    f1.close();
    f2.close();
    return resultado;
}


int main(){
    char rut[] = "33333333-3";
    int servicio = 3;
    string consumos_dia = "consumos.txt";
    bool prueba = puedeConsumir(rut,servicio, consumos_dia);
    if (prueba){
        cout<<"Puede consumir"<<endl;
    }else{
        cout<<"No puede consumir"<<endl;
    }
    return 0;
}