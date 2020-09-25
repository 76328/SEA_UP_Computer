#include "Global.h"
#include <fstream>
float  sysidf_u[100000];

PVE idf;

SYSIDF sysidf;

DWORD WINAPI Idf_Read(LPVOID lpParamter)
{
    std::ofstream file2;
    file2.open("SYSIDFOUT.txt");

    while(1)
    {
        gData.udp->UdpUserRecv(gData.ebd_data);  
        if (gData.ebd_data->cmd == CMD_READ_POS)
        {
        // std::cout <<"Position:(rad)"<< gData.ebd_data->pos << std::endl;
        //std::cout << "rec" << endl;
        // pre = now;
        // now = gData.tick->GetTickCountMs();
        file2 << idf.pos << " " << gData.ebd_data->pos << std::endl;
       // pre = now;
       // now = gData.tick->GetTickCountMs();
        }
        //Sleep(1);
    }
   
    return 0;

}

DWORD WINAPI Idf_Send(LPVOID lpParamter)
{
    double  uk = 0; 
    DWORD uki = 0;
    char is_first = 0;
 
    int i = 0;
    float u = 0;
    
    while (i<100000)
    {
         std::cout << "s" << std::endl;
         idf.pos = sysidf_u[i];
         gData.udp->UdpUserCmd(idf, CMD_WRITE_PVE,1);
         gData.udp->UdpUserCmd(idf, CMD_READ_POS,1);
         gData.tick->DelayMs(10);
        // Sleep(50);
         i++;
    }
    return 0;
}



void SysIdfInit(SYSIDF **p)
{
    char change = 1;
    float read_t = 0;
    float t_flag;
    float sysidf_u_aux;
    for (int i = 0; i < 100000; i++)
    {
        sysidf_u[i] = 0;
    }
    std::ifstream file1;
    file1.open("SYSIDF.txt");
    for (int i = 0; i < 100000; i++)
    {
        if (change)
        {
            file1 >> sysidf_u_aux;
            file1 >> t_flag;
            change = 0;
        }
        read_t = read_t + 0.05;
        sysidf_u[i] = sysidf_u_aux;
        //cout << sysidf_u[i] << endl;
        if (read_t > t_flag)
        {
            change = 1;
        }
    }

    sysidf.send = CreateThread(NULL, 0, Idf_Send, NULL, 0, NULL);
    sysidf.rec = CreateThread(NULL, 0, Idf_Read, NULL, 0, NULL);

}