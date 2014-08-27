// Función que mira arriba y abajo de cada letra que se va a poner y cambia el valor de toca para saber si se están encadenando las palabras
// En el caso de que se haya utilizado una letra del tablero con '_' ya se sabe que se está encadenando
void toca_palabra(char palabra[15], int fila, int columna, int orientacion)
{
	int toca=0;

	if (cod_error==0) {
		
		if (primera_jugada!=0) {
			
			for (i=0;i<strlen(palabra);i++) {
				if (palabra[i]=='_') toca=1;
			}
				
			if (orientacion==0) {	//horizontal
				for (i=columna;i<columna+strlen(palabra);i++) {
					if (((tablero[fila-1][i].letra[0]>='A') && (tablero[fila-1][i].letra[0]<='Z')) || ((tablero[fila-1][i].letra[0]>='a') && (tablero[fila-1][i].letra[0]<='z'))) toca=1;
					if (((tablero[fila+1][i].letra[0]>='A') && (tablero[fila+1][i].letra[0]<='Z')) || ((tablero[fila+1][i].letra[0]>='a') && (tablero[fila+1][i].letra[0]<='z'))) toca=1;
				}
			}
			
			if (orientacion==1) { 	// vertical
				for (i=fila;i<fila+strlen(palabra);i++) {
					if (((tablero[i][columna-1].letra[0]>='A') && (tablero[i][columna-1].letra[0]<='Z')) || ((tablero[i][columna-1].letra[0]>='a') && (tablero[i][columna-1].letra[0]<='z'))) toca=1;
					if (((tablero[i][columna+1].letra[0]>='A') && (tablero[i][columna+1].letra[0]<='Z')) || ((tablero[i][columna+1].letra[0]>='a') && (tablero[i][columna+1].letra[0]<='z'))) toca=1;
				}
			}
			
			if (toca==0) cod_error=-10;
		}
	}
	return;
}
