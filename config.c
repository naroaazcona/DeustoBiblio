#include "config.h"
#include <stdio.h>
#include <string.h>

Config leerConfiguracion(char *fich){
	Config c;
	FILE *pf;
	char linea[100], clave[TAM], valor[TAM];

	pf = fopen(fich, "r");
	if(pf != (FILE*)NULL){
		while(fgets(linea, 100, pf) != NULL){
			sscanf(linea, "%s = %s", clave, valor);
			if (strcmp(clave, "puerto", 6) == 0){
				c.puerto = atoi(valor);
			}else if(strncmp(clave, "nombreBD", 8) == 0){
				strcpy(c.nombreBD, valor);
			}
		}
		fclose(pf);
	}
	return c;
}

