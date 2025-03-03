#ifndef DOMAIN_CLIENTE_H_
#define DOMAIN_CLIENTE_H_

typedef struct{
	char dni[10];
	char nombre[20];
	char apellido[20];
	char email[50];
	char contrasenia[50];
	char numeroTlf[10];
	char direccion[50];
	Libro librosReservados[];
	int numerosLReservados;
}Cliente;

void registriar();
void inicioSesion(Cliente *cliente);
void reservaLibros(Cliente *cliente, ListaLibros *listaLibros, char *isbn);
void devolverLibro(Cliente *cliente, ListaLibros *listaLibros, char *isbn);
void verLibrosReservador(Cliente c);
void verPerfil(Cliente c);




#endif /* DOMAIN_CLIENTE_H_ */
