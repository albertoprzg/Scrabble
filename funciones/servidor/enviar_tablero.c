// Función que manda todos los caracteres del tablero separándolos por ','

void enviar_tablero(int socket_mandar)
{
	bzero(buffer,buffer_length);
	for (i=0;i<15;i++) {
		for (j=0;j<15;j++) {
			strcat(buffer,tablero[i][j].letra);
			strcat(buffer,",");
		}
	}
	write(socket_mandar,buffer,strlen(buffer));
	return;
}
