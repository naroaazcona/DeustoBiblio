#ifndef DOMAIN_ADMINISTRADOR_H_
#define DOMAIN_ADMINISTRADOR_H_

typedef struct{
	char usuario[50];
	char contrasenia[50];
}Admin;

void iniciarSesion(Admin *admin, char *usuario, char *contrasenia);
void agregarLibro(Admin *admin, ListaLibros *listaLibros);
void eliminarLibroAdmin(Admin *admin, ListaLibros *listaLibros, char *isbn);
void verLibrosAdmin(ListaLibros listaLibros);


#endif /* DOMAIN_ADMINISTRADOR_H_ */
