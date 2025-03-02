#include "menu.h"
#include <stdio.h>

char menuPrincipal(){
	char opcion;

	printf("Bienvenid@ a DeustoBiblio\n");
	printf("Menu Principal\n");
	printf("1. Administrador\n");
	printf("2. Cliente\n");
	printf("0. Salir\n");
	printf("Elige una opción: ");
	fflush(stdout);

	fflush(stdin);
	scanf("%c",&opcion);
	return opcion;
}


char menuClienteInicio(){
	char opcion;

	printf("Menu Inicio de Sesión de Cliente\n");
	printf("1. Iniciar Sesión\n");
	printf("2. Registrarse\n");
	printf("0. Salir\n");
	printf("Elige una opción: ");
	fflush(stdout);

	fflush(stdin);
	scanf("%c",&opcion);

	return opcion;

}


char menuPrincipalCliente(){
	char opcion;

	printf("Menu Principal del Cliente\n");
	printf("1. Ver Perfil\n");
	printf("2. Ver libros disponibles\n");
	printf("3. Reservar libros\n");
	printf("4. Devolver libros\n");
	printf("5. Libros Reservados\n");
	printf("0. Salir\n");
	printf("Elige una opción: ");
	fflush(stdout);

	fflush(stdin);
	scanf("%c",&opcion);
	return opcion;

}

char menuAdministradorInicio(){
	char opcion;

	printf("Menu Inicio de Sesión del Administrador\n");
	printf("1. Iniciar Sesión\n");
	printf("0. Salir\n");
	printf("Elige una opción: ");
	fflush(stdout);

	fflush(stdin);
	scanf("%c",&opcion);
	return opcion;

}

char menuPrincipalAdministrador(){
	char opcion;

	printf("Menu Principal del Administrador\n");
	printf("1. Eliminar libro\n");
	printf("2. Añadir libro\n");
	printf("3. Visualizar datos de los cliente\n");
	printf("4. Visualizar datos de los libros\n");
	printf("0. Salir\n");
	printf("Elige una opción: ");
	fflush(stdout);

	fflush(stdin);
	scanf("%c",&opcion);
	return opcion;
}




