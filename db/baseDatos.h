#ifndef BD_BASEDATOS_H_
#define BD_BASEDATOS_H_

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <winsock2.h>
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

void alquilarLibroBBDD(sqlite3 *db, char *dniUsuario,  char *titulo, SOCKET comm_socket, char *sendBuff);
void devolverLibroBBDD(sqlite3 *db, char *dniUsuario, char *titulo, SOCKET comm_socket, char *sendBuff);
void agregarLibroBD(sqlite3 *db, Admin *admin, ListaLibros *listaLibros);

void verLibrosReservadosBBDD(sqlite3 *db, char *dniUsuario,SOCKET comm_socket, char *sendBuff);
void iniciarSesionClienteBD(sqlite3 *db, Cliente *cliente, int *enc, char *dni, char *contrasenia, SOCKET comm_socket, char *sendBuff);
void eliminarLibroBD(sqlite3 *db, ListaLibros *listaLibros);


void visualizarLibrosBBDD(sqlite3 *db,SOCKET comm_socket, char *sendBuff);
void registrarBD(sqlite3 *db, SOCKET s, char *sendBuff, char *recvBuff);
int existeCliente(sqlite3 *db, const char *dni);
void marcarLibroComoNoDisponibleBD(sqlite3 *db, const char *isbn);

#endif /* BD_BASEDATOS_H_ */
