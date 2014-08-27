void recibir_ok(socket_recibir)
{
	bzero(buffer,buffer_length);
	read(socket_recibir,buffer,buffer_length-1);
	return;
}
