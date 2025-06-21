//Ejercicio #3 – Laberinto 

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
using namespace std;

#define MAX 7
//prtotipos de funciones
void crearMatriz();
int laberinto(int **, int, int, int*, int*);

// funcion principal
int main() {
    // creacion de matriz con memoria dinamica
    int **M=new int*[MAX];
    for(int i=0; i<MAX; i++){//asignar memoria dinamica a cada fila de la matriz
        M[i]=new int[MAX];
    }
    if(M==NULL){
        cout<<"Error al asignar memoria.";
        return 1;
    }

    //variables para obtener datos
    int posF=0, posC=0, suma=0;

    //llamada a la funcion para crear la matriz
    crearMatriz();

    //abrir el archivo de entrada como lectura
    FILE* entrada= fopen("entrada.txt","r");

    //verificar si el no archivo existe o esta vacio
    if (!entrada) {
        cout << "Error al abrir el archivo de entrada." << endl;
        entrada = fopen("entrada.txt", "w");    // Si no existe, lo crea como sobreescritura
        fclose(entrada);    //cerrar archivo
        cout << "ingrese los datos de la matriz al archivo 'entrada.txt' antes de volver a ejecutar el programa." << endl;
        return 1;
    }

    //crear o abrir el archivo de salida como sobreescritura
    FILE* salida= fopen("salida.txt","w");  

    //verificar si el archivo se abre correctamente
    if (salida==NULL) { 
        cout << "Error al abrir el archivo de salida." << endl;
        return 1;
    }

    cout << "Matriz:" << endl; // Imprimir en pantalla
    fprintf(salida,"Matriz: \n"); //guardar en archivo de salida

    //variables para manejo de filas y de columnas
    int i=0;//Filas
    int j=0;//Columnas

    //ciclo para leer los datos del archivo de entrada
    while (i < MAX && fscanf(entrada, "%d", &M[i][j]) == 1) {
        j++;
        if (j == MAX) {  // Cambiar de fila
            j = 0;  //reiniciar columna
            i++;    //aumentar fila
        }
    }

    //validar si se leyeron todos los datos
    if(i!=MAX){
        cout<<"No se leyeron todos los datos!";
    }
    
    //ciclo para mostrar la matriz de numeros
    for (int x = 0; x <i; x++) {
        for (int y = 0; y < MAX; y++) {
            cout << M[x][y] << " ";//mostrar en pantalla
            fprintf(salida,"%d ", M[x][y]);//guardar datos en el archivo de salida
        }
        // Nueva linea al final de cada fila
        cout << endl;//mostrar en pantalla
        fprintf(salida,"\n"); //guardar en archivo de salida
    }

    //llamada a la funcion laberinto para obtener la suma de la diagonal y de la ultima columna
    suma = laberinto(M, MAX, MAX, &posF, &posC);

    //mostrar datos en pantalla
    cout << "Suma del recorrido: " << suma << endl;
    cout << "Posicion final: (" << posF + 1 << ", " << posC + 1 << ")" << endl;

    //guardar datos en el archivo de salida
    fprintf(salida, "Suma del recorrido: %d\n", suma); 
    fprintf(salida, "Posicion final: (%d,%d)\n" ,posF + 1, posC + 1);
    
    //cerrar archivos
    fclose(entrada);    //cerrar el archivo de entrada
    fclose(salida);     //cerrar el archivo de salida

    //liberar memoria de la matriz y sus filas
    for(int i=0; i<MAX; i++){
        delete[] M[i]; 
    }
    delete[]M;

    return 0;
}

//funcion para crear una matriz de aleatorios en un archivo de texto
void crearMatriz() {
    srand(time(NULL));  //para uso de creacion de numeros aleatorios
    
    //crear o abrir archivo de entrada como sobreescritura
    FILE* entrada=fopen("entrada.txt","w");

    // Verificar si el archivo se abre correctamente
    if (entrada==NULL) {  
        cout << "No se pudo crear el archivo de entrada" << endl;
        return;
    }

    // Llenar la matriz con numeros aleatorios entre 0 y 5 (para que aparezcan mas chacales)
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            int numero = rand() % 5;  
            fprintf(entrada,"%d ",numero);   // Escribir el numero en el archivo
        }
        fprintf(entrada,"\n");  // Nueva linea al final de cada fila del archivo
    }

    //cerrar archivo de entrada
    fclose(entrada);
}
int laberinto(int **M,int ren,int col, int *posF, int *posC) {
    int suma = 0,chacales = 0;
    // Recorre la diagonal principal
    for (int i = 0; i < ren; i++) {
        suma += M[i][i];
        if (M[i][i] == 0) { // Si encuentra un chacal (0), incrementa el contador
            chacales++;
            if (chacales == 3) {    // Si encuentra 3 chacales, guarda la posicion de filas y de columnas
                *posF = i;
                *posC = i;
                return suma;    //retorna suma
            }
        }
    }
    // Recorre la ultima columna de abajo hacia arriba
    for (int i = ren - 2; i >= 0; i--) {    //ren-2 para evitar repetir la esquina
        suma += M[i][col - 1];
        if (M[i][col - 1] == 0) {//si la celda actual encuentra un chacal lo incrementa
            chacales++;
            if (chacales == 3) {// si encuentra 3 harales guarda la posicion y retorna la suma
                *posF = i;
                *posC = MAX - 1;
                return suma;
            }
        }
    }

    // Si no se encontraron 3 chacales, termina en la posicion (1,col-1)
    *posF = 0;
    *posC = col -1;
    return suma;
}