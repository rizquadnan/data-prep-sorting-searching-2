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

void heapify(string arr[], int n, int i) {
    // Find largest among root, left child and right child
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
  
    if (left < n && arr[left] > arr[largest])
      largest = left;
  
    if (right < n && arr[right] > arr[largest])
      largest = right;
  
    // Swap and continue heapifying if root is not largest
    if (largest != i) {
      swap(arr[i], arr[largest]);
      heapify(arr, n, largest);
    }
  }
  
// main function to do heap sort
void heapSort(string arr[], int n) {
  // Build max heap
  for (int i = n / 2 - 1; i >= 0; i--)
    heapify(arr, n, i);

  // Heap sort
  for (int i = n - 1; i >= 0; i--) {
    swap(arr[0], arr[i]);

    // Heapify root element to get highest element at root again
    heapify(arr, i, 0);
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

    // data prep start
    auto begin1 = chrono::high_resolution_clock::now();

    string* referenceArray = new string[27 * 27 * 27]; // ie: Z * Z * Z
    string stringVal;
    string firstThree;
    int stringNumber;

    for (size_t looper = 0; looper < arrSize; looper++)
    {
        stringVal = newArr[looper];
        firstThree = stringVal.substr(0, 3);
        // cout << "stringVal: " << stringVal << endl;
        // cout << "firstThree: " << firstThree << endl;
        // cout << "" << endl;
    }  


    auto end1 = chrono::high_resolution_clock::now();


    // sort UNSTA to SOSTA
    auto begin2 = chrono::high_resolution_clock::now();

    heapSort(newArr, arrSize);

    auto end2 = chrono::high_resolution_clock::now();

    // checks if array is sorted
    // this step should not be timed
    bool checker = check(newArr, arrSize);            
    if (checker)
    {
        cout << chrono::duration<double>(end2 - begin2).count() << endl;
    }
    else
    {
        cout << "Something went wrong" << endl;
        cout << chrono::duration<double>(end2 - begin2).count() << endl;
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

    // cout << "10k" << endl;
    // for (size_t i = 0; i < numOfIterations; i++)
    // {
    //     driver("../datasets/10k.txt");
    // }

    // cout << "100k" << endl;
    // for (size_t i = 0; i < numOfIterations; i++)
    // {
    //     driver("../datasets/100k.txt");
    // }

    // cout << "1m" << endl;
    // for (size_t i = 0; i < numOfIterations; i++)
    // {
    //     driver("../datasets/1m.txt");
    // }

    // cout << "10m" << endl;
    // for (size_t i = 0; i < numOfIterations; i++)
    // {
    //     driver("../datasets/10m.txt");
    // }
}