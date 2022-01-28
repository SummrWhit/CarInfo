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
#include "can.h"
#include "canctrl.h"

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

std::vector<int> canctrlnode::candump(const struct can_frame &frame_candump)
{
	std::vector<int> vec;
	short int i;
	int id=frame_candump.can_id;
	int dlc=frame_candump.can_dlc;
	int data[8];
	for(i=0; i<=7; i++)
		data[i]= frame_candump.data[i];
	printf("CANDUMP ID=0x%x DLC=%d data[0]=0x%x data[1]=0x%x data[2]=0x%x data[3]=0x%x data[4]=0x%x data[5]=0x%x data[6]=0x%x data[7]=0x%x\n", id, dlc, data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]);
	if(id == 0x6B)
	{
		v_speed=(data[6]*256+data[5])*0.01;
		acc=(data[2]*256+data[1])*0.03125-16;
	}
	if(id==0x65)
	{
		sign=data[3]>>5;
		if(sign)
		{
			steering=((data[3]-32)*256+data[2])*0.1;
		}
		else
		{
			steering=(data[3]*256+data[2])*(-0.1);
		}
	}
        std::cout<<"vehicle speed:"<<v_speed<<"vehicle accleration"<<acc<<"vehicle steering"<<steering<<std::endl;
	vec.push_back(v_speed);
	vec.push_back(acc);
	vec.push_back(steering);
	return vec;//vec[0]=vehicle speed,vec[1]=vehicle accleration,vec[2]=vehicle steering
}


/* void* send()
{
	int ss = socket_up();
	pthread_t send_id;
	pthread_create(&send_id, NULL, thread_sed, &ss);
	pthread_join(send_id, NULL);
}

void* thread_sed(void* args)
{
	int socksed = (int)(* ((int*) args));
	while(true)
	{
		sequence();
		int wbytes = write(socksed, &frame_sed[0], sizeof(frame_sed[0]));
		if(wbytes != sizeof(frame_sed[0]))
		{
			perror("can send failed");
			return 0;
		}
		else
		{
			std::cout<<"send bytes:"<<wbytes<<std::endl;
		}
		if(kbhit())
		{
			interupt=getch();
			if(iterupt=="x")
			{
				pthread_exit(0);
			}
		}
	}
}

void sequence()
{
	frame_sed[0].can_id=0x1A;
	frame_sed[0].can_dlc=8;
	frame_sed[0].data[0]=100;
}*/
