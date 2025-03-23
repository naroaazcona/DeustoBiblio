#ifndef DOMAIN_CLIENTE_H_
#define DOMAIN_CLIENTE_H_

#include "libro.h"

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

int telefonoValido(char *telefono);
int dniValido(char *dni);
void registrar();
void iniciarSesionCliente(Cliente *cliente, char *email, char *contrasenia);
void reservaLibros(Cliente *cliente, ListaLibros *listaLibros, char *isbn);
int buscarLibroCliente(Cliente c, char *isbn);
void devolverLibroCliente(Cliente *cliente, ListaLibros *listaLibros, char *isbn);
void verLibrosReservados(Cliente c);
void verPerfil(Cliente c);




#endif /* DOMAIN_CLIENTE_H_ */
