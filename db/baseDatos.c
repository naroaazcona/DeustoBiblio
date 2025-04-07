#include "baseDatos.h"

sqlite3* conectarDB() {
	sqlite3 *db;
	int resultado = sqlite3_open("db/bd.sqlite", &db);
	if (resultado != SQLITE_OK) {
		printf("Error en la apertura de la base de datos\n");
		fflush(stdout);
	} else {
		printf("\033[1;32m Base de datos abierta correctamente!\033[0m\n");
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
		printf("Error en la apertura del fichero\n");
		fflush(stdout);
	}

	while (fgets(linea, sizeof(linea), fichero)) {
		char *token = strtok(linea, ";");
		if (token) {
			strcpy(libro.ISBN, token);
			printf("\033[1;31m%s \033[0m", token);
			fflush(stdout);
		}

		token = strtok(NULL, ";");
		if (token) {
			strcpy(libro.titulo, token);
			printf("\033[1;31m%s \033[0m", token);
			fflush(stdout);
		}

		token = strtok(NULL, ";");
		if (token) {
			libro.anioPubli = atoi(token);
			printf("\033[1;31m%s \033[0m", token);
			fflush(stdout);
		}

		token = strtok(NULL, ";");
		if (token) {
			strcpy(libro.autor, token);
			printf("\033[1;31m%s \033[0m", token);
			fflush(stdout);
		}
		token = strtok(NULL, ";");
		if (token) {
			strcpy(libro.genero, token);
			printf("\033[1;31m%s \033[0m", token);
			fflush(stdout);
		}
		token = strtok(NULL, ";");
		if (token) {
			libro.disponibilidad = atoi(token);
			printf("\033[1;31m%s \033[0m", token);
			fflush(stdout);
		}

		sprintf(sql, "INSERT INTO Libro VALUES('%s', '%s', %d, '%s', '%s', %d)",
				libro.ISBN, libro.titulo, libro.anioPubli, libro.autor,
				libro.genero, libro.disponibilidad);

		sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	}
	fclose(fichero);
	printf("\033[1;32m Libros volcados a la base de datos correctamente.\033[0m\n");

}

void volcarFicheroClienteABBDD(char *nomfich, sqlite3 *db) {
	sqlite3_stmt *stmt;
	FILE *fichero;
	Cliente cliente;
	char linea[512], sql[512];

	fichero = fopen(nomfich, "r");
	if (fichero == NULL) {
		printf("Error en la apertura del fichero\n");
		fflush(stdout);
	}

	while (fgets(linea, sizeof(linea), fichero)) {
		char *token = strtok(linea, ";");
		if (token) {
			strcpy(cliente.dni, token);
			printf("\033[1;36m %s \033[0m", token);
			fflush(stdout);
		}

		token = strtok(NULL, ";");
		if (token) {
			strcpy(cliente.nombre, token);
			printf("\033[1;36m%s \033[0m", token);
			fflush(stdout);

		}
		token = strtok(NULL, ";");
		if (token) {
			strcpy(cliente.apellido, token);
			printf("\033[1;36m%s \033[0m", token);
			fflush(stdout);

		}
		token = strtok(NULL, ";");
		if (token) {
			strcpy(cliente.email, token);
			printf("\033[1;36m%s \033[0m", token);
			fflush(stdout);

		}
		token = strtok(NULL, ";");
		if (token) {
			strcpy(cliente.contrasenia, token);
			printf("\033[1;36m%s \033[0m", token);
			fflush(stdout);

		}
		token = strtok(NULL, ";");
		if (token) {
			strcpy(cliente.numeroTlf, token);
			printf("\033[1;36m%s \033[0m", token);
			fflush(stdout);

		}
		token = strtok(NULL, ";");
		if (token) {
			strcpy(cliente.direccion, token);
			printf("\033[1;36m%s \033[0m", token);
			fflush(stdout);

		}
		token = strtok(NULL, ";");
		if (token) {
			cliente.numerosLReservados = atoi(token);
			printf("\033[1;36m%s \n\033[0m", token);
			fflush(stdout);

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
	printf("\033[1;32mClientes volcados a la base de datos correctamente.\033[0m\n");
}

void volcarBBDDLibroAFichero(char *nomfich, sqlite3 *db) {
	sqlite3_stmt *stmt;
	FILE *fichero = fopen(nomfich, "w");

	if (fichero == NULL) {
		printf("No se ha podido abrir el fichero\n");
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
	printf("\033[1;32mBBDD volcada correctamente al fichero.\033[0m\n");
	fflush(stdout);
	fclose(fichero);

}

void volcarBBDDClienteAFichero(char *nomfich, sqlite3 *db) {
	sqlite3_stmt *stmt;
	FILE *fichero = fopen(nomfich, "w");

	if (fichero == NULL) {
		printf("No se ha podido abrir el fichero\n");
		fflush(stdout);
		return;
	}

	char *sql = "SELECT * FROM Cliente";
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
		printf("Error a la hora de preparar la consulta");
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
	printf("\033[1;32mBBDD volcada correctamente al fichero.\033[0m\n");
	fflush(stdout);
	fclose(fichero);
}

void alquilarLibroBBDD(sqlite3 *db, char *dniUsuario) {
	sqlite3_stmt *stmt;
	char titulo[100];
	int disponibilidad = -1;
	char isbn[10];

	printf("Introduce el título del libro que quieres alquilar: ");
	fflush(stdout);
	fflush(stdin);
	gets(titulo);

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
		printf("Libro con título '%s' no encontrado.\n", titulo);
		fflush(stdout);
		return;
	} else if (disponibilidad == 0) {
		printf("No hay copias disponibles del libro '%s'.\n", titulo);
		fflush(stdout);
		return;
	}

	char *actualiza = "UPDATE Libro SET Disponibilidad = Disponibilidad - 1 "
			"WHERE Titulo = ?";
	if (sqlite3_prepare_v2(db, actualiza, -1, &stmt, NULL) == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1, titulo, -1, SQLITE_STATIC);
		if (sqlite3_step(stmt) == SQLITE_DONE) {
			printf("\033[1;32mLibro '%s' alquilado correctamente.\033[0m\n", titulo);
		}
	}
	sqlite3_finalize(stmt);

	char *insert = "INSERT INTO Reserva (ISBN, DNI, Fecha) VALUES (?, ?, ?)";
	if (sqlite3_prepare_v2(db, insert, -1, &stmt, NULL) == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1, isbn, -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 2, dniUsuario, -1, SQLITE_STATIC);
		sqlite3_bind_int64(stmt, 3, (sqlite3_int64) time(NULL));
		if (sqlite3_step(stmt) == SQLITE_DONE) {
			printf("\033[1;34mReserva registrada correctamente.\033[0m\n\n");
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

void devolverLibroBBDD(sqlite3 *db, char *dniUsuario) {
	sqlite3_stmt *stmt;
	char titulo[100];
	int encontrado = 0;
	char isbn[10];

	printf("Introduce el título del libro que deseas devolver: ");
	fflush(stdout);
	fflush(stdin);
	gets(titulo);

	char *selectLibro = "SELECT ISBN FROM Libro WHERE Titulo = ?";
	if (sqlite3_prepare_v2(db, selectLibro, -1, &stmt, NULL) == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1, titulo, -1, SQLITE_STATIC);
		if (sqlite3_step(stmt) == SQLITE_ROW) {
			strncpy(isbn, (char*) sqlite3_column_text(stmt, 0), 10);
		} else {
			printf("Libro con título '%s' no encontrado.\n", titulo);
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
		printf("\033[1;31mNo tienes ninguna reserva activa para el libro '%s'.\033[0m\n\n",
				titulo);
		fflush(stdout);
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

	printf("\033[1;32mLibro '%s' devuelto correctamente.\033[0m\n\n", titulo);

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
		printf("Error al insertar el libro en la base de datos: %s\n",
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
			printf("Error al reservar memoria para el nuevo libro\n");
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
        fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    return existe;
}


void registrarBD(sqlite3 *db){
	Cliente nuevoCliente;

	printf("Introduce DNI: ");
	fflush(stdout);
	fflush(stdin);
	gets(nuevoCliente.dni);

	if (existeCliente(db, nuevoCliente.dni)) {
        printf("\033[1;32m El usuario con DNI %s ya está registrado.\033[0m\n", nuevoCliente.dni);
		return;
	}

	printf("Introduce nombre: ");
	fflush(stdout);
	gets(nuevoCliente.nombre);

	printf("Introduce apellido: ");
	fflush(stdout);
	gets(nuevoCliente.apellido);

	printf("Introduce email: ");
	fflush(stdout);
	gets(nuevoCliente.email);

	printf("Introduce contraseña: ");
	fflush(stdout);
	gets(nuevoCliente.contrasenia);

	printf("Introduce número de teléfono: ");
	fflush(stdout);
	gets(nuevoCliente.numeroTlf);

	printf("Introduce dirección: ");
	fflush(stdout);
	gets(nuevoCliente.direccion);

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
			printf("\033[1;32m Registro completado correctamente.\033[0m\n");
		} else {
			printf("\033[1;31m Error al registrar el cliente: %s\033[0m\n", sqlite3_errmsg(db));
		}
	} else {
		fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
	}

	sqlite3_finalize(stmt);
}


void visualizarLibrosBBDD(sqlite3 *db) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT ISBN, Titulo, Año, Autor, Genero, Disponibilidad FROM Libro";

    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (result != SQLITE_OK) {
        fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
        return;
    }
    printf("LISTA DE LIBROS\n");

    printf("\033[1;33m%-15s|%-50s|%-6s|%-30s|%-20s|%-15s\033[0m\n",
           "ISBN", "TITULO", "AÑO", "AUTOR", "GENERO", "DISPONIBILIDAD");

    int count = 0;

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *isbn = (const char*)sqlite3_column_text(stmt, 0);
        const char *titulo = (const char*)sqlite3_column_text(stmt, 1);
        int anioPubli = sqlite3_column_int(stmt, 2);
        const char *autor = (const char*)sqlite3_column_text(stmt, 3);
        const char *genero = (const char*)sqlite3_column_text(stmt, 4);
        int disponibilidad = sqlite3_column_int(stmt, 5);

        printf("\033[0m%-15s|%-50s|%-6d|%-30s|%-20s|%-15s\033[0m\n",
               isbn, titulo, anioPubli, autor, genero, disponibilidad ? "Disponible" : "No disponible");

        count++;
    }

    if (count == 0) {
        printf("\033[1;31m No hay libros registrados en la base de datos.\033[0m\n");
    } else {
        printf("\nTotal de libros: %d\n", count);
    }

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
        fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
}


