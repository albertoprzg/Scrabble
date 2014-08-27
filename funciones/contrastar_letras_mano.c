// Mira si el jugador dispone de las letras que ha utilizado, tanto si va a cambiar letras como si va a poner una palabra
// si la jugada es de cambiar letras las repondrá en el saco las letras cambiadas

void contrastar_letras_mano(char palabra[15], int cambiar)	// el segundo argumento distingue si es jugada de cambiar o no
{
	
	int i,j,cont;
	char aux[7];	// aux se va a utilizar para modificar las letras del jugador sin cambiarlas definitivamente por si hay algún un error
	strcpy(aux,jug[player].letras);
	
	if (cambiar==0) {
		if (cod_error==0) {					
			for(i=0;i<strlen(palabra);i++) {		// bucle de la palabra introducida
				cont=0;
				if ((palabra[i]>='A') && (palabra[i]<='Z')) {
					for (j=0;j<strlen(jug[player].letras);j++) {	// bucle de las letras del jugador
						if (palabra[i]==aux[j]) {
						aux[j]='.';
						cont++;
						break;
						}
					}
					if (cont==0) {
						cod_error=-8;
						return;
					}
				}
					
				else if (palabra[i]=='*') {
					for (j=0;j<strlen(jug[player].letras);j++) {
						if (palabra[i]==aux[j]) {
							 aux[j]='.';
							 cont++;
							 break;
						 }
					}
					if (cont==0) {
					cod_error=-8;
					return;
					}
				}
			}
		}
	}
	if (cambiar==1) {
		if (cod_error==0) {											// si la jugada es de cambiar letras habrá que meter esas letras al saco
			for(i=0;i<strlen(palabra);i++) {						// bucle de la palabra
				cont=0;
				if ((palabra[i]>='A') && (palabra[i]<='Z')) {
					for (j=0;j<strlen(jug[player].letras);j++) {		// bucle de las letras
						if (palabra[i]==aux[j]) {
						aux[j]='.';
						cont++;
						break;
						}
					}
					if (cont==0) {
						cod_error=-8;
						return;
					}
				}
					
				else if (palabra[i]=='*') {
					for (j=0;j<strlen(jug[player].letras);j++) {
						if (palabra[i]==aux[j]) {
							 aux[j]='.';
							 cont++;
							 break;
						 }
					}
					if (cont==0) {
					cod_error=-8;
					return;
					}
				}
			}
		}
		if (cod_error==0) {
			for (i=0;i<strlen(palabra);i++)  {
				if (palabra[i]=='*') {
					letrasdisp[0].disp++;
					dim_fichas_disp++;
				}
				else if ((palabra[i]>='A') && (palabra[i]<='Z')) {
					letrasdisp[palabra[i]-64].disp++;
					dim_fichas_disp++;
				}
			}
		}
	}
		
	if (cod_error==0) strcpy(jug[player].letras,aux);		// si tiene todas las letras de la jugada finalmente se modifican sus letras
															
	return;	
}

