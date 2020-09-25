#include "EmbededData.h"
static EMBEDED_DATA _ebd_data;


bool EmbededDataModuleRegister(EMBEDED_DATA** p)
{
	_ebd_data.pos = 0.00000001;
	*p = &_ebd_data;
	return 0;
}