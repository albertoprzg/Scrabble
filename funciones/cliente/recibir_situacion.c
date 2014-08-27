// Necesitas conocer el numero de jugadores en la partida para luego representar todas las puntuaciones
// aux es el numero de jugadores
// También recibes las fichas que quedan

void recibir_situacion()
{
	char aux[2], puntuacion_jugador[4], fichas[3];

	bzero(buffer,buffer_length);
	read(sockfd,buffer,buffer_length-1);
	token=strtok(buffer,",");
	strcpy(aux,token);
	numero_jugadores=atoi(aux);
	for (i=0;i<numero_jugadores;i++) {
		token=strtok(NULL,",");
		strcpy(puntuacion_jugador,token);
		jug[i].punt=atoi(puntuacion_jugador);
	}
	token=strtok(NULL,",");
	strcpy(fichas,token);
	dim_fichas_disp=atoi(fichas);
	return;
}
