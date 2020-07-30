
#include <cstdlib>
#include <iostream>
#include <time.h>
#include<string.h>
using namespace std;

#define COLUMNAS 6
#define FILAS 6
#define NO_MINAS -2
#define SI_MINAS -1
#define SIN_JUGAR -3
/*
0 pierde
1 gana
2 esta en juego
*/
//Matriz para mostrar las minas y las contidad de minas alrededor
int Celda[FILAS][COLUMNAS],condicionJugador=2;
bool Estado[FILAS][COLUMNAS];//Estado de la celdas (logica)
//Matriz para mostrar los caracteres de X y -1(Casilla cerrda o casilla abierta)
char MostrarCelda[5][5][5];

void CargarMatrices(){
    for(int fila = 1; fila < FILAS; fila++){
        for(int columna = 1; columna < COLUMNAS; columna++){
            Celda[fila][columna] = NO_MINAS;//Toda la tabla no se agregan minas
            Estado[fila][columna] = false; //No se ha jugado la celdas
}}}

void PonerMinas(int CantidadMinas){
    int contador=0;// contador de las minas
    while( contador <= CantidadMinas){
        Celda[1+rand()%FILAS-1][1+rand()%COLUMNAS-1] = SI_MINAS;//Poner las minas de forma aleatoria en la tabla
        contador++;
}}

void MostrarTabla(){
    cout << "\n    1  2  3  4  5  \n" << endl;//Referencia de la columna
    for(int fila = 1; fila < FILAS; fila++){
        cout << " " << fila << " ";//Referencia de las filas
        for(int columna = 1; columna < COLUMNAS; columna++){
            if( Estado[fila][columna]==true ){
                if( Celda[fila][columna] == SI_MINAS){ cout<<strcpy(MostrarCelda[fila][columna],"-1 ");}
                else{ cout << " " << Celda[fila][columna] << " "; }}
            else{ cout<<strcpy(MostrarCelda[fila][columna]," X "); }}
        cout <<"\n\n";
}}

//retorna el numero de minas que estan alrededor de la celda
int contarMinas(int x, int y){
    int Minas = 0;
    for(int i = x-1; i < x+2; i++){
        for(int j = y-1; j < y+2; j++){
            if( i > 0 && i < FILAS && j > 0 && j < COLUMNAS ){
                if( Celda[i][j] == SI_MINAS){ //Existe mina
                    Minas++;
                }}}}
    return Minas;
}

void NumeroMinasCercanas(){
    int  numero;
    for(int x = 1; x < FILAS; x++){
        for(int y = 1; y < COLUMNAS; y++){
            if( Celda[x][y] == NO_MINAS){ //no tiene mina
                numero = contarMinas(x,y);//Se manda a contar la minas alrededor
                Celda[x][y] = numero;//La celda se cargar con el numero de minas alrededor
            }}}}

//Cuenta las celdas abiertas
int contarCeldas(){
    int numero = 0;
    for(int fila = 1; fila < FILAS; fila++){
        for(int columna = 1; columna < COLUMNAS; columna++){
            if ( Celda[fila][columna]==true){
                numero++;
            }}}
    return numero;
}

//Metodo para abrir una celda
void NumeroCelda(int x, int y){
    if( x >= 0 && x < FILAS && y >= 0 && y < COLUMNAS ){
        Estado[x][y] = true;//Estado abierta
        if( Celda[x][y] == SI_MINAS){
            condicionJugador = 0;
            MostrarTabla();
        }else if( Celda[x][y] == 0){//Cero minas alrededor
            for(int fila = x-1; fila < x+2; fila++){
                for(int columna = y-1; columna < y+2; columna++){
                    if( fila >0 && fila < FILAS && columna > 0 && columna < COLUMNAS ){
                        if( Celda[fila][columna] == 0 && !Estado[fila][columna]){ NumeroCelda(fila,columna); /*Existe Mina*/ }
                        else{ Estado[fila][columna] = true; }
}}}}}}

int main() {
    int NMinas = 12,Fila,Columna,NCasillas;

    condicionJugador = 2;//Estado jugando
    NCasillas = 0;

    CargarMatrices();

    srand ( time(NULL) );
    PonerMinas( NMinas );//Agregamso las minas
    NumeroMinasCercanas();//Contamos las minas al rededor

    while( condicionJugador == 2){ //Condicion del juego
        MostrarTabla();//Mostramos el los estados de la celdas
        cout << "\nIngrese el numero de Fila: ";cin >> Fila;//Se pide la fila
        cout << "Ingrese el numero de la Columna: ";cin >> Columna;//Se pide la columna
        /*
        Se llama al metodo que sirve para abrir la celda 
        de acuerdo a la fila y columna ingresada
        */
        NumeroCelda(Fila,Columna);
        system("cls");
        NCasillas = contarCeldas();//Se cuentan las celdad abiertas
        //Se compara so el el numero de celdas abiertas es igual a total de celdas sin incluir la cantidad de minas
        if( NCasillas == ( FILAS*COLUMNAS - NMinas) ){
            condicionJugador = 1;//Estado gana
    }}

    if( condicionJugador == 0){
        MostrarTabla();
        cout << "Perdiste, Encontraste una mina" << endl;
    }else if (condicionJugador==1){
        MostrarTabla();
        cout << "Felicitaciones eres un crack, Has ganado el Juego" << endl;
    }
        system("pause");
        system("cls");
    return 0;
}
/*
Este juego fue desarrollado por los estudiantes:
>>Royner Oporta Meza.
>>Rene Francisco Ramos Lazo.
*/
