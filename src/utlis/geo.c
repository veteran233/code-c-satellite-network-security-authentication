#include "header/geo.h"

int socketFd;
struct sockaddr_in saddr;

void sockInit()
{
    socketFd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    saddr.sin_addr.s_addr = INADDR_ANY;
    saddr.sin_port = htons(0);
    saddr.sin_family = AF_INET;

    bind(socketFd, (LPSOCKADDR)&saddr, sizeof(saddr));

    struct sockaddr_in tccSAddr;
    tccSAddr.sin_addr.s_addr = inet_addr(TCC_DEFAULT_ADDR);
    tccSAddr.sin_port = htons(TCC_DEFAULT_PORT);
    tccSAddr.sin_family = AF_INET;

    int tccLen = sizeof(tccSAddr);

    char msg[MAXLEN];

    msg[0] = 0;
    strcpy(msg + 1, "geo1");
    sendto(socketFd, msg, MAXLEN, 0, (LPSOCKADDR)&tccSAddr, tccLen);
}