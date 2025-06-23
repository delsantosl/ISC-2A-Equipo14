//Ejercicio #3 – Laberinto 

#include <iostream>
#include <math.h>   //para usar sqrt
using namespace std;

//prtotipos de funciones
int laberinto(int **, int, int*, int*);
void manejoArch();
bool esValido(const char*);
int obtenerTam(FILE*);
int** crearMatDinamica(int);
bool leerArch(FILE*,int**,int);
void liberarMat(int**,int);
void mostrarMat(int**,int,FILE*);
void guardarRes(FILE*,int,int,int);

// funcion principal
int main() {
    //llamada a funcion para manejar archivos y procesamiento
    manejoArch();
    return 0;
}
void manejoArch(){
    //abrir el archivo de entrada como lectura
    FILE* entrada= fopen("entrada.txt","r");

    //verificar si el no archivo existe o esta vacio
    if (!entrada) {
        cout << "Error al abrir el archivo de entrada." << endl;
        entrada = fopen("entrada.txt", "w");    // Si no existe, lo crea como sobreescritura
        fclose(entrada);    //cerrar archivo
        cout << "ingrese los datos al archivo 'entrada.txt' antes de volver a ejecutar el programa." << endl;
        return ;
    }

    //Determinar el tamaño de la matriz
    int MAX=obtenerTam(entrada);//llamada a la funcion para obtener cuantos valores tiene el archivo

    if(MAX==0){ //si el archivo no tiene valores o si es una matriz cuadrada
        cout<<"El archivo no contiene una matriz valida o no es cuadrada";
        fclose(entrada);    //cerrar archivo
        return; //detener ejecucion 
    }

    //crear matriz con memoria dinamica
    int ** M=crearMatDinamica(MAX); //llamada a funcion para asignar memoria dinamica
    if(M==NULL){    //si la asignacion de memoria fallo
        cout<<"Error al asignar memoria.";
        fclose(entrada);    //cerrar archivo 
        return ;   //detener ejecucion 
    }

    //leer datos del archivo
    if(!leerArch(entrada,M,MAX)){   //si no se pudo leer el archivo correctamente
        cout<<"Error al leer los datos del archivo";
        liberarMat(M,MAX);  //libera memoria de la matriz
        fclose(entrada);    //cerrar archivo
        return; //detener ejecucion
    }

    //cerrar archivo de entrada
    fclose(entrada);

    //crear o abrir el archivo de salida como sobreescritura
    FILE* salida= fopen("salida.txt","w");  

    //verificar si el archivo se abre correctamente
    if (!salida) { 
        cout << "Error al abrir el archivo de salida." << endl;
        liberarMat(M,MAX);  //libera memoria
        return ;    //detiene la ejecucion
    }

    //llamada a funcion para mostrar Matriz
    mostrarMat(M,MAX,salida);

    //llamada a la funcion laberinto para obtener la suma de la diagonal y de la ultima columna
    int posF=0, posC=0, suma=0; //variables para obtener datos
    suma = laberinto(M, MAX, &posF, &posC);

    //llamada a funcion para guardar resultados en archivo de salida
    guardarRes(salida,suma,posF,posC);

    //mostrar resultados en pantalla
    cout << "Suma del recorrido: " << suma << endl;
    cout << "Posicion final: (" << posF + 1 << ", " << posC + 1 << ")" << endl;
    
    //liberar recursos
    liberarMat(M,MAX);
    fclose(salida);     //cerrar el archivo de salida
}

//funcion para asignar memoria a matriz
int** crearMatDinamica(int MAX){
    // creacion de matriz con memoria dinamica
    int **M=new int*[MAX];
    for(int i=0; i<MAX; i++){//asignar memoria dinamica a cada fila de la matriz
        M[i]=new int[MAX];
    }
    return M;

}

//funcion para liberar memoria utilizada
void liberarMat(int** M,int MAX){
    for(int i=0; i<MAX; i++){
        delete[] M[i];
    }
    delete[] M;
}

//funcion para obtener total de numeros del archivo
int obtenerTam(FILE* entrada){

    //variables para contar elemento y verificar matriz cuadrada
    int elementos=0;
    char buffer [100];  //variable para validar si es numero

    //regresar al inicio del archivo
    fseek(entrada,0,SEEK_SET);
    
    //contar numeros
    while(fscanf(entrada,"%s", buffer)==1){
        if (!esNumeroValido(buffer)){
            cout << "El valor no es nuemrico!\n";
            return 0;
        }
        elementos++;
    }

    //calcular tamaño de la posible matriz cuadrada sacando la raiz cuadrada al total de elementos calculados
    float tam=sqrt(elementos);

    //verificar si es matriz cuadrada perfecta
    if(tam*tam==elementos){
        return tam;
    }
    return 0;
}

//funcion para leer datos numericos de un archivo y guardarlos en una matriz
bool leerArch(FILE* entrada,int** M,int MAX){
    fseek(entrada,0,SEEK_SET);  //volver al inicio del archivo
    //ciclo para leer los datos del archivo de entrada
    for(int i=0;i<MAX;i++){ //recorre filas
        for(int j=0; j<MAX;j++){    //recorre columnas
            if(fscanf(entrada,"%d", &M[i][j])!=1){// intenta leer un entero
                return false; //si falla, retorna false
            }
        }
    }
    return true;    //si todos los datos se leyeron correctamente, retorna true

}

//mostrar matriz en pantalla y guardarla en el archivo de salida
void mostrarMat(int** M,int MAX,FILE* salida){
    cout << "Matriz " << MAX<<"x"<<MAX<<":"<<endl; // Imprimir en pantalla
    fprintf(salida,"Matriz: %dx%d: \n",MAX,MAX); //guardar en archivo de salida
    
    //ciclo para mostrar la matriz de numeros
    for (int i=0; i<MAX; i++) { //filas
        for (int j = 0; j < MAX; j++) {//columnas
            cout << M[i][j] << " ";//mostrar en pantalla
            fprintf(salida,"%d ", M[i][j]);//guardar datos en el archivo de salida
        }
        // Nueva linea al final de cada fila
        cout << endl;//mostrar en pantalla
        fprintf(salida,"\n"); //guardar en archivo de salida
    }

}

//funcion para obtener la suma de la diagonal y de ultima columna
int laberinto(int **M,int MAX, int *posF, int *posC) {
    int suma = 0,chacales = 0;
    // Recorre la diagonal principal
    for (int i = 0; i < MAX; i++) {
        suma += M[i][i];    //sumar diagonal
        if (M[i][i] == 0) { // Si encuentra un chacal (0), incrementa el contador
            chacales++;
            if (chacales == 3) {    // Si encuentra 3 chacales, guarda la posicion de filas y de columnas
                *posF = i;  //asigna el valor para posicion de Filas
                *posC = i;  //asigna el valor para posicion de Columnas
                return suma;    //retorna suma
            }
        }
    }
    // Recorre la ultima columna de abajo hacia arriba
    for (int i = MAX - 2; i >= 0; i--) {    //recorre de MAX-2 para no volver a sumar la esquina (ultimo elemento de la diagonal) sumada anteriormente
        suma += M[i][MAX - 1]; //-1 ya que el 0 tambien se toma como indice
        if (M[i][MAX - 1] == 0) {//si la celda actual encuentra un chacal lo incrementa
            chacales++;
            if (chacales == 3) {// si encuentra 3 chacales, guarda la posicion y retorna la suma
                *posF = i;
                *posC = MAX - 1;
                return suma;
            }
        }
    }

    // Si no se encontraron 3 chacales, termina en la posicion (1,col-1)
    *posF = 0;
    *posC = MAX -1;
    return suma;
}

//guardar datos en el archivo de salida
void guardarRes(FILE* salida,int suma,int posF,int posC){
    fprintf(salida, "Suma del recorrido: %d\n", suma); 
    fprintf(salida, "Posicion final: (%d,%d)\n" ,posF + 1, posC + 1);
}

//verificar si lo que contiene la cadena son digitos
bool esNumeroValido(const char* str) {
    if (*str == '-') str++; // Permitir numeros negativos si es necesario
    bool tieneDigitos = false;
    while (*str) {          //mientras tenga algo que leer
        if (!isdigit(*str)) {   //si no es digito retorna falso
            return false;
        }
        tieneDigitos = true;    //si es digito tineDigitos se hace true
        str++;                  //pasa al sig caracter
    }
    return tieneDigitos;    //si es digito retorna true
}