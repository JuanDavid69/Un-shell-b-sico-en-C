#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "obtener-palabras.h"
#include "comandos.h"

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
		if (comandoArgs(comando) == 1){
			break;
		}
	}
	
	return 0;
}
