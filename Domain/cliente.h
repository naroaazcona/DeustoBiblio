#ifndef DOMAIN_CLIENTE_H_
#define DOMAIN_CLIENTE_H_

#include "libro.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

typedef struct{
	char dni[10];
	char nombre[20];
	char apellido[20];
	char email[50];
	char contrasenia[50];
	char numeroTlf[10];
	char direccion[50];
	int numerosLReservados;
	Libro librosReservados[];
}Cliente;

typedef struct{
	Cliente *aClientes;
	int numeroClientes;
}ListaClientes;

void inicializarListaClientes(ListaClientes *ll);
int telefonoValido(char *telefono);
int dniValido(char *dni);
void registrar();
void iniciarSesionCliente(Cliente *cliente, int *encontrado);
int buscarLibroCliente(Cliente c, char *isbn);
void verLibrosReservados(Cliente c);
void visualizarTitulosPerfil();
void verPerfil(Cliente c);
int cargarClientesFicheroEnLista(ListaClientes *listaClientes);



#endif /* DOMAIN_CLIENTE_H_ */
