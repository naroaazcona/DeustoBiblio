#include "administrador.h"
#include <stdio.h>


void iniciarSesion(char *usuario, char *contrasenia){

	printf("Iniciando sesion como administrador...\n");
	printf("Introduce tu nombre de usuario: ");
	fflush(stdout);
	fflush(stdin);
	gets(usuario);

	printf("Introduce tu contraseña: ");
	fflush(stdout);
	fflush(stdin);
	gets(contrasenia);

}


