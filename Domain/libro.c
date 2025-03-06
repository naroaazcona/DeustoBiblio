#ifndef DOMAIN_LIBRO_C_
#define DOMAIN_LIBRO_C_
#include "libro.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Libro pedirDatosLibro(){
	Libro l;
	printf("ISBN: ");
	fflush(stdout);
	fflush(stdin);
	gets(l.ISBN);
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
	printf("%20s%20s%10d%20s%15s%10d\n", l.ISBN, l.titulo, l.anioPubli, l.autor, l.genero, l.disponibilidad);

}

void marcarLibroComoNoDispo(Libro *l){
	l->disponibilidad = 0;
}


void aniadirLibro(ListaLibros *ll, Libro l){
	int i;
	if(ll->aLibros == NULL){
		ll->aLibros = (Libro*)malloc(1*sizeof(Libro));
	}else{
		Libro *aux = (Libro*)malloc(ll->numeroLibros * sizeof(Libro));
		for(i=0; i<ll->numeroLibros;i++){
			ll->aLibros[i] = aux[i];
		}
		free(aux);
	}
	ll->aLibros[ll->numeroLibros] = l;
	ll->numeroLibros++;

}

void eliminarLibro(ListaLibros *listaLibro, Libro libro){
	int i;
	int pos = buscarLibro(*listaLibro, libro.ISBN);
	if(pos == -1){
		printf("No se ha eliminado el libro porque no existe en la biblioteca\n");
	}else{
		for(i=pos; i<listaLibro->numeroLibros -1; i++){
			listaLibro->aLibros[i] = listaLibro->aLibros[i+1];
		}
		listaLibro->numeroLibros--;
	}

}

int buscarLibro(ListaLibros ll, char * isbn){
	int pos = 0, enc = 0;
	while(!enc && pos < ll.numeroLibros){
		if(strcmp(ll.aLibros[pos].ISBN, isbn) == 0){
			enc = 1;
		}else{
			pos++;
		}
	}
	if(enc == 1){
		return pos;
	}else{
		return -1;
	}

}

void visualizarLibros(ListaLibros ll){


}

int alquilarLibro(ListaLibros *ll, char *isbn){
	return 0;

}

int devolverLibro(ListaLibros *ll, char *isbn){
	return 0;

}


#endif /* DOMAIN_LIBRO_C_ */
