void mandar_ok(socket_mandar)
{
	bzero(buffer,buffer_length);
	write(socket_mandar,"OK",2);
	return;
}
