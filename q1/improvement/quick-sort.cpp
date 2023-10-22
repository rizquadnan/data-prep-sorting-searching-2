#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <cmath>

using namespace std;

struct refer {
    int prefixCounter;
    vector<string> stringValues;
};

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

// function to swap elements
void swap(string *a, string *b) {
  string t = *a;
  *a = *b;
  *b = t;
}

// function to print the array
void printArray(string array[], int size) {
  int i;
  for (i = 0; i < size; i++)
    cout << array[i] << " ";
  cout << endl;
}

// function to rearrange array (find the partition point)
int partition(string array[], int low, int high) {
    
  // select the rightmost element as pivot
  string pivot = array[high];
  
  // pointer for greater element
  int i = (low - 1);

  // traverse each element of the array
  // compare them with the pivot
  for (int j = low; j < high; j++) {
    if (array[j] <= pivot) {
        
      // if element smaller than pivot is found
      // swap it with the greater element pointed by i
      i++;
      
      // swap element at i with element at j
      swap(&array[i], &array[j]);
    }
  }
  
  // swap pivot with the greater element at i
  swap(&array[i + 1], &array[high]);
  
  // return the partition point
  return (i + 1);
}

void quickSort(string array[], int low, int high) {
  if (low < high) {
      
    // find the pivot element such that
    // elements smaller than pivot are on left of pivot
    // elements greater than pivot are on righ of pivot
    int pi = partition(array, low, high);

    // recursive call on the left of pivot
    quickSort(array, low, pi - 1);

    // recursive call on the right of pivot
    quickSort(array, pi + 1, high);
  }
}

int partitionDn(vector<string> array, int low, int high) {
    
  // select the rightmost element as pivot
  string pivot = array[high];
  
  // pointer for greater element
  int i = (low - 1);

  // traverse each element of the array
  // compare them with the pivot
  for (int j = low; j < high; j++) {
    if (array[j] <= pivot) {
        
      // if element smaller than pivot is found
      // swap it with the greater element pointed by i
      i++;
      
      // swap element at i with element at j
      swap(&array[i], &array[j]);
    }
  }
  
  // swap pivot with the greater element at i
  swap(&array[i + 1], &array[high]);
  
  // return the partition point
  return (i + 1);
}

void quickSortDn(vector<string> array, int low, int high) {
  if (low < high) {
      
    // find the pivot element such that
    // elements smaller than pivot are on left of pivot
    // elements greater than pivot are on righ of pivot
    int pi = partitionDn(array, low, high);

    // recursive call on the left of pivot
    quickSortDn(array, low, pi - 1);

    // recursive call on the right of pivot
    quickSortDn(array, pi + 1, high);
  }
}

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
    int myNumber = 0;
    string safeText = trim(myText);

    for (size_t i = 0; i < safeText.length(); i++)
    {
        if (safeText[i] == '@') {
            myNumber += 0;
        } else {
            myNumber += tableBased[i][safeText[i]] * pow(27, i);
        }
    }
    return myNumber;
}

void driver(string inFile)
{
    // start initate code to convert string to number
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
    // end initate code to convert string to number

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

    // fill in reference array
    int referenceArraySize = pow(27, 1) + pow(27, 2) + pow(27, 3) + 1;;
    refer* referenceArray = new refer[referenceArraySize];
    string stringVal;
    string firstThree;
    int integerRepresentation;

    for (size_t looper = 0; looper < referenceArraySize; looper++)
    {
      referenceArray[looper].prefixCounter = 0;
    } 

    for (size_t looper = 0; looper < arrSize; looper++)
    {
        stringVal = newArr[looper];
        firstThree = stringVal.substr(0, 3);
        integerRepresentation = table_based(firstThree, tableBased);

        referenceArray[integerRepresentation].prefixCounter += 1;
        referenceArray[integerRepresentation].stringValues.push_back(stringVal);
        // cout << "stringVal: " << stringVal << endl;
        // cout << "firstThree: " << firstThree << endl;
        // cout << "integerRepresentation: " << integerRepresentation << endl;
        // cout << "" << endl;
    }

    
    // code to see reference array
    // for (size_t looper = 0; looper < referenceArraySize; looper++)
    // {
    //   if (referenceArray[looper].prefixCounter > 0)
    //   {
    //     cout << "looper: " << looper << endl; 
    //     cout << "referenceArray[looper].prefixCounter: " << referenceArray[looper].prefixCounter << endl;
    //     int size = referenceArray[looper].stringValues.size();
    //     cout << "referenceArray[looper].stringValues.size(): " << size << endl;
    //     cout << "stringValues: " << endl;
        
    //     for (size_t looperIn = 0; looperIn < size; looperIn++) {
    //       cout << "referenceArray[looper].stringValues[looperIn]: " << referenceArray[looper].stringValues[looperIn] << endl;
    //     }

    //     cout << "" << endl;
    //   }
    // }

    // fill in indexed sorting array
    vector<refer> indexedSortingArray;
    for (size_t looper = 0; looper < referenceArraySize; looper++)
    {
      if (referenceArray[looper].prefixCounter > 0)
      {
        indexedSortingArray.push_back(referenceArray[looper]);
      }
    }

    // code to see indexed sorting array
    // int isaSize = indexedSortingArray.size();
    // for (size_t looper = 0; looper < isaSize; looper++)
    // {
    //   cout << "looper: " << looper << endl;
    //   cout << "indexedSortingArray[looper].prefixCounter: " << indexedSortingArray[looper].prefixCounter << endl;
    //   int size = indexedSortingArray[looper].stringValues.size();
    //   cout << "indexedSortingArray[looper].size(): " << size << endl;
    //   cout << "stringValues: " << endl;
      
    //   for (size_t looperIn = 0; looperIn < size; looperIn++) {
    //     cout << "indexedSortingArray[looper].stringValues[looperIn]: " << indexedSortingArray[looper].stringValues[looperIn] << endl;
    //   }

    //   cout << "" << endl;
    // }

    auto end1 = chrono::high_resolution_clock::now();


    // start sorting
    auto begin2 = chrono::high_resolution_clock::now();

    int isaSize = indexedSortingArray.size();
    for (size_t looper = 0; looper < isaSize; looper++)
    {
      quickSortDn(indexedSortingArray[looper].stringValues, 0, indexedSortingArray[looper].stringValues.size() - 1);
    } 

    // code to see indexed sorting array
    // for (size_t looper = 0; looper < isaSize; looper++)
    // {
    //   cout << "looper: " << looper << endl;
    //   cout << "indexedSortingArray[looper].prefixCounter: " << indexedSortingArray[looper].prefixCounter << endl;
    //   int size = indexedSortingArray[looper].stringValues.size();
    //   cout << "indexedSortingArray[looper].size(): " << size << endl;
    //   cout << "stringValues: " << endl;
      
    //   for (size_t looperIn = 0; looperIn < size; looperIn++) {
    //     cout << "indexedSortingArray[looper].stringValues[looperIn]: " << indexedSortingArray[looper].stringValues[looperIn] << endl;
    //   }
    //   cout << "" << endl;
    // }

    // put sorted indexed sorting array back together
    string* resultArr = new string[arrSize];
    int fillInResultCounter = 0;
    for (size_t looper = 0; looper < isaSize; looper++)
    {
      int size = indexedSortingArray[looper].stringValues.size();
      for (size_t looperIn = 0; looperIn < size; looperIn++) {
        resultArr[fillInResultCounter] = indexedSortingArray[looper].stringValues[looperIn];
        fillInResultCounter += 1;
      }
    }

    // code to see indexed sorting result
    // for (size_t looper = 0; looper < arrSize; looper++) {
    //   cout << "looper: " << looper << endl;
    //   cout << "resultArr[looper]: " << resultArr[looper] << endl;
    //   cout << "" << endl;
    // }

    quickSort(resultArr, 0, arrSize - 1);

    auto end2 = chrono::high_resolution_clock::now();

    // checks if array is sorted
    // this step should not be timed
    bool checker = check(resultArr, arrSize);            
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

    cout << "10m" << endl;
    for (size_t i = 0; i < numOfIterations; i++)
    {
        driver("../datasets/10m.txt");
    }
}