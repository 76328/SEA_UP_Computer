#pragma once
#ifndef POLYPLANNER_H
#define POLYPLANNER_H



typedef struct _polytask POLYTASK;

struct _polytask
{

	HANDLE 	poshThread;
	HANDLE 	spdhThread;
	HANDLE 	efthThread;
};






bool polyplan(float* p, float* t, float* v, float* a, int num, float* buf);
bool polyplan_p2p(float start, float target, float t, float* buf_p, float* buf_v,float* buf_a);
void polytask_init(POLYTASK** p);

#endif