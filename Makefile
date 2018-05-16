MainShell: libobtener-palabras.a
	gcc -L. -o exe MainShell.c -lobtener-palabras -lcomandos -lexecPipe -lvalidaciones
libobtener-palabras.a: obtener-palabras.o
	ar -cvq libobtener-palabras.a obtener-palabras.o
	ar -cvq libcomandos.a comandos.o
	ar -cvq libexecPipe.a execPipe.o
	ar -cvq libvalidaciones.a validaciones.o
obtener-palabras.o: 
	gcc -c obtener-palabras.c
	gcc -c comandos.c
	gcc -c execPipe.c
	gcc -c validaciones.c
clean:
	rm -f MainShell a.out lib*.a *.o exe
