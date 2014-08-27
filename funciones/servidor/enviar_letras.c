// Se mandan las letras al socket de un jugador separadas por ','

void enviar_letras(int socket_mandar)
{
	char letra[2];
	bzero(buffer,buffer_length);
	for (k=0;k<7;k++) {
		sprintf(letra,"%c",jug[player].letras[k]);
		strcat(buffer,letra);
		strcat(buffer,",");
	}
	write(socket_mandar,buffer,strlen(buffer));
	return;
}
