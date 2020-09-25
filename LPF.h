#pragma once
#ifndef LPF_H
#define LPF_H


typedef struct _lpf LPF;

struct _lpf
{
	float x;
	float a;

};

float LPF_CAL(float in, LPF* p);
extern LPF refacc;


#endif // !SIGNALGEN_H
