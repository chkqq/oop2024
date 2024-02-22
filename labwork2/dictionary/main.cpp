#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <Windows.h>
#include "dictionary.h"

using namespace std;

void SetLocale()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}

int main(int argc, char* argv[])
{
    SetLocale();

    if (argc != 2)
    {
        cerr << "Usage: " << argv[0] << " <dictionary_file>\n";
        return 1;
    }

    string dictionaryFileName = argv[1];
    unordered_map<string, string> forwardDictionary;
    unordered_map<string, string> reverseDictionary;

    ReadDictionaryFromFile(forwardDictionary, reverseDictionary, dictionaryFileName);
    DictionaryRun(forwardDictionary, reverseDictionary, dictionaryFileName);
    

    return 0;
}
