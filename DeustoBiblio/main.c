/*Este va a ser el main*/
#include <stdio.h>
#include "domain/menu.h"

int main(){
	char opcion, opcionInicioAdmin;

	do{
		opcion = menuPrincipal();
		switch(opcion){
			case '1':
				menuAdministradorInicio();
				break;
			case '2':
				menuClienteInicio();
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






