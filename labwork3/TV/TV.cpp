#include <iostream>
#include <map>
#include <string>
#include "TVSet.h"

int main()
{
    CTVSet tv;
    tv.TurnOn();
    tv.SelectChannel(5);
    tv.SetChannelName(5, "Discovery");
    std::cout << "Channel 5 name: " << tv.GetChannelName(5) << "\n";
    std::cout << "Channel 'Discovery' number: " << tv.GetChannelByName("Discovery") << "\n";
    tv.Info();

    return 0;
}
