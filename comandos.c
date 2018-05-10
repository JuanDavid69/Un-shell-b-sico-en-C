#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int comandoArgs (char ** comando, int size){
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
