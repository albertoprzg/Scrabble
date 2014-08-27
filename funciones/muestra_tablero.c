// Función para respresentar el tablero, y las letras del saco en el caso del servidor
	
void muestra_tablero(int a)
{
	int letras_por_fila=0;		// Para colocar las fichas en filas de 25 letras
	int m,l;
	
	printf(DEF);
	printf(BRIGHT "\n               SITUACIÓN DEL TABLERO:\n");
	printf(B_GREEN "\n  | 1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 |\n");
	printf("  | -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  |\n");
	for (i=0;i<15;i++) {
		if (i<9) {
			printf(" %d| " DEF,(i+1));
		 }
		else printf("%d| " DEF,(i+1));
		for (j=0;j<14;j++) {
			switch (tablero[i][j].letra[0])	// en función del caracter del tablero se muestra por pantalla un caracter distinto
			{
				case '5': printf(B_RED "3w " DEF);
				break;
				case '4': printf(B_YELLOW "2w " DEF);
				break;
				case '3': printf(BRIGHT);
				printf(CYAN "3l " DEF);
				break;
				case '2': printf(B_BLUE"2l " DEF);
				break;
				case '.': printf(BRIGHT ".  " DEF);
				break;
				default: printf(BRIGHT "%c  " DEF,tablero[i][j].letra[0]);
				break;
			}
		}
		switch (tablero[i][14].letra[0])
		{
			case '5': printf(B_RED "3w ");
			printf(B_GREEN "|\n");
			break;
			case '4': printf(B_YELLOW "2w ");
			printf(B_GREEN "|\n");
			break;
			case '3': printf(BRIGHT);
			printf(CYAN "3l ");
			printf(B_GREEN "|\n");
			break;
			case '2': printf(B_BLUE "2l ");
			printf(B_GREEN "|\n");
			break;
			case '.': printf(BRIGHT ".  ");
			printf(B_GREEN "|\n");
			break;
			default: printf(BRIGHT "%c  ",tablero[i][14].letra[0]);
			printf(B_GREEN "|\n");
			break;
		}
	}
	printf("  | -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  |\n\n" DEF);

	
	// Mostrar las letras restantes del saco si eres servidor
	
	if (a==1) {
		
		m=0;
		for (k=0;k<dim;k++) {
			for (l=m;l<=(m+letrasdisp[k].disp);l++) {
				letras_disp[l]=letrasdisp[k].letra;
			}
		m=m+letrasdisp[k].disp;
		}
		
		printf(BRIGHT "               LETRAS RESTANTES: %d\n\n" DEF, dim_fichas_disp);
		for(k=0;k<dim_fichas_disp;k++) {
			if (letras_por_fila==24){
				printf(BRIGHT "%c\n" DEF,letras_disp[k]);
				letras_por_fila=0;
			}
			else {
				printf(BRIGHT "%c " DEF,letras_disp[k]);
				letras_por_fila++;
			}
		}
		printf("\n" DEF);
	}
	
	return;
}
