#include "cliente.h"


void inicializarListaClientes(ListaClientes *ll){
	ll->aClientes = NULL;
	ll->numeroClientes = 0;
}
void visualizarTitulosPerfil(SOCKET comm_socket, char *sendBuff) {
	sprintf(sendBuff,"\033[1;33m%10s|%10s|%10s|%30s|%20s|%20s|%20s|%20s\n\033[0m", "DNI",
			"NOMBRE", "APELLIDO", "EMAIL", "CONTRASEÑA", "NÚMERO TELÉFONO",
			"DIRECCIÓN", "LIBROS RESERVADOS");
	send(comm_socket,sendBuff,sizeof(sendBuff),0);  //enviar
	sprintf(sendBuff,
			"\033[1;33m-----------------------------------------------------------------------------------------------------------------------------------------------\n\033[0m");
	send(comm_socket,sendBuff,sizeof(sendBuff),0);
}

void verPerfil(Cliente c, SOCKET comm_socket, char *sendBuff) {
	visualizarTitulosPerfil(comm_socket,sendBuff);
	sprintf(sendBuff,"\033[1;33m%10s|%10s|%10s|%30s|%19s|%18s|%19s|%20d\n\033[0m", c.dni,
			c.nombre, c.apellido, c.email, c.contrasenia, c.numeroTlf,
			c.direccion, c.numerosLReservados);
	send(comm_socket,sendBuff,sizeof(sendBuff),0);
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

