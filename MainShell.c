#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "obtener-palabras.h"
#include "comandos.h"
#include "validaciones.h"
#include "execPipe.h"

int main(int argc, char const *argv[])
{ 

	while(1) {
		char entrada[100];
		char ** comando;
		//VERIFICAR EL SIZE DE comando
		int size;
		printf("#-> ");
		scanf(" %99[^\n]", entrada);

		comando = obtenerPalabras(entrada, &size);
		if(!strcmp("exit", comando[0])) {
			break;
		}
		if (ejecutar(comando, size) != 0){
			break;
		}
	}
	
	return 0;
}
