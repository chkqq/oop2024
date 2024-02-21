#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <Windows.h>

using namespace std;


const string PROMPT = "> ";
const string EXIT_MESSAGE = "До свидания.";
const string EXIT_COMMAND = "...";
const string SAVE_CHANGES_PROMPT = "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.";
const string SAVE_SUCCESS_MESSAGE = "Изменения сохранены. До свидания.";
const string NO_SAVE_MESSAGE = "Изменения не сохранены. До свидания.";
const string OPEN_FILE_ERROR_MESSAGE = "Ошибка открытия файла: ";
const string UNKNOWN_WORD_MESSAGE = "Неизвестное слово \"";
const string ENTER_TRANSLATION_PROMPT = "\". Введите перевод или пустую строку для отказа.";
const string WORD_SAVED_MESSAGE = "Слово \"";
const string SAVED_IN_DICTIONARY_MESSAGE = "\" сохранено в словаре как \"";

string ToLowerCase(const string& str) 
{
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

void DictionaryFillingFromFile(unordered_map<string, string>& dictionary, const char* dictionaryFileName)
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
                dictionary[ToLowerCase(key)] = value;
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
    unordered_map<string, string>& dictionary, 
    const char* dictionaryFileName
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
                    for (const auto& pair : dictionary)
                    {
                        outFile << pair.first << "," << pair.second << "\n";
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
    unordered_map<string, string>& dictionary, 
    bool& changesMade
)
{
    string translation;
    cout << UNKNOWN_WORD_MESSAGE << input << ENTER_TRANSLATION_PROMPT << "\n";
    getline(cin, translation);
    if (!translation.empty())
    {
        dictionary[ToLowerCase(input)] = translation;
        cout << WORD_SAVED_MESSAGE << input << SAVED_IN_DICTIONARY_MESSAGE << translation << "\".\n";
        changesMade = true;
    }
}

int main(int argc, char* argv[]) 
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    if (argc != 2) 
    {
        cerr << "Usage: " << argv[0] << " <dictionary_file>\n";
        return 1;
    }

    char* dictionaryFileName = argv[1];
    unordered_map<string, string> dictionary;

    DictionaryFillingFromFile(dictionary, dictionaryFileName);

    bool changesMade = false;
    bool programRunning = true;

    string input;
    while (programRunning)
    {
        cout << PROMPT;
        getline(cin, input);

        OverwriteTheDictionaryFile(input, programRunning, changesMade, dictionary, dictionaryFileName);

        auto it = dictionary.find(ToLowerCase(input));
        if (it != dictionary.end()) 
        {
            cout << it->second << "\n";
        }
        else 
        {
            SaveInDictionary(input, dictionary, changesMade);
        }
    }

    return 0;
}
