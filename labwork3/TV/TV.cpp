#include <iostream>
#include <map>
#include <string>
#include "TVSet.h"
using namespace std;


int main() {
    CTVSet tv;
    tv.TurnOn();
    tv.SelectChannel(5);
    tv.SetChannelName(5, "Discovery");
    std::cout << "Channel 5 name: " << tv.GetChannelName(5) << std::endl;
    std::cout << "Channel 'Discovery' number: " << tv.GetChannelByName("Discovery") << std::endl;
    tv.Info();

    return 0;
}
