#include "cliente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int telefonoValido(char *telefono){
	if(strlen(telefono)!=9) return 0;
	for(int i = 0; i<9; i++){
		if(!isdigit(telefono[i])) return 0;

	}
	return 1;
}
int dniValido(char *dni){
	if(strlen(dni)!= 9) return 0;
	for(int i = 0; i < 8; i++){
		if(!isdigit(dni[i])) return 0;
	}
	if(!isalpha(dni[8])) return 0;
	return 1;
}

void registrar(){
	Cliente c;
	FILE *ficheroClientes;

	printf("Registrando nuevo usuario....\n");
	printf("Introduce tu nombre:\n");
	fflush(stdout);
	fflush(stdin);
	gets(c.nombre);
	c.nombre[strcspn(c.nombre, "\n")] = 0;

	printf("Introduce tu apellido:\n");
	fflush(stdout);
	fflush(stdin);
	gets(c.apellido);
	c.apellido[strcspn(c.apellido, "\n")] = 0;

	do{
		printf("Introduce tu DNI:\n");
			fflush(stdout);
			fflush(stdin);
			gets(c.dni);
			c.dni[strcspn(c.dni, "\n")] = 0;

			if(!dniValido(c.dni)){
				printf("ERROR: DNI introducido no es valido. Debe de tener 8 números y 1 letra. Intentelo de nuevo");
				fflush(stdout);
			}

	}while(!dniValido(c.dni));


	printf("Introduce tu correo electrónico:\n");
	fflush(stdout);
	fflush(stdin);
	gets(c.email);
	c.email[strcspn(c.email, "\n")] = 0;

	do{
		printf("Introduce tu número de telefono:\n");
		fflush(stdout);
		fflush(stdin);
		gets(c.numeroTlf);
		c.numeroTlf[strcspn(c.numeroTlf, "\n")] = 0;

		if(!telefonoValido(c.numeroTlf)){
			printf("ERROR: El número de telefono introducido no es valido. Debe de tener 9 números. Intentelo de nuevo. ");
			fflush(stdout);
		}
	}while(telefonoValido(c.numeroTlf));


	printf("Introduce tu dirección:\n");
	fflush(stdout);
	fflush(stdin);
	gets(c.numeroTlf);
	c.direccion[strcspn(c.direccion, "\n")] = 0;

	printf("Introduce tu contraseña:\n");
	fflush(stdout);
	fflush(stdin);
	gets(c.contrasenia);
	c.contrasenia[strcspn(c.contrasenia, "\n")] = 0;


	ficheroClientes = fopen("clientes.txt", "a");
	if(ficheroClientes == NULL){
		printf("ERROR: No se ha podido abrir el fichero\n");
		fflush(stdout);
		return;
	}else{
		fprintf(ficheroClientes, "%s;%s;%s;%s;%s;%s;%s;%d\n",
		c.dni, c.nombre, c.apellido, c.email, c.contrasenia, c.numeroTlf, c.direccion, c.numerosLReservados);	}

	fclose(ficheroClientes);
	printf("El registro se ha realizado correctamente!\n");

}


void iniciarSesionCliente(Cliente *cliente, char *email, char *contrasenia){
	FILE *ficheroClientes;
	int encontrado = 0;
	int intentos = 3;

	printf("Iniciando sesion como cliente...\n");
	printf("Introduce tu email: ");
	fflush(stdout);
	fflush(stdin);
	gets(email);

	ficheroClientes = fopen("clientes.txt", "r");
	    if (ficheroClientes == NULL) {
	        printf("No se pudo abrir el archivo de clientes.\n");
	        fflush(stdout);
	        return;
	    }else
	    	while (fscanf(ficheroClientes, "%9[^;];%19[^;];%19[^;];%49[^;];%49[^;];%9[^;];%49[^;];%d\n",
		                  cliente->dni, cliente->nombre, cliente->apellido, cliente->email,
		                  cliente->contrasenia, cliente->numeroTlf, cliente->direccion,
		                  &cliente->numerosLReservados) != EOF) {
			 if (strcmp(email, cliente->email) == 0) {
				 encontrado = 1;
				 while (intentos > 0) {
					 printf("Introduce tu contraseña (%d intentos restantes): ", intentos);
				     fflush(stdin);
				     fgets(contrasenia, sizeof(contrasenia), stdin);
				     contrasenia[strcspn(contrasenia, "\n")] = 0;

				     if (strcmp(contrasenia, cliente->contrasenia) == 0) {
				    	 printf("Inicio de sesión exitoso. ¡Bienvenid@, %s %s!\n", cliente->nombre, cliente->apellido);
				    	 fclose(ficheroClientes);
				    	 return;
				     } else {
				    	 printf("Contraseña incorrecta.\n");
				    	 intentos--;
				     }
				 }

				 printf("Demasiados intentos fallidos. Inicio de sesión cancelado.\n");
				 fclose(ficheroClientes);
				 return;
			 }
	    	}
	    fclose(ficheroClientes);

	    if (!encontrado) {
	    	printf("El email no está registrado.\n");
	    	fflush(stdout);
	    }

}

void reservaLibros(Cliente *cliente, ListaLibros *listaLibros, char *isbn){


}
void devolverLibroCliente(Cliente *cliente, ListaLibros *listaLibros, char *isbn){


}
void verLibrosReservador(Cliente c){


}
void verPerfil(Cliente c){


}


