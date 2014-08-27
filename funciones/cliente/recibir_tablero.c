// Se recibe un buffer con todos los caracteres separados por ',' por lo que se va leyendo ese buffer y guardando los caracteres
// en los caracteres del tablero

void recibir_tablero()
{
	int i,j;
	
	bzero(buffer,buffer_length);
	read(sockfd,buffer,buffer_length-1);
	for (i=0;i<15;i++) {
		for (j=0;j<15;j++) {
			if ((i==0) && (j==0)) {
				token=strtok(buffer,",");
				strcpy(tablero[0][0].letra,token);
			}
			else {
				token=strtok(NULL,",");
				strcpy(tablero[i][j].letra,token);
			}
		}
	}
	return;
}
