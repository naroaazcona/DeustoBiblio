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


void visualizarClientes(ListaClientes clientes) {
	int i;

	if(clientes.numeroClientes == 0){
		printf("No hay clientes");
		fflush(stdout);
	}

    printf("\033[1;33m%10s|%20s|%20s|%30s|%20s|%30s|%20s\n\033[0m", "DNI", "NOMBRE", "APELLIDO", "EMAIL",
			"NÚMERO TELÉFONO", "DIRECCIÓN", "LIBROS RESERVADOS");
	printf("\033[1;33m----------------------------------------------------------------------------------------------------------------------------------------------------------\n\033[0m");
    fflush(stdout);

    for (i = 0; i < clientes.numeroClientes; i++) {
        printf("\033[1;33m%10s|%20s|%20s|%30s|%20s|%30s|%17d\n\033[0m",
                clientes.aClientes[i].dni, clientes.aClientes[i].nombre, clientes.aClientes[i].apellido, clientes.aClientes[i].email,
				clientes.aClientes[i].numeroTlf, clientes.aClientes[i].direccion, clientes.aClientes[i].numerosLReservados);
    }
}

