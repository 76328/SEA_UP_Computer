#include "datatrans.h"

void FLOAT_TO_U8(float val,unsigned char *data)
{
	union 
	{
		float x;
		unsigned char buf[4];
	}temp;
	temp.x = val;
	*(data + 0) = temp.buf[0];
	*(data + 1) = temp.buf[1];
	*(data + 2) = temp.buf[2];
	*(data + 3) = temp.buf[3];

}

float U8_TO_FLOAT(char* data)
{
	union 
	{
		float x;
	    char buf[4];
	}temp;
	temp.buf[0] = *(data + 0);
	temp.buf[1] = *(data + 1);
	temp.buf[2] = *(data + 2);
	temp.buf[3] = *(data + 3);

	return temp.x;
}