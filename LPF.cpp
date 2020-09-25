#include "LPF.h"

LPF refacc;


float LPF_CAL(float in,LPF *p)
{
	p->a = 0.01;
	p->x = p->x + p->a * (in - p->x);
	return p->x;
		  
}