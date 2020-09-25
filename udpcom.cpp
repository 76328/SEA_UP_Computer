#pragma comment(lib, "ws2_32.lib") 
#include "udpcom.h"
#include "../Data/EmbededData.h"
#include "../Tinyxml/xmlprotocal.h"
#include <string>

static UDP udp;
SOCKET sockClient = socket(AF_INET, SOCK_DGRAM, 0); //only to creat one socket
SOCKADDR_IN  addrClient1,addrClient2,addrClient3,addrClient4,addrClient5,addrClient6;

static void _UdpUserCmd(PVE pve,unsigned char cmd,char joint_num)
{
	unsigned int crc;
	unsigned char *buf=(unsigned char*)malloc(19);
	buf[0] = 0xAA;
	buf[1] = 0x55;
	buf[2] = 0;
	buf[3] = 19;
	buf[4] = cmd;
	FLOAT_TO_U8(pve.pos,&buf[5]);
	FLOAT_TO_U8(pve.vel, &buf[9]);
	FLOAT_TO_U8(pve.eft, &buf[13]);
	crc=PCCRC_Cal((char*)buf,17);
	buf[17] = (crc >> 8) & 0xff;
	buf[18] = crc & 0xff;
	switch (joint_num)
	{
		case 1:
		{
			sendto(sockClient, (char*)buf, 19, 0, (SOCKADDR*)&addrClient1, sizeof(SOCKADDR));
			break;
		}
		case 2:
		{
			sendto(sockClient, (char*)buf, 19, 0, (SOCKADDR*)&addrClient2, sizeof(SOCKADDR));
			break;
		}
		case 3:
		{
			sendto(sockClient, (char*)buf, 19, 0, (SOCKADDR*)&addrClient3, sizeof(SOCKADDR));
			break;
		}
		case 4:
		{
			sendto(sockClient, (char*)buf, 19, 0, (SOCKADDR*)&addrClient4, sizeof(SOCKADDR));
			break;
		}
		case 5:
		{
			sendto(sockClient, (char*)buf, 19, 0, (SOCKADDR*)&addrClient5, sizeof(SOCKADDR));
			break;
		}
		case 6:
		{
			sendto(sockClient, (char*)buf, 19, 0, (SOCKADDR*)&addrClient6, sizeof(SOCKADDR));
			break;
		}
		default:
		{
			break;
		}
	}
	free(buf);
}



static void _UdpUserRecv(EMBEDED_DATA *p)
{
	char buf[19];
	float smp=1.0;
	int len = sizeof(SOCKADDR);
	recvfrom(sockClient, buf,19,0,(SOCKADDR*)&addrClient1,&len);
	smp=U8_TO_FLOAT(&buf[PRO_DATA_POS]);
	p->cmd = buf[PRO_CMD_POS];
	//std::cout << smp << std::endl;
	switch (buf[PRO_CMD_POS])
	{

		case CMD_READ_POS:
		{
			p->pos = smp;
		}

		default:
		break;
	}
}


unsigned char UdpModuleRegister(UDP **p)
{
	u_short port;
	
	std::string ip_1;
	
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		printf("WSAStartup failed with error: %d\n", err);
		return 1;
	}
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		printf("Could not find a usable version of Winsock.dll\n");
		WSACleanup();
		return 1;
	}
	else
	{
		printf("The Winsock 2.2 dll was found okay\n");
	}
	sockClient = socket(AF_INET, SOCK_DGRAM, 0);

	memset(&addrClient1, 0, sizeof(addrClient1));
	memset(&addrClient2, 0, sizeof(addrClient2));
	memset(&addrClient3, 0, sizeof(addrClient3));
	memset(&addrClient4, 0, sizeof(addrClient4));
	memset(&addrClient5, 0, sizeof(addrClient5));
	memset(&addrClient6, 0, sizeof(addrClient6));
	std::cout << "Client Process Start:" << std::endl;

	

	
	inet_pton(AF_INET, "192.168.1.193", &(addrClient1.sin_addr.S_un.S_addr));			   //2
	addrClient1.sin_family = AF_INET;
	inet_pton(AF_INET, "192.168.1.86", &(addrClient2.sin_addr.S_un.S_addr));			   //3
	addrClient2.sin_family = AF_INET;
	inet_pton(AF_INET, "192.168.1.111", &(addrClient3.sin_addr.S_un.S_addr));			   //1
	addrClient3.sin_family = AF_INET;
	inet_pton(AF_INET, "192.168.1.84", &(addrClient4.sin_addr.S_un.S_addr));
	addrClient4.sin_family = AF_INET;
	inet_pton(AF_INET, "192.168.1.122", &(addrClient5.sin_addr.S_un.S_addr));
	addrClient5.sin_family = AF_INET;
	inet_pton(AF_INET, "192.168.1.89", &(addrClient6.sin_addr.S_un.S_addr));
	addrClient6.sin_family = AF_INET;

	std::cout << "Enter port" << std::endl;
	std::cin >> port;

	addrClient1.sin_port = htons(port);
	addrClient2.sin_port = htons(port);
	addrClient3.sin_port = htons(port);
	addrClient4.sin_port = htons(port);
	addrClient5.sin_port = htons(port);
	addrClient6.sin_port = htons(port);

	udp.UdpUserCmd = _UdpUserCmd;
	udp.UdpUserRecv = _UdpUserRecv;
	udp.Socket_Joint = &sockClient;
	*p = &udp;
	return 0;
}