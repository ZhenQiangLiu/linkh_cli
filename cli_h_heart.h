/*
 * Cli_H_heart.h
 *
 *  Created on: Mar 15, 2017
 *      Author: w
 */


#ifndef CLI_H_HEART_H_
#define CLI_H_HEART_H_

static char heart_r_buff[1024]={0};
static char heart_s_buff[1024]={0};
static int soc_h_fd=0;
static int auth_state=1;
int do_heart(int *fd,char *buf,int len);
void heart_init();

#endif /* CLI_H_HEART_H_ */
