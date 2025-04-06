#include "cliente.h"


void inicializarListaClientes(ListaClientes *ll){
	ll->aClientes = NULL;
	ll->numeroClientes = 0;
}

int telefonoValido(char *telefono) {
	if (strlen(telefono) != 9)
		return 0;
	for (int i = 0; i < 9; i++) {
		if (!isdigit(telefono[i]))
		return 0;
	}
	return 1;
}
int dniValido(char *dni) {
	if (strlen(dni) != 9)
		return 0;
	for (int i = 0; i < 8; i++) {
		if (!isdigit(dni[i]))
			return 0;
	}
	if (!isalpha(dni[8]))
		return 0;
	return 1;
}

void registrar() {
	Cliente c;
	FILE *ficheroClientes;

	printf("Registrando nuevo usuario....\n");
	printf("Introduce tu nombre:\n");
	fflush(stdout);
	fflush(stdin);
	gets(c.nombre);
	c.nombre[strcspn(c.nombre, "\n")] = 0;

	printf("Introduce tu apellido:\n");
	fflush(stdout);
	fflush(stdin);
	gets(c.apellido);
	c.apellido[strcspn(c.apellido, "\n")] = 0;

	do {
		printf("Introduce tu DNI:\n");
		fflush(stdout);
		fflush(stdin);
		gets(c.dni);
		c.dni[strcspn(c.dni, "\n")] = 0;

		if (!dniValido(c.dni)) {
			printf(
					"ERROR: DNI introducido no es valido. Debe de tener 8 números y 1 letra. Intentelo de nuevo");
			fflush(stdout);
		}

	} while (!dniValido(c.dni));

	printf("Introduce tu correo electrónico:\n");
	fflush(stdout);
	fflush(stdin);
	gets(c.email);
	c.email[strcspn(c.email, "\n")] = 0;

	do {
		printf("Introduce tu número de telefono:\n");
		fflush(stdout);
		fflush(stdin);
		gets(c.numeroTlf);
		c.numeroTlf[strcspn(c.numeroTlf, "\n")] = 0;

		if (!telefonoValido(c.numeroTlf)) {
			printf(
					"ERROR: El número de telefono introducido no es valido. Debe de tener 9 números. Intentelo de nuevo. ");
			fflush(stdout);
		}
	} while (!telefonoValido(c.numeroTlf));

	printf("Introduce tu dirección:\n");
	fflush(stdout);
	fflush(stdin);
	gets(c.numeroTlf);
	c.direccion[strcspn(c.direccion, "\n")] = 0;

	printf("Introduce tu contraseña:\n");
	fflush(stdout);
	fflush(stdin);
	gets(c.contrasenia);
	c.contrasenia[strcspn(c.contrasenia, "\n")] = 0;

	c.numerosLReservados = 0;

	ficheroClientes = fopen("clientes.txt", "a");
	if (ficheroClientes == NULL) {
		printf("ERROR: No se ha podido abrir el fichero\n");
		fflush(stdout);
		return;
	} else {
		fprintf(ficheroClientes, "%s;%s;%s;%s;%s;%s;%s;%d\n", c.dni, c.nombre,
				c.apellido, c.email, c.contrasenia, c.numeroTlf, c.direccion,
				c.numerosLReservados);
	}

	fclose(ficheroClientes);
	printf("El registro se ha realizado correctamente, %s %s!\n", c.nombre,
			c.apellido);
	fflush(stdout);

}

void iniciarSesionCliente(Cliente *cliente, int *encontrado) {
	FILE *ficheroClientes;
	int intentos = 3;
	char linea[400], temp[50], tempC[50];

	*encontrado = 0;

	printf("Iniciando sesion como cliente...\n");
	printf("Introduce tu email: ");
	fflush(stdout);
	fflush(stdin);
	gets(temp);

	ficheroClientes = fopen("clientes.txt", "r");
	if (ficheroClientes == NULL) {
		printf("No se pudo abrir el archivo de clientes.\n");
		fflush(stdout);
		return;
	} else
		while (!(*encontrado) && fgets(linea, 400, ficheroClientes) != NULL) {
			sprintf(cliente->dni, "%s", strtok(linea, ";"));
			sprintf(cliente->nombre, "%s", strtok(NULL, ";"));
			sprintf(cliente->apellido, "%s", strtok(NULL, ";"));
			sprintf(cliente->email, "%s", strtok(NULL, ";"));
			sprintf(cliente->contrasenia, "%s", strtok(NULL, ";"));
			sprintf(cliente->numeroTlf, "%s", strtok(NULL, ";"));
			sprintf(cliente->direccion, "%s", strtok(NULL, ";"));
			cliente->numerosLReservados = atoi(strtok(NULL, ""));
			if (strcmp(temp, cliente->email) == 0) {
				*encontrado = 1;
			}
		}
	if (*encontrado) {
		while (intentos > 0) {
			printf("Introduce tu contraseña (%d intentos restantes): ",
					intentos);
			fflush(stdout);
			fflush(stdin);
			gets(tempC);

			if (strcmp(tempC, cliente->contrasenia) == 0) {
				printf("Inicio de sesión exitoso. ¡Bienvenid@, %s %s!\n",
						cliente->nombre, cliente->apellido);
				fflush(stdout);
				fclose(ficheroClientes);
				return;
			} else {
				printf("Contraseña incorrecta.\n");
				fflush(stdout);
				intentos--;
			}
		}

		printf("Demasiados intentos fallidos. Inicio de sesión cancelado.\n");
		fflush(stdout);
		fclose(ficheroClientes);
		*encontrado = 0;
		return;

		fclose(ficheroClientes);
	} else {
		printf("El email no está registrado.\n");
		fflush(stdout);
	}

}


int buscarLibroCliente(Cliente c, char *isbn) {
	int pos = 0, enc = 0;
	while (!enc && pos < c.numerosLReservados) {
		if (strcmp(c.librosReservados[pos].ISBN, isbn) == 0) {
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

void verLibrosReservados(Cliente c) {
	if (c.numerosLReservados == 0) {
		printf("No tienes libros reservados \n");
		return;
	}

	printf("Libros reservados por %s %s : \n", c.nombre, c.apellido);
	for (int i = 0; i < c.numerosLReservados; i++) {
		printf(" - ISBN: %s \n", c.librosReservados[i].ISBN);
	}
}

void visualizarTitulosPerfil() {
	printf("\033[1;33m%10s|%10s|%10s|%30s|%20s|%20s|%20s|%20s\n\033[0m", "DNI",
			"NOMBRE", "APELLIDO", "EMAIL", "CONTRASEÑA", "NÚMERO TELÉFONO",
			"DIRECCIÓN", "LIBROS RESERVADOS");
	printf(
			"\033[1;33m-----------------------------------------------------------------------------------------------------------------------------------------------\n\033[0m");
	fflush(stdout);
}

void verPerfil(Cliente c) {
	visualizarTitulosPerfil();
	printf("\033[1;33m%10s|%10s|%10s|%30s|%19s|%18s|%19s|%20d\n\033[0m", c.dni,
			c.nombre, c.apellido, c.email, c.contrasenia, c.numeroTlf,
			c.direccion, c.numerosLReservados);
	fflush(stdout);

}

int cargarClientesFicheroEnLista(ListaClientes *listaClientes) {
	FILE *fichero = fopen("clientes.txt", "r");

	if (fichero == NULL) {
		printf("Error al abrir el fichero");
		fflush(stdout);
	}

	listaClientes->aClientes = NULL;
	listaClientes->numeroClientes = 0;

	char linea[256];
	while (fgets(linea, sizeof(linea), fichero) != NULL) {
		Cliente c;

		char *dni = strtok(linea, ";");
		char *nombre = strtok(NULL, ";");
		char *apellido = strtok(NULL, ";");
		char *email = strtok(NULL, ";");
		char *contrasenia = strtok(NULL, ";");
		char *numTlf = strtok(NULL, ";");
		char *direccion = strtok(NULL, ";");
		char *numLibros = strtok(NULL, "\n");

		if (dni && nombre && apellido && email && contrasenia && numTlf
				&& direccion) {
			strcpy(c.dni, dni);
			strcpy(c.nombre, nombre);
			strcpy(c.apellido, apellido);
			strcpy(c.email, email);
			strcpy(c.contrasenia, contrasenia);
			strcpy(c.numeroTlf, numTlf);
			strcpy(c.numeroTlf, numTlf);
			strcpy(c.direccion, direccion);
			c.numerosLReservados = atoi(numLibros);

			listaClientes->aClientes = realloc(listaClientes->aClientes,
					(listaClientes->numeroClientes + 1) * sizeof(Cliente));
			listaClientes->aClientes[listaClientes->numeroClientes] = c;
			listaClientes->numeroClientes++;

			if (listaClientes->aClientes == NULL) {
				printf("Error: No se pudo asignar memoria\n");
				fflush(stdout);
				fclose(fichero);
				return 0;

			}
		} else {
			printf("Error en el formato de la línea: %s\n", linea);
			fflush(stdout);
		}
	}
	fclose(fichero);
	return 1;
}

