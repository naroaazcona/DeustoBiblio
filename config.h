#ifndef CONFIG_H_
#define CONFIG_H_
#define TAM 100

typedef struct{
	int puerto;
	char nombreBD[TAM];
}Config;

Config leerConfiguracion(char *fich);


#endif
