#ifndef TVSET_H
#define TVSET_H

#include <iostream>
#include <map>
#include <string>

using namespace std;

class CTVSet {
private:
    bool m_isOn;
    int m_currentChannel;
    map<int, string> m_channelNames;

public:
    CTVSet();

    void TurnOn();
    void TurnOff();
    void SelectChannel(int channel);
    void SelectPreviousChannel();
    void SetChannelName(int channel, const string& name);
    string GetChannelName(int channel);
    int GetChannelByName(const string& name);
    void DeleteChannelName(const string& name);
    void Info();
};

#endif
