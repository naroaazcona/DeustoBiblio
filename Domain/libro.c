#ifndef DOMAIN_LIBRO_C_
#define DOMAIN_LIBRO_C_
#include "libro.h"
#include <stdio.h>
#include <string.h>

Libro pedirDatosLibro(){
	Libro l;
	printf("ISBN: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%d", &l.ISBN);
	printf("TÍTULO: ");
	fflush(stdout);
	fflush(stdin);
	gets(l.titulo);
	printf("AÑO DE PUBLICACIÓN: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%d", &l.anioPubli);
	printf("AUTOR: ");
	fflush(stdout);
	fflush(stdin);
	gets(l.autor);
	printf("GÉNERO: ");
	fflush(stdout);
	fflush(stdin);
	gets(l.genero);
	l.disponibilidad = 1;
	return l;
}

void visualizarTitulosLibro(){
	printf("%20s%20s%10s%20s%15s%10s\n", "ISBN", "TÍTULO", "AÑO PUBLICACIÓN", "AUTOR", "GÉNERO", "DISPONIBILIDAD");
	fflush(stdout);

}

void visualizarLibro(Libro l){
	printf("%20d%20s%10d%20s%15s%10d\n", l.ISBN, l.titulo, l.anioPubli, l.autor, l.genero, l.disponibilidad);

}

void marcarLibroComoNoDispo(Libro *l){
	l->disponibilidad = 0;
}

/*
void aniadirLibro(ListaLibros *ll, Libro l){

}

void eliminarLibro(ListaLibros *ll, Libro l){

}

int buscarLibro(ListaLibros ll, char * isbn){

}

void visualizarLibros(ListaLibros ll){

}

int alquilarLibro(ListaLibros *ll, char *isbn){

}

int devolverLibro(ListaLibros *ll, char *isbn){

}*/


#endif /* DOMAIN_LIBRO_C_ */
