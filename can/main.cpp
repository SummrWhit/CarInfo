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


/*
float canctrlnode::v_speed = 0.0;
float canctrlnode::acc = 0.0;
float canctrlnode::steering = 0.0;
*/
void* thread_rev(void* argr);
void* thread_sed(void* args);
void lis_sed();

int main(int argc, char **argv)
{
        lis_sed();
}

void* thread_rev(void* argr)
{
        //      int sockrev=(int)(* ((int*) argr));

        char interupt='a';
        canctlnd.sendSingal();
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

void lis_sed()
{
        pthread_t write_id;
        pthread_t send_id;
        pthread_create(&write_id, NULL, thread_rev, NULL);
        pthread_create(&send_id, NULL, thread_sed, NULL);
        pthread_join(send_id, NULL);
        pthread_join(write_id, NULL);
}

