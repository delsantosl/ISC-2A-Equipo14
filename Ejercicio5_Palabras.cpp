// Ejercicio 5 (PALABRAS)

#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
using namespace std;
#define MAX 500

typedef struct {
    int tipo;
    char palabra[20];
    char pista[100];
    char ini[5];
    char fin[5];
} juegoT;

//PROTOPTIPOS

int puntajePalabra(char *cad, juegoT e);
void cargarJuego(FILE *entrada, juegoT A[], int *tam);
bool validarLinea(FILE* entrada, juegoT &aux);
void mezclarArreglo(juegoT A[], int tam);

//MAIN

int main() {
    srand(time(NULL));
    // Abrir el archivo de entrada
    FILE *entrada = fopen("palabras.txt", "r");
    if (!entrada) {
        cout << "No se pudo abrir el archivo de entrada." << endl;
        entrada = fopen("palabras.txt", "w");
        fclose(entrada);
        return 1;
    }
    // Abrir el archivo de salida
    FILE *salida = fopen("resultados.txt", "w");
    if (!salida) {
        cout << "No se pudo abrir el archivo de salida." << endl;
        fclose(entrada);
        return 1;
    }
    juegoT A[100];
    int tam;
    cargarJuego(entrada, A, &tam);
    fclose(entrada);
    mezclarArreglo(A, tam);
    if (tam < 10) {             // Si no hay suficientes palabras validas termina el programa
        cout << "No hay suficientes palabras validas para jugar (minimo 10)." << endl;
        fclose(salida);
        return 1;
    }
    char cad[250];
    int totalPuntos = 0;
    //Juego
    for (int i = 0; i < 10; i++) {       // Mostrar las primeras 10 palabras ya mezcladas
        cout << "Adivina un: ";
        switch (A[i].tipo) {
            case 1: cout << "verbo"; break;
            case 2:cout << "adjetivo"; break;
            case 3:cout << "sustantivo"; break;
        }
        cout << endl;
        cout << "Pista: " << A[i].pista << endl;
        cout << "Ingrese una palabra: ";
        cin >> cad;
        int puntos = puntajePalabra(cad, A[i]);     // Llamar a la funcion para obtener los puntos por la palabra ingresada
        cout << "Puntos: " << puntos << endl << endl;
        totalPuntos += puntos;
        // Guardar resultados en el archivo
        fprintf(salida, "%s,%d\n", cad, puntos);
    }
    cout << "Puntaje total: " << totalPuntos << endl;
    fclose(salida);
    return 0;
}

//FUNCIONES
//Funcion que carga el juego desde el archivo de entrada (pone en un arreglo de estructuras las palabras, pistas, tipo, inicio y fin de cada palabra valida)
void cargarJuego(FILE *entrada, juegoT A[], int *tam) {
    juegoT aux;
    *tam = 0;
    while (!feof(entrada)) {            // Leer hasta el final del archivo
        if (validarLinea(entrada, aux)) {           // Validar la linea leida
            bool repetida = false;              // Variable para verificar si la palabra ya fue ingresada
            for (int i = 0; i < *tam; i++) {
                if (strcmp(A[i].palabra, aux.palabra) == 0) {   // Comparar la palabra ingresada con las palabras ya guardadas
                    repetida = true;                            // Si la palabra ya existe en el arreglo, marcarla como repetida
                    break;                  // Salir del ciclo si se encuentra una palabra repetida
                }
            }
            if (!repetida) {        // Si la palabra no esta repetida
                A[*tam] = aux;      // Si es valida, agregar al arreglo
                (*tam)++;           // Incrementar el tamaño a de los registros validos
            }
        }
    }
}

// Funcion que valida una linea del archivo de entrada y guarda los datos en la estructura aux, verificando si es una linea valida o no
bool validarLinea(FILE* entrada, juegoT &aux) {
    char *tipoTmp = new char[MAX] ();
    char *palabraTmp = new char[MAX] ();
    char *pistaTmp = new char[MAX] ();
    char *iniTmp = new char[MAX] ();
    char *finTmp = new char[MAX] ();
    bool valido = true;
    // Leer una línea del archivo (el int n indica el número de elementos leídos)
    int n = fscanf(entrada, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n",tipoTmp, palabraTmp, pistaTmp, iniTmp, finTmp);  //Leer las partes de la linea separadas por comas (%[^,] lee hasta la coma y [^\n] lee hasta el salto de linea), el \n final es para que no se quede el salto de linea en el buffer
    if (n != 5) {           // Si no se leyeron las 5 partes correctamente
        // Saltar la línea si no se leyeron los 5 elementos
        char noValida[1000];            
        fgets(noValida, 1000, entrada);     //Leer para saltar la linea que no es valida
        valido = false;
    }
    // Validar que la variable tipo contenga solo digitos
    if (valido) {
        for (int i = 0; tipoTmp[i] != '\0'; ++i) {
            if (!isdigit(tipoTmp[i])) {
                valido = false;
                break;
            }
        }
    }
    int tipo = 0;
    if (valido) {                   // Convertir tipoTmp a entero para validar que sea un tipo valido
        tipo = atoi(tipoTmp);
        if (tipo < 1 || tipo > 3) {
            valido = false;
        }
    }
    if (valido) {                 // Validar que las cadenas no esten vacias y que tengan un tamaño adecuado (que no excedan los limites)
        if (strlen(palabraTmp) == 0 || strlen(palabraTmp) > 19 || strlen(pistaTmp) == 0 || strlen(pistaTmp) > 99 || strlen(iniTmp) == 0 || strlen(iniTmp) > 4 || strlen(finTmp) == 0 || strlen(finTmp) > 4 || (strlen(iniTmp) + strlen(finTmp) > strlen(palabraTmp))) {
            valido = false;
        }
    }
    // Validar que iniTmp coincida con el inicio de palabraTmp
    if (valido && strncmp(palabraTmp, iniTmp, strlen(iniTmp)) != 0) {   //strcmp (cadena 1, cadena 2, longitud de caracteres a comparar de ambas cadenas)
        valido = false;
    }
    // Validar que finTmp coincida con el final de palabraTmp
    if (valido) {
        int longPalabra = strlen(palabraTmp);
        int longFin = strlen(finTmp);
        if (longFin > longPalabra || strcmp(palabraTmp + longPalabra - longFin, finTmp) != 0) {
            valido = false;
        }
    }
    // Validar que: palabra, ini y fin no contengan espacios
    if (valido) {
        for (int i = 0; palabraTmp[i]; ++i)
            if (isspace(palabraTmp[i])) valido = false;

        for (int i = 0; iniTmp[i]; ++i)
            if (isspace(iniTmp[i])) valido = false;

        for (int i = 0; finTmp[i]; ++i)
            if (isspace(finTmp[i])) valido = false;

        for (int i = 0; tipoTmp[i]; ++i)
            if (isspace(tipoTmp[i])) valido = false;
    }
    if (valido){                        // Si todo es valido, asignar los valores a la estructura aux
        aux.tipo = tipo;
        strcpy(aux.palabra, palabraTmp);
        strcpy(aux.pista, pistaTmp);
        strcpy(aux.ini, iniTmp);
        strcpy(aux.fin, finTmp);
    }
    delete[] tipoTmp;
    delete[] palabraTmp;
    delete[] pistaTmp;
    delete[] iniTmp;
    delete[] finTmp;
    return valido;
}

// Funcion que calcula el puntaje de la palabra ingresada comparandola con la palabra del juego
int puntajePalabra(char *cad, juegoT e) {
    int puntos = 0;
    // Copias temporales
    char *cadMin = new char[250] ();
    char *palabraMin = new char[20] ();
    char *iniMin = new char[5] ();
    char *finMin= new char[5] ();
    // Copiar las cadenas originales a las temparales para convertir todo a minusculas y comparar (asi no importa si se ingresa la respuesta en mayusculas o minusculas)
    strcpy(cadMin, cad);
    strcpy(palabraMin, e.palabra);
    strcpy(iniMin, e.ini);
    strcpy(finMin, e.fin);
    // Convertir a minsculas
    for (int i = 0; cadMin[i]; i++) cadMin[i] = tolower(cadMin[i]);
    for (int i = 0; palabraMin[i]; i++) palabraMin[i] = tolower(palabraMin[i]);
    for (int i = 0; iniMin[i]; i++) iniMin[i] = tolower(iniMin[i]);
    for (int i = 0; finMin[i]; i++) finMin[i] = tolower(finMin[i]);
    // Obtener las longitudes de las cadenas para compararlas
    int longCad = strlen(cadMin);
    int longIni = strlen(iniMin);
    int longFin = strlen(finMin);

    if (strcmp(cadMin, palabraMin) == 0) {      //si la palabra ingresada es igual a la palabra del juego
        puntos = 10;
    } else if (strncmp(cadMin, iniMin, longIni) == 0) {     //strcmp (cadena 1, cadena 2, longitud de caracteres de ambas cadenas)      compara los primeros caracteres de ambas cadenas
        puntos = 3;
    } else if (strcmp(cadMin + longCad - longFin, finMin) == 0) {   //strcmp (cadena ingresada + longitud de la cadena ingresada - longitud del final (esto son los ultimos longFin caracteres), cadena final)
        puntos = 2;
    }
    return puntos;
}

// Funcion que mezcla el arreglo de estructuras que se usara en el juego para salgan en orden aleatorio
void mezclarArreglo(juegoT A[], int tam) {
    for (int i = tam - 1; i > 0; i--) {     //(Algoritmo de Fisher-Yates) algroitmo para mezclar el arreglo de estructuras y salgan en distinto orden, y en caso de ser mas de 10, que muestre 10 al azar
        int aleatorio = rand() % (i + 1);
        juegoT temp = A[i];             // Copiar A[i] a una variable temporal
        A[i] = A[aleatorio];            // A[i] ahora es el elemento aleatorio
        A[aleatorio] = temp;            // El elemento aleatorio ahora es A[i]
    }
}
