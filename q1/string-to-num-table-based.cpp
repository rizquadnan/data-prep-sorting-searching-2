#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <cmath>

using namespace std;

inline string& rtrim(string& s)
{
  const char* ws = " \t\n\r\f\v";

    s.erase(s.find_last_not_of(ws) + 1);
    return s;
}

// trim from beginning of string (left)
inline string& ltrim(string& s)
{
  const char* ws = " \t\n\r\f\v";

    s.erase(0, s.find_first_not_of(ws));
    return s;
}

// trim from both ends of string (right then left)
inline string& trim(string& s)
{
  const char* ws = " \t\n\r\f\v";

  return ltrim(rtrim(s));
}

int table_based(string myText, int** tableBased)
{
    int myNumber = 1;
    string safeText = trim(myText);

    for (size_t i = 0; i < myText.length(); i++)
    {
        if (safeText[i] == '@') {
            myNumber *= 1;
        } else {
            myNumber *= tableBased[i][safeText[i]];
        }
    }
    return myNumber;
}

void driver(string inFile)
{
    string myText;
    ifstream myReadFile(inFile);

    vector<string> datas;

    int asciiSize = 128;

    int* asciiIndex = new int [asciiSize];

    for (size_t looper = 0; looper < asciiSize; looper++)
    {
        if (looper >= 64 && looper <= 90)
        {
            asciiIndex[looper] = looper - 63;
        }
        else if (looper >= 97 && looper <= 122)
        {
            asciiIndex[looper] = looper - 95;
        }
    }

    int tableBasedSize = 6;
    int** tableBased = new int* [tableBasedSize];

    for (size_t looper = 0; looper < tableBasedSize; looper++)
    {
        tableBased[looper] = new int[asciiSize]{0};
    }

    for (size_t tabloop = 0; tabloop < tableBasedSize; tabloop++)
    {
        for (size_t looper = 0; looper < asciiSize; looper++)
        {
            tableBased[tabloop][looper] = asciiIndex[looper];
        }
    }

    // put textfile data to vector
    // this step should not be timed
    while (getline(myReadFile, myText))
    {
        datas.push_back(myText);
    }

    myReadFile.close();

    int arrSize = datas.size();
    // string* fileData = new string[arrSize];
    string fileData[5] = {"zzz@@@", "bfa@@@", "ssw@@@", "jg@@@@", "aaa@@@"};

    // start counting each word by the first letter
    auto begin1 = chrono::high_resolution_clock::now();
    // int* fileDataNum = new int[arrSize];

    // for (size_t looper = 0; looper < arrSize; looper++)
    // {
    //     fileDataNum[looper] = table_based(fileData[looper], tableBased);
    // }

    int* fileDataNum = new int[5];

    for (size_t looper = 0; looper < 5; looper++)
    {
        fileDataNum[looper] = table_based(fileData[looper], tableBased);
    }

    auto end1 = chrono::high_resolution_clock::now();
    cout << chrono::duration<double>(end1 - begin1).count() << endl;

    for (size_t looper = 0; looper < 5; looper++)
    {
        cout << "fileDataNum[looper]: " << fileDataNum[looper] << endl;
        cout << "fileData[looper]: " << fileData[looper] << endl;
        cout << "" << endl;
    }
}


int main()
{

    cout << "1k" << endl;
    for (size_t i = 0; i < 1; i++)
    {
        driver("../1k.txt");
    }
    // cout << "10k" << endl;
    // for (size_t i = 0; i < 10; i++)
    // {
    //     driver("../10k.txt");
    // }
    // cout << "100k" << endl;
    // for (size_t i = 0; i < 10; i++)
    // {
    //     driver("../100k.txt");
    // }
    // cout << "1m" << endl;
    // for (size_t i = 0; i < 10; i++)
    // {
    //     driver("../1m.txt");
    // }
    // cout << "10m" << endl;
    // for (size_t i = 0; i < 10; i++)
    // {
    //     driver("../10m.txt");
    // }

    // system("pause");
}