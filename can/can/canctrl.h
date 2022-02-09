#include <stdio.h>
#include <vector>

short int sign;
static float v_speed, acc, steering;

void sequence();
void listening();
void send();
int socket_up();
void* thread_rev(void* argr);


class canctrlnode
{
private:

public:
    void candump(const struct can_frame &frame_candump);
    static void getCanInfo(std::vector<int> &info);
};
