// Función que mira si la palabra se solapa con otra ya existente en el tablero, si la palabra se solapa con otra debería 
// ser porque se ha introducido un '_', si el cruce de las palabras no es un '_' devuelve error

void se_solapa(char palabra[15], int fila, int columna, int orientacion)
{
	if (cod_error==0) {
		
		if (orientacion==0) { //horizontal
			for(i=0;i<strlen(palabra);i++) {
				if ((tablero[fila][i+columna].letra[0]!='.') && (tablero[fila][i+columna].letra[0]!='*') && (tablero[fila][i+columna].letra[0]!='5') && (tablero[fila][i+columna].letra[0]!='4') && (tablero[fila][i+columna].letra[0]!='3') && (tablero[fila][i+columna].letra[0]!='2')) {
					if (palabra[i]!='_' ) cod_error=-4;	// ERROR si en el tablero hay una letra y lo que quiero poner no es '_' 
				}		
			}
		}
		else {	//vertical
			for(i=0;i<strlen(palabra);i++) {
				if ((tablero[i+fila][columna].letra[0]!='.') && (tablero[i+fila][columna].letra[0]!='*') && (tablero[i+fila][columna].letra[0]!='5') && (tablero[i+fila][columna].letra[0]!='4') && (tablero[i+fila][columna].letra[0]!='3') && (tablero[i+fila][columna].letra[0]!='2')) {
					if (palabra[i]!='_' ) cod_error=-4;
				}
			}
		}
	}
	return;
}
