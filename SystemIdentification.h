#ifndef SYSTEMIDENTIFICATION_H
#define SYSTEMIDENTIFICATION_H

typedef struct _sysidf SYSIDF;

struct _sysidf
{
	HANDLE send;
	HANDLE rec;
};

void SysIdfInit(SYSIDF** p);

#endif // !SYSTEMIDENTIFICATION_H

