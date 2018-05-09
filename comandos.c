#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int comandoArgs (char ** comando){
	int error = 0;
	pid_t pid = fork();
	if(!pid) {
		execvp(comando[0], comando);
		printf("Error  al  ejecutar  el  comando \n");
		error = 1;
	} else {
		wait(NULL);
	}
	return error;
}
