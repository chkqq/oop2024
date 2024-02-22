#include "dictionary.h"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <Windows.h>

using namespace std;

const string PROMPT = "> ";
const string EXIT_MESSAGE = "�� ��������.";
const string EXIT_COMMAND = "...";
const string SAVE_CHANGES_PROMPT = "� ������� ���� ������� ���������. ������� Y ��� y ��� ���������� ����� �������.";
const string SAVE_SUCCESS_MESSAGE = "��������� ���������. �� ��������.";
const string NO_SAVE_MESSAGE = "��������� �� ���������. �� ��������.";
const string OPEN_FILE_ERROR_MESSAGE = "������ �������� �����: ";
const string UNKNOWN_WORD_MESSAGE = "����������� ����� \"";
const string ENTER_TRANSLATION_PROMPT = "\". ������� ������� ��� ������ ������ ��� ������.";
const string WORD_SAVED_MESSAGE = "����� \"";
const string SAVED_IN_DICTIONARY_MESSAGE = "\" ��������� � ������� ��� \"";


string ToLowerCase(const string& str)
{
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}


void ReadDictionaryFromFile(
    unordered_map<string, string>& forwardDictionary,
    unordered_map<string, string>& reverseDictionary,
    const string& dictionaryFileName
)
{
    ifstream file(dictionaryFileName);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            size_t pos = line.find(',');
            if (pos != string::npos)
            {
                string key = line.substr(0, pos);
                string value = line.substr(pos + 1);
                forwardDictionary[ToLowerCase(key)] = value;
                reverseDictionary[ToLowerCase(value)] = key;
            }
        }
        file.close();
    }
    else
    {
        cerr << OPEN_FILE_ERROR_MESSAGE << dictionaryFileName << "\n";
    }
}

void OverwriteTheDictionaryFile(
    const string& input,
    bool& programRunning,
    bool& changesMade,
    const unordered_map<string, string>& forwardDictionary,
    const unordered_map<string, string>& reverseDictionary,
    const string& dictionaryFileName
)
{
    if (input == EXIT_COMMAND)
    {
        if (changesMade)
        {
            char save;
            cout << SAVE_CHANGES_PROMPT << "\n";
            cin >> save;
            if (save == 'Y' || save == 'y')
            {
                ofstream outFile(dictionaryFileName);
                if (outFile.is_open())
                {
                    for (const auto& pair : forwardDictionary)
                    {
                        outFile << pair.first << "," << pair.second << "\n";
                    }
                    for (const auto& pair : reverseDictionary)
                    {
                        outFile << pair.second << "," << pair.first << "\n";
                    }
                    outFile.close();
                    cout << SAVE_SUCCESS_MESSAGE << "\n";
                }
                else
                {
                    cerr << OPEN_FILE_ERROR_MESSAGE << dictionaryFileName << "\n";
                }
            }
            else
            {
                cout << NO_SAVE_MESSAGE << "\n";
            }
        }
        else
        {
            cout << EXIT_MESSAGE << "\n";
        }
        programRunning = false;
    }
}

void SaveInDictionary(
    const string& input,
    unordered_map<string, string>& forwardDictionary,
    unordered_map<string, string>& reverseDictionary,
    bool& changesMade
)
{
    string translation;
    if (!(input == EXIT_COMMAND))
    {
        cout << UNKNOWN_WORD_MESSAGE << input << ENTER_TRANSLATION_PROMPT << "\n";
        getline(cin, translation);
    }
    if (!translation.empty())
    {
        forwardDictionary[ToLowerCase(input)] = translation;
        reverseDictionary[translation] = input;
        cout << WORD_SAVED_MESSAGE << input << SAVED_IN_DICTIONARY_MESSAGE << translation << "\".\n";
        changesMade = true;
    }
}

void DictionaryRun(
    unordered_map<string, string>& forwardDictionary,
    unordered_map<string, string>& reverseDictionary,
    const string& dictionaryFileName
)
{
    bool changesMade = false;
    bool programRunning = true;
    string input;
    while (programRunning)
    {
        cout << PROMPT;
        getline(cin, input);

        OverwriteTheDictionaryFile(input, programRunning, changesMade, forwardDictionary, reverseDictionary, dictionaryFileName);

        auto it = forwardDictionary.find(ToLowerCase(input));
        if (it != forwardDictionary.end())
        {
            cout << it->second << "\n";
        }
        else
        {
            it = reverseDictionary.find(ToLowerCase(input));
            if (it != reverseDictionary.end())
            {
                cout << it->second << "\n";
            }
            else
            {
                SaveInDictionary(input, forwardDictionary, reverseDictionary, changesMade);
            }
        }
    }
}