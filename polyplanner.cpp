#include "../Global.h"
#include "stdio.h"


POLYTASK POLY;

//bool polyplan(float *p, float *t, float *v,float *a,int num,float *buf)
//{
//	int HZ = 100;
//	int PN = t[num - 1] * 100;
//	int A;
//	int K=0;
//	float ts;
//	float tf;
//
//	float dk1;
//	float dk2;
//
//	//float v_t[10];
//	//float a0[10];
//	//float a1[10];
//	//float a2[10];
//	//float a3[10];
//	//float a4[10];
//	//float a5[10];
//
//	float* v_t = (float*)malloc(sizeof(float)* num);
//	float* a0 = (float*)malloc(sizeof(float) * num);
//	float* a1 = (float*)malloc(sizeof(float) * num);
//	float* a2 = (float*)malloc(sizeof(float) * num);
//	float* a3 = (float*)malloc(sizeof(float) * num);
//	float* a4 = (float*)malloc(sizeof(float) * num);
//	float* a5 = (float*)malloc(sizeof(float) * num);
//	
//	if ((v_t == NULL) || (a0 == NULL) || (a1 == NULL) || (a2 == NULL) || (a3 == NULL) || (a4 == NULL) || (a5 == NULL))
//	{
//		return false;
//	}
//
//	for (int i = 0; i < num-1; i++)
//	{
//		if (i == 0)
//		{
//			v_t[i] = v[i];
//		}
//		else
//		{
//			dk1 = (p[i] - p[i - 1]) / (t[i] - t[i - 1]);
//			dk2 = (p[i + 1] - p[i]) / (t[i + 1] - t[i]);
//			if (((dk1 > 0) && (dk2 > 0)) || ((dk1 < 0) && (dk2 < 0)))
//			{
//				v_t[i] = 0.5f * (dk1 + dk2);
//			}
//			else
//			{
//				v_t[i] = 0.0f;
//			}
//		}
//	}
//	v_t[num-1] = v[num-1];
//	for (int i = 0; i < num-1; i++)
//	{
//		tf = t[i + 1] - t[i];
//		a0[i] = p[i];
//		a1[i] = v_t[i];
//		a2[i] = a[i] / 2;
//		a3[i] = (20 * p[i + 1] - 20 * p[i] - (8 * v_t[i + 1] + 12 * v_t[i]) * tf - (3 * a[i] - a[i + 1]) * pow(tf, 2)) / (2 * pow(tf, 3));
//		a4[i] = (30 * p[i] - 30 * p[i + 1] + (14 * v_t[i + 1] + 16 * v_t[i]) * tf + (3 * a[i] - 2 * a[i + 1]) * pow(tf, 2)) / (2 * pow(tf, 4));
//		a5[i] = (12 * p[i + 1] - 12 * p[i] - (6 * v_t[i + 1] + 6 * v_t[i]) * tf - (a[i] - a[i + 1]) * pow(tf, 2)) / (2 * pow(tf, 5));
//	}
//
//	for (int i = 0; i < num-1; i++)
//	{
//		A = (t[i + 1] - t[i]) * 100;
//		for (int j = 0; j<A;j++)
//		{
//			ts = (float)(j / 100.0);
//			buf[K] = a0[i] + a1[i] * ts + a2[i] * pow(ts, 2) + a3[i] * pow(ts, 3) + a4[i] * pow(ts, 4) + a5[i] * pow(ts, 5);
//			K++;
//		}
//	}
//	
//	buf[K] = p[num-1];
//	free(v_t);
//	free(a0);
//	free(a1);
//	free(a2);
//	free(a3);
//	free(a4);
//	free(a5);
//
//	return true;
//	
//}

bool polyplan_p2p(float start, float target, float t,float* buf_p,float *buf_v,float *buf_a)
{
	float v_t, a0, a1, a2, a3, a4,a5;
	a0 = start;
	a1 = 0.0;
	a2 = 0.0;
	a3 = (20 * target - 20 * start)/ (2 * pow(t, 3));
	a4 = (30 * start - 30 * target) / (2 * pow(t, 4));
	a5 = (12 * target - 12 * start) / (2 * pow(t, 5));
	int T = t * 100;
	
	float ts = 0;
	for (int i=0;i<T+1;i++)
	{
		buf_p[i]= a0 + a1 * ts + a2 * pow(ts, 2) + a3 * pow(ts, 3) + a4 * pow(ts, 4) + a5 * pow(ts, 5);
		buf_v[i] = a1 + 2 * a2 * ts + 3 * a3 * pow(ts, 2) + 4 * a4 * pow(ts, 3) + 5 * a5 * pow(ts, 4);
		buf_a[i] = 2 * a2 + 6 * a3 * ts + 12 * a4 * pow(ts, 2) + 20 * a5 * pow(ts, 3);
		ts = ts + 0.01;
	}
	buf_p[T] = target;
	buf_v[T] = 0.0;
	buf_a[T] = 0.0;
	return true;

}

DWORD WINAPI PloyP2PTask(LPVOID lpParamter)
{
	//float p1[6] = {0.338174,-0.363357,-2.6933,-2.33047,-3.14009,1.90897};
	//float p2[6] = {0.338174,-0.678719,-2.18328,-1.50509,-3.14009,1.90897};
	//float p3[6] = {0.186591,-0.081176,-1.80461,-1.72373,-3.14003,1.75739};
	//float p4[6] = {0.186591,0.216072,-2.16003,-2.3764,-3.14003,1.75739};
	
	float p1[6] = {0.338174,-0.632983,-2.48193,-1.84948,-3.14009,1.90897};	  // A
	float p2[6] = {0.338174,-0.678719,-2.18328,-1.50509,-3.14009,1.90897};	  // B
	float p3[6] = {0.186591,-0.081176,-1.80461,-1.72373,-3.14003,1.75739};	//C
	float p4[6] = {0.186591,0.0203453,-2.03056,-2.0512,-3.14003,1.75739};	 //D

	float p5[6] = {-0.411455,-1.23836,-1.35174,1.45941,- 1.98225,-0.00182474}; //É¨Âëµã£¨200£¬-300£¬400£¬1.57£©
	float p6[6] = {-0.411455,-1.23836,-1.35174,1.45941,-1.98225,3.14};
	float p7[6] = { -0.411455,-1.23836,-1.35174,1.45941,-1.98225,0};
	
	
	int sel = 1;
	int is_first = 1;

	float start1 = 0;
	float start2 = 0;
	float start3 = 0;
	float start4 = 0;
	float start5 = 0;
	float start6 = 0;

	float target1 = 0;
	float target2 = 0;
	float target3 = 0;
	float target4 = 0;
	float target5 = 0;
	float target6 = 0;
	float t;
	char dir = 0;










	while (1)
	{
		float* bufp1;
		float* bufv1;
		float* bufa1;

		float* bufp2;
		float* bufv2;
		float* bufa2;

		float* bufp3;
		float* bufv3;
		float* bufa3;

		float* bufp4;
		float* bufv4;
		float* bufa4;

		float* bufp5;
		float* bufv5;
		float* bufa5;

		float* bufp6;
		float* bufv6;
		float* bufa6;

		//std::cout << "ENTER_TARGET_POS_1" << std::endl;
		//std::cin >> target1;
		//std::cout << "ENTER_TARGET_POS_2" << std::endl;
		//std::cin >> target2;
		std::cout << "Enter_target_pos" << std::endl;
		//scanf_s("%f %f %f %f %f %f", &target1, &target2, &target3, &target4, &target5, &target6);
		//std::cin >> sel;
		if (is_first)
		{
			t = 8;
			is_first = 0;
		}
		else
		{
			if (sel == 5)
			{
				t =5;
			}
			else if (sel == 1)
			{
				t = 5;
			}
			else if (sel == 6)
			{
				t = 3;
			}
			else if (sel == 7)
			{
				t = 3;
			}
			else
			{
				t = 2;
			}

		}
		if (sel == 1)
		{
			target1 = p1[0];
			target2 = p1[1];
			target3= p1[2];
			target4 = p1[3];
			target5 = p1[4];
			target6 = p1[5];
		};
		if (sel == 2)
		{
			target1 = p2[0];
			target2 = p2[1];
			target3 = p2[2];
			target4 = p2[3];
			target5 = p2[4];
			target6 = p2[5];

		};
		if (sel == 3)
		{
			target1 = p3[0];
			target2 = p3[1];
			target3 = p3[2];
			target4 = p3[3];
			target5 = p3[4];
			target6 = p3[5];

		};
		if (sel == 4)
		{
			target1 = p4[0];
			target2 = p4[1];
			target3 = p4[2];
			target4 = p4[3];
			target5 = p4[4];
			target6 = p4[5];
		};
		if (sel == 5)
		{
			target1 = p5[0];
			target2 = p5[1];
			target3 = p5[2];
			target4 = p5[3];
			target5 = p5[4];
			target6 = p5[5];

		}
		if (sel == 6)
		{
			target1 = p6[0];
			target2 = p6[1];
			target3 = p6[2];
			target4 = p6[3];
			target5 = p6[4];
			target6 = p6[5];

		}
		if (sel == 7)
		{
			target1 = p7[0];
			target2 = p7[1];
			target3 = p7[2];
			target4 = p7[3];
			target5 = p7[4];
			target6 = p7[5];
		}
		std::cout << "ENTER_POS_TIME" << std::endl;
		//std::cin >> t;

		bufp1 = (float*)malloc((int)(sizeof(float) * t * 100) + sizeof(float));
		bufv1 = (float*)malloc((int)(sizeof(float) * t * 100) + sizeof(float));
		bufa1 = (float*)malloc((int)(sizeof(float) * t * 100) + sizeof(float));

		bufp2 = (float*)malloc((int)(sizeof(float) * t * 100) + sizeof(float));
		bufv2 = (float*)malloc((int)(sizeof(float) * t * 100) + sizeof(float));
		bufa2= (float*)malloc((int)(sizeof(float) * t * 100) + sizeof(float));

		bufp3 = (float*)malloc((int)(sizeof(float) * t * 100) + sizeof(float));
		bufv3 = (float*)malloc((int)(sizeof(float) * t * 100) + sizeof(float));
		bufa3 = (float*)malloc((int)(sizeof(float) * t * 100) + sizeof(float));

		bufp4 = (float*)malloc((int)(sizeof(float) * t * 100) + sizeof(float));
		bufv4 = (float*)malloc((int)(sizeof(float) * t * 100) + sizeof(float));
		bufa4 = (float*)malloc((int)(sizeof(float) * t * 100) + sizeof(float));

		bufp5 = (float*)malloc((int)(sizeof(float) * t * 100) + sizeof(float));
		bufv5 = (float*)malloc((int)(sizeof(float) * t * 100) + sizeof(float));
		bufa5 = (float*)malloc((int)(sizeof(float) * t * 100) + sizeof(float));

		bufp6 = (float*)malloc((int)(sizeof(float) * t * 100) + sizeof(float));
		bufv6 = (float*)malloc((int)(sizeof(float) * t * 100) + sizeof(float));
		bufa6 = (float*)malloc((int)(sizeof(float) * t * 100) + sizeof(float));

		polyplan_p2p(start1, target1, t, bufp1, bufv1, bufa1);
		polyplan_p2p(start2, target2, t, bufp2, bufv2, bufa2);
		polyplan_p2p(start3, target3, t, bufp3, bufv3, bufa3);
		polyplan_p2p(start4, target4, t, bufp4, bufv4, bufa4);
		polyplan_p2p(start5, target5, t, bufp5, bufv5, bufa5);
		polyplan_p2p(start6, target6, t, bufp6, bufv6, bufa6);
		for (int i = 0; i < (int)(t * 100) + 1; i++)
		{
			//std::cout << "POS:" << bufp2[i] << "VEL:" << bufv1[i] << "ACC:" << bufa1[i] << std::endl;
			//poly << bufp[i] << " " << 0.0 << endl;
			//std::cout << "POS" << std::endl;
			gData.udp->pve.pos = bufp1[i];
			gData.udp->pve.vel = 0.8 * bufv1[i];
			//gData.udp->pve.eft = 5.5 * sin(gData.udp->pve.pos) + 0.25 * bufa[i];
			gData.udp->pve.eft = bufp2[i];	 //0.25bufa
			gData.udp->UdpUserCmd(gData.udp->pve, CMD_WRITE_PVE,ARM_BASE);
			
			gData.udp->pve.pos = bufp2[i];
			gData.udp->pve.vel = 1.6 * bufv2[i];
			gData.udp->pve.eft = bufp3[i];
			gData.udp->UdpUserCmd(gData.udp->pve, CMD_WRITE_PVE, ARM_SHOULDER);

			gData.udp->pve.pos = bufp3[i];
			gData.udp->pve.vel = 1.6 * bufv3[i];
			gData.udp->pve.eft = bufp2[i];
			gData.udp->UdpUserCmd(gData.udp->pve, CMD_WRITE_PVE, ARM_EBLOW);

			gData.udp->pve.pos = bufp4[i];
			gData.udp->pve.vel = 0;
			gData.udp->pve.eft = 0;
			gData.udp->UdpUserCmd(gData.udp->pve, CMD_WRITE_PVE, ARM_WRIST_1);

			gData.udp->pve.pos = bufp5[i];
			gData.udp->pve.vel = 0;
			gData.udp->pve.eft = 0;
			gData.udp->UdpUserCmd(gData.udp->pve, CMD_WRITE_PVE, ARM_WRIST_2);

			gData.udp->pve.pos = bufp6[i];
			gData.udp->pve.vel = 0;
			gData.udp->pve.eft = 0;
			gData.udp->UdpUserCmd(gData.udp->pve, CMD_WRITE_PVE, ARM_WRIST_3);
			//Sleep(10);
			gData.tick->DelayMs(10);
		}
		start1 = target1;
		start2 = target2;
		start3 = target3;
		start4 = target4;
		start5 = target5;
		start6 = target6;
		
		free(bufp1);
		free(bufv1);
		free(bufa1);

		free(bufp2);
		free(bufv2);
		free(bufa2);

		free(bufp3);
		free(bufv3);
		free(bufa3);

		free(bufp4);
		free(bufv4);
		free(bufa4);

		free(bufp5);
		free(bufv5);
		free(bufa5);

		free(bufp6);
		free(bufv6);
		free(bufa6);

		sel++;
		if (sel == 8)
		{
			sel = 1;
		}
	}
	return 0;
}

DWORD WINAPI PloyV2VTask(LPVOID lpParamter)
{
	float start = 0;
	float target = 0;
	float t;
	

	while (1)
	{
		float* bufp;
		float* bufv;
		float* bufa;

		std::cout << "ENTER_TARGET_VEL" << std::endl;
		std::cin >> target;
		std::cout << "ENTER_VEL_TIME" << std::endl;
		std::cin >> t;

		bufp = (float*)malloc((int)(sizeof(float) * t * 100) + sizeof(float));
		bufv = (float*)malloc((int)(sizeof(float) * t * 100) + sizeof(float));
		bufa = (float*)malloc((int)(sizeof(float) * t * 100) + sizeof(float));

		polyplan_p2p(start, target, t, bufp, bufv, bufa);
		for (int i = 0; i < (int)(t * 100) + 1; i++)
		{
			//std::cout << "POS:" << bufp[i] << "VEL:" << bufv[i] << "ACC:" << bufa[i] <<std::endl;
			std::cout << "VEL" << std::endl;
			//poly << bufp[i] << " " << 0.0 << endl;
		   // gData.udp->pve.pos = bufp[i];
			gData.udp->pve.vel = bufp[i];
			//gData.udp->pve.eft = 5.5 * sin(gData.udp->pve.pos) + 0.25 * bufa[i];
			gData.udp->UdpUserCmd(gData.udp->pve, CMD_WRITE_PVE,1);
			Sleep(10);
		}
		start = target;
		free(bufp);
		free(bufv);
		free(bufa);
	}
	return 0;
}

DWORD WINAPI PloyE2ETask(LPVOID lpParamter)
{
	float start = 0;
	float target = 0;
	float t;
	char dir = 0;
	float it = 0;
	while (1)
	{
		float* bufp;
		float* bufv;
		float* bufa;

		std::cout << "ENTER_TARGET_EFT" << std::endl;
		std::cin >> target;
		std::cout << "ENTER_EFT_TIME" << std::endl;
		std::cin>>t;



		bufp = (float*)malloc((int)(sizeof(float) * t * 100) + sizeof(float));
		bufv = (float*)malloc((int)(sizeof(float) * t * 100) + sizeof(float));
		bufa = (float*)malloc((int)(sizeof(float) * t * 100) + sizeof(float));

		polyplan_p2p(start, target, t, bufp, bufv, bufa);
		for (int i = 0; i < (int)(t * 100 + 1); i++)
		{
			std::cout << "EFT" << std::endl;
			//std::cout << "POS:" << bufp[i] << "VEL:" << bufv[i] << "ACC:" << bufa[i] << std::endl;
			//poly << bufp[i] << " " << 0.0 << endl;
			gData.udp->pve.eft = bufp[i];
			gData.udp->pve.vel = 0.0 * bufv[i] + 0.0 * bufa[i];
			gData.udp->pve.pos = 0;
			gData.udp->UdpUserCmd(gData.udp->pve, CMD_WRITE_PVE,1);
			gData.tick->DelayMs(10);
			//Sleep(10);
		}

		start = target;
		free(bufp);
		free(bufv);
		free(bufa);
	}
}



void polytask_init(POLYTASK **p)
{
	POLY.poshThread= CreateThread(NULL, 0, PloyP2PTask, NULL, 0, NULL);
	//POLY.spdhThread = CreateThread(NULL, 0, PloyV2VTask, NULL, 0, NULL);
	//POLY.efthThread = CreateThread(NULL, 0, PloyE2ETask, NULL, 0, NULL);
	*p = &POLY;

}