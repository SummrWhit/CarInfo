#include <string.h>
#include <stdio.h>
#include <vector>
#include "can.h"

class canctrlnode
{
private:
	float m_speed, m_acc, m_steering;
public:
	void setSpeed(float);
	void setSteering(float);
	void setAcc(float);
	void getCanInfo(std::vector<int> &info);
};
