// Función que muestra las letras
// Argumento a para que represente las de todos los jugadores si es el server o solo las de cada jugador
// El otro argumento servirá para indicar la puntuación que tiene el cliente (ya que el no sabe qué número de jugador es)

void muestra_letras(int a, int jugador)		
{											
	if (a==1) {
		for (i=0;i<numero_jugadores;i++) {
			printf(B_RED "Letras del jugador %d: '",i+1);
			for (k=0;k<7;k++) {
				printf(B_RED "%c",jug[i].letras[k]);
			}
			printf("'\n" DEF);
		}
		printf("\n" DEF);
	}
	else if (a==0) {
		printf(B_RED "\nJugador %d, tus letra son: '",jugador);
		for (k=0;k<7;k++) {
			printf(B_RED "%c",jug[jugador].letras[k]);
		}
		printf("'\n" DEF);
	}
}
