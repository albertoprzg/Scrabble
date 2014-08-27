// Se envía el numero de jugadores en la partida
// Se envían todas las puntuaciones de los jugadores
// Se envía el número de fichas restantes

void enviar_situacion(socket_mandar)
{
	int i;
	
	char numero_jug[2], puntuacion_jugador[4], num_fichas[3];
	
	bzero(buffer,buffer_length);
	sprintf(numero_jug,"%d",numero_jugadores);
	strcat(buffer,numero_jug);
	strcat(buffer,",");
	for (i=0;i<numero_jugadores;i++) {
		sprintf(puntuacion_jugador,"%d",jug[i].punt);
		strcat(buffer,puntuacion_jugador);
		strcat(buffer,",");
	}
	sprintf(num_fichas,"%d",dim_fichas_disp);
	strcat(buffer,num_fichas);
	strcat(buffer,",");
	write(socket_mandar,buffer,strlen(buffer));
	return;
}
		
