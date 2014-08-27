// Función de creación del tablero inicial y asignación de las letras disponibles

void crea_tablero()
{
	// Inicializamos los caracteres de cada casilla a '.'

	for (i=0;i<15;i++) {
		for (j=0;j<15;j++) {
			tablero[i][j].letra[0]='.';
		}
	}

	// Se comienza poniendo en los caracteres del tablero un número en función del multiplicado 2l,3l,2w,3w
	
	tablero[0][0].letra[0]='5'; tablero[0][3].letra[0]='2'; tablero[0][7].letra[0]='5'; tablero[1][5].letra[0]='3';
	tablero[2][6].letra[0]='2'; tablero[3][7].letra[0]='2'; tablero[5][5].letra[0]='3'; tablero[6][6].letra[0]='2'; 
	tablero[1][1].letra[0]='4'; tablero[2][2].letra[0]='4'; tablero[3][3].letra[0]='4'; tablero[4][4].letra[0]='4';
	tablero[7][7].letra[0]='*';
	
	// Completamos los valores del resto del tablero por simetría

	for (i=0;i<8;i++) {
		for (j=0;j<8;j++) {
			tablero[j][i].letra[0]=tablero[i][j].letra[0];
		}
	}

	for (i=0;i<8;i++) {
		for (j=8;j<15;j++) {
			tablero[i][j].letra[0]=tablero[i][14-j].letra[0];
			}
		}
	for (i=8;i<15;i++) {
		for (j=0;j<15;j++) {
			tablero[i][j].letra[0]=tablero[14-i][j].letra[0];
			}
		}

	// Bucle para inicializar los valores de cada casilla
	
	for (i=0;i<15;i++) {
		for (j=0;j<15;j++) {
			if (tablero[i][j].letra[0]=='.') tablero[i][j].valor=1;
			else tablero[i][j].valor=(tablero[i][j].letra[0]-48);	// se resta 48 para que el valor equivalga al caracter (tabla ASCII)
		}
	}
	
	tablero[7][7].valor=1;
		
	// Estructura de fichas disponibles
	// Fichas totales: 100
	
	letrasdisp[0].letra='*'; letrasdisp[0].valor=0; letrasdisp[0].disp=2;
	letrasdisp[1].letra='A'; letrasdisp[1].valor=1; letrasdisp[1].disp=9;
	letrasdisp[2].letra='B'; letrasdisp[2].valor=3; letrasdisp[2].disp=2;
	letrasdisp[3].letra='C'; letrasdisp[3].valor=3; letrasdisp[3].disp=2;
	letrasdisp[4].letra='D'; letrasdisp[4].valor=2; letrasdisp[4].disp=4;
	letrasdisp[5].letra='E'; letrasdisp[5].valor=1; letrasdisp[5].disp=12;
	letrasdisp[6].letra='F'; letrasdisp[6].valor=4; letrasdisp[6].disp=2;
	letrasdisp[7].letra='G'; letrasdisp[7].valor=2; letrasdisp[7].disp=3;
	letrasdisp[8].letra='H'; letrasdisp[8].valor=4; letrasdisp[8].disp=2;
	letrasdisp[9].letra='I'; letrasdisp[9].valor=1; letrasdisp[9].disp=9;
	letrasdisp[10].letra='J'; letrasdisp[10].valor=8; letrasdisp[10].disp=1;
	letrasdisp[11].letra='K'; letrasdisp[11].valor=5; letrasdisp[11].disp=1;
	letrasdisp[12].letra='L'; letrasdisp[12].valor=1; letrasdisp[12].disp=4;
	letrasdisp[13].letra='M'; letrasdisp[13].valor=3; letrasdisp[13].disp=2;
	letrasdisp[14].letra='N'; letrasdisp[14].valor=1; letrasdisp[14].disp=6;
	letrasdisp[15].letra='O'; letrasdisp[15].valor=1; letrasdisp[15].disp=8;
	letrasdisp[16].letra='P'; letrasdisp[16].valor=3; letrasdisp[16].disp=2;
	letrasdisp[17].letra='Q'; letrasdisp[17].valor=10; letrasdisp[17].disp=1;
	letrasdisp[18].letra='R'; letrasdisp[18].valor=1; letrasdisp[18].disp=6;
	letrasdisp[19].letra='S'; letrasdisp[19].valor=1; letrasdisp[19].disp=4;
	letrasdisp[20].letra='T'; letrasdisp[20].valor=1; letrasdisp[20].disp=6;
	letrasdisp[21].letra='U'; letrasdisp[21].valor=1; letrasdisp[21].disp=4;
	letrasdisp[22].letra='V'; letrasdisp[22].valor=4; letrasdisp[22].disp=2;
	letrasdisp[23].letra='W'; letrasdisp[23].valor=4; letrasdisp[23].disp=2;
	letrasdisp[24].letra='X'; letrasdisp[24].valor=8; letrasdisp[24].disp=1;
	letrasdisp[25].letra='Y'; letrasdisp[25].valor=4; letrasdisp[25].disp=2;
	letrasdisp[26].letra='Z'; letrasdisp[26].valor=10; letrasdisp[26].disp=1;
	
	return;
}
