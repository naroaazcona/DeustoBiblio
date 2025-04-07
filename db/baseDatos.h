#ifndef BD_BASEDATOS_H_
#define BD_BASEDATOS_H_

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "sqlite3.h"
#include "../Domain/libro.h"
#include "../Domain/cliente.h"
#include "../Domain/administrador.h"

sqlite3* conectarDB();

void crearTablaLibro(sqlite3 *db);
void crearTablaUsuario(sqlite3 *db);
void crearTablaReserva(sqlite3 *db);

void volcarFicheroLibroABBDD(char *nomfich, sqlite3 *db);
void volcarFicheroClienteABBDD(char *nomfich, sqlite3 *db);
void volcarBBDDLibroAFichero(char *nomfich, sqlite3 *db);
void volcarBBDDClienteAFichero(char *nomfich, sqlite3 *db);

void alquilarLibroBBDD(sqlite3 *db, char *dniUsuario);
void devolverLibroBBDD(sqlite3 *db, char *dniUsuario);
void agregarLibroBD(sqlite3 *db, Admin *admin, ListaLibros *listaLibros);

void verLibrosReservadosBBDD(sqlite3 *db, char *dniUsuario);
void iniciarSesionClienteBD(sqlite3 *db, Cliente *cliente, int *enc);
void eliminarLibroBD(sqlite3 *db, ListaLibros *listaLibros);


void visualizarLibrosBBDD(sqlite3 *db);
void registrarBD(sqlite3 *db);
int existeCliente(sqlite3 *db, const char *dni);
void marcarLibroComoNoDisponibleBD(sqlite3 *db, const char *isbn);

#endif /* BD_BASEDATOS_H_ */
