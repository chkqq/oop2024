#pragma once

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;
void ReadDictionaryFromFile(
    unordered_map<string, string>& forwardDictionary,
    unordered_map<string, string>& reverseDictionary,
    const string& dictionaryFileName
);

void DictionaryRun(
    unordered_map<string, string>& forwardDictionary,
    unordered_map<string, string>& reverseDictionary,
    const string& dictionaryFileName
);