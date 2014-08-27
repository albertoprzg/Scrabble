// Función para coger letras aleatoriamente del array letras_disp

char letra_aleatoria()
{
	int k,l,m=0; // Contadores
	int p=0;	 // Elemento del array 'letras_disp' que cogemos

	// Bucle de creacion del array con todas las letras disponibles

	for (k=0;k<dim;k++) {	// se recorren todos los tipos de ficha A,B,C,...,Z,*
		for (l=m;l<=(m+letrasdisp[k].disp);l++) {	// Se va generando un array con todas las fichas teniendo en cuenta 
			letras_disp[l]=letrasdisp[k].letra;		// las que quedan disponibles
		}
	m=m+letrasdisp[k].disp;
	}

	// Bucle de seleccion de letras, de entre todas las letras del array se coge 1

	if (dim_fichas_disp>0) {
		p=rand() % (dim_fichas_disp+1);
		for(k=0;k<dim;k++) {			// se recorre de nuevo el array para ver qué letra ha tocado y se decrementa la disponibilidad
			if(letrasdisp[k].letra==letras_disp[p]) letrasdisp[k].disp--;	// de esa letra
		}
	}

	dim_fichas_disp--;	// se decrementa el número de fichas totales del saco

	return letras_disp[p];	// se devuelve la letra que ha salido aleatoriamente
}
