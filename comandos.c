#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "execPipe.h"
#include "validaciones.h"

char ** agregarNull (char ** comando, int size){
	char ** comandoP;
	comandoP = malloc(sizeof *comandoP * (size + 1));
	for (int i = 0; i < size + 1; i++){
		if ( i < size){
			comandoP[i] = malloc(sizeof * comandoP[i] * (strlen(comando[i])));
			comandoP[i] = strdup(comando[i]);
		}else{
			comandoP[i] = NULL;
		}
	}
	return comandoP;
}

int comandoArgs (char ** comando, int size){
	char ** comandoP;
	comandoP = agregarNull (comando, size);

	int error = 0;
	pid_t pid = fork();
	if(!pid) {
		execvp(comandoP[0], comandoP);
		printf("Error  al  ejecutar  el  comando \n");
		error = 1;
	} else {
		wait(NULL);
	}
	return error;
}

int redireccionarSalida (char ** comando, char * nombre, int pos){
	char ** comandoP;
	comandoP = agregarNull (comando, pos);

	int error = 0;
	pid_t pid = fork();
	if(!pid) {
		close(STDOUT_FILENO);
		open(nombre, O_EXCL|O_CREAT|O_WRONLY, S_IRWXU);
		execvp(comandoP[0], comandoP);
		printf("Error  al  ejecutar  el  comando \n");
		error = 1;
	} else {
		wait(NULL);
	}
	return error;
}

int ejecutar (char ** comando, int size){
	
	/**
	 * Tipos de comando:
	 * 	- Comando simples.
	 * 	- Comando con pipe.
	 *  - Comando con redireccion a archivo.
	 * 	- Comando con pipe y redireccion archivo.
	**/
	
	int validacionesR[6];
	validaciones(comando, size, validacionesR);
	
	if(validacionesR[0] == 0 && validacionesR[1]==0) { //Comandos simples
		return comandoArgs(comando,size);
	} else if(validacionesR[0] == 1 && validacionesR[1] == 0 && //Comando con pipe.
	          validacionesR[2] == 0 && validacionesR[3] == 0) {
		
		///Obtenemos la posicion del pipe
		int posPipe = 0;
		for(int i = 0; i < size; i++) {
			if(!strcmp(comando[i], "|")){
				posPipe = i;
				i = size;
			}
		}
		return execPipe(comando, size, posPipe); 
	} else if(validacionesR[0] == 0 && validacionesR[1] == 1 && //Comando con redireccion archivo.
	          validacionesR[2] == 0 && validacionesR[3] == 0 /*&&
	          validacionesR[5] == 0*/) {
		return redireccionarSalida (comando, comando[size-1], size-2);
	} else if(validacionesR[0] == 1 && validacionesR[1] == 1 && //Comando con pipe y redireccion archivo.
	          validacionesR[2] == 0 && validacionesR[3] == 0 &&
	          validacionesR[4] == 0 && validacionesR[5] == 0) {
		
		int posPipe = 0;
		for(int i = 0; i < size; i++) {
			if(!strcmp(comando[i], "|")){
				posPipe = i;
				i = size;
			}
		}
		
		char ** comandoP;
		comandoP = agregarNull (comando, size - 2);

		int error = 0;
		pid_t pid = fork();
		if(!pid) {
			close(STDOUT_FILENO);
			open(comando[size-1], O_EXCL|O_CREAT|O_WRONLY, S_IRWXU);
			execPipe(comandoP, size-2, posPipe);
			printf("Error  al  ejecutar  el  comando \n");
			error = 1;
		} else {
			wait(NULL);
		}
		return error;

	} else {
		//El comando no es valido
		return comandoArgs(comando,size);
	}

}




