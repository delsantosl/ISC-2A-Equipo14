//EJERCICIO 2 Teclado


#include <iostream>
#include <string.h>
using namespace std;

void transTxt(char cadEnt[]);
void mostrar (char cadSal[], int longCad);

int main(){
    char cadEnt[100];
    cout << "Introduce un texto: ";
    cin >> cadEnt;
    transTxt(cadEnt);
}

//Funcion para transformar el texto

void transTxt(char cadEnt[]){
    int longCad=0, i=0, j=0, k=0, l=0, m=0;
    char cadAux[100], cadAux2[100];
    longCad = strlen(cadEnt);

    //copiar el contenido de la cadena de entrada a una auxiliar
    while (cadEnt[j] != '\0'){
        cadAux[j] = cadEnt[j];
        j++;
    }
    cadAux[j] = '\0';

    //ciclo que recorre la cadena y transforma los caracteres indicados
    while (cadAux[i] != '\0'){
        if (cadAux[i] == '-'){
            cadAux[i] = '3';
            i = 0;
        }
        else if (cadAux[i] == '+'){
            cadAux[i] = '3';
            i = longCad;
        }
        else if (cadAux[i] == '*'){
            cadAux[i] = '3';
            if (i < longCad-2){
            i += 2;
            }
            else{
                i++;
            }
        }
        else if (cadAux[i] == '3'){
            if( i < longCad-1){
            cadAux[i+1]= '3';
            i += 2;
            }
            else{
                i++;
            }
        }else{
            i++;
        }
    }

    //copia la cadena transformada a otra auxiliar
    while(cadAux[k] != '\0'){
        if (cadAux[k] == '-' || cadAux[k] == '+' || cadAux[k] == '*' || cadAux[k] == '3'){
            k++;
            continue;
        }
            cadAux2[l] = cadAux[k];
            k++;
            l++;
    }
    cadAux2[l] = '\0';

    longCad = strlen (cadAux2);
    char cadSal[longCad+1];

    //copia la segunda cadena auxiliar a la cadena de salida
    while (m<longCad){
        cadSal[m] = cadAux2[m];
        m++;
    }
    cadSal[m] = '\0';

    mostrar(cadSal, longCad);
}

//Funcion para mostrar la cadena de salida
void mostrar (char cadSal[], int longCad){
    for(int i=0; i<longCad; i++){
        cout << cadSal[i];
    }
}