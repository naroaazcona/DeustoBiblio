#include "administrador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void iniciarSesion(char *usuario, char *contrasenia, int *resultado, int *intentos) {
    char linea[200];
    char *u, *c;
    int encontrado = 0;

    *resultado = 0;

    FILE *fichero = fopen("admin.txt", "r");
    if (fichero == NULL) {
        printf("Error: No se pudo abrir el archivo admin.txt\n");
        *resultado = 0;
        return;
    }

    while (fgets(linea, sizeof(linea), fichero) != NULL && !encontrado) {
        linea[strcspn(linea, "\n")] = 0;

        u = strtok(linea, ";");
        c = strtok(NULL, ";");

        if (u != NULL && c != NULL) {
            if (strcmp(u, usuario) == 0) {
                encontrado = 1; // Usuario encontrado
                *resultado = 1; // Usuario correcto, verificar contraseña

                if (strcmp(c, contrasenia) == 0) {
                    *resultado = 2; // Usuario y contraseña correctos
                    break;
                }
                break;
            }
        }
    }

    fclose(fichero);

    if (!encontrado) {
        *resultado = 0;
    }
}

void visualizarClientes(ListaClientes clientes) {
	int i;

	if (clientes.numeroClientes == 0) {
		printf("No hay clientes");
		fflush(stdout);
	}

	printf("\033[1;33m%10s|%20s|%20s|%30s|%20s|%30s|%20s\n\033[0m", "DNI",
			"NOMBRE", "APELLIDO", "EMAIL", "NÚMERO TELÉFONO", "DIRECCIÓN",
			"LIBROS RESERVADOS");
	printf(
			"\033[1;33m----------------------------------------------------------------------------------------------------------------------------------------------------------\n\033[0m");
	fflush(stdout);

	for (i = 0; i < clientes.numeroClientes; i++) {
		printf("\033[1;33m%10s|%20s|%20s|%30s|%20s|%30s|%17d\n\033[0m",
				clientes.aClientes[i].dni, clientes.aClientes[i].nombre,
				clientes.aClientes[i].apellido, clientes.aClientes[i].email,
				clientes.aClientes[i].numeroTlf,
				clientes.aClientes[i].direccion,
				clientes.aClientes[i].numerosLReservados);
	}
}

