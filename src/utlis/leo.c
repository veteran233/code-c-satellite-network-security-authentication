#include "header/leo.h"

int socketFd;
struct sockaddr_in saddr;
struct sockaddr_in geoSAddr;

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
    strcpy(msg + 1, "leo1");
    sendto(socketFd, msg, MAXLEN, 0, (LPSOCKADDR)&tccSAddr, tccLen);

    msg[0] = 1;
    strcpy(msg + 1, "geo1");
    sendto(socketFd, msg, MAXLEN, 0, (LPSOCKADDR)&tccSAddr, tccLen);
    recvfrom(socketFd, msg, MAXLEN, 0, (LPSOCKADDR)&tccSAddr, &tccLen);
    geoSAddr.sin_addr.s_addr = inet_addr(msg);

    msg[0] = 2;
    strcpy(msg + 1, "geo1");
    sendto(socketFd, msg, MAXLEN, 0, (LPSOCKADDR)&tccSAddr, tccLen);
    recvfrom(socketFd, msg, MAXLEN, 0, (LPSOCKADDR)&tccSAddr, &tccLen);
    int port = ((msg[0] & 0xff) << 8) + ((msg[1] & 0xff));
    geoSAddr.sin_port = htons(port);

    geoSAddr.sin_family = AF_INET;
}

void firstOperation()
{
}