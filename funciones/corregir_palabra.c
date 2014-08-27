// Función que mira si la palabra está en el diccionario, para ello hay que modificar la palabra de la jugada enviada
// sustituir los '_' por las letras del tablero y los '*' por la letra que corresponde al comodín
// como el comodín va a ir representado por una minúscula habrá que transformarla en mayúscula para entrar al diccionario
// ya que no se puede verificar la palabra 'HOlA' por ejemplo, y luego deshacer el cambio para que la minúscula salga en el tablero

void corregir_palabra(char palabra[15], int fila, int columna, int orientacion, int a)	// a para elegir si es la palabra introducida o nuevas palabras
{
	int aux_comodin=0;	// para ver si hay dos comodines
	int i;
	
	bzero(auxiliar,15);
	
	if (cod_error==0) {
		AspellConfig * spell_config = new_aspell_config();
		aspell_config_replace(spell_config, "lang", "en_US");
		AspellCanHaveError * possible_err = new_aspell_speller(spell_config);
		AspellSpeller * spell_checker = 0;
		if (aspell_error_number(possible_err) != 0) {
			puts(aspell_error_message(possible_err));
		}
		else spell_checker = to_aspell_speller(possible_err);
		
		if (orientacion==0) {	// horizontal
			for (i=0;i<15;i++) {
				if (palabra[i]=='_') {		// si la letra es '_' se toma la letra del tablero
					if (tablero[fila][columna+i].letra[0]>='a' && tablero[fila][columna+i].letra[0]<='z') auxiliar[i]=tablero[fila][columna+i].letra[0]-32;
					else auxiliar[i]=tablero[fila][columna+i].letra[0];
				}
				else if (palabra[i]=='*') {				// si la letra es '*' se toma la letra del comodín
					if (aux_comodin==0) {				// para el primer comodín 
						auxiliar[i]=comodin[0]-32;		// se resta 32 para transformarla en mayúscula
						aux_comodin++;
					}
					else auxiliar[i]=comodin2[0]-32;	// para el posible segundo comodín
				}
				else if (palabra[i]>='a' && palabra[i]<='z') auxiliar[i]=palabra[i]-32;	//puede ser que se haya cogido una letra comodín del tablero
				else auxiliar[i]=palabra[i];
			}
		}
		if (orientacion==1) {	// vertical, mismo procedimiento que en horizontal
			for (i=0;i<15;i++) {
				if (palabra[i]=='_') {
					if (tablero[fila+i][columna].letra[0]>='a' && tablero[fila+i][columna].letra[0]<='z') auxiliar[i]=tablero[fila+i][columna].letra[0]-32;
					else auxiliar[i]=tablero[fila+i][columna].letra[0];
				}
				else if (palabra[i]=='*') {
					if (aux_comodin==0) {
						auxiliar[i]=comodin[0]-32;
						aux_comodin++;
					}
					else auxiliar[i]=comodin2[0]-32;
				}
				else if (palabra[i]>='a' && palabra[i]<='z') auxiliar[i]=palabra[i]-32;
				else auxiliar[i]=palabra[i];
			}
		}
		printf(B_YELLOW "Palabra introducida: %s " DEF,auxiliar);
		int correct = aspell_speller_check(spell_checker, auxiliar, strlen(palabra));
		if (correct==0) {
			printf(B_YELLOW "incorrecta\n" DEF);
			cod_error=-3;
		}
		else printf(B_YELLOW "correcta\n" DEF);
		
		// Para transformar los comodines en minusculas y que estas aparezcan en el tablero
		
		aux_comodin=0;
		
		for (i=0;i<15;i++) {
			if (palabra[i]=='*') {
				if (aux_comodin==0) {
					auxiliar[i]=comodin[0];
					aux_comodin++;
				}
				else auxiliar[i]=comodin2[0];
			}
		}
		if (a==1) strcpy(palabra2,auxiliar);
	}
	
	return;
}
