

#include "client_h.h"

void close_all_cfd()
{
	close(sockfd);
	kill(0,SIGQUIT);
}

int main()
{
	while(1){
		do{
		}while(Cli_H_init(&sockfd));
		Cli_auth_token(&sockfd);
	}
	close_all_cfd();
}
