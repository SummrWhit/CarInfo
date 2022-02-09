#include "can.h"
#include "canctrl.h"
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
#include <pthread.h>
#include <net/if.h>
#include <sys/epoll.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/uio.h>

int main(int argc, char **argv)
{
        //ros::init(argc, argv, "canctrl");
        //ros::NodeHakbhit’ was not declared in this scondle nh;
        listening();
//	send();
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
        //ifr.ifr_ifindex=if_nametoindex(ifr.ifr_name);
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

void listening()
{
        pthread_t write_id;
        int ls = socket_up();
        pthread_create(&write_id, NULL, thread_rev, &ls);
        pthread_join(write_id, NULL);
}

void* thread_rev(void* argr)
{
        canctrlnode canctlnd;
        char interupt='a';
        struct can_frame frame_rev;
        int sockrev=(int)(* ((int*) argr));
        while(true)
        {
                int rbytes = read(sockrev, &frame_rev, sizeof(frame_rev));
                canctlnd.candump(frame_rev);
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
                                pthread_exit(0);
                        }
                }
        }
}
