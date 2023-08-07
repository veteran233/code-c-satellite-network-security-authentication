#pragma once
#include "__GLOBAL__.h"
#include "casmsg.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>

extern int socketFd;

extern struct sockaddr_in saddr;
extern struct sockaddr_in geoSAddr;

void sockInit();

void firstOperation();