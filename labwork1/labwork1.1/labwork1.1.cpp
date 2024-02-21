#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<int> FindStringInFile(ifstream& file, const string& search_word)
{
    vector<int> found_lines;
    string line;
    int line_number = 1;

    while (getline(file, line))
    {
        size_t found = line.find(search_word);
        if (found != string::npos)
        {
            found_lines.push_back(line_number);
        }
        line_number++;
    }

    return found_lines;
}

void PrintFoundLineIndex(vector<int> found_lines)
{
    for (int num : found_lines)
    {
        cout << num << endl;
    }
}

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        cerr << "Usage: " << argv[0] << " <filename> <search_word>" << endl;
        return 1;
    }

    string filename = argv[1];
    string search_word = argv[2];

    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "File open error." << endl;
        return 1;
    }

    vector<int> found_lines = FindStringInFile(file, search_word);

    file.close();

    if (found_lines.empty())
    {
        cout << "Text not found" << endl;
        return 1;
    }

    PrintFoundLineIndex(found_lines);

    return 0;
}