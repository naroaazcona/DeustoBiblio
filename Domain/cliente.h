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

void registrar();
void iniciarSesionCliente(/*Cliente *cliente*/char *email, char *contrasenia);
void reservaLibros(Cliente *cliente, ListaLibros *listaLibros, char *isbn);
void devolverLibroCliente(Cliente *cliente, ListaLibros *listaLibros, char *isbn);
void verLibrosReservador(Cliente c);
void verPerfil(Cliente c);




#endif /* DOMAIN_CLIENTE_H_ */
