#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Valida el arreglo que se obtiene al ejecutar obtenerPalabras();
 * 
 * @ comando: El resultado de obtenerPalabras().
 * 
 * @ size: Tamaño de comando.
 * 
 * @ resultados[0]: La cantidad de pipes
 * 
 * @ resultados[1]: La cantidad de ">"
 * 
 * @ resultados[2]: 0->El inicio está ok
 *                  1->El inicio contiene pipe o ">"
 * 
 * @ resultados[3]: 0->El final está ok
 *                  1->El final contiene pipe o ">"
 * 
 * @ resultados[4]: 0->El "|" precede al ">" (si aplica)
 *                  1->El orden de "|" y ">" no es correcto (si aplica)
 * 
 * @ resultados[5]: 0->El ">" está en el lugar correcto
 *                  1->">" no está en el lugar correcto 
 *
 * @return void
 */
void validaciones(char** comando, int sizeEntrada, int resultados[]){
	int cantPipes=0, cantMayor=0, inicio=0, final=0, posPipe=0, posMayor=0;
	for (int i = 0; i < sizeEntrada; i++){
		if (!strcmp(">", comando[i])){
			cantMayor++;
			posMayor = i;
		} else if (!strcmp("|", comando[i])) {
			cantPipes++;
			posPipe = i;
		}	
	}
	
	
	resultados[0] = cantPipes;
	resultados[1] = cantMayor;
	
	
	
	if(!strcmp(">", comando[0]) || !strcmp("|", comando[0])) {
		inicio = 1;
	}
	resultados[2] = inicio;
	
	
	if(!strcmp(">", comando[sizeEntrada-1]) || !strcmp("|", comando[sizeEntrada-1])){
		final = 1;
	}
	resultados[3] = final;
	
	
	if(posPipe<posMayor) {
		resultados[4] = 0;
	} else {
		resultados[4] = 1;
	}
	
	
	if(posMayor == sizeEntrada-2) {
		resultados[5] = 0;
	} else {
		resultados[5] = 1;
	}
}

//PRUEBAS
/**int main(int argc, char const *argv[]) {
	int resultados[6];
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
	
	validaciones(entrada, 6, resultados);
	
	for(int i = 0; i < 6; i++) {
		printf("%d-", resultados[i]);
	}
	
}*/
