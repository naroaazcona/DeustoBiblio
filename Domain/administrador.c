#include "administrador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void iniciarSesion(char *usuario, char *contrasenia, int *resultado,
		int *intentos) {
	char linea[200];
	*intentos = 3;
	*resultado = 0;
	printf("Iniciando sesion como administrador...\n");
	printf("Introduce tu nombre de usuario: ");
	fflush(stdout);
	fflush(stdin);
	gets(usuario);
	printf("Introduce tu contrase�a (%d intentos restantes): ", *intentos);
	fflush(stdout);
	fflush(stdin);
	gets(contrasenia);
	while (*resultado != 2 && *intentos > 0) {
		(*intentos)--;
		FILE *fichero = fopen("admin.txt", "r");
		if (fichero != (FILE*) NULL) {
			while (fscanf(fichero, "%s", linea) !=EOF && *resultado != 2) {
				char *u = strtok(linea, ";");
				char *c = strtok(NULL, "");
				if (strcmp(u, usuario) == 0) {
					*resultado = 1;
					if (strcmp(c, contrasenia) == 0) {
						*resultado = 2;
					}
				}
			}
			fclose(fichero);

		}
		if (*resultado == 0) {
			printf("Introduce tu usuario (%d intentos restantes): ", *intentos);
			fflush(stdout);
			fflush(stdin);
			gets(usuario);

		} else if (*resultado == 1) {
			printf("Introduce tu contrase�a (%d intentos restantes): ",
					*intentos);
			fflush(stdout);
			fflush(stdin);
			gets(contrasenia);
		}

	}

}


void agregarLibro(Admin *admin, ListaLibros *listaLibros) {
	Libro libro = pedirDatosLibro();
	int i = 0;

	FILE *ficheroLibros = fopen("libros.txt", "r");

	if (ficheroLibros == NULL) {
		printf("No se ha podido abrir el fichero de los libros");
		fflush(stdout);
		return;
	} else {
		fprintf(ficheroLibros, "%s;%s;%d;%s;%s;%d\n", libro.ISBN, libro.titulo,
				libro.anioPubli, libro.autor, libro.genero,
				libro.disponibilidad);
		if (listaLibros->aLibros == NULL) {
			printf("ENTRO");
			listaLibros->aLibros = (Libro*) malloc(sizeof(Libro));
		} else {
			Libro *aux = (Libro*) malloc(
					listaLibros->numeroLibros * sizeof(Libro));
			for (i = 0; i < listaLibros->numeroLibros; i++) {
				aux[i] = listaLibros->aLibros[i];
			}
			free(listaLibros->aLibros);

			listaLibros->aLibros = (Libro*) malloc(
					(listaLibros->numeroLibros + 1) * sizeof(Libro));
			for (i = 0; i < listaLibros->numeroLibros; i++) {
				listaLibros->aLibros[i] = aux[i];
			}
			free(aux);
		}

		listaLibros->aLibros[listaLibros->numeroLibros] = libro;
		listaLibros->numeroLibros++;
	}

	fclose(ficheroLibros);
	printf("Libro añadido correctamente y añadido al fichero.\n");
	fflush(stdout);
}
void eliminarLibroAdmin(Admin *admin, ListaLibros *listaLibros, char *isbn) {
	int pos = buscarLibro(*listaLibros, isbn);
	int i;
	if (pos != -1) {
		printf("ERROR: No se ha encontrado ningun libro con el ISBN %s\n",isbn);
		fflush(stdout);
		return;
	}

	for (i = pos; i < listaLibros->numeroLibros; i++) {
		listaLibros->aLibros[i] = listaLibros->aLibros[i + 1];
	}

	listaLibros->numeroLibros--;
}

void verLibrosAdmin(ListaLibros listaLibros){
	int i;

	if(listaLibros.numeroLibros == 0){
		printf("No hay libros para visualizar");
		fflush(stdout);
	}

	printf("%10s%30s%10s%20s%15s%10s\n", "ISBN", "Título", "Año",
			"Autor", "Género", "Disponible");
	printf("-------------------------------------------------------------------------------------------\n");
	fflush(stdout);

	for(i = 0; i < listaLibros.numeroLibros; i++){
		Libro l = listaLibros.aLibros[i];
		printf("%10s%30s%10d%20s%15s%10i\n", l.ISBN, l.titulo, l.anioPubli,
				l.autor, l.genero, l.disponibilidad);
	}
}


