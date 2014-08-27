// Read from socket

void recibir_jugada(int socket_recibir)
{
	int f,c,o;
	puntuacion_ext=0;
	
	bzero(jugada,strlen(jugada));
	bzero(palabra,strlen(palabra));
	bzero(palabra1,strlen(palabra1));
	bzero(palabra2,strlen(palabra2));
	bzero(fila,strlen(fila));
	bzero(columna,strlen(columna));
	bzero(orientacion,strlen(orientacion));
	bzero(comodines,strlen(comodines));
	bzero(comodin,strlen(comodin));
	bzero(comodin2,strlen(comodin2));
	
	bzero(buffer,buffer_length);
	read(socket_recibir,buffer,buffer_length-1);
	token=strtok(buffer,",");
	strcpy(jugada,token);

	if (jugada[0]=='1') {
		token=strtok(NULL,",");
		strcpy(palabra,token);
		strcpy(palabra1,palabra);
		token=strtok(NULL,",");
		strcpy(comodines,token);
		if (atoi(comodines)>0) {
			token=strtok(NULL,",");
			strcpy(comodin,token);
		}
		if (atoi(comodines)>1) {
			token=strtok(NULL,",");
			strcpy(comodin2,token);
		}
		token=strtok(NULL,",");
		strcpy(fila,token);
		token=strtok(NULL,",");
		strcpy(columna,token);
		token=strtok(NULL,",");
		strcpy(orientacion,token);
		
		f=atoi(fila)-1;
		c=atoi(columna)-1;
		o=atoi(orientacion);
		
		correccion=devuelve_error_jugada(palabra,f,c,o);	// se verifica que no haya errores en la jugada

		if (correccion==0) {	// comprueba que no haya errores para hacer la jugada
		
			puntuacion_ext=calc_puntuacion(palabra2,f,c,o)+puntuacion_prov+scrabble;	// puntuación de la jugada
			
			if (scrabble==50) printf(B_GREEN "\nSCRABBLE! 50 puntos\n" DEF);
			
			printf(B_GREEN "\nPuntuacion de la jugada: %d\n" DEF,puntuacion_ext);
			
			jug[player].punt=jug[player].punt+puntuacion_ext;	// modificar la puntuación del jugador
			
			coloca_palabra(palabra2,f,c,o);						// colocar la palabra
			
			dar_letras(0,player);								// reponerle letras al jugador
			
			primera_jugada++;									// cambiar la variable primera_jugada para no verificar otra vez si se contiene al [8,8]
		}
	}
	
	if (jugada[0]=='2') {		// ahora la palabra son las letras que quieres cambiar
	
		token=strtok(NULL,",");
		
		strcpy(palabra,token);
		
		correccion=devuelve_error_cambiar(palabra);	// se verifica si hay algún error al cambiar de letras
		
		if (correccion==0) {
			
			dar_letras(0,player);					// si no ha habido errores se reponen '.' por nuevas letras
		}
	}
	
	if (jugada[0]=='3') {
		
		printf(B_YELLOW "Ha pasado turno\n" DEF);
		
	}
	
	if (cod_error==0) {						// si no ha habido error y la jugada es pasar turno se incrementa la variable
		if (jugada[0]=='3') pasa_turno++;	// pasa_turno, esto permite acabar la partida si se pasan 2 rondas seguidas
		else pasa_turno=0;					// si no ha sido jugada de pasar turno se inicializa a 0 esa variable
	}
	
	return;
}
