// Funcion que tiene en cuenta si una nueva palabra puesta en el tablero crea palabras extra al entrar en contacto
// con otras palabras ya existentes del tablero

void palabras_nuevas(char palabra[15], int f, int c, int o)
{
		
// Las variables fila_com, fila_fin, columna_com, columna_fin indican los limites de las nuevas palabras formadas
// La variable nueva_palabra[15] almacena las nuevas palabras formadas

	int fila_com, fila_fin, columna_com, columna_fin, nueva_o;
	char nueva_palabra[15];
	int punt_aux;			// es una puntuación auxiliar que se modifica cada vez que se crea una nueva palabra, y esta modifica la puntuación provisional
	char letra[2];			// permite concatenar cada letra de la nueva palabra en el string nueva_palabra
	
	int i,j,k;

	puntuacion_prov=0;	
	
	if (cod_error==0) {
			
		if (o==0) {
			for (j=c;j<c+strlen(palabra);j++) {
				if (palabra[j-c]!='_') {
					
					// si se está tocando una letra del tablero se analiza esa nueva palabra
					
					if (((tablero[f-1][j].letra[0]>='A' && tablero[f-1][j].letra[0]<='Z') || (tablero[f+1][j].letra[0]>='A' && tablero[f+1][j].letra[0]<='Z')) || ((tablero[f-1][j].letra[0]>='a' && tablero[f-1][j].letra[0]<='z') || (tablero[f+1][j].letra[0]>='a' && tablero[f+1][j].letra[0]<='z'))) {
						
						bzero(nueva_palabra,15);
						bzero(letra,2);	
						
						// se determina la fila de comienzo
						
						fila_com=f-1;
						while (tablero[fila_com][j].letra[0]>='A') fila_com--;
						fila_com++;
						
						// se determina la fila de final
						
						fila_fin=f+1;
						while (tablero[fila_fin][j].letra[0]>='A') fila_fin++;
						fila_fin--;
						
						// se construye la nueva palabra, en el caso de llegar a la fila en la que se va a poner la palabra es necesario
						// añadir la letra que se va a poner y no la letra del tablero porque todavía no está puesta la palabra en el tablero

						for (k=fila_com;k<=fila_fin;k++) {
							if (k==f) {
								sprintf(letra,"%c",palabra[j-c]);
								strcat(nueva_palabra,letra);
							}
							else {
								sprintf(letra,"%c",tablero[k][j].letra[0]);
								strcat(nueva_palabra,letra);
							}
						}
						
						columna_com=j;
						nueva_o=1;
						
						printf(B_YELLOW "\nNueva palabra creada de [%d,%d] a [%d,%d]\n" DEF, fila_com+1, j+1, fila_fin+1, j+1);
						
						// se corrige esa nueva palabra
						
						corregir_palabra(nueva_palabra,fila_com,columna_com,nueva_o,0);
						
						if (cod_error==0) {
							punt_aux=calc_puntuacion(auxiliar,fila_com,columna_com,nueva_o);	// se calcula la puntuación de la nueva palabra, teniendo en cuenta que se han podido coger comodines, en cuyo caso la letra minúscula no puntúa
							puntuacion_prov=puntuacion_prov+punt_aux;
						}
						else if (cod_error==-3) {
							cod_error=-11;
							return;
						}
					}
				}
			}
		}
			
		if (o==1) {
			for (i=f;i<f+strlen(palabra);i++) {
				if (palabra[i-f]!='_') {
					if (((tablero[i][c-1].letra[0]>='A' && tablero[i][c-1].letra[0]<='Z') || (tablero[i][c+1].letra[0]>='A' && tablero[i][c+1].letra[0]<='Z')) || ((tablero[i][c-1].letra[0]>='a' && tablero[i][c-1].letra[0]<='z') || (tablero[i][c+1].letra[0]>='a' && tablero[i][c+1].letra[0]<='z'))) {						
						
						bzero(nueva_palabra,15);
						bzero(letra,2);	
						
						columna_com=c-1;
						while (tablero[i][columna_com].letra[0]>='A') columna_com--;
						columna_com++;
						
						columna_fin=c+1;
						while (tablero[i][columna_fin].letra[0]>='A') columna_fin++;
						columna_fin--;
						
						for (k=columna_com;k<=columna_fin;k++) {
							if (k==c) {
								sprintf(letra,"%c",palabra[i-f]);
								strcat(nueva_palabra,letra);
							}
							else {
								sprintf(letra,"%c",tablero[i][k].letra[0]);
								strcat(nueva_palabra,letra);
							}
						}

						fila_com=i;
						nueva_o=0;
						
						printf(B_YELLOW "\nNueva palabra creada de [%d,%d] a [%d,%d]\n" DEF, i+1, columna_com+1, i+1, columna_fin+1);
						
						corregir_palabra(nueva_palabra,fila_com,columna_com,nueva_o,0);
						
						if (cod_error==0) {
							punt_aux=calc_puntuacion(nueva_palabra,fila_com,columna_com,nueva_o);
							puntuacion_prov=puntuacion_prov+punt_aux;
						}
						else if (cod_error==-3) {
							cod_error=-11;
							return;
						}
					}
				}
			}
		}
		printf(B_GREEN "\nPuntuación total de nuevas palabras: %d\n\n" DEF,puntuacion_prov);
	}
	
	return;
}
