void enviar_jugada()
{
	int correcto;		// te dará la opción de corregir tu jugada si te has equivocado en algún dato introducido

	do {				// se repite el bucle de preguntas hasta que estés seguro de la jugada que quieres hacer
		
		// Ponemos a cero todas las variables que se van a enviar por socket para evitar errores
		
		bzero(buffer,buffer_length);
		bzero(jugada,strlen(jugada));
		bzero(palabra,strlen(palabra));
		bzero(fila,strlen(fila));
		bzero(columna,strlen(columna));
		bzero(orientacion,strlen(orientacion));
		bzero(comodin,strlen(comodin));
		bzero(comodin2,strlen(comodin2));
		
		correcto=0;
		
		// Mostrar tablero sin enseñar las letras que quedan en el saco
		
		muestra_tablero(0);
		
		// Mostrar situacion de puntos de todos los jugadores
		
		printf(BRIGHT);
		printf(CYAN "Fichas restantes: %d\n", dim_fichas_disp);
		for (i=0;i<numero_jugadores;i++) {
			printf("Jugador %d: %d puntos\n",i+1,jug[i].punt);
		}
		
		// Mostrar solo tus letras
		
		muestra_letras(0,numero_jugador);
		
		do {
			printf(DEF "\nQué jugada quieres hacer: \n1: Jugar palabra\n2: Cambiar letras\n3: Pasar turno\n" DEF);
			scanf("%s",jugada);
		}
		while ((jugada[0]!='1') && (jugada[0]!='2') && (jugada[0]!='3'));
		strcat(buffer,jugada);
		strcat(buffer,",");
		
		if  (jugada[0]=='1') {			// poner palabra
		
			printf(DEF "Por favor, escribe tu palabra en mayúsculas\n(si utilizas comodín ponlo como *)\n(si quieres incluir una letra del tablero ponla como _): ");
			scanf("%s",palabra);
			strcat(buffer,palabra);
			strcat(buffer,",");
			k=0;
			numero_comodines=0;
			while (palabra[k]!=0) {
				if( palabra[k]=='*') numero_comodines++;		// ver cuantos comodines ha utilizado en la jugada
				k++;
			}
			if (numero_comodines==0) strcat(buffer,"0");
			if (numero_comodines==1) strcat(buffer,"1");
			if (numero_comodines==2) strcat(buffer,"2");
			strcat(buffer,",");
			if (numero_comodines>0) {							// letra para el primer comodín
			
				printf("Introduce la letra que quieres en el comodín\n(en minúsula): ");
				scanf("%s",comodin);
				strcat(buffer,comodin);
				strcat(buffer,",");
			}
			if (numero_comodines>1) {							// se contempla la posibilidad de que tenga dos comodines
			
				printf("Introduce la letra que quieres en el segundo comodín\n(en minúscula): ");
				scanf("%s",comodin2);
				strcat(buffer,comodin2);
				strcat(buffer,",");
			}
			printf("En qué fila quieres empezar?: ");
			scanf("%s",fila);
			strcat(buffer,fila);
			strcat(buffer,",");
			printf("En qué columna quieres empezar?: ");
			scanf("%s",columna);
			strcat(buffer,columna);
			strcat(buffer,",");
			printf("Vertical (1) u horizontal (0)?: ");
			scanf("%s",orientacion);
			strcat(buffer,orientacion);
			printf(B_YELLOW "\nLa jugada que quieres hacer es:\nPalabra: %s\n", palabra);
			if (numero_comodines==1) printf("El comodín es: %s\n",comodin);
			if (numero_comodines==2) printf("El segundo comodín es: %s\n",comodin2);
			printf("Fila: %s\nColumna: %s\nOrientación: %s\nIntroduce 1 si es correcto, o 0 si no lo es: ", fila, columna, orientacion);
			scanf("%d",&correcto);
		}
		
		else if (jugada[0]=='2') {
			printf(DEF "Introduce las letras que quieres cambiar (en mayúsculas):\n" DEF);
			scanf("%s",palabra);
			strcat(buffer,palabra);
			strcat(buffer,",");
			printf(B_YELLOW "\nLas letras que quieres cambiar son: '%s'\nIntroduce 1 si es correcto, o 0 si no lo es: ", palabra);
			scanf("%d",&correcto);
		}
		
		else if (jugada[0]=='3') {
			printf(B_YELLOW "\nVas a pasar tu turno\nIntroduce 1 si es correcto, o 0 si no lo es: ");
			scanf("%d",&correcto);
			if (correcto==1) printf(DEF "\nHas pasado el turno\n" DEF);
		}
	}
	while (correcto==0);
	
	write(sockfd,buffer,strlen(buffer));
	return;
}
