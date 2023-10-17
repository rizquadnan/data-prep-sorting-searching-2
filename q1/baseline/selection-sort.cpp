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

// function to swap the the position of two elements
void swap(string *a, string *b) {
  string temp = *a;
  *a = *b;
  *b = temp;
}

// function to print an array
void printArray(string array[], int size) {
  for (int i = 0; i < size; i++) {
    cout << array[i] << " ";
  }
  cout << endl;
}

void selectionSort(string array[], int size) {
  for (int step = 0; step < size - 1; step++) {
    int min_idx = step;
    for (int i = step + 1; i < size; i++) {

      // To sort in descending order, change > to < in this line.
      // Select the minimum element in each loop.
      if (array[i] < array[min_idx])
        min_idx = i;
    }

    // put min at the correct position
    swap(&array[min_idx], &array[step]);
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

    selectionSort(newArr, arrSize);

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

    cout << "1m" << endl;
    for (size_t i = 0; i < numOfIterations; i++)
    {
        driver("../datasets/1m.txt");
    }
}