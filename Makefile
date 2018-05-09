MainShell: libobtener-palabras.a
	gcc -L. -o exe MainShell.c -lobtener-palabras -lcomandos
libobtener-palabras.a: obtener-palabras.o
	ar -cvq libobtener-palabras.a obtener-palabras.o
	ar -cvq libcomandos.a comandos.o
obtener-palabras.o: 
	gcc -c obtener-palabras.c
	gcc -c comandos.c
clean:
	rm -f MainShell a.out lib*.a *.o
