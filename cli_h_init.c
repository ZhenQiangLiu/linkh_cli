#include "client_h.h"

void Cli_sighandler(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close_all_cfd();

}

int Cli_H_init(int *soc_fd)
{	
	int ret=0;
	signal(SIGINT,(__sighandler_t) Cli_sighandler);
	signal(SIGQUIT,(__sighandler_t) Cli_sighandler);
	signal(SIGCHLD, SIG_IGN);
	heart_init();
	//read user input
	printf("please input ip and port\n");

	scanf("%s%d",ip_buf,&port);
	*soc_fd=socket(AF_INET,SOCK_STREAM,0);
	if(*soc_fd==-1){
		perror("socket");
	}
	struct sockaddr_in serv;
	serv.sin_family=AF_INET;
	serv.sin_port=htons(port);
	printf("%d\n",port);
	inet_pton(AF_INET,ip_buf,&serv.sin_addr);
	ret=connect(*soc_fd,(struct sockaddr*)&serv,sizeof(struct sockaddr_in));
	if(ret==-1){
		perror("connect:");
		return 1;
	}
	return 0;
}

