#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "obtener-palabras.h"

int main(int argc, char const *argv[])
{
	while(1) {
		char entrada[80];
		char ** comando;
		printf("#-> ");
		scanf("%[^\n]%*c", entrada);
		comando = obtenerPalabras(entrada);
		if(!strcmp("exit", comando[0])) {
			break;
		}
		

		pid_t pid = fork();

		if(!pid) {
			execvp(comando[0], comando);
			break;
		} else {
			wait(NULL);
		}
	}
	
	return 0;
}

/*
int main(int argc, char const *argv[]){
	while(1) {
		char entrada[];
		char ** comando;
		printf("#-> ");
		scanf("%s", entrada);
		comando = obtenerPalabras(entrada)

		if(!strcmp("exit", comando)) {
			break;
		}

		pid_t pid = fork();

		if(!pid) {
			char * myargs[2];
			myargs[0] = strdup(comando);
			myargs[1] = NULL;
			execvp(myargs[0], myargs);
		} else {
			wait(NULL);
		}
	}
	return 0;
}


 int main(int argc, char const *argv[]) {
   char entrada1[] = " a  -com --a";
   char ** entradaProcesada1;

   entradaProcesada1 = obtenerPalabras(entrada1);
   for (int i = 0; i < 3; i++) {
     printf("%s\n", entradaProcesada1[i]);
   }
   return 0;
 }*/
