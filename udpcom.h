#pragma once
#ifndef UDPCOM_H
#define UDPCOM_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <Windows.h>
#include "datatrans.h"
#include "stdio.h"
#include <iostream>
#include "crc.h"
#include "..\Data\EmbededData.h"


#define PRO_START1_POS		0
#define PRO_START2_POS		1
#define PRO_LEN_H_POS		2
#define PRO_LEN_L_POS		3
#define PRO_CMD_POS			4
#define PRO_DATA_POS		5
#define PRO_PRO_LEN			7

#define CMD_READ_BASE (0x01)
#define CMD_READ_POS (CMD_READ_BASE+2)
#define CMD_READ_VOL (CMD_READ_BASE+4)
#define CMD_READ_VEL 	 	(CMD_READ_BASE +5)
#define CMD_READ_TEMP 	 	(CMD_READ_BASE +10)
#define CMD_READ_EFFORT 	(CMD_READ_BASE +8)


#define WRITE_BASE 	 		(0X10)
#define CMD_WRITE_PVE 	 	(WRITE_BASE +0)
#define CMD_WRITE_VOL (CMD_WRITE_BASE+10)

#define ARM_BASE 1
#define ARM_SHOULDER 2
#define ARM_EBLOW 3
#define ARM_WRIST_1 4
#define ARM_WRIST_2 5
#define ARM_WRIST_3 6


typedef struct _udp UDP;
typedef struct _pve PVE;

struct _pve {
    float pos;
    float vel;
    float eft;
};

struct _udp {
    SOCKET* Socket_Joint;
    PVE pve;
    void (*UdpUserCmd)(PVE pve ,unsigned char cmd,char joint_num);
    void (*UdpUserRecv)(EMBEDED_DATA* p);
};





unsigned char UdpModuleRegister(UDP **p);

#endif // !UDPCOM_H

