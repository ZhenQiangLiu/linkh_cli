/*
 * Client_H.h
 *
 *  Created on: Mar 15, 2017
 *      Author: w
 */

#ifndef CLIENT_H_H_
#define CLIENT_H_H_

#include "cli_h_init.h"
#include "crc16.h"
#include "cli_h_heart.h"
#include "cli_token.h"
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>

static int sockfd=0;

void close_all_cfd();

#endif /* CLIENT_H_H_ */
