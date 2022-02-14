#include <string.h>
#include <stdio.h>
#include <vector>
#include "can.h"

class canctrlnode
{
private:
    float m_speed, m_acc, m_steering;
    short int sign;
public:
    void sendSingal();
    void sequence();
    void send();
    int steeringtest();
    int socket_up();
    int candump(const struct can_frame &frame_candump);
    void setSpeed(float speed) {m_speed = speed;}
    void setSteering(float steering) {m_steering = steering;}
    void setAcc(float acc) {m_acc = acc;}
    void getCanInfo(std::vector<int> &info);
};
