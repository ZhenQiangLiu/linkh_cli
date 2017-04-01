/*
 * Cli_token.c
 *
 *  Created on: Mar 1, 2017
 *      Author: w
 */


#include "client_h.h"

void send_token()
{
	int i=0;
	char p[]="<gwsctrl><token val=\"abcdef0123456789abcdef0123456789\"/></gwsctrl>";
	unsigned int length=0;
	length=strlen(p);
	unsigned short crc_num=0;
	crc_num=crc16_calc(p,length);
	char msgbuff[1024]={0};
	char *tmp=(char *)(msgbuff+8);
	num NUM,NUM1,NUM2;
	NUM.n=Cli_Seq;
	NUM1.n=length;
	NUM2.n=crc_num;
	msgbuff[0]=0x55;
	msgbuff[1]=0xAA;
	msgbuff[2]=NUM.change[1];
	msgbuff[3]=NUM.change[0];
	msgbuff[4]=0x02;
	msgbuff[5]=0x10;
	msgbuff[6]=NUM1.change[1];
	msgbuff[7]=NUM1.change[0];
	strncat((msgbuff+8),p,length+1);
	printf("msgbuff: %s\n",&msgbuff[8]);
	msgbuff[9+length]=NUM2.change[1];
	msgbuff[10+length]=NUM2.change[0];
	msgbuff[11+length]=0xEE;
	i=send(soc_t_fd,&msgbuff[0],511,0);
	heart_count=3;
	printf("\n%d,sockfd=%d\nmsg: %s\n",i,soc_t_fd,&msgbuff[0]);
}

int read_data()
{
	int ret=0;
	bzero(token_r_buff,1024);
	usleep(500000);
	ret=recv(soc_t_fd,token_r_buff,1023,MSG_WAITALL);
	if(ret==-1 || ret==0){
		if(auth_state==0 && heart_count>1){
			printf("heart_count out! sockfd = %d ,heart_count =%d\n",soc_t_fd,heart_count);
			heart_count--;
			read_data();
		}
		else if(auth_state==1 && auth_count>1){
			printf("auth_count out! sockfd = %d ,auth_count =%d\n",soc_t_fd,auth_count);
			auth_count--;
			start_token();
		}
		else {
			printf("token error! sockfd = %d ,heart_count =%d ,auth_count =%d\n",soc_t_fd,heart_count,auth_count);
			close_all_cfd();
			return ret;
		}
	}
	else{
		printf("ret=%d\n",ret);
		return ret;
	}
}

int start_token()
{
	send_token();
	return read_data();
}

int Cli_auth_token(int *fd)
{
	int flags=0,ret=0;
	flags = fcntl(*fd, F_GETFL, 0);
	fcntl(*fd, F_SETFL, flags | O_NONBLOCK);
	soc_t_fd=*fd;
	printf("token\n");
	ret=start_token();
	if(ret>0)
		do_heart(fd,token_r_buff,ret);
	return 0;
}


