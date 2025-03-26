/*Este va a ser el main*/
#include <stdio.h>
#include "domain/menu.h"
#include "domain/cliente.h"
#include "domain/administrador.h"
#include "domain/libro.h"

int main(){
	char opcion, opcionClienteInicio, opcionAdminInicio, opcionClientePrincipal, opcionAdminPrincipal, usuario[20], contrasenia[20];
	int resultado, intentos;
	Cliente c;
	Admin admin;
	ListaLibros listaLibros;
	Libro libro;
	Config conf;

	conf = leerConfiguracion("config.properties");

	do{

		opcion = menuPrincipal();
		switch(opcion){
			case '1':
				do{
					opcionAdminInicio = menuAdministradorInicio();
					switch(opcionAdminInicio){
					case '1':
						iniciarSesion(usuario, contrasenia, &resultado, &intentos);
						if (resultado != 2) {
							printf("Se te han acabado los intentos\n");
							fflush(stdout);
							break;
						} else {
							printf("Ongi etorri!!!\n");
							fflush(stdout);
						}
						do{
							opcionAdminPrincipal = menuPrincipalAdministrador();
							switch(opcionAdminPrincipal){
								case '1':
									printf("Eliminal libro\n");
									fflush(stdout);
									eliminarLibroAdmin(&admin, &listaLibros, libro.ISBN);
									break;
								case '2':
									printf("Añadir libro\n");
									fflush(stdout);
									agregarLibro(&admin, &listaLibros);
									break;
								case '3':
									printf("Visualizar datos de los clientes:\n");
									fflush(stdout);
									//DUDA
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

						}while(opcionAdminPrincipal != '0');
						break;
					case '0':
						printf("Volviendo al menú principal...\n");
						fflush(stdout);
						break;
					default:
						printf("Error! La opción seleccionada no es correcta\n");
						fflush(stdout);
					}
				}while(opcionAdminInicio != '0');
					break;
			case '2':
				do{
					opcionClienteInicio = menuClienteInicio();
					switch(opcionClienteInicio){
						case '1':
							iniciarSesionCliente(&c, c.email, c.contrasenia);
							do{
								opcionClientePrincipal = menuPrincipalCliente();
								switch(opcionClientePrincipal){
									case '1':
										printf("Visitar perfil\n");
										fflush(stdout);
										verPerfil(c);
										break;
									case '2':
										printf("Ver libros disponibles\n");
										fflush(stdout);
										verLibrosReservados(c);
										break;
									case '3':
										printf("Reservar libros\n");
										fflush(stdout);
										reservaLibros(&c, &listaLibros, libro.ISBN);
										break;
									case '4':
										printf("Devolver libros\n");
										fflush(stdout);
										devolverLibroCliente(&c, &listaLibros, libro.ISBN);
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

							}while(opcionClientePrincipal != '0');
							break;
						case '2':
							registrar();
							break;
						case '0':
							printf("Volviendo al menú principal...\n\n");
							fflush(stdout);
							break;
						default:
							printf("Opción invalida. Por favor, ingrese una opción válida.\n");
							fflush(stdout);
					}

				}while(opcionClienteInicio !='0');

				break;
			case '0':
				printf("Hasta pronto!!\n");
				fflush(stdout);
				break;
			default:
				printf("Opción invalida. Por favor, ingrese una opción válida.\n");
				fflush(stdout);
		}
	}while(opcion!='0');

	return 0;

}
