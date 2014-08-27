#include "funciones/game_definitions.h"
#include "funciones/letra_aleatoria.c"
#include "funciones/dar_letras.c"
#include "funciones/contrastar_letras_mano.c"
#include "funciones/crea_tablero.c"
#include "funciones/muestra_tablero.c"
#include "funciones/muestra_letras.c"
#include "funciones/codigo_error.c"
#include "funciones/corregir_palabra.c"
#include "funciones/se_solapa.c"
#include "funciones/toca_palabra.c"
#include "funciones/calc_puntuacion.c"
#include "funciones/palabras_nuevas.c"
#include "funciones/devuelve_error_jugada.c"
#include "funciones/devuelve_error_cambiar.c"
#include "funciones/coloca_palabra.c"
#include "funciones/servidor/recibir_jugada.c"
#include "funciones/servidor/enviar_tablero.c"
#include "funciones/servidor/enviar_situacion.c"
#include "funciones/servidor/enviar_letras.c"
#include "funciones/servidor/recibir_ok.c"

int main(int argc, char *argv[])
{
	system("clear");
	printf(DEF);
	
	// Para generar el numero aleatorio se cambia la semilla

	srand(time(NULL));
	crea_tablero();
	
	// Comprobar que se ha pasado argumento de puerto a la función
	
	if (argc < 2) {
		fprintf(stderr,"uso: %s puerto\n",argv[0]);
		exit(1);
	}
	
	// Crear socket
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	// Preguntar cuantos jugadores van a participar en la partida
	
	printf("Cual es el numero de jugadores de la partida\n");
	scanf("%d",&numero_jugadores);
	
	// Bucle hasta que se conecten todos los jugadores
	
	k=0;
	
	while (k<numero_jugadores) {
		
		// Bind socket
		
		portno = atoi(argv[1]);
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = INADDR_ANY;
		serv_addr.sin_port = htons(portno);
		
		bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
		
		// Aceptar conexiones al socket
		
		listen(sockfd,numero_comodines);
		clilen = sizeof(cli_addr);
		if (newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen)) {
			strcpy(jug[k].jugador,(char *) inet_ntoa(cli_addr.sin_addr));
			jug[k].socket=newsockfd;
			printf(B_GREEN "Jugador %d (IP:%s) conectado (%d)\n" DEF, k+1, jug[k].jugador,jug[k].socket);
			k++;
		}
	}
	
	// Bucle para mandar a cada jugador el número de jugador que es cada uno
	
	for (k=0;k<numero_jugadores;k++) {
		bzero(buffer,buffer_length);
		sprintf(buffer,"%d",k);
		write(jug[k].socket,buffer,strlen(buffer));
		
		// Leer mensaje de ok
		
		recibir_ok(jug[k].socket);
	}
	
	// Bucle de asignacion de letras iniciales a cada jugador
	
	for (k=0;k<numero_jugadores;k++) {
		dar_letras(1,k);
	}
	
	while (partida_activa==1) {
		
		// Asignar turno
	
		if (numero_jugadores==1) player=0;
		else {
			player=turno%numero_jugadores;
		}
		printf("\nTurno del Jugador %d\n\n",player+1);
			
		// Mirar si la partida sigue activa
		
		for (i=0;i<numero_jugadores;i++) {							// o un jugador se queda sin fichas
			huecos=0;
			for (k=0;k<strlen(jug[player].letras);k++) {
				if (jug[player].letras[k]=='.') huecos++;
			}
			if (huecos==7) partida_activa=0;
		}
		
		if (pasa_turno==2*numero_jugadores) partida_activa=0;		// o se pasa el turno 2 rondas consecutivas
		
		// Manda si sigue la partida activa al jugador que dispone de turno
			
		bzero(buffer,buffer_length);
		sprintf(buffer,"%d",partida_activa);						
		write(jug[player].socket,buffer,strlen(buffer));
		
		// si no sigue activa avisa a todos los demás que se ha acabado
		
		if (partida_activa==0) {
			for (i=0;i<numero_jugadores;i++) {
				if (i!=player) {					
					write(jug[i].socket,buffer,strlen(buffer));
				}
			}
			break;
		}
		
		// si todavia sigue activa la partida
		
		else if (partida_activa==1) {
			
			// Mostrar las letras de los jugadores
			
			muestra_letras(1,0);
			
			// Mostrar fichas restantes y puntuacion de los jugadores
			
			printf(BRIGHT);
			for (i=0;i<numero_jugadores;i++) {
				printf(CYAN "Jugador %d: %d puntos\n",i+1,jug[i].punt);
			}
				
			// Bucle para que repita la jugada si hay error
			
			do {
				
				muestra_tablero(1);
				
				printf(DEF "\nEsperando a Jugador %d\n\n" DEF,player+1);
			
				cod_error=0;	// inicializamos el valor del error a cero
				
				// Leer mensaje de ok
			
				recibir_ok(jug[player].socket);
				
				// Mandar tablero antes de jugar
				
				enviar_tablero(jug[player].socket);	
				
				// Leer mensaje de ok
			
				recibir_ok(jug[player].socket);
				
				// Mandar situacion antes de jugar
				
				enviar_situacion(jug[player].socket);
				
				// Leer mensaje de ok
			
				recibir_ok(jug[player].socket);
				
				// Mandar letras del jugador
				
				enviar_letras(jug[player].socket);
				
				// Leer mensaje de ok
			
				recibir_ok(jug[player].socket);

				// Recibir jugada
				
				recibir_jugada(jug[player].socket);				
				muestra_tablero(1);
				
				// Mandar si hay error o no
				
				bzero(buffer,buffer_length);
				sprintf(buffer,"%d",cod_error);
				write(jug[player].socket,buffer,strlen(buffer));

			}

			while (cod_error!=0);

			// Leer mensaje de ok
			
			recibir_ok(jug[player].socket);
			
			// Mandar puntuacion de la jugada
			
			bzero(buffer,buffer_length);
			sprintf(buffer,"%d",puntuacion_ext);
			write(jug[player].socket,buffer,strlen(buffer));
					
			// Leer mensaje de ok
			
			recibir_ok(jug[player].socket);
			
			// Mandar situacion despues de jugar
			
			enviar_tablero(jug[player].socket);
			
			// Leer mensaje de ok
			
			recibir_ok(jug[player].socket);
			
			turno++;
		}
	}
	
	if (partida_activa==0) {
		
		printf(B_BLUE "\nLa partida ha terminado\n\nPuntuación final de los jugadores:\n" DEF);
		
		// Manda la puntuacion final a todos los jugadores e imprime las puntuciones
		
		for (i=0;i<numero_jugadores;i++) {
			
			printf(B_BLUE "Jugador %d: %d puntos\n" DEF,i+1,jug[i].punt);
				
			enviar_situacion(jug[i].socket);

			close(sockfd);	// cerramos el socket
		}
	}

	return 0;
}
