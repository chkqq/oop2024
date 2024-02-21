#include "TVSet.h"

CTVSet::CTVSet() : m_isOn(false), m_currentChannel(0) {}

void CTVSet::TurnOn()
{
    m_isOn = true;
    if (m_currentChannel == 0)
    {
        m_currentChannel = 1;
    }
}

void CTVSet::TurnOff()
{
    m_isOn = false;
}

void CTVSet::SelectChannel(int channel)
{
    if (m_isOn && channel >= 1 && channel <= 99)
    {
        m_currentChannel = channel;
    }
}

void CTVSet::SelectPreviousChannel()
{
    if (m_isOn && m_currentChannel > 1)
    {
        m_currentChannel--;
    }
}

void CTVSet::SetChannelName(int channel, const std::string& name)
{
    if (m_isOn && channel >= 1 && channel <= 99 && !name.empty())
    {
        m_channelNames[channel] = name;
    }
}

std::string CTVSet::GetChannelName(int channel)
{
    if (m_channelNames.find(channel) != m_channelNames.end())
    {
        return m_channelNames[channel];
    }
    return "";
}

int CTVSet::GetChannelByName(const std::string& name)
{
    for (const auto& pair : m_channelNames)
    {
        if (pair.second == name)
        {
            return pair.first;
        }
    }
    return 0;
}

void CTVSet::DeleteChannelName(const std::string& name)
{
    for (auto it = m_channelNames.begin(); it != m_channelNames.end(); ++it)
    {
        if (it->second == name)
        {
            m_channelNames.erase(it);
            break;
        }
    }
}

void CTVSet::Info()
{
    std::cout << "TV is " << (m_isOn ? "ON" : "OFF") << "\n";
    if (m_isOn)
    {
        std::cout << "Current channel: " << m_currentChannel << "\n";
        std::cout << "Channel names:\n";
        for (const auto& pair : m_channelNames) {
            std::cout << pair.first << " - " << pair.second << "\n";
        }
    }
}
