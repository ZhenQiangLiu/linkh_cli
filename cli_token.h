/*
 * Cli_token.h
 *
 *  Created on: Mar 1, 2017
 *      Author: w
 */



#ifndef CLI_TOKEN_H_
#define CLI_TOKEN_H_

typedef union {
	unsigned short n;
	unsigned char change[2];
}num;

static unsigned short Cli_Seq=1;
static int soc_t_fd=0;
static char token_r_buff[1024]={0};

int read_data();
int start_token();

#endif /* CLI_TOKEN_H_ */
