#pragma once
#include <string.h>
#include <stdlib.h>

void *casmsg_1(void *msg);

void *casmsg_2(void *msg1, void *msg2);

void *casmsg_3(void *msg1, void *msg2, void *msg3);

void *casmsg_4(void *msg1, void *msg2, void *msg3, void *msg4);

void *casmsg_get(void *msg, int startPos, int endPos);