/*
 * Cli_H_heart.c
 *
 *  Created on: Mar 15, 2017
 *      Author: w
 */
#include "client_h.h"

void heart_init()
{
	heart_s_buff[0]=0x55;
	heart_s_buff[1]=0xAA;
	heart_s_buff[2]=0;
	heart_s_buff[3]=0;
	heart_s_buff[4]=0xFF;
	heart_s_buff[5]=0;
	heart_s_buff[6]=0;
	heart_s_buff[7]=0;
	heart_s_buff[8]=0;
	heart_s_buff[9]=0;
	heart_s_buff[10]=0xEE;
}

int find_heart(char *buf,int len)
{
	char look[2]={0};
	look[0]=0xFF;
	look[1]=0x00;
	char *tmp=NULL;
	tmp=strstr(buf+4,look);
	if((tmp-buf)==4){
		printf("heart ok! heart_count=3; auth_count=3;\n");
		heart_count=3;
		auth_count=3;
		auth_state=0;
		return 0;
	}
	else if((tmp-buf)!=4){
		printf("heart error!\n");
		if(auth_state==0){
			if(heart_count>1){
				printf("heart_count out! sockfd = %d ,heart_count =%d\n",soc_h_fd,heart_count);
				heart_count--;
				read_data();
			}
			else {
				printf("heart over! sockfd = %d ,heart_count =%d\n",soc_h_fd,heart_count);
				close_all_cfd();
				return -1;
			}
		}
		else{
			if(auth_count>1){
				printf("auth_count out! sockfd = %d ,auth_count =%d\n",soc_h_fd,auth_count);
				auth_count--;
				start_token();
			}
			else {
				printf("token over! sockfd = %d ,auth_count =%d\n",soc_h_fd,auth_count);
				close_all_cfd();
				return -1;
			}			
		}
	}
}

int read_heart()
{
	while(1){
		int ret=0;
		bzero(heart_r_buff,1024);
		usleep(500000);
		ret=recv(soc_h_fd,heart_r_buff,1023,MSG_WAITALL);
		if(ret==-1 || ret==0){
			printf("recvtimeout!%d\n",soc_h_fd);
			if(heart_count>1){
				heart_count--;
				read_heart();
			}
			else {
				printf("close all sfd!\n");
				close_all_cfd();
				return ret;
			}
		}
		else{
			printf("ret=%d\n",ret);
			find_heart(heart_r_buff,ret);
		}
	}
}

void send_heart()
{
	int i=0;
	while(1){
		i=send(soc_h_fd,heart_s_buff,12,0);
		printf("%d,sockfd=%d,len %d\n",i,soc_h_fd,12);
		usleep(500000);
	}
}

int do_heart(int *fd,char *buf,int len)
{
	soc_h_fd=*fd;
	if(find_heart(buf,len)==0){
		pid_t pid;
		pid=fork();
		if(pid<0)
			perror("fork");
		else if(pid==0){
			printf("..\n");
			send_heart();
		}
		else{
			printf(",,\n");
			read_heart();
		}
	}
	return -1;
}
