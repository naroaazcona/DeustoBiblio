#include "baseDatos.h"

sqlite3* conectarDB() {
	sqlite3 *db;
	int resultado = sqlite3_open("db/bd.sqlite", &db);
	if (resultado != SQLITE_OK) {
		printf("Error en la apertura de la base de datos\n");
		fflush(stdout);
	}
	return db;
}

void crearTablaLibro(sqlite3 *db) {
	sqlite3_stmt *stmt;
	char *sql = "CREATE TABLE IF NOT EXISTS Libro ("
			"ISBN TEXT PRIMARY KEY NOT NULL, "
			"Titulo TEXT, "
			"Año INTEGER, "
			"Autor TEXT, "
			"Genero TEXT, "
			"Disponibilidad INTEGER)";

	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
}

void crearTablaUsuario(sqlite3 *db) {
	sqlite3_stmt *stmt;
	char *sql = "CREATE TABLE IF NOT EXISTS Cliente ("
			"DNI TEXT PRIMARY KEY NOT NULL, "
			"Nombre TEXT, "
			"Apellido TEXT, "
			"Email TEXT, "
			"Contraseña TEXT, "
			"NumeroTlf TEXT, "
			"Direccion TEXT, "
			"LibrosReservados INTEGER)";

	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
}

void crearTablaReserva(sqlite3 *db) {
	sqlite3_stmt *stmt;
	char *sql = "CREATE TABLE IF NOT EXISTS Reserva ("
			"ISBN TEXT NOT NULL,"
			"DNI TEXT NOT NULL,"
			"Fecha INTEGER NOT NULL,"
			"PRIMARY KEY (ISBN, DNI), "
			"FOREIGN KEY (ISBN) REFERENCES Libro(ISBN),"
			"FOREIGN KEY (DNI) REFERENCES Cliente(DNI))";

	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
}

void volcarFicheroLibroABBDD(char *nomfich, sqlite3 *db) {
	sqlite3_stmt *stmt;
	FILE *fichero;
	Libro libro;
	char linea[512], sql[512];

	fichero = fopen(nomfich, "r");
	if (fichero == NULL) {
		printf("\033[0;31mError en la apertura del fichero\n\033[0m");
		fflush(stdout);
	}

	while (fgets(linea, sizeof(linea), fichero)) {
		char *token = strtok(linea, ";");
		if (token) {
			strcpy(libro.ISBN, token);
		}

		token = strtok(NULL, ";");
		if (token) {
			strcpy(libro.titulo, token);
		}

		token = strtok(NULL, ";");
		if (token) {
			libro.anioPubli = atoi(token);
		}

		token = strtok(NULL, ";");
		if (token) {
			strcpy(libro.autor, token);
		}
		token = strtok(NULL, ";");
		if (token) {
			strcpy(libro.genero, token);
		}
		token = strtok(NULL, ";");
		if (token) {
			libro.disponibilidad = atoi(token);
		}

		sprintf(sql, "INSERT INTO Libro VALUES('%s', '%s', %d, '%s', '%s', %d)",
				libro.ISBN, libro.titulo, libro.anioPubli, libro.autor,
				libro.genero, libro.disponibilidad);

		sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	}
	fclose(fichero);

}

void volcarFicheroClienteABBDD(char *nomfich, sqlite3 *db) {
	sqlite3_stmt *stmt;
	FILE *fichero;
	Cliente cliente;
	char linea[512], sql[512];

	fichero = fopen(nomfich, "r");
	if (fichero == NULL) {
		printf("\033[0;31mError en la apertura del fichero\n\033[0m");
		fflush(stdout);
	}

	while (fgets(linea, sizeof(linea), fichero)) {
		char *token = strtok(linea, ";");
		if (token) {
			strcpy(cliente.dni, token);
		}

		token = strtok(NULL, ";");
		if (token) {
			strcpy(cliente.nombre, token);
		}
		token = strtok(NULL, ";");
		if (token) {
			strcpy(cliente.apellido, token);
		}
		token = strtok(NULL, ";");
		if (token) {
			strcpy(cliente.email, token);
		}
		token = strtok(NULL, ";");
		if (token) {
			strcpy(cliente.contrasenia, token);
		}
		token = strtok(NULL, ";");
		if (token) {
			strcpy(cliente.numeroTlf, token);
		}
		token = strtok(NULL, ";");
		if (token) {
			strcpy(cliente.direccion, token);
		}
		token = strtok(NULL, ";");
		if (token) {
			cliente.numerosLReservados = atoi(token);
		}

		sprintf(sql,"INSERT INTO Cliente VALUES('%s', '%s', '%s', '%s', '%s', '%s', '%s', %d)",
				cliente.dni, cliente.nombre, cliente.apellido, cliente.email,
				cliente.contrasenia, cliente.numeroTlf, cliente.direccion,
				cliente.numerosLReservados);

		sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	}

	fclose(fichero);
}

void volcarBBDDLibroAFichero(char *nomfich, sqlite3 *db) {
	sqlite3_stmt *stmt;
	FILE *fichero = fopen(nomfich, "w");

	if (fichero == NULL) {
		printf("\033[0;31mNo se ha podido abrir el fichero\n\033[0m");
		fflush(stdout);
		return;
	}

	char *sql = "SELECT * FROM Libro";
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
		printf("Error a la hora de preparar la consulta");
		fflush(stdout);
		fclose(fichero);
		sqlite3_finalize(stmt);
		return;
	}
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		fprintf(fichero, "%d;%s;%d;%s;%s;%d\n", sqlite3_column_int(stmt, 0), sqlite3_column_text(stmt, 1), sqlite3_column_int(stmt, 2),
		sqlite3_column_text(stmt, 3), sqlite3_column_text(stmt, 4), sqlite3_column_int(stmt, 5));
	}
	sqlite3_finalize(stmt);
	fclose(fichero);

}

void volcarBBDDClienteAFichero(char *nomfich, sqlite3 *db) {
	sqlite3_stmt *stmt;
	FILE *fichero = fopen(nomfich, "w");

	if (fichero == NULL) {
		printf("\033[0;31mNo se ha podido abrir el fichero\n\033[0m");
		fflush(stdout);
		return;
	}

	char *sql = "SELECT * FROM Cliente";
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
		printf("\033[0;31mError a la hora de preparar la consulta\033[0m\n");
		fflush(stdout);
		fclose(fichero);
		sqlite3_finalize(stmt);
		return;
	}

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		fprintf(fichero, "%s;%s;%s;%s;%s;%s;%s;%d\n", sqlite3_column_text(stmt, 0), sqlite3_column_text(stmt, 1), sqlite3_column_text(stmt, 2), sqlite3_column_text(stmt, 3),
				sqlite3_column_text(stmt, 4), sqlite3_column_text(stmt, 5), sqlite3_column_text(stmt, 6), sqlite3_column_int(stmt, 7));
	}

	sqlite3_finalize(stmt);
	fclose(fichero);
}

void alquilarLibroBBDD(sqlite3 *db, char *dniUsuario, char *titulo, SOCKET comm_socket, char *sendBuff) {
	sqlite3_stmt *stmt;
	int disponibilidad = -1;
	char isbn[10];

	char *select = "SELECT Disponibilidad, ISBN FROM Libro WHERE Titulo = ?";
	if (sqlite3_prepare_v2(db, select, -1, &stmt, NULL) == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1, titulo, -1, SQLITE_STATIC);
		if (sqlite3_step(stmt) == SQLITE_ROW) {
			disponibilidad = sqlite3_column_int(stmt, 0);
			strncpy(isbn, (const char*) sqlite3_column_text(stmt, 1),
					sizeof(isbn));
		}
	}
	sqlite3_finalize(stmt);

	if (disponibilidad == -1) {
		sprintf(sendBuff,"\033[0;31mLibro con título '%s' no encontrado.\n\033[0m", titulo);
		return;
	} else if (disponibilidad == 0) {
		sprintf(sendBuff,"\033[0;31mNo hay copias disponibles del libro '%s'.\n\033[0m", titulo);
		return;
	}
	send(comm_socket, sendBuff, strlen(sendBuff)+1, 0);



	char *actualiza = "UPDATE Libro SET Disponibilidad = Disponibilidad - 1 "
			"WHERE Titulo = ?";
	if (sqlite3_prepare_v2(db, actualiza, -1, &stmt, NULL) == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1, titulo, -1, SQLITE_STATIC);
		if (sqlite3_step(stmt) == SQLITE_DONE) {
			sprintf(sendBuff, "\033[1;32mLibro '%s' alquilado correctamente.\033[0m\n", titulo);
			send(comm_socket, sendBuff, strlen(sendBuff)+1, 0);
		}
	}
	sqlite3_finalize(stmt);

	char *insert = "INSERT INTO Reserva (ISBN, DNI, Fecha) VALUES (?, ?, ?)";
	if (sqlite3_prepare_v2(db, insert, -1, &stmt, NULL) == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1, isbn, -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 2, dniUsuario, -1, SQLITE_STATIC);
		sqlite3_bind_int64(stmt, 3, (sqlite3_int64) time(NULL));
		if (sqlite3_step(stmt) == SQLITE_DONE) {
			sprintf(sendBuff,"\033[1;34mReserva registrada correctamente.\033[0m\n\n");
			send(comm_socket, sendBuff, strlen(sendBuff)+1, 0);
		}
	}
	sqlite3_finalize(stmt);

	char *actualizaCliente ="UPDATE Cliente SET LibrosReservados = LibrosReservados + 1 "
					"WHERE DNI = ?";
	if (sqlite3_prepare_v2(db, actualizaCliente, -1, &stmt, NULL) == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1, dniUsuario, -1, SQLITE_STATIC);
		if (sqlite3_step(stmt) != SQLITE_DONE) {
			fprintf(stderr, "Error al actualizar LibrosReservados: %s\n", sqlite3_errmsg(db));
		}
	}
	sqlite3_finalize(stmt);

}

void devolverLibroBBDD(sqlite3 *db, char *dniUsuario, char *titulo, SOCKET comm_socket, char *sendBuff) {
		sqlite3_stmt *stmt;
		int encontrado = 0;
		char isbn[10];

		char *selectLibro = "SELECT ISBN FROM Libro WHERE Titulo = ?";
		if (sqlite3_prepare_v2(db, selectLibro, -1, &stmt, NULL) == SQLITE_OK) {
			sqlite3_bind_text(stmt, 1, titulo, -1, SQLITE_STATIC);
			if (sqlite3_step(stmt) == SQLITE_ROW) {
				strncpy(isbn, (char*) sqlite3_column_text(stmt, 0), 10);
			} else {
				sprintf(sendBuff, "\033[0;31mLibro con título '%s' no encontrado.\n\033[0m", titulo);
				send(comm_socket, sendBuff, strlen(sendBuff)+1, 0);
				sqlite3_finalize(stmt);
				return;
			}
		}
		sqlite3_finalize(stmt);

		char *selectReserva ="SELECT * FROM Reserva WHERE ISBN = ? AND DNI = ?";
		if (sqlite3_prepare_v2(db, selectReserva, -1, &stmt, NULL) == SQLITE_OK) {
			sqlite3_bind_text(stmt, 1, isbn, -1, SQLITE_STATIC);
			sqlite3_bind_text(stmt, 2, dniUsuario, -1, SQLITE_STATIC);
			if (sqlite3_step(stmt) == SQLITE_ROW) {
				encontrado = 1;
			}
		}
		sqlite3_finalize(stmt);

		if (!encontrado) {
			sprintf(sendBuff,"\033[1;31mNo tienes ninguna reserva activa para el libro '%s'.\033[0m\n\n",
					titulo);
			send(comm_socket, sendBuff, strlen(sendBuff)+1, 0);
			return;
		}

		char *actualizarLibro ="UPDATE Libro SET Disponibilidad = Disponibilidad + 1 WHERE ISBN = ?";
		if (sqlite3_prepare_v2(db, actualizarLibro, -1, &stmt, NULL) == SQLITE_OK) {
			sqlite3_bind_text(stmt, 1, isbn, -1, SQLITE_STATIC);
			sqlite3_step(stmt);
		}
		sqlite3_finalize(stmt);

		char *eliminarReserva = "DELETE FROM Reserva WHERE ISBN = ? AND DNI = ?";
		if (sqlite3_prepare_v2(db, eliminarReserva, -1, &stmt, NULL) == SQLITE_OK) {
			sqlite3_bind_text(stmt, 1, isbn, -1, SQLITE_STATIC);
			sqlite3_bind_text(stmt, 2, dniUsuario, -1, SQLITE_STATIC);
			sqlite3_step(stmt);
		}
		sqlite3_finalize(stmt);

		char *actualizarCliente ="UPDATE Cliente SET LibrosReservados = LibrosReservados - 1 WHERE DNI = ?";
		if (sqlite3_prepare_v2(db, actualizarCliente, -1, &stmt, NULL) == SQLITE_OK) {
			sqlite3_bind_text(stmt, 1, dniUsuario, -1, SQLITE_STATIC);
			sqlite3_step(stmt);
		}
		sqlite3_finalize(stmt);

		sprintf(sendBuff, "\033[1;32mLibro '%s' devuelto correctamente.\033[0m\n\n", titulo);
		send(comm_socket, sendBuff, strlen(sendBuff)+1, 0);

}

void agregarLibroBD(sqlite3 *db, Admin *admin, ListaLibros *listaLibros) {
	sqlite3_stmt *stmt;
	Libro libro = pedirDatosLibro();

	char *insert ="INSERT INTO Libro (ISBN, Titulo, \"Año\", Autor, Genero, Disponibilidad) VALUES (?, ?, ?, ?, ?, ?)";

	if (sqlite3_prepare_v2(db, insert, -1, &stmt, NULL) == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1, libro.ISBN, -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 2, libro.titulo, -1, SQLITE_STATIC);
		sqlite3_bind_int(stmt, 3, libro.anioPubli);
		sqlite3_bind_text(stmt, 4, libro.autor, -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 5, libro.genero, -1, SQLITE_STATIC);
		sqlite3_bind_int(stmt, 6, libro.disponibilidad);
		printf("GUARDO EL LIBRO\n");
	}

	if (sqlite3_step(stmt) != SQLITE_DONE) {
		printf("\033[1;31mError al insertar el libro en la base de datos: %s\n\033[0m",
				sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return;
	}

	sqlite3_finalize(stmt);

	if (listaLibros->aLibros == NULL) {
		listaLibros->aLibros = (Libro*) malloc(sizeof(Libro));
	} else {
		Libro *temp = realloc(listaLibros->aLibros,
				(listaLibros->numeroLibros + 1) * sizeof(Libro));
		if (temp == NULL) {
			printf("\033[1;31mError al reservar memoria para el nuevo libro\n\033[0m");
			return;
		}

		listaLibros->aLibros = temp;
		listaLibros->aLibros[listaLibros->numeroLibros++] = libro;
	}
	printf("\033[1;32mLibro añadido correctamente a la BASE DE DATOS y añadido al fichero.\033[0m\n");

}


int existeCliente(sqlite3 *db, const char *dni) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT 1 FROM Cliente WHERE DNI = ?";
    int existe = 0;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, dni, -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            existe = 1;
        }
    } else {
        fprintf(stderr, "\033[1;31mError al preparar la consulta: %s\n\033[0m", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    return existe;
}


void registrarBD(sqlite3 *db, SOCKET s, char *sendBuff, char *recvBuff){
	Cliente nuevoCliente;

	recv(s, recvBuff, sizeof(recvBuff), 0);
	strcpy(nuevoCliente.dni, recvBuff);

	int encontrado = 0;
	char enc[2];
	if (existeCliente(db, nuevoCliente.dni)) {
		encontrado = 1;
		sprintf(enc, "%d", encontrado);
		strcpy(sendBuff, enc);
		send(s, sendBuff, strlen(sendBuff)+1, 0);
		return;
	}
	//printf("Introduce nombre: ");
	//gets(nuevoCliente.nombre);

	recv(s, recvBuff, sizeof(recvBuff), 0);
	strcpy(nuevoCliente.nombre, recvBuff);

	//printf("Introduce apellido: ");
	//gets(nuevoCliente.apellido);

	recv(s, recvBuff, sizeof(recvBuff), 0);
	strcpy(nuevoCliente.apellido, recvBuff);

	//printf("Introduce email: ");
	//gets(nuevoCliente.email);

	recv(s, recvBuff, sizeof(recvBuff), 0);
	strcpy(nuevoCliente.email, recvBuff);

	//printf("Introduce contraseña: ");
	//gets(nuevoCliente.contrasenia);

	recv(s, recvBuff, sizeof(recvBuff), 0);
	strcpy(nuevoCliente.contrasenia, recvBuff);

	//printf("Introduce número de teléfono: ");
	//gets(nuevoCliente.numeroTlf);

	recv(s, recvBuff, sizeof(recvBuff), 0);
	strcpy(nuevoCliente.numeroTlf, recvBuff);

	//printf("Introduce dirección: ");
	//gets(nuevoCliente.direccion);

	recv(s, recvBuff, sizeof(recvBuff), 0);
	strcpy(nuevoCliente.direccion, recvBuff);

	nuevoCliente.numerosLReservados = 0;

    sqlite3_stmt *stmt;
    const char *insertCliente = "INSERT INTO Cliente (DNI, Nombre, Apellido, Email, Contraseña, NumeroTlf, Direccion, LibrosReservados) "
                                "VALUES (?, ?, ?, ?, ?, ?, ?, ?)";

    if (sqlite3_prepare_v2(db, insertCliente, -1, &stmt, NULL) == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1, nuevoCliente.dni, -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 2, nuevoCliente.nombre, -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 3, nuevoCliente.apellido, -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 4, nuevoCliente.email, -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 5, nuevoCliente.contrasenia, -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 6, nuevoCliente.numeroTlf, -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 7, nuevoCliente.direccion, -1, SQLITE_STATIC);
		sqlite3_bind_int(stmt, 8, nuevoCliente.numerosLReservados);

		if (sqlite3_step(stmt) == SQLITE_DONE) {
			sprintf(sendBuff,"\033[1;32m Registro completado correctamente.\033[0m\n");
		} else {
			sprintf(sendBuff,"\033[1;31m Error al registrar el cliente: %s\033[0m\n", sqlite3_errmsg(db));
		}

		send(s, sendBuff, strlen(sendBuff)+1, 0);
	} else {
		fprintf(stderr, "\033[1;31mError al preparar la consulta: %s\n\033[0m", sqlite3_errmsg(db));
	}

	sqlite3_finalize(stmt);
}


void visualizarLibrosBBDD(sqlite3 *db,SOCKET comm_socket, char *sendBuff) {
    sqlite3_stmt *stmt;
    char *sql = "SELECT ISBN, Titulo, Año, Autor, Genero, Disponibilidad FROM Libro";

    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (result != SQLITE_OK) {
        fprintf(stderr, "\033[1;31mError al preparar la consulta: %s\n\033[0m", sqlite3_errmsg(db));
        return;
    }

    //EMPIEZA SOCKET
    visualizarTitulosLibro(comm_socket,sendBuff); //AQUI HAY 1 ENVIO
	sprintf(sendBuff,"\033[1;33m--------------------------------------------------------------------------------------------------------------------------------------"
			"--------------------------------\n\033[0m");
	send(comm_socket,sendBuff,strlen(sendBuff)+1,0);  //enviar
    int count = 0;

    int fin = 0; //VARIABLE CREADA
    sprintf(sendBuff,"%d",fin);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
    	send(comm_socket,sendBuff,strlen(sendBuff)+1,0);  //enviar
        const char *isbn = (const char*)sqlite3_column_text(stmt, 0);
        const char *titulo = (const char*)sqlite3_column_text(stmt, 1);
        int anioPubli = sqlite3_column_int(stmt, 2);
        const char *autor = (const char*)sqlite3_column_text(stmt, 3);
        const char *genero = (const char*)sqlite3_column_text(stmt, 4);
        int disponibilidad = sqlite3_column_int(stmt, 5);

        sprintf(sendBuff,"\033[1;33m%30s|%30s|%20d|%40s|%20s|%20s\n\033[0m",
               isbn, titulo, anioPubli, autor, genero, disponibilidad ? "Disponible" : "No disponible");
        send(comm_socket,sendBuff,strlen(sendBuff)+1,0);  //enviar

        count++;
    }

    fin = 1;
    sprintf(sendBuff,"%d",fin);
    send(comm_socket,sendBuff,strlen(sendBuff)+1,0);  //enviar

    if (count == 0) {
        sprintf(sendBuff,"\033[1;31m No hay libros registrados en la base de datos.\033[0m\n");
    } else {
        sprintf(sendBuff,"\nTotal de libros: %d\n", count);
    }
    send(comm_socket,sendBuff,strlen(sendBuff)+1,0);  //enviar

    sqlite3_finalize(stmt);
}
void marcarLibroComoNoDisponibleBD(sqlite3 *db, const char *isbn) {
    sqlite3_stmt *stmt;
    const char *updateDispoLibro = "UPDATE Libro SET Disponible = 0 WHERE ISBN = ?";

    if (sqlite3_prepare_v2(db, updateDispoLibro, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, isbn, -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_DONE) {
            printf("\033[1;32m El libro con ISBN %s ha sido marcado como NO disponible.\033[0m\n", isbn);
        } else {
            printf("\033[1;31m Error al actualizar el estado del libro: %s\033[0m\n", sqlite3_errmsg(db));
        }
    } else {
        fprintf(stderr, "\033[1;31mError al preparar la consulta: %s\n\033[0m", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
}

void verLibrosReservadosBBDD(sqlite3 *db, char *dniUsuario,SOCKET comm_socket, char *sendBuff) {
	sqlite3_stmt *stmt;
	char *select = "SELECT Libro.Titulo "
			"FROM Reserva "
			"JOIN Libro ON Reserva.ISBN = Libro.ISBN "
			"WHERE Reserva.DNI = ?";

	if (sqlite3_prepare_v2(db, select, -1, &stmt, NULL) == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1, dniUsuario, -1, SQLITE_STATIC);
		int contador = 0;

		sprintf(sendBuff,"\033[1;33mLibros reservados por el usuario con DNI %s:\n\033[0m", dniUsuario);
		send(comm_socket, sendBuff, strlen(sendBuff)+1,0);

		while (sqlite3_step(stmt) == SQLITE_ROW) {
			const unsigned char *titulo = sqlite3_column_text(stmt, 0);
			sprintf(sendBuff,"\033[1;33m- Título: %s \n\033[0m", titulo);
			send(comm_socket, sendBuff, strlen(sendBuff)+1, 0);
			contador++;
		}

		if (contador == 0) {
			sprintf(sendBuff,"\033[1;31mNo tienes libros reservados.\n\033[0m");
			send(comm_socket, sendBuff, strlen(sendBuff)+1, 0);
		}

		sqlite3_finalize(stmt);
	} else {
		fprintf(stderr, "Error al preparar la consulta: %s\n",
				sqlite3_errmsg(db));
	}
}


void iniciarSesionClienteBD(sqlite3 *db, Cliente *cliente, int *enc, char *dni, char *contrasenia, SOCKET comm_socket, char *sendBuff) {
	sqlite3_stmt *stmt;

	char *sql = "SELECT * FROM Cliente WHERE DNI = ? AND Contraseña = ?";
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
		printf("Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
		*enc = 0;
		return;
	}
	sqlite3_bind_text(stmt, 1, dni, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, contrasenia, -1, SQLITE_STATIC);

	if (sqlite3_step(stmt) == SQLITE_ROW) {
		strcpy(cliente->dni, (const char*) sqlite3_column_text(stmt, 0));
		strcpy(cliente->nombre, (const char*) sqlite3_column_text(stmt, 1));
		strcpy(cliente->apellido, (const char*) sqlite3_column_text(stmt, 2));
		strcpy(cliente->email, (const char*) sqlite3_column_text(stmt, 3));
		strcpy(cliente->contrasenia,(const char*) sqlite3_column_text(stmt, 4));
		strcpy(cliente->numeroTlf, (const char*) sqlite3_column_text(stmt, 5));
		strcpy(cliente->direccion, (const char*) sqlite3_column_text(stmt, 6));
		cliente->numerosLReservados = sqlite3_column_int(stmt, 7);
		*enc = 1;
		sprintf(sendBuff,"\033[1;32mInicio de sesión exitoso. ¡Bienvenid@, %s %s!\033[0m\n", cliente->nombre, cliente->apellido);

	} else {
		sprintf(sendBuff, "\033[1;31mError: DNI o contraseña incorrectos.\033[0m\n");
		*enc = 0;
	}

	sqlite3_finalize(stmt);
}

void eliminarLibroBD(sqlite3 *db, ListaLibros *listaLibros) {
	sqlite3_stmt *stmt;
	int enc = -1, i;
	char isbn[10];

	printf("Introduce el ISBN del libro que deseas eliminar: ");
	fflush(stdout);
	fflush(stdin);
	gets(isbn);

	char *select = "SELECT COUNT(*) FROM Reserva WHERE ISBN = ?";
	if (sqlite3_prepare_v2(db, select, -1, &stmt, NULL) != SQLITE_OK) {
		printf("\033[1;31mError al preparar la consulta: %s\n\033[0m", sqlite3_errmsg(db));
		return;
	}

	sqlite3_bind_text(stmt, 1, isbn, -1, SQLITE_STATIC);

	if (sqlite3_step(stmt) == SQLITE_ROW) {
		int reservas = sqlite3_column_int(stmt, 0);
		if (reservas > 0) {
			printf(
					"\033[1;31mError: No se puede eliminar el libro porque tiene reservas activas.\033[0m\n");
			sqlite3_finalize(stmt);
			return;
		}
	}
	sqlite3_finalize(stmt);

	char *eliminar = "DELETE FROM Libro WHERE ISBN = ?";
	if (sqlite3_prepare_v2(db, eliminar, -1, &stmt, NULL) != SQLITE_OK) {
		printf("Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
		return;
	}

	sqlite3_bind_text(stmt, 1, isbn, -1, SQLITE_STATIC);

	if (sqlite3_step(stmt) != SQLITE_DONE) {
		printf("\033[1;31mError al eliminar el libro: %s\033[0m\n",
				sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		return;
	}

	sqlite3_finalize(stmt);

	for (i = 0; i < listaLibros->numeroLibros; i++) {
		if (strcmp(listaLibros->aLibros[i].ISBN, isbn) == 0) {
			enc = i;
			break;
		}
	}

	if (enc != -1) {
		for (i = enc; i < listaLibros->numeroLibros - 1; i++) {
			listaLibros->aLibros[i] = listaLibros->aLibros[i + 1];
		}
		listaLibros->numeroLibros--;

		printf("\033[1;32mLibro con ISBN %s eliminado correctamente.\033[0m\n",
				isbn);
	} else {
		printf(
				"\033[1;33mEl libro se eliminó de la base de datos pero no se encontró en la lista de memoria.\033[0m\n");
	}
}




