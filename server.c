#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT 8080
#define BACKLOG 3
#define BUFFER_SIZE 256


int main (){
	int fd;
	char *buffer[BUFFER_SIZE];
	struct sockaddr_in address;
	char *message = "VOCE ME CHAMOU?";
	int connfd;

	if((fd = socket(AF_INET, SOCK_STREAM, 0)) <0) {
		printf("A porta nao foi criada\n");
		return 1;
	}

	address.sin_family=AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = PORT;

	if(bind(fd, (struct sockaddr*) &address, sizeof(address))< 0) {
		printf("Interface de rede indisponivel\n");
		return 1;
	}


	if(listen(fd, BACKLOG) < 0) {
		printf("Nao foi possivel configurar\n");
		return 1;
	}

	printf("O servidor esta pronta para receber requisicoes:)\n");
	connfd = accept(fd,(struct sockaddr *) NULL, NULL);
	if(connfd< 0) {
		printf("nao foi possivel aceitar a conexao\n");
		return 1;
	}

	read(connfd, buffer, BUFFER_SIZE);
	printf("mensagem recebida: %s\n", buffer);



	write(connfd, message, strlen(message));
	printf("Resposta enviada: %s\n", message);

	close(connfd);
	close(fd);
	return 0;

}
