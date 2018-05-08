MainShell: libobtener-palabras.a
	gcc -L. -o MainShell obtener-palabras.c -lobtener-palabras
libobtener-palabras.a: obtener-palabras.o
	ar -cvq libobtener-palabras.a obtener-palabras.o
obtener-palabras.o: 
	gcc -c obtener-palabras.c
clean:
	rm -f MainShell a.out lib*.a *.o
