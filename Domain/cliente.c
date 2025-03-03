#include "cliente.h"
#include <stdio.h>

void iniciarSesionCliente(char *email, char *contrasenia){

	printf("Iniciando sesion como cliente...\n");
	printf("Introduce tu email: ");
	fflush(stdout);
	fflush(stdin);
	gets(email);

	printf("Introduce tu contraseña: ");
	fflush(stdout);
	fflush(stdin);
	gets(contrasenia);

}


void registroCliente(){
	Cliente c;

	printf("Registrando nuevo usuario....\n");
	printf("Introduce tu nombre:\n");
	fflush(stdout);
	fflush(stdin);
	gets(c.nombre);

	printf("Introduce tu apellido:\n");
	fflush(stdout);
	fflush(stdin);
	gets(c.apellido);

	printf("Introduce tu DNI:\n");
	fflush(stdout);
	fflush(stdin);
	gets(c.dni);

	printf("Introduce tu correo electrónico:\n");
	fflush(stdout);
	fflush(stdin);
	gets(c.email);

	printf("Introduce tu número de telefono:\n");
	fflush(stdout);
	fflush(stdin);
	gets(c.numeroTlf);

	printf("Introduce tu contraseña:\n");
	fflush(stdout);
	fflush(stdin);
	gets(c.contrasenia);

}


