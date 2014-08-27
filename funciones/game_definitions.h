#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Aspell

#include <aspell.h>

// Para el random necesitamos cambiar una semilla, utilizamos un valor variable, el tiempo

#include <time.h>

// Para los sockets

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>

// =======================
// Definicion de variables
// =======================

// Constante de tipos de ficha A,B,C,...,Z,*

#define dim 27

// Colores

#define DEF "\033[m"
#define RED "\033[31m"
#define B_RED "\033[31;1m"
#define GREEN "\033[32m"
#define B_GREEN "\033[32;1m"
#define YELLOW "\033[33m"
#define B_YELLOW "\033[33;1m"
#define BLUE "\033[34m"
#define B_BLUE "\033[34;1m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define BRIGHT "\033[1m"

// Jugadores, jugador contiene dirección ip, socket contiene el número de socket que ve el servidor, letras y puntuación del jugador

struct jugador {char jugador[15]; int socket; char letras[7]; int punt;};
struct jugador jug[4];

// Para el tablero, i,j variables para recorrer filas y columnas (a veces se utilizan para bucles)

int i,j;											
struct tipocasilla {char letra[2]; int valor;}; 	// Estructura del tablero, se define la letra del tablero como string de 2 char
struct tipocasilla tablero[15][15];					// por comodidad en el envío a través de los sockets (bastará con hacer strcat al buffer)
													// aunque luego sólo se modificará el valor tablero[i][j].letra[0] que será quien lleve 
													// la letra, el entero valor llevará el multiplicador de la casilla

// Estructura de fichas

struct letrasdisponibles {char letra; int valor; int disp;};	// letrasdisp contendrá todas las letras del saco, el char de la letra
struct letrasdisponibles letrasdisp[dim];						// su valor de puntuación y las fichas disponibles de esa letra

// Desarrollo del juego

char letras_disp[100];		// Array que contiene las fichas que todavía no se han cogido del saco

int dim_fichas_disp=100;	// Numero total de fichas disponibles

char auxiliar[15];			// Esta variable auxiliar permite recomponer la jugada introducida colocando comodines y cogiendo las letras
							// del tablero para luego verificar si es correcta
							
int cod_error=0;			// Será 0 si no hay error al hacer una jugada y un numero negativo si lo hay

int player,turno=0;			// Turno irá incrementándose y player hará el resto de su división entera entre el número de jugadores
							// para ir eligiendo el turno a un jugador u otro
							
int k; 						// Contador para distintos bucles

int correccion;	 			// Nos dira si se ha producido algun error

char palabra[15];			// Palabra que se va a poner en el tablero

char palabra1[15];			// Nos permite comprobar las letras que ha utilizado el jugador para ver si dispone de ellas
							// sin contar las letras que ha cogido del tablero ni los comodine ('*' o '_')
							
char palabra2[15]; 			// Nos permite calcular la puntuación de una palabra teniendo en cuenta las letras del tablero
							// que se han utilizado, no tiene en cuenta ni '*' ni '_'

int puntuacion_ext;			// Para mandar puntuación de cada jugada vía sockets

int puntuacion_prov;		// Para almacenar una puntuacion mientras se determina si hay errores, y no modificar la puntuación global

int primera_jugada=0;		// Distinguir primera jugada del resto, para contener la casilla [8,8]

int numero_jugador;			// Identifica a cada jugador como 0,1,2,3, sirve para que cada cliente sepa que número de jugador es

int partida_activa=1;		// Para indicar si todavia se sigue jugando o si ya se ha acabado la partida

int scrabble;				// Determina si se han puesto las 7 letras del jugador y suma 50 puntos

int huecos;					// Cuenta huecos en las letras de cada jugador, para saber si se le han acabado las letras y terminar la partida

int pasa_turno=0;			// Cuenta las veces que se pasa de turno, cuando llega a 2*numero_jugadores se acaba la partida

// Para sockets vamos a utilizar un buffer en el cual vamos concatenando la información y la separamos con ',' (utilizando el comando strcat)
// El buffer recibido se separará leyendo hasta la siguiente ',' por medio de tokenes (utilizando strtok) de esta manera podemos distinguir
// distintos tipos de jugada, situaciones (como tener comodín o no)

char buffer[512];			// Buffer con toda la información

int buffer_length=512;		// Para longitud del buffer

char *token;				// Recorrerá el buffer encontrando la siguiente ','

// Toda la información enviada se concatena en el buffer, por ello utilizamos strings en vez de enteros
// Luego haremos uso de la función atoi que nos convertirá ese string enviado en un entero para un uso más cómodo

char jugada[1], fila[3], columna[3], orientacion[3], comodin[3], comodin2[3], comodines[3];

// Numero de jugadores en la partida, número de comodines que hay en cada palabra enviada, es posible que se juegue con uno o dos comodines

int numero_jugadores, numero_comodines;

// Declaraciones para la construcción de sockets

int sockfd, newsockfd, portno;
socklen_t clilen;
struct sockaddr_in serv_addr, cli_addr;

