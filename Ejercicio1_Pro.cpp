#include <iostream>
#include <cstring>
using namespace std;

void ISBN(char codigo[], int A[]);
bool ISBNValido(int A[]);
void imprimirArreglo(int A[], int size);

int main() {
    char codigoISBN[14]; 
    int A[13];  

    cout << "Ingrese el ISBN de 13 dígitos: ";
    cin >> codigoISBN;

    if (strlen(codigoISBN) != 13) {
        cout << "El ISBN ingresado no tiene 13 dígitos." << endl;
        return 1;
    }

    ISBN(codigoISBN, A);

    cout << "Los dígitos del ISBN son: ";
    imprimirArreglo(A, 13);

    if (ISBNValido(A)) {
        cout << "El ISBN es válido." << endl;
    } else {
        cout << "El ISBN no es válido." << endl;
    }

    return 0;
}

void ISBN(char codigo[], int A[]) {
    for (int i = 0; i < 13; i++) {
        A[i] = codigo[i] - '0';  
    }
}

bool ISBNValido(int A[]) {
    int suma = 0;

    for (int i = 0; i < 12; i++) {
        if (i % 2 == 0) {
            suma += A[i];  
        } else {
            suma += A[i] * 3;
        }
    }

    int residuo = suma % 10;
    int resultado = 10 - residuo;

    if (resultado == 10) {
        resultado = 0;  
    }

    return resultado == A[12];  
}

void imprimirArreglo(int A[], int size) {
    for (int i = 0; i < size; i++) {
        cout << A[i];
    }
    cout << endl;
}
