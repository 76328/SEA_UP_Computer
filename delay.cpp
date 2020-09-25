#include "delay.h"
#include "Windows.h"

static DELAY _delay;

static void _DelayMs(double dMilliseconds)
{
	__int64 nFreq = 0; //频率
	__int64 nStart = 0; //起始计数
	if (QueryPerformanceCounter((LARGE_INTEGER*)&nStart)
		&& QueryPerformanceFrequency((LARGE_INTEGER*)&nFreq)
		&& nFreq > 0
		)
	{
		__int64 nEnd = 0; //终止计数
		double k = 1000.0 / (double)nFreq; //将计数转换为毫秒
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
		{//乘以1000，把秒化为毫秒
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