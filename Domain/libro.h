#ifndef DOMAIN_LIBRO_H_
#define DOMAIN_LIBRO_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
	char ISBN[10];
	char titulo[50];
	int anioPubli;
	char autor[20];
	char genero[20];
	int disponibilidad;
}Libro;

typedef struct{
	Libro * aLibros;
	int numeroLibros;
}ListaLibros;

void inicializarListaLibros(ListaLibros *ll);
Libro pedirDatosLibro();
void visualizarTitulosLibro(SOCKET comm_socket, char *sendBuff);
int cargarLibrosDesdeFichero(ListaLibros *ll);


#endif /* DOMAIN_LIBRO_H_ */
