#include <iostream>
using namespace std;

#define TAM 9
#define CENTRO

enum orientacion{ VERTICAL, HORIZONTAL};

bool colocarPalabra(char T[TAM][TAM], int f, int c, orientacion o, char *palabra);
bool estaVacio(char T[TAM][TAM]);
bool esPalabra(char *palabra);

int main(){
	char T[TAM][TAM];
	
	
	return 0;
}

bool estaVacio(char T[TAM][TAM]){
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
