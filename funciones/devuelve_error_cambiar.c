// Mira que no se produzcan errores al cambiar de letras

int devuelve_error_cambiar(char palabra[7])
{
	
	cod_error=0;
	
	// Mirar si las letras que has introducido no sobrepasan las que puedes cambiar
	
	if (strlen(palabra)>7) cod_error=-9;
	
	// Mirar si dispones de las letras que quieres cambiar, te sustituye esas letras por '.' si no ha habido errores 
	
	contrastar_letras_mano(palabra,1);
		
	codigo_error(cod_error);
	return cod_error;
}
