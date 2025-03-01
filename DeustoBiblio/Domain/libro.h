#ifndef DOMAIN_LIBRO_H_
#define DOMAIN_LIBRO_H_

typedef struct{
	int ISBN;
	char titulo[50];
	char año[11];
	char autor[20];
	char genero[20];
	int disponibilidad;
}Libro;

typedef struct{
	Libro libros[200];
	int numeroLibros;
}ListaLibros;


void marcarLibroAlquilado(Libro *libro);
void aniadirLibro(ListaLibros *listaLibros, Libro libro);
void eliminarLibro(ListaLibros *listaLibro, char *isbn);
int buscarLibro(ListaLibros listaLibros, char *isbn);
void visualizarLibro(ListaLibros listaLibros);



#endif /* DOMAIN_LIBRO_H_ */
