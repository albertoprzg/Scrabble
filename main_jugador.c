#include "funciones/game_definitions.h"
#include "funciones/muestra_tablero.c"
#include "funciones/muestra_letras.c"
#include "funciones/cliente/recibir_tablero.c"
#include "funciones/cliente/enviar_jugada.c"
#include "funciones/cliente/recibir_situacion.c"
#include "funciones/cliente/recibir_letras.c"
#include "funciones/cliente/mandar_ok.c"
#include "funciones/codigo_error.c"


int main(int argc, char *argv[])
{
	struct hostent *server;
	
	system("clear");
	printf(DEF);
	
	// Mirar si se han introducido argumentos en la llamada de la función
	
	if (argc < 3) {
		fprintf(stderr,"uso: %s servidor puerto\n",argv[0]);
		exit(0);
	}
	
	// Construir la dirección del server
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	server = gethostbyname(argv[1]);
	serv_addr.sin_family = AF_INET;
	
	serv_addr.sin_addr.s_addr = * (unsigned long *)server->h_addr;
	
	portno = atoi(argv[2]);
	serv_addr.sin_port = htons(portno);
	
	// Conectar al socket
	
	connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr));
	
	printf(B_GREEN "Conectado al servidor (IP:%s)\n\n" DEF,(char *) inet_ntoa(serv_addr.sin_addr));
	
	// Recibir el numero de jugador que eres
	
	bzero(buffer,buffer_length);
	read(sockfd,buffer,buffer_length-1);
	numero_jugador=atoi(buffer)+1;
	printf(B_GREEN "Eres el jugador %d\n\n" DEF,numero_jugador);
	
	// Mandar ok
	
	mandar_ok(sockfd);
	
	while (partida_activa==1) {
		
		printf(DEF "Espera tu turno\n\n" DEF);
		
		// Leer mensaje de si sigue activa la partida
		
		bzero(buffer,buffer_length);
		read(sockfd,buffer,buffer_length-1);
		partida_activa=atoi(buffer);
		
		if (partida_activa==0) break;
		
		else if (partida_activa==1) {
			
			printf(DEF "Es tu turno\n\n" DEF);
			
			do {
				
				cod_error=0;
						
				// Mandar ok
			
				mandar_ok(sockfd);

				// Recibir el tablero antes de jugar
				
				recibir_tablero();
					
				// Mandar ok
			
				mandar_ok(sockfd);
		
				// Recibir situacion de puntos
				
				recibir_situacion();
				
				// Mandar ok
				
				mandar_ok(sockfd);
				
				// Recibir tus letras
				
				recibir_letras();
				
				// Mandar ok
				
				mandar_ok(sockfd);
				
				// Enviar la jugada que quieres hacer
				
				enviar_jugada();
				
				system("clear");
			
				// Recibir si hay error en la jugada que has hecho
				
				bzero(buffer,buffer_length);
				read(sockfd,buffer,buffer_length-1);
				cod_error=atoi(buffer);
				codigo_error(cod_error);

			}
			
			while (cod_error!=0);
			
			// Mandar ok
			
			mandar_ok(sockfd);

			// Recibir puntuacion de la jugada
			
			bzero(buffer,buffer_length);
			read(sockfd,buffer,buffer_length-1);
			puntuacion_ext=atoi(buffer);
			printf(B_GREEN "\nLa puntuacion de la jugada es: %d\n" DEF, puntuacion_ext);
		
			// Mandar ok

			mandar_ok(sockfd);
			
			// Recibir el tablero despues de jugar
			
			recibir_tablero();
			muestra_tablero(0);
			
			// Mandar ok

			mandar_ok(sockfd);
		}
    }
    
    if (partida_activa==0) {
		
		printf(B_BLUE "La partida ha terminado\n\nPuntuación final de los jugadores:\n" DEF);
		
		// Recibir situacion de puntos
			
		recibir_situacion();
		
		for (i=0;i<numero_jugadores;i++) {
			printf(B_BLUE "Jugador %d: %d puntos\n" DEF,i+1,jug[i].punt);
		}
	}
	
	// Cerramos el socket
	
	close(sockfd);
	
	return 0;
}
