#ifndef DOMAIN_LIBRO_H_
#define DOMAIN_LIBRO_H_

typedef struct{
	char ISBN[10];
	char titulo[50];
	int anioPubli;
	char autor[20];
	char genero[20];
	int disponibilidad;
}Libro;

typedef struct{
	Libro * aLibros;
	int numeroLibros;
}ListaLibros;

Libro pedirDatosLibro();
void visualizarTitulosLibro();
void visualizarLibro(Libro l);
//void marcarLibroComoNoDispo(Libro *l);
void marcarLibroComoNoDispo(ListaLibros *lista, char *isbn);
void aniadirLibro(ListaLibros *listaLibros, Libro libro);
void eliminarLibro(ListaLibros *listaLibro, Libro libro);
int buscarLibro(ListaLibros listaLibros, char *isbn);
void visualizarListaLibros(ListaLibros listaLibros);
int alquilarLibro(ListaLibros *ll, char *isbn);
int devolverLibro(ListaLibros *ll, char *isbn);

#endif /* DOMAIN_LIBRO_H_ */
