#include <pthread.h>
//#include <ros/ros.h>
#include <ctype.h>
#include <errno.h>
#include <libgen.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <iostream>
#include <conio.h>
//#include <pthread.h>
#include <net/if.h>
#include <sys/epoll.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <string.h>
#include <time.h>
#include <vector>
#include "can.h"
#include "canctrl.h"

canctrlnode canctlnd;

short int sign;

/*
float canctrlnode::v_speed = 0.0;
float canctrlnode::acc = 0.0;
float canctrlnode::steering = 0.0;
*/

void sequence();
void lis_sed();
void send();
int steeringtest();
int socket_up();
void* thread_rev(void* argr);
void* thread_sed(void* args);
int candump(const struct can_frame &frame_candump);

int main(int argc, char **argv)
{
        lis_sed();
}

int socket_up()
{
        struct sockaddr_can addr;
        struct ifreq ifr;
        int sockup=socket(AF_CAN, SOCK_RAW, CAN_RAW);
        if(sockup<0)
        {
                perror("socket create failed\n");
                return 0;
        }
        else
        {
                std::cout<<"socket create success"<<std::endl;
        }
        strcpy(ifr.ifr_name, "can0");
        if(ioctl(sockup, SIOCGIFINDEX, &ifr) < 0)
        {
                perror("ioctl failed\n");
                return 0;
        }
        else
        {
                std::cout<<"ioctl success"<<std::endl;
        }
        std::cout<<"ifr_name:"<<ifr.ifr_name<<std::endl;
        std::cout<<"can_ifindex:"<<ifr.ifr_ifindex<<std::endl;
        addr.can_family = AF_CAN;
        addr.can_ifindex = ifr.ifr_ifindex;
        if(bind(sockup, (struct sockaddr *)&addr, sizeof(addr)) < 0)
        {
                perror("bind failed\n");
                return 0;
        }
        else
        {
                std::cout<<"bind success"<<std::endl;
        }
        return sockup;
}

/*void lis_sed()
{
        pthread_t write_id;
        pthread_t send_id;
        pthread_create(&write_id, NULL, thread_rev, NULL);
        pthread_create(&send_id, NULL, thread_sed, NULL);
        pthread_join(send_id, NULL);
        pthread_join(write_id, NULL);
}*/

void* thread_rev(void* argr)
{
        //      int sockrev=(int)(* ((int*) argr));
        
        char interupt='a';
        struct can_frame frame_rev;
        int sockrev = socket_up();
        std::vector<int> info;
        while(true)
        {
                int rbytes = read(sockrev, &frame_rev, sizeof(frame_rev));
                candump(frame_rev);
                canctlnd.getCanInfo(info);
                std::cout<<"info="<<info[0]<<std::endl;
                if(rbytes < 0)
                {
                        perror("can read failed");
                }
                else
                {
                        std::cout<<"read bytes:"<<rbytes<<std::endl;
                        printf("ID=0x%x DLC=%d data[0]=0x%x data[1]=0x%x data[2]=0x%x data[3]=0x%x data[4]=0x%x data[5]=0x%x data[6]=0x%x data[7]=0x%x\n", frame_rev.can_id, frame_rev.can_dlc, frame_rev.data[0], frame_rev.data[1], frame_rev.data[2], frame_rev.data[3], frame_rev.data[4], frame_rev.data[5], frame_rev.data[6], frame_rev.data[7]);
                }
                if(kbhit())
                {
                        interupt=getch();
                        if(interupt=='x')
                        {
                                close(sockrev);
                                pthread_exit(0);
                        }
                }
        }       
}

int candump(const struct can_frame &frame_candump)
{
        short int i;
        int id=frame_candump.can_id;
        int dlc=frame_candump.can_dlc;
        int data[8];
        for(i=0; i<=7; i++)
                data[i]= frame_candump.data[i];
        printf("CANDUMP ID=0x%x DLC=%d data[0]=0x%x data[1]=0x%x data[2]=0x%x data[3]=0x%x data[4]=0x%x data[5]=0x%x data[6]=0x%x data[7]=0x%x\n", id, dlc, data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]);
        if(id == 0x6B)
        {
                canctlnd.setSpeed((data[6]*256+data[5])*0.01);
                //canctrlnode::setSpeed()
                canctlnd.setAcc((data[2]*256+data[1])*0.03125-16);
        }
        if(id==0x65)
        {
                sign=data[3]>>5;
                if(sign)
                {
                        canctlnd.setSteering(((data[3]-32)*256+data[2])*0.1);
                }
                else
                {
                        canctlnd.setSteering((data[3]*256+data[2])*(-0.1));
                }
        }
        //std::cout<<"vehicle speed:"<<canctrlnode::v_speed<<"vehicle accleration"<<canctrlnode::acc<<"vehicle steering"<<canctrlnode::steering<<std::endl;
        return dlc;//vec[0]=vehicle speed,vec[1]=vehicle accleration,vec[2]=vehicle steering
}

void lis_sed()
{
        pthread_t write_id;
        pthread_t send_id;
        pthread_create(&write_id, NULL, thread_rev, NULL);
        pthread_create(&send_id, NULL, thread_sed, NULL);
        pthread_join(send_id, NULL);
        pthread_join(write_id, NULL);
}


void* thread_sed(void* args)
{
        //      int socksed = (int)(* ((int*) args));
        int choose=1;
        //std::cin>>choose; 
        switch(choose)
        {
                case 1:
                        steeringtest();
                        break;
                default:
                        break;
        }
        pthread_exit(0);
}

int steeringtest()
{
        int sock_st = socket_up();
        char interupt='a';
        int row=0;
        struct can_frame frame_sed[5];
        int table[45][2] = {0,0,20,0,0,0,50,0,0,0,100,0,0,0,200,0,0,0,244,1,0,0,132,3,0,0,8,7,0,0,140,10,0,0,16,14,0,0,148,17,0,0,80,20,0,0,20,128,0,0,50,128,0,0,100,128,0,0,200,128,0,0,244,33024>>8,0,0,132,33536>>8,0,0,8,135,0,0,140,138,0,0,16,142,0,0,148,145,0,0,80,148,0,0};   
        frame_sed[0].can_id=0x60;
        frame_sed[0].can_dlc=8;
        frame_sed[1].can_id=0x66;
        frame_sed[1].can_dlc=8;
        frame_sed[2].can_id=0x64;
        frame_sed[2].can_dlc=8;
        frame_sed[1].data[1]=0x1<<7;
        frame_sed[1].data[2]=0x8<<4;
        int wbytes=write(sock_st, &frame_sed[1], sizeof(frame_sed[1]));
        sleep(5);
        if(wbytes != sizeof(frame_sed[1]))
        {
                perror("can send gear enable command failed");
                return 0;
        }
        frame_sed[0].data[1]=0x1<<7;
        frame_sed[0].data[2]=220;
        frame_sed[0].data[3]=4;
        wbytes=write(sock_st, &frame_sed[0], sizeof(frame_sed[0]));
        usleep(10000);
        if(wbytes != sizeof(frame_sed[0]))
        {
                perror("can send brake command failed");
                return 0;
        }
        frame_sed[1].data[2]=0x5<<4;
        wbytes=write(sock_st, &frame_sed[1], sizeof(frame_sed[1]));
        sleep(1);
        if(wbytes != sizeof(frame_sed[1]))
        {
                perror("can send gear command failed");
                return 0;
        }
        while(row<45)
        {
                frame_sed[2].data[3]=0x1<<7;
                frame_sed[2].data[1]=table[row][0];
                frame_sed[2].data[2]=table[row][1];
                wbytes=write(sock_st, &frame_sed[2], sizeof(frame_sed[2]));
                sleep(10);
                if(wbytes != sizeof(frame_sed[1]))
                {
                        perror("can send steering command failed");
                        return 0;
                }
                row++;
                if(kbhit())
                {
                        interupt=getch();
                        if(interupt=='x')
                        {
                                close(sock_st);
                                pthread_exit(0);
                        }
                }
        }
        close(sock_st);
        return 1;
}
