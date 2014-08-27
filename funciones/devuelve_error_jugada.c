// Función que detecta algun error al hacer una jugada

int devuelve_error_jugada(char palabra[15], int f, int c, int o)
{
	int k, cont=0;
	
	int c_aux, f_aux, contiene_asterisco=0;	// para mirar si la palabra contiene la posición central en la primera jugada
	
	cod_error=0;	// se inicializa el código de error a cero, y se modifica según el tipo de error que haya dado
	
	scrabble=0;		// variable que determina si has utilizado todas las letras
	
	// Detecta palabras que se salen del tablero horizontales o verticales
	
	if (o==1) {
		if ((f+strlen(palabra)>15) || ((c<0) && (c>=15))) cod_error=-1;
	}
	
	else if (o==0) {
		if ((c+strlen(palabra)>15) || ((f<0) && (f>=15))) cod_error=-2;
	}

	corregir_palabra(palabra,f,c,o,1);	// busca en el diccionario y devuelve -3 si no existe la palabra
	
	se_solapa(palabra,f,c,o);	// si la palabra que quieres poner se solapa con otra devuelve -4
	
	if (cod_error==0) {			// si la orientacion no es 0 o 1 devuelve -5
		if ((o!=0) && (o!=1)) cod_error=-5;
	}
	
	if (cod_error==0) {			// si la primera jugada no contiene la posición central devuelve -6
		if (primera_jugada==0) {
			if (o==0) {
				if (f==7) {
					if (c==7) contiene_asterisco=1;
					else {
						for (c_aux=c;c_aux<c+strlen(palabra);c_aux++) {
							if (c_aux==7) contiene_asterisco=1;
						}
					}
				}
			}
			else if (o==1) {
				if (c==7) {
					if (f==7) contiene_asterisco=1;
					else {
						for (f_aux=f;f_aux<f+strlen(palabra);f_aux++) {
							if (f_aux==7) contiene_asterisco=1;
						}
					}
				}
			}
			if (contiene_asterisco==0) cod_error=-6;
		}
	}
	
	if (cod_error==0) {			// si la palabra tiene algún caracter que no es ni mayúscula ni _ ni *
		for (i=0;i<strlen(palabra);i++) {
			if (!isupper(palabra[i]) && (palabra[i]!='_') && (palabra[i]!='*')) cod_error=-7;
		}
	}
	
	// Mirar si la jugada toca alguna de las letras del tablero
	
	toca_palabra(palabra,f,c,o);
	
	// Mira las nuevas palabras creadas en la direccion perpendicular a la introducida y calcula sus puntuaciones

	palabras_nuevas(palabra,f,c,o);
	
	// Detecta el uso de letras que no se tienen	
	
	contrastar_letras_mano(palabra1,0);
	
	// Mirar si se ha hecho scrabble
	
	for (k=0;k<strlen(jug[player].letras);k++) if (jug[player].letras[k]=='.') cont++;
	
	if (cont==7) scrabble=50;

	codigo_error(cod_error);
	return cod_error;
}
