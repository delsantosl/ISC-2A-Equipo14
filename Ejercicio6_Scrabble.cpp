#include <iostream>
#include <string.h>
#include <ctype.h>
using namespace std;

#define TAM 9
#define CENTRO

enum orientacion{ VERTICAL, HORIZONTAL};

bool colocarPalabra(char **, int , int , orientacion, char*);
bool estaVacio(char **);
bool esPalabra(char *);
void mostrarTab(char **);
bool yaExiste(char**,char*);
void liberarT(char**);
void colocarEnCentro(char**,char*,orientacion);
int main(){
	char **T;
	char *palabra;
	int fila,columna,ori;
	orientacion o;
	char respuesta;
	//Crear espacio para palabra
	palabra=(char*)calloc(50,sizeof(char));
	//Crear matriz dinamica
	T=(char**)calloc(TAM,sizeof(char*));
	for(int i=0; i<TAM; i++){
		T[i]=(char*)calloc(TAM,sizeof(char));
	}
	// Empezar con el tablero con espacios
	for(int i=0; i<TAM; i++){
		for(int j=0; j<TAM; j++){
			T[i][j]=' ';
		}
	}
	do{
		cout<<"Palabra a ingresar:"<<endl;
		cin>>palabra;
		
		for(int i=0; palabra[i]!='\0'; i++){//convertir la palabra a mayusculas
			palabra[i]=toupper(palabra[i]);
		}
		if(!esPalabra(palabra)){//Evaluar si  la palabra esta en el diccionario
			cout<<"La palabra no esta en el diccionario"<<endl;
			mostrarTab(T);
		}else{
			if(estaVacio(T)){
				cout<<"Es la primera palabra ingresada"<<endl;
				cout<<"Orientacion....Horizontal=1 y Vertical=0 "<<endl;
				cin>>ori;
				o=(orientacion)ori;
				colocarEnCentro(T,palabra,o);
				mostrarTab(T);
			}else{
				if(yaExiste(T,palabra)){//Evaluar si ya esta en el tablero
					cout<<"La palabra ya esta en el tablero"<<endl;
					mostrarTab(T);
				}else{//Pedir en donde se quiere poner la palabra
					cout<<"Fila inicial:"<<endl;
					cin>> fila;
					cout<<"Columna inicial"<<endl;
					cin>> columna;
					cout<<"Orientacion....Horizontal=1 y Vertical=0 "<<endl;
					cin>>ori;
					o=(orientacion)ori;
					if(colocarPalabra(T,fila,columna,o,palabra)){//Evaluar si se pudo colocar la palabra
						cout<<"Palabra colocada:"<<endl;
						mostrarTab(T);
					}else{
						cout<<"No se pudo colocar la palabra:"<<endl;
						mostrarTab(T);
					}
				}
			}
		}
		cout<<"Ingresar otra palabra....s"<<endl;
		cin>>respuesta;
	}while(tolower(respuesta)=='s');
	mostrarTab(T);
	free (palabra);
	liberarT(T);//liberar memoria del tablero
	return 0;
}

bool estaVacio(char **T){
	for(int i=0; i<TAM; i++){
		for(int j=0; j<TAM; j++){
			if(T[i][j] != ' '){
				return false;
			}
		}
	}
	return true;
}
void colocarEnCentro(char**T,char*palabra,orientacion o){
	int longitud=strlen(palabra);
	int centrof=TAM/2,centroc=TAM/2;
	//Ajustar donde inicia segun la orientacion
	if(o==HORIZONTAL){
		centroc-=longitud/2;
	}else{
		centrof-=longitud/2;
	}
	//Verificar si cabe en el tablero
	if(centrof<0||centroc<0||(o==HORIZONTAL&& centroc+longitud>TAM)||(o==VERTICAL && centrof+longitud>TAM)){
		cout<<"La palabra no cabe"<<endl;
		return ;
	}
	//Colocar palabra
	for(int i=0; i<longitud; i++){
		int fila=centrof;
		int col=centroc;
		if(o==VERTICAL){
			fila+=i;
		}else{
			col+=i;
		}
		T[fila][col]=palabra[i];
	}
}

bool esPalabra(char *palabra){
	FILE *diccionario = fopen("diccionario.txt","r");
	if(!diccionario) return false;

	char temp[50];
	while(fscanf(diccionario, "%s", temp) == 1){
		if(strcmp(temp, palabra) == 0){
			fclose(diccionario);
			return true;
		}
	}
	fclose(diccionario);
	return false;
}

bool yaExiste(char**T,char*palabra){
	int longitud;
	bool encontrada;
	longitud=strlen(palabra);//Contar caracteres de la palabra
	//Comprobar si la palabra ya existe de manera horizontal
	for(int i=0; i<TAM; i++){//para ir evaluando en cada renglon
		for(int j=0; j<TAM-longitud; j++){//para ir evaluando las columnas dejando los espacios que tendriaa los laterales
			encontrada=true;
			for(int k=0; k<longitud; k++){//para evaluar la palabra en las columnas
				if(T[i][j+k]!=palabra[k]){//va comparando cada caracter
					encontrada=false;
					break;//No seguir evaluando si ya no coincide
				}
			}
			if(encontrada){
				return true;
			}
		}
	}
	for(int i=0; i<TAM; i++){//para ir evaluando en cada columna
		for(int j=0; j<TAM-longitud; j++){//para ir evaluando conforme a los renglones segun los espacion que tendria a los laterales
			encontrada=true;
			for(int k=0; k<longitud; k++){
				if(T[i+k][j]!=palabra[k]){
					encontrada=false;
					break;
				}
			}
			if(encontrada){
				return true;
			}
		}
	}
	return false;
}

//Verifica si alguna letra coincide con el tablero
bool coincideConTablero(char **T, int fila, int columna, orientacion o, char *palabra){
	int len = strlen(palabra);
	for(int i=0; i<len; i++){
		int fi=fila, ci=columna;

		if(o == VERTICAL){
			fi = fi+i;
		}
		else{
			fi = fila;
			ci = ci+i;
		}
		if(fi>=TAM||ci>=TAM){
			return false;
		}
		if(T[fi][ci] == palabra[i]){
			return true;
		}
	}
	return false;	
}


bool colocarPalabra(char **T, int fila , int columna, orientacion o, char*palabra){
	int longitud=strlen(palabra);
	int f,c;
	//Verificar que la palabra quepa en el tablero
	if(((o==HORIZONTAL) && (columna+longitud>TAM))||((o==VERTICAL) && (fila+longitud>TAM))){
		return false;
	}
	//Verificar que alguna letra coincida con la palabra ya existente
	if(!coincideConTablero(T,fila,columna,o,palabra)){
		return false;
	}
	//Verificar que no sobrescriba letras diferentes
	for(int i = 0; i < longitud; i++){
		f = fila;
		c = columna;
		if(o == VERTICAL){
			f += i;
		} 
			else {
				c += i;
			}	
		if(T[f][c] != ' ' && T[f][c] != palabra[i]){
			//Conflicto con letra diferente
			return false;
		}
	}

	//Colocar la palabra si no hay conflictos
	for(int i = 0; i < longitud; i++){
		f = fila;
		c = columna;
		if(o == VERTICAL){
			f += i;
		} 
			else {
				c += i;
			}
		T[f][c] = palabra[i];
	}
	return true;
}

void mostrarTab(char **T) {
    FILE* salida = fopen("salida.txt", "w");   
    if (salida == NULL) {
        cout << "Error al abrir el archivo.";
        return;
    }

    // Encabezado de columnas
    cout << "    ";
    fprintf(salida, "    ");
    for (int j = 0; j < TAM; j++) {
        cout << " " << j << "  ";
        fprintf(salida, " %d  ", j);
    }
    cout << "\n";
    fprintf(salida, "\n");

    // Separador superior
    cout << "   +";
    fprintf(salida, "   +");
    for (int j = 0; j < TAM; j++) {
        cout << "---+";
        fprintf(salida, "---+");
    }
    cout << "\n";
    fprintf(salida, "\n");

    for (int i = 0; i < TAM; i++) {
        // Fila con valores
        cout << " " << i << " |";
        fprintf(salida, " %d |", i);
        for (int j = 0; j < TAM; j++) {
            if (T[i][j] == ' ') {
                cout << "   |";
                fprintf(salida, "   |");
            } else {
                cout << " " << T[i][j] << " |";
                fprintf(salida, " %c |", T[i][j]);
            }
        }
        cout << "\n";
        fprintf(salida, "\n");

        // Separador entre filas
        cout << "   +";
        fprintf(salida, "   +");
        for (int j = 0; j < TAM; j++) {
            cout << "---+";
            fprintf(salida, "---+");
        }
        cout << "\n";
        fprintf(salida, "\n");
    }

    fclose(salida);
}

void liberarT(char** T){
	for(int i=0; i<TAM; i++){
		free(T[i]);
	}
	free(T);
}
	

	
	
