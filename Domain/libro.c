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

void visualizarTitulosLibro() {
	printf("%30s%30s%20s%40s%20s%20s\n", "ISBN", "TÍTULO", "AÑO PUBLICACIÓN",
			"AUTOR", "GÉNERO", "DISPONIBILIDAD");
	fflush(stdout);

}

void visualizarLibro(Libro l) {
	printf("%30s%30s%20d%40s%20s%20d\n", l.ISBN, l.titulo, l.anioPubli, l.autor,
			l.genero, l.disponibilidad);
	fflush(stdout);

}

void marcarLibroComoNoDispo(ListaLibros *lista, char *isbn) {
	//l->disponibilidad = 0;
	int pos = buscarLibro(*lista, isbn);
	if (pos != -1) {
		lista->aLibros[pos].disponibilidad = 0;
		printf(
				"Libro con ISBN %s ha sido marcado como que no esta disponible ahora\n",
				isbn);
		fflush(stdout);
	} else {
		printf("Libro no encontrado\n");
	}
}

void eliminarLibro(ListaLibros *listaLibro, Libro libro) {
	int i;
	int pos = buscarLibro(*listaLibro, libro.ISBN);
	if (pos == -1) {
		printf(
				"No se ha eliminado el libro porque no existe en la biblioteca\n");
	} else {
		for (i = pos; i < listaLibro->numeroLibros - 1; i++) {
			listaLibro->aLibros[i] = listaLibro->aLibros[i + 1];
		}
		listaLibro->numeroLibros--;
	}

}

int buscarLibro(ListaLibros ll, char *isbn) {
	int pos = 0, enc = 0;
	while (!enc && pos < ll.numeroLibros) {
		if (strcmp(ll.aLibros[pos].ISBN, isbn) == 0) {
			enc = 1;
		} else {
			pos++;
		}
	}
	if (enc == 1) {
		return pos;
	} else {
		return -1;
	}

}

void visualizarLibros(ListaLibros ll) {
	int i;
	visualizarTitulosLibro();
	for (i = 0; i < ll.numeroLibros; i++) {
		visualizarLibro(ll.aLibros[i]);
	}
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
