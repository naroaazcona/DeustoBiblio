// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include <winsock2.h>
/*Este va a ser el main*/
#include "domain/menu.h"
#include "domain/cliente.h"
#include "domain/administrador.h"
#include "domain/libro.h"
#include "db/baseDatos.h"
#include "config.h"
#include "logger.h"
#define BUFFER_SIZE 512

#define FICHERO_LIBROS "libros.txt"
#define FICHERO_CLIENTE "clientes.txt"
#define FICHERO_ADMIN "admin.txt"
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

int main(int argc, char *argv[]) {

	WSADATA wsaData;
	SOCKET conn_socket; //el que lleva la conexion
	SOCKET comm_socket; //el que lo comunica
	struct sockaddr_in server;
	struct sockaddr_in client;
	char sendBuff[512], recvBuff[512]; // lo que yo envio, lo que yo recibo

	printf("\nInitialising Winsock...\n"); // inicializa la libreria
	fflush(stdout);
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("Failed. Error Code : %d", WSAGetLastError());
		fflush(stdout);
		return -1;
	}

	printf("Initialised.\n");
	fflush(stdout);
	//SOCKET creation creacion del socket( la primera estructura
	if ((conn_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Could not create socket : %d", WSAGetLastError());
		fflush(stdout);
		WSACleanup();
		return -1;
	}

	printf("Socket created.\n");
	fflush(stdout);
	// cual es la ip y cual es el puerto
	server.sin_addr.s_addr = inet_addr(SERVER_IP); //INADDR_ANY;
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//BIND (the IP/port with socket)
	if (bind(conn_socket, (struct sockaddr*) &server,
			sizeof(server)) == SOCKET_ERROR) {
		printf("Bind failed with error code: %d", WSAGetLastError());
		fflush(stdout);
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	printf("Bind done.\n"); //DEJAR EL SOCKET EN ESPERA
	fflush(stdout);
	//LISTEN to incoming connections (socket server moves to listening mode)
	if (listen(conn_socket, 1) == SOCKET_ERROR) {
		printf("Listen failed with error code: %d", WSAGetLastError());
		fflush(stdout);
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	//ACCEPT incoming connections (server keeps waiting for them)
	printf("Waiting for incoming connections...\n");
	fflush(stdout);
	int stsize = sizeof(struct sockaddr);
	comm_socket = accept(conn_socket, (struct sockaddr*) &client, &stsize);
	// Using comm_socket is able to send/receive data to/from connected client
	if (comm_socket == INVALID_SOCKET) {
		printf("accept failed with error code : %d", WSAGetLastError());
		fflush(stdout);
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}
	printf("Incomming connection from: %s (%d)\n", inet_ntoa(client.sin_addr),
			ntohs(client.sin_port));
	fflush(stdout);
	// Closing the listening sockets (is not going to be used anymore)
	closesocket(conn_socket);

	int fin = 0;
	do {
		/*EMPIEZA EL PROGRAMA DEL SERVIDOR*/
		char opcion, opcionClienteInicio, opcionAdminInicio,
				opcionClientePrincipal, opcionAdminPrincipal, usuario[20],
				contrasenia[20], dni[10], titulo[100];
//			int resultado, intentos;
		int intentos = 3; //???
		int resultado = 0; //???
		Cliente c;
		ListaLibros listaLibros;
		ListaClientes listaClientes;
		int encontrado;

		/*Config conf = leerConfiguracion("config.properties");
		 escribirLog("Configuración leída correctamente.");
		 insertarLog("\033[3;35m Configuración leída correctamente.\033[0m\n");*/

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
//				opcion = menuPrincipal();
			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);  //recibir
			sscanf(recvBuff, "%c", &opcion); //obtener datos
			send(comm_socket, sendBuff, sizeof(sendBuff), 0);  //enviar
			switch (opcion) {
			case '1':
				do {
//						opcionAdminInicio = menuAdministradorInicio();
					recv(comm_socket, recvBuff, sizeof(recvBuff), 0);  //recibir
					sscanf(recvBuff, "%c", &opcionAdminInicio); //obtener datos
					sprintf(sendBuff, "Servidor Recibido: %c",
							opcionAdminInicio);
					send(comm_socket, sendBuff, sizeof(sendBuff), 0);  //enviar

					switch (opcionAdminInicio) {
					case '1':
						intentos = 3;
						resultado = 0;

						do {
							sprintf(sendBuff, "%d", intentos);
							send(comm_socket, sendBuff, sizeof(sendBuff), 0);
							sprintf(sendBuff, "%d", resultado);
							send(comm_socket, sendBuff, sizeof(sendBuff), 0);

							recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
							strcpy(usuario, recvBuff);
							recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
							strcpy(contrasenia, recvBuff);

							printf("Usuario recibido: %s\n", usuario);
							printf("Contraseña recibida: %s\n", contrasenia);

							iniciarSesion(usuario, contrasenia, &resultado, &intentos);

							sprintf(sendBuff, "%d", resultado);
							send(comm_socket, sendBuff, sizeof(sendBuff), 0);

							if (resultado == 2) {
								sprintf(sendBuff, "Ongi etorri!!!");
								send(comm_socket, sendBuff, sizeof(sendBuff), 0);

								do {
									recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
									sscanf(recvBuff, "%c", &opcionAdminPrincipal);

									switch (opcionAdminPrincipal) {
										case '1':
											sprintf(sendBuff, "=== ELIMINAR LIBRO ===");
											send(comm_socket, sendBuff, sizeof(sendBuff), 0);

											sprintf(sendBuff, "Introduce el ISBN del libro a eliminar: ");
											send(comm_socket, sendBuff, sizeof(sendBuff), 0);

											recv(comm_socket, recvBuff, sizeof(recvBuff), 0);

											eliminarLibroBD(db, &listaLibros, comm_socket, sendBuff, BUFFER_SIZE, recvBuff);
											break;

										case '2':
											sprintf(sendBuff, "=== VISUALIZAR CLIENTES ===\n");
											send(comm_socket, sendBuff, strlen(sendBuff), 0);
											visualizarClientesBBDD(db, comm_socket, sendBuff);
											break;

										case '3':
											sprintf(sendBuff, "=== VISUALIZAR LISTA DE LIBROS ===\n");
											send(comm_socket, sendBuff, strlen(sendBuff), 0);
											visualizarLibrosAdminBBDD(db, comm_socket, sendBuff);
											break;

										case '0':
											sprintf(sendBuff, "Cerrando sesión de administrador...");
											send(comm_socket, sendBuff, sizeof(sendBuff), 0);
											break;

										default:
											sprintf(sendBuff, "Opción no válida. Intente de nuevo.");
											send(comm_socket, sendBuff, sizeof(sendBuff), 0);
									}
								} while (opcionAdminPrincipal != '0');

							} else {
								intentos--;
								if (intentos > 0) {
									if (resultado == 0) {
										sprintf(sendBuff, "Usuario incorrecto. Intentos restantes: %d", intentos);
									} else if (resultado == 1) {
										sprintf(sendBuff, "Contraseña incorrecta. Intentos restantes: %d", intentos);
									}
									send(comm_socket, sendBuff, sizeof(sendBuff), 0);
								} else {
									sprintf(sendBuff, "Se han agotado los intentos. Acceso denegado.");
									send(comm_socket, sendBuff, sizeof(sendBuff), 0);
								}
							}

						} while (resultado != 2 && intentos > 0);

						break;
					case '0':
						printf("Volviendo al menú principal...\n");
						fflush(stdout);
						break;
					default:
						printf(
								"\033[0;31mError! La opción seleccionada no es correcta\n\033[0m");
						fflush(stdout);
						escribirLog("Opción escogida NO correcta.");
						insertarLog(
								"\033[3;35m Opción escogida NO correcta.\033[0m\n");
					}
				} while (opcionAdminInicio != '0');
				break;
			case '2':
				do {
					recv(comm_socket, recvBuff, sizeof(recvBuff), 0);  //recibir
					sscanf(recvBuff, "%c", &opcionClienteInicio);

					switch (opcionClienteInicio) {
					case '1':
						recv(comm_socket, recvBuff, sizeof(recvBuff), 0); //recibir varible DNi
						sprintf(dni, "%s", recvBuff);
						recv(comm_socket, recvBuff, sizeof(recvBuff), 0); //recibir variable CONTRASEÑA
						sprintf(contrasenia, "%s", recvBuff);

						iniciarSesionClienteBD(db, &c, &encontrado, dni,
								contrasenia, comm_socket, sendBuff); //AQUI SOLO HAY UN SEND
						send(comm_socket, sendBuff, sizeof(sendBuff), 0); //enviar

						sprintf(sendBuff, "%d", encontrado);
						send(comm_socket, sendBuff, sizeof(sendBuff), 0);
						escribirLog("Sesión iniciada por el Cliente.");
						insertarLog(
								"\033[3;35m Sesión iniciada por el Cliente.\033[0m\n");
						if (encontrado) {
							do {
								recv(comm_socket, recvBuff, sizeof(recvBuff),
										0);
								sscanf(recvBuff, "%c", &opcionClientePrincipal);

								switch (opcionClientePrincipal) {
								case '1':
									sprintf(sendBuff, "Visitar perfil\n");
									printf("%s\n", sendBuff);
									fflush(stdout);
									send(comm_socket, sendBuff,
											sizeof(sendBuff), 0);  //enviar

									verPerfil(c, comm_socket, sendBuff);

									break;
								case '2':
									sprintf(sendBuff,
											"Ver libros disponibles\n");
									send(comm_socket, sendBuff,
											strlen(sendBuff) + 1, 0);  //enviar

									visualizarLibrosBBDD(db, comm_socket,
											sendBuff);

									break;
								case '3':
									sprintf(sendBuff, "Reservar libros\n");
									send(comm_socket, sendBuff,
											strlen(sendBuff) + 1, 0);

									recv(comm_socket, recvBuff,
											sizeof(recvBuff), 0);
									strcpy(titulo, recvBuff);

									alquilarLibroBBDD(db, c.dni, titulo,
											comm_socket, sendBuff);

									break;
								case '4':
									sprintf(sendBuff, "Devolver libros\n");
									send(comm_socket, sendBuff,
											strlen(sendBuff) + 1, 0);

									recv(comm_socket, recvBuff,
											sizeof(recvBuff), 0);
									strcpy(titulo, recvBuff);

									devolverLibroBBDD(db, c.dni, titulo,
											comm_socket, sendBuff);

									break;
								case '5':
									sprintf(sendBuff,
											"Ver libros reservados\n");
									send(comm_socket, sendBuff,
											strlen(sendBuff) + 1, 0);

									verLibrosReservadosBBDD(db, c.dni,
											comm_socket, sendBuff);

									break;
								case '0':
									sprintf(sendBuff,"Volviendo al menu principal...\n");
									send(comm_socket, sendBuff, strlen(sendBuff)+1, 0);									break;
								default:
									sprintf(sendBuff,"\033[0;31mError! La opción seleccionada no es correcta\n\033[0m");
									send(comm_socket, sendBuff, strlen(sendBuff)+1, 0);

								}

							} while (opcionClientePrincipal != '0');
						}
						break;
					case '2':
						registrarBD(db, comm_socket, sendBuff, recvBuff);
						break;
					case '0':
						sprintf(sendBuff, "Volviendo al menú principal...\n\n");
						send(comm_socket, sendBuff, strlen(sendBuff)+1, 0);
						break;
					default:
						sprintf(sendBuff,
								"\033[0;31mOpción invalida. Por favor, ingrese una opción válida.\n\033[0m");
						send(comm_socket, sendBuff, strlen(sendBuff)+1, 0);

					}

				} while (opcionClienteInicio != '0');

				break;
			case '0':
				sprintf(sendBuff,"Hasta pronto!!\n");
				send(comm_socket, sendBuff, strlen(sendBuff)+1, 0);

				escribirLog("Se ha cerrado sesión.");
				insertarLog("\033[3;35m Se ha cerrado sesión.\033[0m\n");
				break;
			default:
				sprintf(sendBuff,
						"\033[0;31mOpción invalida. Por favor, ingrese una opción válida.\n\033[0m");
				send(comm_socket, sendBuff, strlen(sendBuff)+1, 0);

			}
		} while (opcion != '0');
		volcarBBDDClienteAFichero(FICHERO_CLIENTE, db);
		volcarBBDDLibroAFichero(FICHERO_LIBROS, db);

		/*ACABA EL PROGRAMA DEL SERVIDOR*/

	} while (fin == 0);

	// CLOSING the sockets and cleaning Winsock...
	closesocket(comm_socket);
	WSACleanup();

	return 0;
}

