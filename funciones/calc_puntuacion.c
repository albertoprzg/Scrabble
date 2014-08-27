// Funcion para calcular la puntuacion de una palabra

int calc_puntuacion(char palabra[15], int f, int c, int o)
{
	printf("\nCalculando puntuación...\n");

	int i,j,k;
	int cont=0;  		/* Contadores */
	int mult=1;			/* Multiplicador de la puntuacion de la palabra */
	int puntuacion=0;	/* Guarda la puntuacion de la jugada */

	if (o==0) {
		for (j=c;j<c+strlen(palabra);j++) {

			/* Obtencion de la puntuacion de cada letra */
			
			for (k=0;k<dim;k++){
				if (palabra[cont]==letrasdisp[k].letra) {		
					printf("Letra: %c, valor letra: %d, valor tablero: %d\n" DEF,letrasdisp[k].letra,letrasdisp[k].valor,tablero[f][j].valor);
					switch (tablero[f][j].valor) {
						case 3 : puntuacion=puntuacion+(letrasdisp[k].valor*3); break;
						case 2 : puntuacion=puntuacion+(letrasdisp[k].valor*2); break;
						default: puntuacion=puntuacion+letrasdisp[k].valor; break;
					}
				}
			}
				
			/* Distingue cuando una palabra se debe multiplicar por 2 o por 3 */
			
			switch (tablero[f][j].valor) {
				case 4 : mult=2*mult; break;
				case 5 : mult=3*mult; break;
			}
			cont++;
		}
	}
		
	else {
		for (i=f;i<f+strlen(palabra);i++) {

			/* Obtencion de la puntuacion de cada letra */
			
			for (k=0;k<dim;k++) {
				if (palabra[cont]==letrasdisp[k].letra) {				
					printf("Letra: %c, valor letra: %d, valor tablero: %d\n" DEF,letrasdisp[k].letra,letrasdisp[k].valor,tablero[i][c].valor);
					switch (tablero[i][c].valor){
						case 3 : puntuacion=puntuacion+(letrasdisp[k].valor*3); break;
						case 2 : puntuacion=puntuacion+(letrasdisp[k].valor*2); break;
						default: puntuacion=puntuacion+letrasdisp[k].valor; break;
					}
				}
			}
				
			/* Distingue cuando una palabra se debe multiplicar por 2 o por 3 */
			
			switch (tablero[i][c].valor) {
				case 4 : mult=2*mult; break;
				case 5 : mult=3*mult; break;
			}
			cont++;
		}
	}
	
	if (primera_jugada==0) mult=2;			// Primera jugada sobre * doble valor de palabra

	puntuacion=puntuacion*mult;				/* Puntuacion de la jugada */

	printf("La puntuacion de la palabra %s es %d (multiplicador=%d)\n" DEF,palabra,puntuacion,mult);

	return puntuacion;
}
