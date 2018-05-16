#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

/*
 * La funcion se encarga de ejecutar las entradas que contienen pipeline
 * 
 * name: execPipe
 * 
 * @entrada: La entrada en forma de arreglo que ha sido obtenido
 * previamente a partir de una entrada valida.
 * 
 * @posPipe: la posicion del pipe en el arreglo.
 * 
 * @return:
 * 	1: Si hubo un error durante la ejecucion.
 * 	0: Si todo se ejecuto correctamente.
 * 
 */
int execPipe(char**entrada, int sizeEntrada, int posPipe) {
	int error=0;
	
	pid_t pid1, pid2;
	int pipefd[2];
	
	///Separamos los dos comandos a ejecutar
	int tam1, tam2;
	tam1 = posPipe+1;
	tam2 = sizeEntrada-posPipe;
	char *comando1[tam1];
	char *comando2[tam2];
	///Comando1
	for(int i = 0; i < tam1; i++) {
		if(i == (tam1-1)){
			comando1[i] = NULL;
		} else {
			comando1[i] = strdup(entrada[i]);
		}
	}
	///Comando2
	for(int i = 0; i < (tam2); i++){
		if(i == (tam2-1)) {
			comando2[i] = NULL;
		} else {
			comando2[i] = strdup(entrada[posPipe+1+i]);
		}
	}
	///Creamos el pipe
	pipe(pipefd);
	
	///Creamos el primer proceso
	pid1 = fork();
	if(pid1 == 0) {
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		execvp(comando1[0], comando1);
		perror("\nexec1: "); ///Mostramos el error
		error = 1; ///Porque hubo un error
	}
	
	///Creamos el segundo proceso
	pid2 = fork();
	if(pid2 == 0) {
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[1]);
		execvp(comando2[0], comando2);
		perror("\nexec2: ");
		error = 1;
	}
	
	///Esperamos y luego terminamos
	int status1, status2 ;
	waitpid(pid1, &status1, WNOHANG);
	waitpid(pid2, &status2, WNOHANG);
	return error;//Para evitar warnings
}


//PRUEBAS
/**int main(int argc, char* argv[]) {
	char **entrada = malloc(sizeof * entrada * 6);
	for(int i = 0; i < 6; i++) {
		entrada[i] = malloc(sizeof *entrada[i] * 20);
	}
	entrada[0] = strdup("ls");
	entrada[1] = strdup("|");
	entrada[2] = strdup("grep");
	entrada[3] = strdup("p");
	entrada[4] = strdup(">");
	entrada[5] = strdup("doc.txt");
	execPipe(entrada, 6, 1, 0);
	
}**/
