#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT 8080
#define BUFFER_SIZE 256

int main (int argc, char **argv){
	int fd;
	char *buffer[BUFFER_SIZE];
	char *message = "Olá servidor!";
	struct sockaddr_in address;

	if((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("O socket não foi criado\n");
		return 1;
  	}

	address.sin_family = AF_INET;
	address.sin_port = PORT;

	inet_pton(AF_INET, argv[1], &address.sin_addr);

	if((connect(fd, (struct sockaddr *) &address, sizeof(address))) < 0) {
		printf("Não foi possivel se conectar ao servidor:/\n");
		return 1;
	}


	send(fd, message, strlen(message), 0);
	printf("Mensagem enviada: %s\n", message);

	read(fd, buffer, BUFFER_SIZE);
	printf("Resposta recebida: %s\n", buffer);

	close(fd);

	return 0;
}
