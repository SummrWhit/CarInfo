#include <iostream>
#include "../canctrl.h"
#include <vector>

using namespace std;
int main(int argc, char const *argv[])
{
	std::vector<int> info;
	canctrlnode can;
	can.setAcc(1.0);
	canctrlnode::getCanInfo(info);
	cout << info[0];
	/* code */
	return 0;
}