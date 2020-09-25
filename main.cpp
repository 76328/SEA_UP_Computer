#include <iostream>
#include <fstream>
#include <math.h>
//#include <windows.h>
#include <string>
#include "Global.h"
#include<TlHelp32.h>
#include<vector>
#include "Filter/LPF.h"
#include "SignalGen/polyplanner.h"

#define POS_MODE 

using namespace std;
ofstream time;
ofstream poly;
float pos;
double now;
double pre;


float samp = 0.05;





float pos_1;
float vel_1;

float GetVel(float in)
{
    float vel;
    vel=(in - pos_1)/0.01;
    pos_1 = in;
    return vel;

}
float GetAcc(float in)
{
    float acc;
    acc = (in - vel_1) / 0.01;
    vel_1 = in;
    return acc;

}


//void SysIdfInit()
//{
//    for (int i=0;i< 100000;i++)
//    {
//        sysidf_u[i] = 0;
//    }
//    ifstream file1;
//    file1.open("SYSIDF.txt");
//    for (int i = 0; i < 100000; i++)
//    {
//        if (change)
//        {
//            file1 >> sysidf_u_aux;
//            file1 >> t_flag;
//            change = 0;
//        }
//         read_t = read_t + 0.05;
//         sysidf_u[i] = sysidf_u_aux;
//         //cout << sysidf_u[i] << endl;
//         if (read_t > t_flag)
//         {
//             change = 1;
//         }
//    }
//
//}




//DWORD WINAPI UdpRead(LPVOID lpParamter)
//{
//    ofstream file2;
//    file2.open("SYSIDFOUT.txt");
//
//    while(1)
//    {
//        gData.udp->UdpUserRecv(gData.ebd_data);  
//        if (gData.ebd_data->cmd == CMD_READ_POS)
//        {
//        // std::cout <<"Position:(rad)"<< gData.ebd_data->pos << std::endl;
//        //std::cout << "rec" << endl;
//        // pre = now;
//        // now = gData.tick->GetTickCountMs();
//        file2 << gu << " " << gData.ebd_data->pos << endl;
//       // pre = now;
//       // now = gData.tick->GetTickCountMs();
//        }
//        //Sleep(1);
//    }
//   
//    return 0;
//
//}

//DWORD WINAPI UdpSend(LPVOID lpParamter)
//{
//    double  uk = 0; 
//    DWORD uki = 0;
//    char is_first = 0;
//    time.open("time.txt");
//    int i = 0;
//    float u = 0;
//    while (i<100000)
//    {
//         gu = sysidf_u[i];
//        // gData.udp->UdpUserCmd(gu, CMD_WRITE_PVE);
//        // gData.udp->UdpUserCmd(gu, CMD_READ_POS);
//         gData.tick->DelayMs(10);
//        // Sleep(50);
//         i++;
//    }
//    return 0;
//}

//DWORD WINAPI KeyTask(LPVOID lpParamter)
//{
//    unsigned char buf2[4];
//    long t=0;
//    char dir = 0;
//    
//    float ddp=0;
//    float p=0;
//    float p_g = 3.14;
//    float w = 0.5;
//    float dp = p_g *w;
//  
//
//      while(1)
//      {
//          //std::cout <<"POS:"<< gData.udp->pve.pos <<"VEL:"<<gData.udp->pve.vel<<"CMP_EFT:"<<gData.udp->pve.eft <<std::endl;
//          gData.udp->pve.pos = p;
//          gData.udp->pve.vel = 1.0*dp;
//          gData.udp->pve.eft = 5.3 * sin(gData.udp->pve.pos)+ 0.1*ddp;
//          gData.udp->UdpUserCmd(gData.udp->pve, CMD_WRITE_PVE);
//        
//          p = p + 0.01*dp;
//          dp = dp + 0.01*ddp;
//          ddp = -p_g*w*w*sin(0.01*w*t);
//
//         while (cin.fail())
//         {
//             cin.clear();
//             cin.ignore();
//             cout << "输入错误，请重新输入" << endl;
//             cin >> pos;
//         }
//          cin.clear();
//          cin.sync();
//          Sleep(10);
//          t++;
//          if (t == 6280000)
//          {
//              t = 0;
//          }
//      }
//      return 0;
//
//}

//DWORD  WINAPI Waitting(LPVOID lpParamter)
//{
//   
//            while (1)
//            {
//
//                    Sleep(100);              
//            }
//        return 0;
//}




int main()
{                                        
    Init();
    //SysIdfInit();
    gData.udp->pve.pos = 0;
    gData.udp->pve.vel = 0;
    gData.udp->UdpUserCmd(gData.udp->pve, CMD_WRITE_PVE,1);
    gData.udp->UdpUserCmd(gData.udp->pve, CMD_WRITE_PVE,2);
   
    while (1)
    {
        Sleep(100);
    }
    return 0;
}
