#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

bool check(string * arr, int n)
{
   int i, j;
   bool result = true;;
   for (i = 0; i < n-1; i++)
   {
     for (j = 0; j < n-i-1; j++)
     {
        if (arr[j] > arr[j+1])
        {
           swap(arr[j], arr[j+1]);
           result = false;
           break;
        }
     }
 
     // IF no two elements were swapped
     // by inner loop, then break
     if (result)
     {
         return result;
     }
   }

   return result;
}

void swap(string* xp, string* yp)
{
    string temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubble_sort(string* arr, int* limit)
{
    int i, j;
    for (i = 0; i < limit[1] - limit[0] - 1; i++)
    {
        for (j = limit[0]; j < limit[1] - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void driver(string inFile)
{
    string myText;
    ifstream myReadFile(inFile);

    vector<string> datas;
    // put textfile data to vector
    // this step should not be timed
    while (getline(myReadFile, myText))
    {
        datas.push_back(myText);
    }

    myReadFile.close();

    int arrSize = datas.size();
    string* newArr = new string[arrSize];

    // convert vector to array
    // this step should not be timed
    for (size_t looper = 0; looper < arrSize; looper++)
    {
        newArr[looper] = datas[looper];
    }   

    // sort UNSTA to SOSTA
    auto begin = chrono::high_resolution_clock::now();

    bubble_sort(newArr, arrSize);

    auto end = chrono::high_resolution_clock::now();

    // checks if array is sorted
    // this step should not be timed
    bool checker = check(newArr, arrSize);            
    if (checker)
    {
        cout << chrono::duration<double>(end - begin).count() << endl;
    }
    else
    {
        cout << "Something went wrong" << endl;
        cout << chrono::duration<double>(end - begin).count() << endl;
    }
}

int main()
{
    int numOfIterations = 1;

    cout << "1k" << endl;
    for (size_t i = 0; i < numOfIterations; i++)
    {
        driver("../datasets/1k.txt");
    }

    cout << "10k" << endl;
    for (size_t i = 0; i < numOfIterations; i++)
    {
        driver("../datasets/10k.txt");
    }

    cout << "100k" << endl;
    for (size_t i = 0; i < numOfIterations; i++)
    {
        driver("../datasets/100k.txt");
    }

    // cout << "1m" << endl;
    // for (size_t i = 0; i < numOfIterations; i++)
    // {
    //     driver("../datasets/1m.txt");
    // }
}