#ifndef DELAY_H
#define DELYA_H

typedef struct _delay DELAY;

struct _delay
{
	void (*DelayMs)(double dMilliseconds);
	double (*GetTickCountMs)();
};

bool DelayModuleRegister(DELAY **p);
#endif
