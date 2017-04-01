
#ifndef CLI_H_INIT_H
#define CLI_H_INIT_H

static char ip_buf[16]={0};
static int port=0;

static int auth_count=3;
static int heart_count=3;

int Cli_H_init(int *soc_fd);

#endif
