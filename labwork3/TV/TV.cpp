#include <iostream>
#include <string>
#include "TVSet.h"

using namespace std;

void displayMenu()
{
    cout << "=== TV Control Menu ===\n"
        << "1. Turn On\n"
        << "2. Turn Off\n"
        << "3. Select Channel\n"
        << "4. Set Channel Name\n"
        << "5. Get Channel Name\n"
        << "6. Get Channel by Name\n"
        << "7. TV Info\n"
        << "8. Exit\n"
        << "=======================\n"
        << "Enter your choice: ";
}

void turnOn(CTVSet& tv)
{
    tv.TurnOn();
}

void turnOff(CTVSet& tv)
{
    tv.TurnOff();
}

void selectChannel(CTVSet& tv)
{
    int channel;
    cout << "Enter channel number: ";
    cin >> channel;
    tv.SelectChannel(channel);
}

void setChannelName(CTVSet& tv)
{
    int channel;
    string name;
    cout << "Enter channel number: ";
    cin >> channel;
    cout << "Enter channel name: ";
    cin.ignore();
    getline(cin, name);
    tv.SetChannelName(channel, name);
}

void getChannelName(CTVSet& tv)
{
    int channel;
    cout << "Enter channel number: ";
    cin >> channel;
    cout << "Channel " << channel << " name: " << tv.GetChannelName(channel) << "\n";
}

void getChannelByName(CTVSet& tv)
{
    string name;
    cout << "Enter channel name: ";
    cin.ignore();
    getline(cin, name);
    int channel = tv.GetChannelByName(name);
    if (channel != -1)
        cout << "Channel '" << name << "' number: " << channel << "\n";
    else
        cout << "Channel '" << name << "' not found.\n";
}

void TVRun()
{
    CTVSet tv;
    bool running = true;
    int choice;
    while (running) {
        displayMenu();
        
        cin >> choice;

        switch (choice) {
        case 1:
            turnOn(tv);
            break;
        case 2:
            turnOff(tv);
            break;
        case 3:
            selectChannel(tv);
            break;
        case 4:
            setChannelName(tv);
            break;
        case 5:
            getChannelName(tv);
            break;
        case 6:
            getChannelByName(tv);
            break;
        case 7:
            tv.Info();
            break;
        case 8:
            running = false;
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
}
