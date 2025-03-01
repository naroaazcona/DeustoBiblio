#include "menu.h"
#include <stdio.h>

char MenuPrincipal(){
	char opcion;

	printf("1. Administrador");
	printf("2. Cliente");
	printf("0. Salir");
	printf("Elige una opción: ");
	fflush(stdout);

	fflush(stdin);
	scanf("%c",&opcion);
	return opcion;
}


char menuClienteInicio(){
	char opcion;

	printf("1. Iniciar Sesión");
	printf("2. Registrarse");
	printf("0. Salir");
	printf("Elige una opción: ");
	fflush(stdout);

	fflush(stdin);
	scanf("%c",&opcion);

	return opcion;

}


char menuPrincipalCliente(){
	char opcion;

	printf("1. Ver Perfil");
	printf("2. Ver libros disponibles");
	printf("3. Reservar libros");
	printf("4. Devolver libros");
	printf("5. Libros Reservados");
	printf("0. Salir");
	printf("Elige una opción: ");
	fflush(stdout);

	fflush(stdin);
	scanf("%c",&opcion);
	return opcion;

}

char menuAdministradorInicio(){
	char opcion;

	printf("1. Iniciar Sesión");
	printf("0. Salir");
	printf("Elige una opción: ");
	fflush(stdout);

	fflush(stdin);
	scanf("%c",&opcion);
	return opcion;

}

char menuPrincipalAdministrador(){
	char opcion;

	printf("1. Eliminar libro");
	printf("2. Añadir libro");
	printf("3. Visualizar datos de los cliente");
	printf("4. Visualizar datos de los libros");
	printf("0. Salir");
	printf("Elige una opción: ");
	fflush(stdout);

	fflush(stdin);
	scanf("%c",&opcion);
	return opcion;
}




