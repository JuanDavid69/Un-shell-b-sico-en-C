#include <stdlib.h>
#include <string.h>
//#include <stdio.h

char** obtenerPalabras(char entrada[]) {
  char ** entradaProcesada;

  int numPalabras = 0;
  int palabraNum = 0;

  //Contamos el numero de numPalabras
  for (int i = 0; i < strlen(entrada); i++) {
    if(entrada[i] == ' ') {
      while(1) {
        if (entrada[i] == 1) {
          i++;
        } else {
          break;
        }
      }
      } else {
        numPalabras++;
        while(1) {
          if (entrada[i] != ' ') {
            i++;
          } else {
            break;
          }
        }
      }
    }

  //Preparamos el arreglo para la entradaProcesada
  entradaProcesada = malloc(sizeof *entradaProcesada * numPalabras);

  char buff[50] = "-";

  //Procesamos la entrada
  for (int i = 0; i < strlen(entrada); i) {
    if(entrada[i] == ' ') {
      while(1) {
        if (entrada[i] == ' ') {
          i++;
        } else {
          break;
        }
      }
      } else {
        while(1) {
          if (entrada[i] != ' ' && entrada[i] != '\0') {
            snprintf(buff + strlen(buff), (sizeof buff) - strlen(buff), "%c", entrada[i]);
            i++;
          } else {
            char *pBuff = buff;
            pBuff++;
            entradaProcesada[palabraNum] = malloc(sizeof * entradaProcesada[palabraNum] * (strlen(buff)));
            strcpy(entradaProcesada[palabraNum], pBuff);
            palabraNum++;
            strcpy(buff, "-");
            break;
          }
        }
      }
    }
    return entradaProcesada;
}
//main para PRUEBA
//
// int main(int argc, char const *argv[]) {
//   char entrada1[] = " a  -com --a";
//   char ** entradaProcesada1;
//
//   entradaProcesada1 = obtenerPalabras(entrada1);
//   for (int i = 0; i < 3; i++) {
//     printf("%s\n", entradaProcesada1[i]);
//   }
//   return 0;
// }
