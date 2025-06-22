#include <iostream>
using namespace std;

#define TAM 9
#define CENTRO

enum orientacion{ VERTICAL, HORIZONTAL};

bool colocarPalabra(char **, int f, int c, orientacion o, char *palabra);
bool estaVacio(char **;
bool esPalabra(char *palabra);

int main(){
	char T**;
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
