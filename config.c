#include "config.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "db/sqlite3.h"

Config leerConfiguracion(char *fich){
	Config conf;
	FILE *pf;
	char linea[100], clave[TAM], valor[TAM];

	pf = fopen(fich, "r");
	if(pf != (FILE*)NULL){
		while(fgets(linea, 100, pf) != NULL){
			sscanf(linea, "%s = %s", clave, valor);
			if (strncmp(clave, "puerto", 6) == 0){
				conf.puerto = atoi(valor);
			}else if(strncmp(clave, "nombreBD", 8) == 0){
				strcpy(conf.nombreBD, valor);
			}
		}
		fclose(pf);
	}
	return conf;
}

