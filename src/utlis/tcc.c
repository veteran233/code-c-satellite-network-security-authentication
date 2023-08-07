#include "header/tcc.h"

int socketFd;
struct sockaddr_in saddr;
struct SatelliteStatus satelliteList[MAXLEN];
int listLen = 0;

void *findSatelliteAddr(void *args)
{
    struct SatelliteStatus *statusArgs = args;
    for (int i = 0; i < listLen; ++i)
    {
        if (!strcmp(satelliteList[i].name, statusArgs->name))
        {
            char *addr = inet_ntoa(satelliteList[i].sin.sin_addr);

            sendto(socketFd, addr, sizeof(addr), 0, (LPSOCKADDR)&statusArgs->sin, sizeof(statusArgs->sin));

            printf("TCC Message: %s:%u query the Address of %s\n",

                   inet_ntoa(statusArgs->sin.sin_addr),
                   ntohs(statusArgs->sin.sin_port),
                   statusArgs->name);

            // free(addr);

            break;
        }
    }

    return (void *)NULL;
}

void *findSatellitePort(void *args)
{
    struct SatelliteStatus *statusArgs = args;
    for (int i = 0; i < listLen; ++i)
    {
        if (!strcmp(satelliteList[i].name, statusArgs->name))
        {
            char *port = (char *)malloc(sizeof(char) * 2);
            port[0] = (satelliteList[i].sin.sin_port & 0x00ff);
            port[1] = ((satelliteList[i].sin.sin_port & 0xff00) >> 8);

            sendto(socketFd, port, sizeof(port), 0, (LPSOCKADDR)&statusArgs->sin, sizeof(statusArgs->sin));

            printf("TCC Message: %s:%u query the Port of %s\n",

                   inet_ntoa(statusArgs->sin.sin_addr),
                   ntohs(statusArgs->sin.sin_port),
                   statusArgs->name);

            free(port);

            break;
        }
    }

    return (void *)NULL;
}

void *add(void *args)
{
    struct SatelliteStatus *statusArgs = args;
    satelliteList[listLen] = *statusArgs;
    ++listLen;

    printf("TCC Message: %s had been add into Satellite List\n", statusArgs->name);

    return (void *)NULL;
}

void sockInit()
{
    socketFd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    saddr.sin_addr.s_addr = inet_addr(TCC_DEFAULT_ADDR);
    saddr.sin_port = htons(TCC_DEFAULT_PORT);
    saddr.sin_family = AF_INET;

    bind(socketFd, (LPSOCKADDR)&saddr, sizeof(saddr));
}

void run()
{
    while (1)
    {
        struct sockaddr_in clientSAddr;
        int clientLen = sizeof(clientSAddr);

        char msg[MAXLEN];

        recvfrom(socketFd, msg, MAXLEN, 0, (LPSOCKADDR)&clientSAddr, &clientLen);

        if (msg[0] == 0)
        {
            pthread_t th;
            struct SatelliteStatus args;

            char *name = casmsg_get(msg, 1, 5);
            strcpy(args.name, name);
            free(name);

            args.sin = clientSAddr;

            pthread_create(&th, NULL, add, &args);
            pthread_detach(th);
        }
        else if (msg[0] == 1)
        {
            pthread_t th;
            struct SatelliteStatus args;

            char *name = casmsg_get(msg, 1, 5);
            strcpy(args.name, name);
            free(name);

            args.sin = clientSAddr;

            pthread_create(&th, NULL, findSatelliteAddr, &args);
            pthread_detach(th);
        }
        else if (msg[0] == 2)
        {
            pthread_t th;
            struct SatelliteStatus args;

            char *name = casmsg_get(msg, 1, 5);
            strcpy(args.name, name);
            free(name);

            args.sin = clientSAddr;

            pthread_create(&th, NULL, findSatellitePort, &args);
            pthread_detach(th);
        }
    }
}