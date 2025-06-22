#include <iostream>
using namespace std;

#define TAM 13

//Enumeracion que indica si un ISBN es valido o invalido
enum EstadoISBN{INVALIDO, VALIDO};

//Estructura que almacena un ISBN, su arreglo de digitos y su estado(valido o invalido)
struct ISBNData{
    unsigned long long codigo;
    int* digitos;
    EstadoISBN estado;
};

//Prototipos de las funciones
void ISBN(unsigned long long codigo, int* A, int i = TAM - 1);
bool ISBNValido(int A[]);
void evaluarISBN(ISBNData* isbn);

//Funcion principal
int main(){
	//Se declaran los archivos
    FILE* entradaArchivo = fopen("entrada.txt", "r");	//Se abre archivo de entrada para lectura
    if (!entradaArchivo) { // Verifica si el archivo no existe 
        cout << "Error al abrir el archivo de entrada." << endl;
        entradaArchivo = fopen("entrada.txt", "w");    // Si no existe, lo crea
        fclose(entradaArchivo);
        cout << "Agregue los ISBN que se quieran evaluar al archivo 'entrada.txt' antes de volver a ejeecutar el programa." << endl;
        return 1;
    }
    FILE* salidaArchivo = fopen("salida.txt", "w");		//Se abre archivo de salida para escritura
    unsigned long long codigo;

	//Verificacion de apertura correcta del archivo de entrada
    if(!entradaArchivo){
        cout << "No se pudo abrir el archivo de entrada." << endl;
        return 1;
    }

	//Ciclo que lee ISBNs del archivo mientras no se llegue al final
    while(fscanf(entradaArchivo, "%llu", &codigo) != EOF){
    	//Reserva memoria dinamica para el ISBNData
        ISBNData* isbn = new ISBNData;
        isbn->codigo = codigo;
        isbn->digitos = new int[TAM];	//Arreglo dinamico para los digitos

        ISBN(isbn->codigo, isbn->digitos);	 //Manda a llamar a la funcion recursiva para llenar el arreglo de digitos
        evaluarISBN(isbn);	//Manda a llamar a la funcion para que le asigne un estado

        cout << "ISBN: " << isbn->codigo << " -> ";
        fprintf(salidaArchivo, "ISBN: %llu -> ", isbn->codigo);
		
		//Verifica el estado y muestra el resultado correspondiente
        if(isbn->estado == VALIDO){
            cout << "VALIDO" << endl;
            fprintf(salidaArchivo, "VALIDO\n");
        } 
			else{
            	cout << "INVALIDO" << endl;
            	fprintf(salidaArchivo, "INVALIDO\n");
        	}
		
		//Libera la memoria reservada dinamicamente
        delete[] isbn->digitos;
        delete isbn;
    }

	//Se cierran los archivos
    fclose(entradaArchivo);
    fclose(salidaArchivo);

    return 0;
}


//Funcion recursiva para llenar el arreglo de derecha a izquierda
void ISBN(unsigned long long codigo, int* A, int i){
    if(i < 0) return;				//Caso base: cuando se han llenado todos los digitos
    A[i] = codigo % 10;				//Extrae el digito mas a la derecha
    ISBN(codigo / 10, A, i - 1);	//Llamada recursiva con el numero reducido y la siguiente posicion
}

//Verifica si el arreglo de digitos representa un ISBN valido
bool ISBNValido(int A[]){
    int suma = 0;
    for(int i = 0; i < 12; i++){
        if(i % 2 == 0){
            suma += A[i] * 1;		//Si la posición es par, se multiplica por 1
        } 
			else{
            	suma += A[i] * 3;	//Si es impar, se multiplica por 3
        	}
    }
    int residuo = suma % 10;					//Calcula el residuo de la suma
    int verificador = (10 - residuo) % 10;		//Calcula el digito verificador esperado
    return verificador == A[12];				//Compara con el ultimo dígito del ISBN
}

//Evalua el estado de un ISBN y lo asigna como VALIDO o INVALIDO
void evaluarISBN(ISBNData* isbn){
    if(ISBNValido(isbn->digitos)){
    	isbn->estado = VALIDO;
	} 
		else{
    		isbn->estado = INVALIDO;
		}
}
