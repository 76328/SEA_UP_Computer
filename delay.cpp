#include "delay.h"
#include "Windows.h"

static DELAY _delay;

static void _DelayMs(double dMilliseconds)
{
	__int64 nFreq = 0; //Ƶ��
	__int64 nStart = 0; //��ʼ����
	if (QueryPerformanceCounter((LARGE_INTEGER*)&nStart)
		&& QueryPerformanceFrequency((LARGE_INTEGER*)&nFreq)
		&& nFreq > 0
		)
	{
		__int64 nEnd = 0; //��ֹ����
		double k = 1000.0 / (double)nFreq; //������ת��Ϊ����
		for (;;)
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&nEnd);
			if (dMilliseconds <= (double)(nEnd - nStart) * k)
			{
				break;
			}
		}
	}
}
static double _GetTickCountA()
{
	__int64 Freq = 0;
	__int64 Count = 0;
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&Freq)
		&& Freq > 0
		&& QueryPerformanceCounter((LARGE_INTEGER*)&Count))
		{//����1000�����뻯Ϊ����
			return (double)Count / (double)Freq * 1000.0;
		}
	return 0.0;
}

bool DelayModuleRegister(DELAY **p)
{
	_delay.DelayMs = _DelayMs;
	_delay.GetTickCountMs = _GetTickCountA;
	*p = &_delay;
	return 0;
}