//Ejercicio #3 – Laberinto 

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

using namespace std;

#define MAX 7
//prtotipos de funciones
void crearMatriz();
int laberinto(int M[MAX][MAX], int *posF, int *posC);

int main() {
    int M[MAX][MAX], posF=0, posC=0, suma=0;
    crearMatriz();  // Crear la matriz
    ifstream entrada("entrada.txt");    //abrir el archivo de entrada
    ofstream salida("salida.txt");  //crear o abrir el archivo de salida

    if (!entrada.is_open() || !salida.is_open()) {  //verificar si se abrieron correctamente
        cout << "Error al abrir los archivos." << endl;
        return 1;
    }
    cout << "Matriz:" << endl; // Imprimir en pantalla
    salida << "Matriz:" << endl; // Imprimir en el archivo de salida
    for(int i = 0; i < MAX; i++){
        for(int j = 0; j < MAX; j++){
            entrada >> M[i][j]; // Leer la matriz del archivo de entrada
            cout << M[i][j] << " ";   // Mostrar la matriz en pantalla
            salida << M[i][j] << " "; // Mostrar la matriz en el archivo de salida
        }
        cout << endl;    
        salida << endl;  // endl en el archivo de salida
    }
    cout << endl; 

    suma = laberinto(M, &posF, &posC); // Llamar a la funcion laberinto
    cout << "Suma del recorrido: " << suma << endl;
    cout << "Posicion final: (" << posF + 1 << ", " << posC + 1 << ")" << endl;
    salida << "Suma del recorrido: " << suma << endl;   // Imprimir la suma en el archivo de salida
    salida << "Posicion final: (" << posF + 1 << ", " << posC + 1 << ")" << endl;   // Imprimir la posicion final en el archivo de salida

    entrada.close();    //cerrar el archivo de entrada
    salida.close();     //cerrar el archivo de salida

    return 0;
}

//funcion para crear una matriz de aleatorios en un archivo de texto
void crearMatriz() {
    srand(time(NULL));
    ofstream archivo("entrada.txt");    // Crear o abrir el archivo de entrada

    if (!archivo.is_open()) {   // Verificar si se pudo abrir el archivo
        cout << "No se pudo crear el archivo de entrada" << endl;
        exit(1);    // Salir si no se pudo abrir el archivo
    }
    // Llenar la matriz con numeros aleatorios entre 0 y 5
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            int numero = rand() % 5;  
            archivo << numero << " ";   // Escribir el numero en el archivo
        }
        archivo << endl;    // Nueva linea al final de cada fila
    }

    archivo.close();    // Cerrar el archivo
}
int laberinto(int M[MAX][MAX], int *posF, int *posC) {
    int suma = 0,chacales = 0;
    // Recorre la diagonal principal
    for (int i = 0; i < MAX; i++) {
        suma += M[i][i];
        if (M[i][i] == 0) { // Si encuentra un chacal (0), incrementa el contador
            chacales++;
            if (chacales == 3) {    // Si encuentra 3 chacales, guarda la posicion de filas y de columnas
                *posF = i;
                *posC = i;
                return suma;
            }
        }
    }
    // Recorre la ultima columna (excepto la celda sumada) 
    for (int i = MAX - 2; i >= 0; i--) {
        suma += M[i][MAX - 1];
        if (M[i][MAX - 1] == 0) {
            chacales++;
            if (chacales == 3) {
                *posF = i;
                *posC = MAX - 1;
                return suma;
            }
        }
    }

    // Si no se encontraron 3 chacales, termina en la posicion (1,MAX-1)
    *posF = 0;
    *posC = MAX -1;
    return suma;
}