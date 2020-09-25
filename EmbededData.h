#pragma once
#ifndef  EMBEDEDDATA_H
#define EMBEDEDDATA_H
typedef struct _embededdata EMBEDED_DATA;

struct _embededdata
{
	float pos;
	char cmd;
};

bool EmbededDataModuleRegister(EMBEDED_DATA **p);

#endif // ! EmbededData_H
