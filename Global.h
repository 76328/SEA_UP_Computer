#ifndef GLOBAL_H
#define GLOBAL_H

#include "Delay/delay.h"
#include "Com/udpcom.h"
#include "Data/EmbededData.h"
#include "SignalGen/polyplanner.h"
#include "SystemIdentification.h"

#define USE_DEFAULT_CONFIG

typedef struct _global GLOBAL;

struct _global
{

    DELAY* tick;
    UDP* udp;
    EMBEDED_DATA* ebd_data;
    POLYTASK* polytask;
    SYSIDF* idftask;
};

extern GLOBAL gData;
void Init();
#endif
