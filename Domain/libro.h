#ifndef DOMAIN_LIBRO_H_
#define DOMAIN_LIBRO_H_

typedef struct{
	int ISBN;
	char titulo[50];
	int anioPubli;
	char autor[20];
	char genero[20];
	int disponibilidad;
}Libro;

typedef struct{
	Libro libros[200];
	int numeroLibros;
}ListaLibros;

Libro pedirDatosLibro();
void visualizarTitulosLibro();
void visualizarLibro(Libro l);
void marcarLibroComoNoDispo(Libro *l);
void aniadirLibro(ListaLibros *listaLibros, Libro libro);
void eliminarLibro(ListaLibros *listaLibro, char *isbn);
int buscarLibro(ListaLibros listaLibros, char *isbn);
void visualizarListaLibros(ListaLibros listaLibros);
int alquilarLibro(ListaLibros *ll, char *isbn);
int devolverLibro(ListaLibros *ll, char *isbn);


//typedef struct{
//	char isbn[20];
//	char titulo[50];
//	int anioPubli;
//	char autor[50];
//	char genero[15];
//	int disponibilidad; //1 disponible - 0 no disponible
//}Libro;

#endif /* DOMAIN_LIBRO_H_ */
