#pragma once
#include "__GLOBAL__.h"
#include "casmsg.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <pthread.h>

extern int socketFd;

extern struct sockaddr_in saddr;

struct SatelliteStatus
{
    char name[5];
    struct sockaddr_in sin;
};

extern struct SatelliteStatus satelliteList[MAXLEN];
extern int listLen;

void *findSatelliteAddr(void *args);

void *findSatellitePort(void *args);

void *add(void *args);

void sockInit();

void run();