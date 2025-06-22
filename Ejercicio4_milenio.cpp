#include <iostream>
#include <string.h> // Para strcspn
#include <ctype.h>  // Para tolower
using namespace std;

// Estructura que almacena una frase y su mensaje oculto
struct frases {
  char msg[2000];
  char ocult[2000];
};

void leer(FILE*, int);
void analisis(FILE*, FILE*);

int main() {
  FILE *archmsg;
  FILE *archocult;
  int num;

  // Abrir archivos en modo lectura-escritura y escritura
  archmsg = fopen("mensaje.txt", "w+");
  archocult = fopen("oculto.txt", "w");

  // Verificar que los archivos se abrieron correctamente
  if (archmsg == NULL || archocult == NULL) {
    cout << "Error al abrir archivos.\n";
    return 1;
  }

  // Comprobar que la si se ingrese un numero de frases
  do {
    cout << "Numero de frases a analizar: ";
    cin >> num;

    if (cin.fail() || num <= 0) {//cin.fail detecta si hubo un error a la hora de leer
      cout << "Ingrese un número válido.\n";
      cin.clear();//limpia el estado porque queda con datos erroneos
      cin.ignore(2000, '\n');//descarta los caractares que quedaron leidos hasta que llegue al caracter2000 
                            //o que se encuentre un \n
    } else {
      break;
    }
  } while (true);

  getchar(); // limpiar el salto de linea
  fprintf(archmsg, "%d\n", num); //Imprimir el numero en el archivo

  leer(archmsg, num); // Leer las frases desde teclado y guardar
  fseek(archmsg, 0, SEEK_SET);   // Regresar al inicio del archivo
  analisis(archmsg, archocult); // Analizar ambas frases

  // Cerrar archivos
  fclose(archmsg);
  fclose(archocult);

  return 0;
}

// Funcion para leer las frases e imprimirlas en el archivo
void leer(FILE* archmsg, int num) {
  // Usamos calloc para asignar memoria dinamica para una estructura
  frases* mensaje = (frases*)calloc(1, sizeof(frases));

  for (int i = 0; i < num; i++) {
    cout << "\nFrase  " << (i + 1) << endl;

    // Leer mensaje con espacios
    fgets(mensaje->msg, 2000, stdin);//guarda el mensaje en la estructura, con una capacidad de 2000 y 
                                    //el stdin es para indicar que lo lea del teclado
    mensaje->msg[strcspn(mensaje->msg, "\n")] = '\0'; // quitar '\n'

    // Leer mensaje oculto
    cout<<"Mensaje oculto: "<<endl;
    fgets(mensaje->ocult, 2000, stdin);
    mensaje->ocult[strcspn(mensaje->ocult, "\n")] = '\0';

    // Imprimir en el archivo
    fprintf(archmsg, "%s\n%s\n", mensaje->msg, mensaje->ocult);
    }

    // Liberar memoria
    free(mensaje);
}

// Funcion que analiza si el mensaje oculto aparece
void analisis(FILE* archmsg, FILE* archocult) {
  int casos;
  frases* mensaje = (frases*)calloc(1, sizeof(frases));

  // Leer el número de frases
  fscanf(archmsg, "%d\n", &casos);

  for (int i = 0; i < casos; i++) {
    // Leer los mensajes desde el archivo
    fgets(mensaje->msg, 2000, archmsg);
    fgets(mensaje->ocult, 2000, archmsg);
    mensaje->msg[strcspn(mensaje->msg, "\n")] = '\0';//retira el salto de linea de la cadena y pone un fin de linea
    mensaje->ocult[strcspn(mensaje->ocult, "\n")] = '\0';

    // Comparar las frases
    int j = 0, k = 0;
    while (mensaje->msg[j] && mensaje->ocult[k]) {
      if (tolower(mensaje->msg[j]) == tolower(mensaje->ocult[k])) {
        k++;
      }
      j++;
    }

    // Imprimir el resultado en el archivo y mostrarlo en pantalla
    if (mensaje->ocult[k] == '\0') {
      fprintf(archocult, "SI\n");
      cout << "Frase" << (i + 1) << ": SI\n";
    } else {
      fprintf(archocult, "NO\n");
      cout << "Frase" << (i + 1) << ": NO\n";
    }
  }

    // Liberar memoria
  free(mensaje);
}
