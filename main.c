/*Este va a ser el main*/
#include <stdio.h>
#include "domain/menu.h"

int main(){
	char opcion, opcionClienteInicio, opcionCliente,opcionAdminInicio;

	do{
		opcion = menuPrincipal();
		switch(opcion){
			case '1':
				do{
					opcionAdminInicio = menuAdministradorInicio();
					switch(opcionAdminInicio){
					case '1':

						break;
					case '0': printf("Volviendo al menú principal...\n");
						      fflush(stdout);
						      break;
					default: printf("Error! La opción seleccionada no es correcta\n");
						     fflush(stdout);
					}
				}while(opcionAdminInicio != '0');
					break;
			case '2':
				do{
					opcionClienteInicio = menuClienteInicio();
					switch(opcionClienteInicio){
						case '1':
							//iniciarSesionCliente();
							break;
						case '2':
							//registroCliente();
							break;
						case '0':
							printf("Hasta pronto!!\n");
							break;
						default:
							printf("Opción invalida. Por favor, ingrese una opción válida.\n");
							fflush(stdout);
					}

				}while(opcion !='0');

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


/**/






