#ifndef DOMAIN_LIBRO_C_
#define DOMAIN_LIBRO_C_
#include "libro.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void inicializarListaLibros(ListaLibros *ll){
	ll->aLibros = NULL;
	ll->numeroLibros = 0;
}
Libro pedirDatosLibro() {
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

void visualizarTitulosLibro(SOCKET comm_socket, char *sendBuff) {
	sprintf(sendBuff,"\033[1;33m%30s|%30s|%20s|%40s|%20s|%20s\n\033[0m", "ISBN", "TÍTULO", "AÑO PUBLICACIÓN",
			"AUTOR", "GÉNERO", "DISPONIBILIDAD");
	send(comm_socket,sendBuff,strlen(sendBuff)+1,0);  //enviar

}

int cargarLibrosDesdeFichero(ListaLibros *ll) {
	FILE *fichero = fopen("libros.txt", "r");

	if (fichero == NULL) {
		printf("Error al abrir el fichero de los libros\n");
		return 0;
	}

	ll->aLibros = NULL;
	ll->numeroLibros = 0;
	char linea[256];

	while (fgets(linea, sizeof(linea), fichero)) {
		linea[strcspn(linea, "\n")] = 0;

		Libro libro;
		char *token = strtok(linea, ";");
		if (token)
			strcpy(libro.ISBN, token);

		token = strtok(NULL, ";");
		if (token)
			strcpy(libro.titulo, token);

		token = strtok(NULL, ";");
		if (token)
			libro.anioPubli = atoi(token);

		token = strtok(NULL, ";");
		if (token)
			strcpy(libro.autor, token);

		token = strtok(NULL, ";");
		if (token)
			strcpy(libro.genero, token);

		token = strtok(NULL, ";");
		if (token)
			libro.disponibilidad = atoi(token);

		Libro *temp = realloc(ll->aLibros,
				(ll->numeroLibros + 1) * sizeof(Libro));
		if (temp == NULL) {
			printf("Error al reservar memoria al cargar libros.\n");
			fclose(fichero);
			return 0;
		}

		ll->aLibros = temp;
		ll->aLibros[ll->numeroLibros++] = libro;
	}

	fclose(fichero);
	return 1;
}

#endif /* DOMAIN_LIBRO_C_ */
