// Se recibe un buffer en el que están las letras separadas por ',' se destokeniza y se van asignando esas letras a tus letras

void recibir_letras()
{
	char letra[2];
	
	bzero(buffer,buffer_length);
	read(sockfd,buffer,buffer_length-1);
	token=strtok(buffer,",");
	strcpy(letra,token);
	jug[numero_jugador].letras[0]=letra[0];
	for (i=1;i<7;i++) {
		token=strtok(NULL,",");
		strcpy(letra,token);
		jug[numero_jugador].letras[i]=letra[0];
	}
	return;
}
