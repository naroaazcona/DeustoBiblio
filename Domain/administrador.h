#ifndef DOMAIN_ADMINISTRADOR_H_
#define DOMAIN_ADMINISTRADOR_H_
#include "libro.h"
#include "cliente.h"

typedef struct{
	char usuario[50];
	char contrasenia[50];
}Admin;

void iniciarSesion(char *usuario, char *contrasenia, int *resultado,int *intentos);
void agregarLibro(Admin *admin, ListaLibros *listaLibros);
void eliminarLibroAdmin(Admin *admin, ListaLibros *listaLibros, char *isbn);
void verLibrosAdmin(ListaLibros listaLibros);
void visualizarClientes(ListaClientes clientes);


#endif /* DOMAIN_ADMINISTRADOR_H_ */
