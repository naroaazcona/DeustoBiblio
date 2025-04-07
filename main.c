/*Este va a ser el main*/
#include <stdio.h>
#include "domain/menu.h"
#include "domain/cliente.h"
#include "domain/administrador.h"
#include "domain/libro.h"
#include "db/baseDatos.h"
#include "config.h"
#include "logger.h"

#define FICHERO_LIBROS "libros.txt"
#define FICHERO_CLIENTE "clientes.txt"
#define FICHERO_ADMIN "admin.txt"

int main() {
	char opcion, opcionClienteInicio, opcionAdminInicio, opcionClientePrincipal,
			opcionAdminPrincipal, usuario[20], contrasenia[20];
	int resultado, intentos;
	Cliente c;
	Admin admin;
	ListaLibros listaLibros;
	ListaClientes listaClientes;
	Libro libro;
	int encontrado;

	Config conf = leerConfiguracion("config.properties");
	escribirLog("Configuración leída correctamente.");
	insertarLog("\033[3;35m Configuración leída correctamente.\033[0m\n");

	inicializarListaClientes(&listaClientes);
	inicializarListaLibros(&listaLibros);
	cargarLibrosDesdeFichero(&listaLibros);
	cargarClientesFicheroEnLista(&listaClientes);

	sqlite3 *db = conectarDB();
	crearTablaLibro(db);
	crearTablaUsuario(db);
	crearTablaReserva(db);
	volcarFicheroLibroABBDD(FICHERO_LIBROS, db);
	volcarFicheroClienteABBDD(FICHERO_CLIENTE, db);

	do {

		opcion = menuPrincipal();
		switch (opcion) {
		case '1':
			do {
				opcionAdminInicio = menuAdministradorInicio();
				switch (opcionAdminInicio) {
				case '1':
					iniciarSesion(usuario, contrasenia, &resultado, &intentos);
					if (resultado != 2) {
						printf("Se te han acabado los intentos\n");
						fflush(stdout);
						escribirLog("Inicio de sesión fallida.");
						insertarLog("\033[3;35m Inicio de sesión fallida.\033[0m\n");
						break;
					} else {
						printf("Ongi etorri!!!\n");
						fflush(stdout);
						escribirLog("Sesión iniciada por el Administrador.");
						insertarLog("\033[3;35m Sesión iniciada por el Administrador.\033[0m\n");

					}
					do {
						opcionAdminPrincipal = menuPrincipalAdministrador();
						switch (opcionAdminPrincipal) {
						case '1':
							printf("Eliminar libro\n");
							fflush(stdout);
							eliminarLibroAdmin(&admin, &listaLibros,
									libro.ISBN);
							break;
						case '2':
							printf("Añadir libro\n");
							fflush(stdout);
							agregarLibroBD(db, &admin, &listaLibros);
							break;
						case '3':
							printf("Visualizar datos de los clientes:\n");
							fflush(stdout);
							visualizarClientes(listaClientes);
							break;
						case '4':
							printf("Visualizar datos de los libros:\n");
							fflush(stdout);
							verLibrosAdmin(listaLibros);
							break;
						case '0':
							printf("Volviendo al menu principal...\n");
							break;
						default:
							printf("Error! La opción seleccionada no es correcta\n");
							fflush(stdout);
						}

					} while (opcionAdminPrincipal != '0');
					break;
				case '0':
					printf("Volviendo al menú principal...\n");
					fflush(stdout);
					break;
				default:
					printf("Error! La opción seleccionada no es correcta\n");
					fflush(stdout);
					escribirLog("Opción escogida NO correcta.");
					insertarLog("\033[3;35m Opción escogida NO correcta.\033[0m\n");
				}
			} while (opcionAdminInicio != '0');
			break;
		case '2':
			do {
				opcionClienteInicio = menuClienteInicio();
				switch (opcionClienteInicio) {
				case '1':
					iniciarSesionCliente(&c, &encontrado);
					escribirLog("Sesión iniciada por el Cliente.");
					insertarLog("\033[3;35m Sesión iniciada por el Cliente.\033[0m\n");
					if (encontrado) {
						do {
							opcionClientePrincipal = menuPrincipalCliente();
							switch (opcionClientePrincipal) {
							case '1':
								printf("Visitar perfil\n");
								fflush(stdout);
								verPerfil(c);
								break;
							case '2':
								printf("Ver libros disponibles\n");
								fflush(stdout);
								visualizarLibrosBBDD(db);
								break;
							case '3':
								printf("Reservar libros\n");
								fflush(stdout);
								alquilarLibroBBDD(db, c.dni);
								break;
							case '4':
								printf("Devolver libros\n");
								fflush(stdout);
								devolverLibroBBDD(db, c.dni);
								break;
							case '5':
								printf("Ver libros reservados\n");
								fflush(stdout);
								verLibrosReservados(c);
								break;
							case '0':
								printf("Volviendo al menu principal...\n");
								break;
							default:
								printf("Error! La opción seleccionada no es correcta\n");
								fflush(stdout);
							}

						} while (opcionClientePrincipal != '0');
					}
					break;
				case '2':
					registrarBD(db);
					break;
				case '0':
					printf("Volviendo al menú principal...\n\n");
					fflush(stdout);
					break;
				default:
					printf("Opción invalida. Por favor, ingrese una opción válida.\n");
					fflush(stdout);
				}

			} while (opcionClienteInicio != '0');

			break;
		case '0':
			printf("Hasta pronto!!\n");
			fflush(stdout);
			escribirLog("Se ha cerrado sesión.");
			insertarLog("\033[3;35m Se ha cerrado sesión.\033[0m\n");
			break;
		default:
			printf("Opción invalida. Por favor, ingrese una opción válida.\n");
			fflush(stdout);
		}
	} while (opcion != '0');
	volcarBBDDClienteAFichero(FICHERO_CLIENTE, db);
	volcarBBDDLibroAFichero(FICHERO_LIBROS, db);

	if (sqlite3_close(db) == SQLITE_OK) {
		printf("\033[1;32m BBDD cerrada correctamente.\033[0m\n");
		fflush(stdout);
	} else {
		printf("\033[1;32m BBDD no se ha cerrado bien.\033[0m\n");
		fflush(stdout);
	}

	return 0;

}
