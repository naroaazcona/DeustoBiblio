/*Este va a ser el main*/
/*#include <stdio.h>
#include "domain/menu.h"
#include "domain/cliente.h"
#include "domain/administrador.h"
#include "domain/libro.h"
#include "db/baseDatos.h"
#include "config.h"
#include "logger.h"
#include <unistd.h>

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
						printf("\033[0;31mSe te han acabado los intentos\n\033[0m");
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
							eliminarLibroBD(db, &listaLibros);
							sleep(1);
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
							sleep(1);
							break;
						case '4':
							printf("Visualizar datos de los libros:\n");
							fflush(stdout);
							visualizarLibrosBBDD(db);
							sleep(1);
							break;
						case '0':
							printf("Volviendo al menu principal...\n");
							break;
						default:
							printf("\033[0;31mError! La opción seleccionada no es correcta\n\033[0m");
							fflush(stdout);
						}

					} while (opcionAdminPrincipal != '0');
					break;
				case '0':
					printf("Volviendo al menú principal...\n");
					fflush(stdout);
					break;
				default:
					printf("\033[0;31mError! La opción seleccionada no es correcta\n\033[0m");
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
					iniciarSesionClienteBD(db,&c,&encontrado);
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
								sleep(1);
								break;
							case '2':
								printf("Ver libros disponibles\n");
								fflush(stdout);
								visualizarLibrosBBDD(db);
								sleep(1);
								break;
							case '3':
								printf("Reservar libros\n");
								fflush(stdout);
								alquilarLibroBBDD(db, c.dni);
								sleep(1);
								break;
							case '4':
								printf("Devolver libros\n");
								fflush(stdout);
								devolverLibroBBDD(db, c.dni);
								break;
							case '5':
								printf("Ver libros reservados\n");
								fflush(stdout);
								verLibrosReservadosBBDD(db,c.dni);
								sleep(1);
								break;
							case '0':
								printf("Volviendo al menu principal...\n");
								break;
							default:
								printf("\033[0;31mError! La opción seleccionada no es correcta\n\033[0m");
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
					printf("\033[0;31mOpción invalida. Por favor, ingrese una opción válida.\n\033[0m");
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
			printf("\033[0;31mOpción invalida. Por favor, ingrese una opción válida.\n\033[0m");
			fflush(stdout);
		}
	} while (opcion != '0');
	volcarBBDDClienteAFichero(FICHERO_CLIENTE, db);
	volcarBBDDLibroAFichero(FICHERO_LIBROS, db);

	return 0;

}*/
