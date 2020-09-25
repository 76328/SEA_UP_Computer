#include "Global.h"

GLOBAL gData;

#define PMODE

void Init()
{
	DelayModuleRegister(&gData.tick);
	UdpModuleRegister(&gData.udp);
	EmbededDataModuleRegister(&gData.ebd_data);
#ifdef PMODE
	polytask_init(&gData.polytask);
#endif // PMODE

#ifdef IDFMODE
	SysIdfInit(&gData.idftask);
#endif // IDFMODE


}