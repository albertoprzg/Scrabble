// Función para dar letras a cada jugador
// Argumento inicio para rellenar las 7 letras o solo las que le falten y jugador al que reponerle las letras

void dar_letras(int inicio, int jugador)		
{
	if (inicio==1) {
		for (i=0;i<7;i++) {
			if (dim_fichas_disp>0) {			// si quedan letras se le da una letra, si no quedan se le da '.'
				jug[jugador].letras[i]=letra_aleatoria();
			}
			else jug[jugador].letras[i]='.';
		}
	}
	
	else if (inicio==0) {
		for (i=0;i<7;i++) {
			if (dim_fichas_disp>0) {
				if (jug[jugador].letras[i]=='.') jug[jugador].letras[i]=letra_aleatoria();
			}
			else jug[jugador].letras[i]='.';
		}
	}
	if (dim_fichas_disp==0) printf(B_RED "\nNo quedan mas fichas\n" DEF);
	return;
}
