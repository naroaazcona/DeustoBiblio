#include "administrador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void iniciarSesion(Admin *admin, char *usuario, char *contrasenia) {
	int encontrado = 0;
	int intentos = 3;
	FILE *fichero = fopen("admin.txt", "r");

	printf("Iniciando sesion como administrador...\n");
	printf("Introduce tu nombre de usuario: ");
	fflush(stdout);
	fflush(stdin);
	gets(usuario);
	//fgets(usuario, 50, stdin);
	//usuario[strcspn(usuario, "\n")] = 0;

	if (fichero == NULL) {
		printf("Error en la apertura del fichero");
		fflush(stdout);
		return;
	} else {
		while (fscanf(fichero, "%49[^;];%49[^;]\n", admin->usuario,
				admin->contrasenia) != EOF) {
			if (strcmp(usuario, admin->usuario) == 0) {
				encontrado = 1;
				while (intentos > 0) {
					printf("Introduce tu contraseña (%d intentos restantes): ",
							intentos);
					fflush(stdout);
					fflush(stdin);
					gets(contrasenia);

					if (strcmp(contrasenia, admin->contrasenia) == 0) {
						printf("Bienvenid@, %s!\n", admin->usuario);
						fclose(fichero);
						return;
					} else {
						printf("Contraseña incorrecta. \n");
						intentos--;
					}
				}
				printf(
						"Demasiados intentos fallidos. Inicio de sesión cancelado");
				fclose(fichero);
			}

}

	printf("Demasiados intentos fallados");
	fflush(stdout);
	fclose(fichero);
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


