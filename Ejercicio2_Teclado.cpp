// Ejercicio 2  (TECLADO)

#include <iostream>
using namespace std;
#define TAM 250

void transTxt(char* cadEnt);
void mostrar(char* cadSal);

int main() {
    //Abrir el archivo de entrada y en caso de que no exista, lo crea
    FILE *archivo = fopen("entrada.txt", "r");
    if (!archivo) { // Verifica si el archivo no existe o esta vacio
        cout << "Error al abrir el archivo de entrada." << endl;
        archivo = fopen("entrada.txt", "w");    // Si no existe, lo crea
        fclose(archivo);
        cout << "Agregue las lineas de texto al archivo 'entrada.txt' antes de volver a ejeecutar el programa." << endl;
        return 1;
    }
    // Limpiar el archivo de salida para que no se acumulon resultados de ejecuciones anteriores y solo muestre los resultados de la ejecución actual
    FILE *salida = fopen("salida.txt", "w");
    if (salida) {
        fclose(salida);
    } else {
        cout << "Error al abrir el archivo de salida." << endl;
        return 1;
    }

    char *cadEnt = new char [TAM] ();
    // Evaluar cada línea del archivo de entrada
    while (fgets(cadEnt, TAM, archivo)) {
        transTxt(cadEnt);
    }
    delete[] cadEnt;
    fclose(archivo);
    return 0;
}

// Funcion que transforma la cadena de entrada dependiendo de las teclas introducidas
void transTxt(char* cadEnt) {
    char *cadSal = new char [TAM] ();
    int cursor = 0;                     // Posicion del "cursor"
    int lon = 0;                        // Longitud de la cadena de salida que sirve para 

    for (int i = 0; cadEnt[i] != '\0'; i++) {
        if (cadEnt[i] == '-') {                     // Mover el "cursor" al inicio
            cursor = 0;
        } else if (cadEnt[i] == '+') {              // Mover el "cursor" al final
            cursor = lon;
        } else if (cadEnt[i] == '*') {              // Mover el "cursor" una posicion a la derecha
            if (cursor < lon) cursor++;
        } else if (cadEnt[i] == '3') {              // Eliminar caracter en la posición actual
            if (lon > 0 && cursor < lon) {              // Verificar que la longitud sea mayor a 0 y que el cursor no este al final
                for (int j = cursor; j < lon; j++) {    // Desplazar caracteres a la izquierda y elimina el caracter (lo que hace es copiar el caracter siguiente al actual, haciendo esto hasta el final de la cadena) 
                    cadSal[j] = cadSal[j + 1];
                }
                lon--;  
            }
        } else {                                // Insertar carácter de entrada en el caracter de salida (copiar el caracter de entrada en el de salida) esto en caso de que no sea ninguna de las teclas especiales
            for (int j = lon; j > cursor; j--) {    // Desplazar caracteres a la derecha e insertar el nuevo carácter
                cadSal[j] = cadSal[j - 1];
            }
            cadSal[cursor] = cadEnt[i]; 
            lon++;
            cursor++;                  // Avanzar la posición del "cursor"
        }
    }
    mostrar(cadSal);
    delete[] cadSal;
}

// Funcion que muestra la cadena de salida y la guarda en el archivo de salida
void mostrar(char* cadSal) {
    cout << cadSal;
    FILE *archivo = fopen("salida.txt", "a");
    if (archivo) {
        fputs(cadSal, archivo);
        fclose(archivo);
    } else {
        cout << "No se pudo abrir el archivo de salida." << endl;
        return;
    }
}
