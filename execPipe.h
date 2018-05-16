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
 * @toScreen?:
 *	0: El resultado de la entrada debe ir a un archivo.
 * 	1: El resultado de la entrada se imprime por pantalla.
 * 
 * @return:
 * 	0: Si hubo un error durante la ejecucion.
 * 	1: Si todo se ejecuto correctamente.
 * 
 */
int execPipe(char**entrada, int sizeEntrada, int posPipe);
