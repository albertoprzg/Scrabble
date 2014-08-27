// Función para colocar la palabra y obtener su puntuación

void coloca_palabra(char palabra[15], int f, int c, int o)
{ 
	
	/* Las entradas a la función son: jugador, palabra que quiere escribir, fila en la que esta la primera letra,
	columna en la que esta la primera letra, y si es vertical u horizontal; respectivamente */

	int cont=0;  		// Contadores


	/* Bucle para colocar la palabra en el tablero*/
	
	if (o==0) {
		for (j=c;j<=(c+strlen(palabra)-1);j++) {
		
			tablero[f][j].letra[0]=palabra[cont];
			tablero[f][j].valor=1;
			cont++;
		}
	}
	
	else {
		for (i=f;i<=(f+strlen(palabra)-1);i++) {
		
			tablero[i][c].letra[0]=palabra[cont];
			tablero[i][c].valor=1;
			cont++;
		}
	}

	return;
}
