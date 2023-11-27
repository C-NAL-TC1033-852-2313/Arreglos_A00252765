#include <iostream>
#include <fstream>
using namespace std;
#include "Vendedor.h"


int buscaDepartamento(Depto listaDept[], int cantDept, int idDeptoABuscar) {
    /*Función que busca un id de un departamento en el arreglo de departamentos
    si lo encuentra que regrese la posición del arreglo donde está, si no regresa -1*/
    for (int cont = 0; cont < cantDept; cont++) {
        if (listaDept[cont].getIdDep() == idDeptoABuscar) {
            return cont; // ya encontré la posición del departamento
        }
    }
    // si sale del for, quiere decir que no existe porque si exisiera se hubiera regresado adentro del for
    cout << "Departamento incorrecto" << endl;
    return -1;
}

string nombreDepartamento(Depto listaDept[], int cantDept, int idDeptoABuscar) {
    /*Función que busca un id de un departamento en el arreglo de departamentos
      si lo encuentra que regrese el nombre del departamento, si no lo encuentra regresa ""*/
    
    return "";
}

void cargaDatosDepartamentos(Depto listaDeptos[], int& cantDeptos) {
    /*Carga datos del archivo Deptos.txt en listaDeptos y cantDeptos lo actualiza
      con el número de departamentos cargados del archivo*/
    int numDepartamento;
    string nombreDepartamento;
    ifstream archivo;
    archivo.open("Deptos.txt");
    if(archivo.is_open()){
        while(archivo >> numDepartamento >> nombreDepartamento){
            listaDeptos[cantDeptos].setIdDep(numDepartamento);
            listaDeptos[cantDeptos].setNombre(nombreDepartamento);
            cantDeptos++;
        }
    }
    else{
        cout << "El archivo no se pudo abrir" << endl;
    }
}

void muestraDepartamentos(Depto listaDept[], int cantDep) {
    /*Muestra la lista de departamentos*/
    cout << "Departamentos de la tienda" << endl;
    for (int cont = 0; cont < cantDep; cont++) {
        listaDept[cont].imprime();
    }
}
    

void cargaDatosVendedores(Vendedor listaVend[], int &cantVend, Depto listaDep[], int cantDep) {
    /* Función que regresa la listaVend y la cantVend con datos recibe el arreglo vacío
       y la variable cantVend sin inicializar y les pone valor en esta función*/
    int idDep;
    string nom;
    double vent;
    int num;
    cout << "Cuantos vendedores? ";
    cin >> cantVend;
    for (int cont = 0; cont < cantVend; cont++) {
        cout << "Teclea el nombre ";
        cin.ignore();
        getline(cin,nom);
        cout << "Teclea las ventas ";
        cin >> vent;
        do{
            cout << "ID del departamento: ";
            cin >> idDep;
            num = buscaDepartamento(listaDep, cantDep, idDep);
        }while(num == -1);
        listaVend[cont].setNombre(nom);
        listaVend[cont].setVentas(vent);
        listaVend[cont].setDepartamento(listaDep[num]);
    }
}

void cargaVendedoresArchivo(Vendedor listaVend[], int &cantVend, Depto listaDep[], int cantDep){
    string nom;
    int id, pos;
    double vent;
    ifstream archivo;
    archivo.open("vendedores.txt");
    if(archivo.is_open()){
        while(archivo >> nom >> vent >> id){
            listaVend[cantVend].setNombre(nom);
            listaVend[cantVend].setVentas(vent);
            pos = buscaDepartamento(listaDep, cantDep, id);
            listaVend[cantVend].setDepartamento(listaDep[pos]);
            cantVend++;
        }
    }
    else{
        cout << "Archivo no encontrado" << endl;
    }

}

void muestraVendedores(Vendedor listaVen[], int cantVen) {
    /*Muestra la lista de vendedores*/
    for (int cont = 0; cont < cantVen; cont++) {
        listaVen[cont].imprime();
    }
}


void vendedoresPorDepartamento(Vendedor listaVen[], int cantVend, int idDeptoAConsultar) {
    /* Muestra los nombres de los vendedores de un departamento */
    for(int i=0; i<cantVend; i++){
        if(listaVen[i].getDepartamento().getIdDep() == idDeptoAConsultar){
            cout << listaVen[i].getNombre() << endl;
        }
    }
    
}

int registrarVentas(Vendedor listaVend[], int cantVend) {
    /* Registra las ventas de un vendedor de la lista de vendedores existentes
       suma las ventas nuevas a las que ya estaban registradas */
}

int main() {
    const int MAX = 10;
    char opcion;
    int numDepto;
    Vendedor listaVendedores[MAX];
    int cantVendedores = 0;  // cantidad de empleados en la lista de empleados
    Depto listaDeptos[MAX]; // inicio el arreglo con Deptos default.
    int cantDeptos = 0;  // cantidad de departamentos en la lista de deptos
    cargaDatosDepartamentos(listaDeptos, cantDeptos);
    //cargaDatosVendedores(listaVendedores, cantVendedores, listaDeptos, cantDeptos);
    cargaVendedoresArchivo(listaVendedores, cantVendedores, listaDeptos, cantDeptos);
    do {
        cout << endl;
        cout << "Opciones disponibles " << endl;
        cout << " 1) Ver la lista de Departamentos " << endl;
        cout << " 2) Ver la lista de Vendedores " << endl;
        cout << " 3) Consultar vendedores de un departamento " << endl;
        cout << " 4) Registrar ventas "<< endl;
        cout << " 5) Terminar " << endl;
        cin >> opcion;
        switch (opcion) {
            case '1':
                muestraDepartamentos(listaDeptos, cantDeptos);
                cin.ignore();
                cout << "Enter para continuar...";
                cin.get();
                break;
            case '2':
                muestraVendedores(listaVendedores, cantVendedores);
                cin.ignore();
                cout << "Enter para continuar...";
                cin.get();
                break;
            case '3': 
                cout << "Teclea el departamento que quieres consultar " << endl;
                cin >> numDepto;
                vendedoresPorDepartamento(listaVendedores, cantVendedores, numDepto);
                cin.ignore();
                cout << "\nEnter para continuar...";
                cin.get();
                break;
            case '4': 
                registrarVentas(listaVendedores, cantVendedores);
                cin.ignore();
                cout << "Enter para continuar...";
                cin.get();
                break;
            case '5':
                cout << "Elegiste salir del programa..."<< endl;
                break;
            default:
                cout << "Opcion invalida"<<endl;
        }
        system("clear");
    } while (opcion != '5');
    return 0;
}