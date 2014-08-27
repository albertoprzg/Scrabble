// Funcion para mostrar el ERROR cuya entrada es el codigo de error

void codigo_error(int cod_error)
{
	switch (cod_error) {
		case -1: printf(B_RED "ERROR: La palabra no cabe en el tablero verticalmente\n" DEF);
		break;
		case -2: printf(B_RED "ERROR: La palabra no cabe en el tablero horizontalmente\n" DEF);
		break;
		case -3: printf(B_RED "ERROR: La palabra no está en el diccionario\n" DEF);
		break;
		case -4: printf(B_RED "ERROR: La palabra no cabe en el tablero\n" DEF);
		break;
		case -5: printf(B_RED "ERROR: Has introducido una orientación no válida\n" DEF);
		break;
		case -6: printf(B_RED "ERROR: La primera jugada tiene que contener la casilla [8,8]\n" DEF);
		break;
		case -7: printf(B_RED "ERROR: Has introducido caracteres inválidos\n" DEF);
		break;
		case -8: printf(B_RED "ERROR: No dispones de esas fichas\n" DEF);
		break;
		case -9: printf(B_RED "ERROR: Has introducido demasiadas fichas para cambiar\n" DEF);
		break;
		case -10: printf(B_RED "ERROR: La palabra introducida tiene que tocar alguna ficha del tablero\n" DEF);
		break;
		case -11: printf(B_RED "ERROR: Has creado una nueva palabra no válida\n" DEF);
		break;
		default: printf(B_GREEN "Jugada realizada con éxito\n" DEF);
	}
}
