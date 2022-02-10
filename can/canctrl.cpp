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

void canctrlnode::setSpeed(float speed) {
	m_speed = speed;
}
void canctrlnode::setSteering(float steering) {
	m_steering = steering;
}
void canctrlnode::setAcc(float acc) {
	m_acc = acc;
}

void canctrlnode::getCanInfo(std::vector<int> &info)
{
	info.push_back(m_speed);
	info.push_back(m_steering);
	info.push_back(m_acc);
}

