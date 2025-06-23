#include <iostream>
using namespace std;

#define TAM 9
#define CENTRO

enum orientacion{ VERTICAL, HORIZONTAL};

bool colocarPalabra(char **, int , int , int, char*);
bool estaVacio(char **;
bool esPalabra(char *);
void mostrarTab(char **);
bool yaExiste(char**,char*);
int main(){
	char T**;
	char *palabra;
	int fila,columna,ori;
	char respuesta;
	//Crear matriz dinamica
	T=(char**)calloc(TAM,sizeof(char*);
	for(int i=0; i<TAM; i++){
		*(t+1)=(char*)calloc(TAM,sizeof(char);
	}
	// Empezar con el tablero con espacios
	for(int i=0; i<TAM; i++){
		for(int j=0; j<TAM; j++){
			*(*(t+i)+j)==' ';
		}
	}
	do{
		cout<<"Palabra a ingresar:"<<endl;
		cin>>palabra;
		toupper(palabra);
		if(!esPalabra(palabra){//Evaluar si  la palabra esta en el diccionario
			cout<<"La palabra no esta en el diccionario"<<endl;
			mostrarTab(T);
		}else{
			if(yaExiste(T,palabra)){//Evaluar si ya esta en el tablero
					cout<<"La palabra ya esta en el tablero"<<endl
					mostrarTab(T);
			}else{//Pedir en donde se quiere poner la palabra
				cout<<"Fila inicial:"<<endl;
				cin>> fila;
				cout<<"Columna inicial"<<endl;
				cin>> columna;
				cout<<"Orientacion....Horizontal=1 y Vertical=0 "<<endl;
				cin>>ori;
				if(colocarPalabra(T,fila,columna,ori,palabra){//Evaluar si se pudo colocar la palabra
					cout<<"Palabra colocada:"<<endl;
					mostrarTab(T);
				}else{
					cout<<"No se pudo colocar la palabra:"<<endl;
					mostrarTab(T)
				}
			}
		}
		cout<<"Ingresar otra palabra....s"<<endl;
		cin>>respuesta;
	}while(tolower(respuesta)=='s');
	delete[] palbra;
	liberarT(T);//liberar memoria del tablero
	return 0;
}

bool estaVacio(char T**){
	for(int i=0; i<TAM; i++){
		for(int j=0; j<TAM; j++){
			if(T[i][j] != ' '){
				return false;
			}
			else{
				return true;
			}
		}
	}
}

bool esPalabra(char *palabra){
	return 
}
bool yaExiste(char**T,char*palabra){
	int long;
	bool encontrada;
	long=strlen(palabra);//Contar caracteres de la palabra
	//Comprobar si la palabra ya existe de manera horizontal
	for(int i=0; i<TAM; i++){//para ir evaluando en cada renglon
		for(int j=0; j<TAM-long; j++){//para ir evaluando las columnas dejando los espacios que tendriaa los laterales
			encontrada=true;
			for(int k=0; k<long; k+){//para evaluar la palabra en las columnas
				if(t[i][j+k]!=palabra[k]){//va comparando cada caracter
					encontrada=false;
				}
			}
			if(encontrada){
				return encontrada
			}
		}
	}
	for(int i=0; i<TAM; i++){//para ir evaluando en cada columna
		for(int j=0; j<TAM-long; j++){//para ir evaluando conforme a los renglones segun los espacion que tendria a los laterales
			encontrada=true;
			for(int k=0; k<long; k+){
				if(t[i+k][j]!=palabra[k]){
					encontrada=false;
				}
			}
			if(encontrada){
				return true;
			}
		}
	}
	return false;
}
	
