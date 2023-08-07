#include "header/casmsg.h"

void *casmsg_1(void *msg)
{
    return msg;
}

void *casmsg_2(void *msg1, void *msg2)
{
    void *ret = malloc(sizeof(msg1) + sizeof(msg2));

    int begin = 0;
    memcpy(ret + begin, msg1, sizeof(msg1));

    begin += sizeof(msg1);
    memcpy(ret + begin, msg2, sizeof(msg2));

    return ret;
}

void *casmsg_3(void *msg1, void *msg2, void *msg3)
{
    void *ret = malloc(sizeof(msg1) + sizeof(msg2) + sizeof(msg3));

    int begin = 0;
    memcpy(ret + begin, msg1, sizeof(msg1));

    begin += sizeof(msg1);
    memcpy(ret + begin, msg2, sizeof(msg2));

    begin += sizeof(msg2);
    memcpy(ret + begin, msg3, sizeof(msg3));

    return ret;
}

void *casmsg_4(void *msg1, void *msg2, void *msg3, void *msg4)
{
    void *ret = malloc(sizeof(msg1) + sizeof(msg2) + sizeof(msg3) + sizeof(msg4));

    int begin = 0;
    memcpy(ret + begin, msg1, sizeof(msg1));

    begin += sizeof(msg1);
    memcpy(ret + begin, msg2, sizeof(msg2));

    begin += sizeof(msg2);
    memcpy(ret + begin, msg3, sizeof(msg3));

    begin += sizeof(msg3);
    memcpy(ret + begin, msg4, sizeof(msg4));

    return ret;
}

void *casmsg_get(void *msg, int startPos, int endPos)
{
    void *ret = malloc(endPos - startPos + 1);

    memcpy(ret, msg + startPos, endPos - startPos + 1);

    return ret;
}