// Ejerc 2


#include <iostream>
#include <string>
using namespace std;

void transTxt(string cadEnt);
void mostrar(const string &cadSal);

int main() {
    string cadEnt;
    cout << "Introduce un texto: ";
    cin >> cadEnt;
    transTxt(cadEnt);
}

//Funcion que transforma la cadena de entrada dependiendo de las teclas introducidas
void transTxt(string cadEnt) {
    string cadSal = ""; // Cadena de salida vacia
    int cursor = 0;     // Posicion del "cursor"

    //Ciclo que recorre la cadena de entrada

                // El .size() se utiliza para verificar si el "cursor" esta dentro de los limites de la cadena antes de realizar alguna operacion
    for (char c : cadEnt) {                 //ciclo for basado en rango
        if (c == '-') {
            cursor = 0;                     // Mover al inicio
        } else if (c == '+') {
            cursor = cadSal.size();         // Mover al final       
        } else if (c == '*') {
            if (cursor < cadSal.size()) {
                cursor++;                   // Mover una posición a la derecha
            }
        } else if (c == '3') {
            if (cursor < cadSal.size()) {
                cadSal.erase(cursor, 1);    // Eliminar carácter en la posición actual
            }
        } else {
            cadSal.insert(cursor, 1, c);    // Insertar carácter en la posición actual
            cursor++;                       // Avanzar la posicion del "cursor"
        }
    }

    mostrar(cadSal);
}

//Funcion que muestra la cadena de salida
void mostrar(const string &cadSal) {
    cout << cadSal << endl;
}
