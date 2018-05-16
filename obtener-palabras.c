#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** Se encarga de cortar las strings en tokens teniendo como delimitador los
*** espacios.
**/
void aux1(char entrada[], char*salida[], int numPalabras) {
  ///Obtenermos las palabras
  const char espacio[] = " ";
  salida[0] = strtok(entrada, espacio);
  for (int i = 1; i < numPalabras; i++) {
    salida[i] = strtok(NULL, espacio);
  }
}

/** Se encarga de los "|" y los ">"
**/
void aux2(char simbolo, int posSimbolo[], char *entrada[], int numPalAux2, char *salida[]) {
  int i = 0;
  int j = 0;
  char * tSimbolo = strdup(&simbolo);
  while (1) {
    switch (posSimbolo[j]) {
      case 0:
        salida[i] = entrada[j];
        i++;
        break;
      case 1:
        salida[i] = strdup(&simbolo);
        i++;
        salida[i] = strtok(strdup(entrada[j]), tSimbolo);
        i++;
        break;
      case 2:
        salida[i] = strtok(strdup(entrada[j]), tSimbolo);
        i++;
        salida[i] = strdup(&simbolo);
        i++;
        salida[i] = strtok(NULL, tSimbolo);
        i++;
        break;
      case 3:
        salida[i] = strtok(strdup(entrada[j]), tSimbolo);
        i++;
        salida[i] = strdup(&simbolo);
        i++;
        break;
    }
    j++;
    if (i >= numPalAux2) {
      break;
    }
  }
}

/** Primera aparicion del simbolo:
*** 0: no esta presente
*** 1: al inicio
*** 2: en el medio
*** 3: al final
**/

int pos(char entrada[], char simbolo) {
  int largo = strlen(entrada);
  int pos = 0;
  for (int i = 0; i < largo; i++) {
    if (entrada[i]==simbolo) {
      pos = i;
      if(largo == 1) {
				return 0;
			} else if (pos == 0) {
        return 1;
      } else if (pos < largo-1) {
        return 2;
      } else if (pos == largo-1) {
        return 3;
      }
      i = largo;
    }
  }
  return 0;
}

char** obtenerPalabras(char entrada[], int *sizeOut) {
  /*------------Fase 1------------*/
  /**Se divide la estrada en un char *[] y se eliminan los
   * espacios
   **/
  ///Primer conteo de palabras
  char * espacio = " ";
  char * token;
  int numPalabras = 0;
  token = strtok(strdup(entrada), espacio);
  while(token){
    token = strtok(NULL, espacio);
    numPalabras++;
  }
  
  ///Primer procesado
  char *outAux1[numPalabras];
  aux1(entrada, outAux1, numPalabras);
  
  
  /*------------Fase 2------------*/
  /** extraen y organiza los pipe **/
  
  ///Segundo conteo de palabras
  int numPalAux2 = numPalabras;
  char * pipe = "|";
  for (int i = 0; i < numPalabras; i++) {
    if ((strstr(outAux1[i], pipe) != NULL) && (strlen(outAux1[i])>1)) {
      token = strtok(strdup(outAux1[i]), pipe);
      while(token){
        token = strtok(NULL, pipe);
        numPalAux2++;
      }
    }
  }
  
  ///Posiciones a ser procesadas
  int posPipe[numPalabras];
  for (int i = 0; i < numPalabras; i++) {
    posPipe[i] = pos(outAux1[i], *pipe);
  }
  
  ///Segundo procesado
  char *outAux2[numPalAux2];
  char simbolo = '|';
  aux2(simbolo, posPipe, outAux1, numPalAux2, outAux2);
  

  
  /*------------Fase 3------------*/
  /** Se extraen y se organizan los ">" **/
  
  ///Tercer conteo de palabras
  int numPalAux2_2 = numPalAux2;
  char * mayor = ">";
  for (int i = 0; i < numPalAux2; i++) {
    if ((strstr(outAux2[i], mayor) != NULL) && (strlen(outAux2[i])>1)) {
      token = strtok(strdup(outAux2[i]), mayor);
      while(token){
        token = strtok(NULL, mayor);
        numPalAux2_2++;
      }
    }
  }
  
  
  ///Posiciones a ser procesadas
  int posMayor[numPalAux2];
  for (int i = 0; i < numPalAux2; i++) {
    posMayor[i] = pos(outAux2[i], *mayor);
  }
  
  ///Tercer procesado
  char *outAux2_2[numPalAux2_2];
  simbolo = '>';
  aux2(simbolo, posMayor, outAux2, numPalAux2_2, outAux2_2);
  
  
  /*------------Fase 4------------*/
   /**
    * Se modifica sizeOut y se vuelca el resultado del char*[] a
    * un char** que es el que se retorna
    **/
  
  *sizeOut = numPalAux2_2;
  char ** salida = malloc(sizeof * salida * numPalAux2_2);
  for(int i = 0; i< numPalAux2_2; i++){
    salida[i] = malloc(sizeof * salida[i] * strlen(outAux2_2[i]));
    salida[i] = strdup(outAux2_2[i]);
  }
	

  
  return salida;
  
  
}


