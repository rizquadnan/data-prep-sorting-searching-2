#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;
 
// An iterative binary search function.
int binarySearch(string arr[], string x, int n)
{
    int l = 0;
    int r = n - 1;

    // Loop to implement Binary Search
    while (l <= r) {

        // Calculatiing mid
        int m = l + (r - l) / 2;

        // Some random value assigned
        // as 0 belongs to index
        int res = -1000;

        if (x == (arr[m]))
            res = 0;

        // Check if x is present at mid
        if (res == 0)
            return m;

        // If x greater, ignore left half
        if (x > (arr[m]))
            l = m + 1;

        // If x is smaller, ignore right half
        else
            r = m - 1;
    }

    return -1;
}

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

// A utility function to swap two elements
void swap(string* a, string* b)
{
    string t = *a;
    *a = *b;
    *b = t;
}

/* This function is same in both iterative and recursive*/
int partition(string* arr, int l, int h)
{
    string x = arr[h];
    int i = (l - 1);

    for (int j = l; j <= h - 1; j++) {
        if (arr[j] <= x) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[h]);
    return (i + 1);
}

/* A[] --> Array to be sorted,
l --> Starting index,
h --> Ending index */
void quickSort(string* arr, int l, int h)
{
    // Create an auxiliary stack
    int* stack = new int[h - l + 1];

    // initialize top of stack
    int top = -1;

    // push initial values of l and h to stack
    stack[++top] = l;
    stack[++top] = h;

    // Keep popping from stack while is not empty
    while (top >= 0) {
        // Pop h and l
        h = stack[top--];
        l = stack[top--];

        // Set pivot element at its correct position
        // in sorted array
        int p = partition(arr, l, h);

        // If there are elements on left side of pivot,
        // then push left side to stack
        if (p - 1 > l) {
            stack[++top] = l;
            stack[++top] = p - 1;
        }

        // If there are elements on right side of pivot,
        // then push right side to stack
        if (p + 1 < h) {
            stack[++top] = p + 1;
            stack[++top] = h;
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
    // this step should not be timed
    quickSort(newArr, 0, arrSize - 1);

    // start searching
    auto begin = chrono::high_resolution_clock::now();
    bool checker = true;
    string notFoundString;

    // search for all elements inside UNSTA 
    for (size_t looper = 0; looper < arrSize; looper++)
    {
      string searchTarget = newArr[looper];
      int targetIndex = binarySearch(newArr, searchTarget, arrSize);
      
      if (targetIndex == -1) {
        checker = false;
        notFoundString = searchTarget;
        break;
      }
    }

    auto end = chrono::high_resolution_clock::now();
            
    if (checker)
    {
        cout << chrono::duration<double>(end - begin).count() << endl;
    }
    else
    {
        cout << "Something went wrong " << notFoundString << " was not Found" << endl;
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