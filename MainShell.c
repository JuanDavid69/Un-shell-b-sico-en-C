#include <stdio.h>
#include <string.h>
#include "obtener-palabras.h"

 int main(int argc, char const *argv[]) {
   char entrada1[] = " a  -com --a";
   char ** entradaProcesada1;

   entradaProcesada1 = obtenerPalabras(entrada1);
   for (int i = 0; i < 3; i++) {
     printf("%s\n", entradaProcesada1[i]);
   }
   return 0;
 }
