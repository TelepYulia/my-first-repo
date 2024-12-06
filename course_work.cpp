#include <iostream>
using namespace std;

int* CreateArray(int n)
{
    int *arr = new int[n];
    for (int i=0; i<n; i++)
    {
        arr[i] = rand() %51;
        cout << arr[i] << " ";
    }
    return arr;
}

int* CopyArray(int* arr, int n)
{
    int* newArr = new int[n];
    for(int i=0; i<n; i++)
    {
        newArr[i]=arr[i];
    }
    return newArr;
}
void PrintArray(int* arr, int n)
{
    for(int i=0; i<n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}
void BubbleSort(int* arr, int n, int& complexity)
{
    for(int i=0; i<n;i++)
    {
        for(int j=i;j<n;j++)
        {
            complexity++;
            if(arr[i]>arr[j])
            {
                swap(arr[i], arr[j]);
                complexity++;
            }
        }
    }
    PrintArray(arr, n);
    cout << "Complexity of bubble sorting:" << complexity << endl;
}

void SelectionSort(int* arr, int n, int& complexity)
{
    for(int i=0;i<n;i++)
    {
        int min=i;
        for(int j=i+1;j<n;j++)
        {
            complexity++;
            if(arr[j]<arr[min])
            {
                min=j;
            }
        }
        if(min !=i)
        {
            swap(arr[min], arr[i]);
            complexity++;
        }
    }
    PrintArray(arr, n);
    cout << "Complexity of selection sorting:" << complexity << endl;
}

void InsertionSort(int* arr, int n, int& complexity)
{
       for (int i = 0; i < n; i++)
       {
           int key = arr[i];
           int j = i-1;
           //переміщуємо елементи, які більші за ключ, на одну позтцію вперед
           while (j >= 0 && arr[j] > key)
           {
               complexity++;
               arr[j + 1] = arr[j];
               complexity++;
               --j;
           }
           complexity++; //for a final check
           arr[j + 1] = key;
       }
    PrintArray(arr, n);
    cout << "Complexity of insertion sorting:" << complexity << endl;
}

void ShellSort(int* arr, int n, int& complexity)
{
    //ділимо масив на 2
    for(int gap=n/2;gap>0;gap/=2)
    {
        //сортуємо елементи, які знаходяться на відстані gap
        for(int i = gap;i<n;i++)
        {
            int temp = arr[i];
            int j;
            //переставляємо елементи всередині груп
            for(j=i;j>=gap && arr[j-gap] > temp; j-=gap)
            {
                complexity++;
                arr[j] = arr[j-gap];
                complexity++;
            }
            complexity++;
            arr[j] = temp;
        }
    }
    PrintArray(arr, n);
    cout << "Complexity of Shell sorting:" << complexity << endl;
}

void QuickSort(int* arr, int low, int high, int& complexity, int n)
{
    if(low < high)
    {
        int pivot = arr[high];
        int i = low-1;
        for(int j = low; j < high; j++)
        {
            complexity++;
            if(arr[j] < pivot)
            {
                i++;
                swap(arr[i], arr[j]);
                complexity++;
            }
        }
        swap(arr[i+1], arr[high]);
        complexity++;
        QuickSort(arr, low, i, complexity,n);
        QuickSort(arr, i+2, high, complexity,n);
    }
}

void Merge(int* arr, int left, int mid, int right, int& complexity)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];
        
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    while (i < n1 && j < n2)
    {
        complexity++;
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
        complexity++;
    }

        
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
        complexity++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
        complexity++;
    }
    delete[] L;
    delete[] R;
}
void MergeSort(int* arr, int left, int right, int& complexity, int n)
{
    if(left < right)
    {
        int mid = left + (right - left)/2;
        MergeSort(arr, left, mid, complexity,n);
        MergeSort(arr, mid+1, right, complexity,n);
        Merge(arr, left, mid, right, complexity);
    }
}

void Heapify(int* arr, int n, int i, int& complexity)
{
    int largest = i;
    int l=2*i+1;
    int r=2*i+2;
    if (l < n) {
            complexity++;
            if (arr[l] > arr[largest]) largest = l;
        }
        if (r < n) {
            complexity++;
            if (arr[r] > arr[l]) largest = r;
        }

        if (largest != i) {
            swap(arr[i], arr[largest]);
            complexity++;
            Heapify(arr, n, largest, complexity);
        }
}

void HeapSort( int* arr, int n, int& complexity)
{
    for (int i = n / 2 - 1; i >= 0; --i) Heapify(arr, n, i, complexity);
       for (int i = n - 1; i > 0; --i) {
           swap(arr[0], arr[i]);
           complexity++;
           Heapify(arr, i, 0, complexity);
       }
}
int main()
{
    int n;
    cout << "Enter the number of array elements: ";
    cin >> n;
    srand((unsigned)time(0));
    cout << endl << "Original array: ";
    int* OriginalArray = CreateArray(n);
    int arr[7];
    
    int complexityBubble = 0;
    int* ArrayBubble = CopyArray(OriginalArray, n);
    cout << endl << "BubbleSort: ";
    BubbleSort(ArrayBubble, n, complexityBubble);
    arr[0] = complexityBubble;
    cout << endl;
    delete[] ArrayBubble;
    ArrayBubble = nullptr;
    
    int complexitySelection = 0;
    int* ArraySelection = CopyArray(OriginalArray, n);
    cout << endl << "SelectionSort: ";
    SelectionSort(ArraySelection, n, complexitySelection);
    arr[1] = complexitySelection;
    cout << endl;
    delete[] ArraySelection;
    ArraySelection = nullptr;
    
    int complexityInsertion = 0;
    int* ArrayInsertion = CopyArray(OriginalArray, n);
    cout << endl << "InsertionSort: ";
    InsertionSort(ArrayInsertion, n, complexityInsertion);
    arr[2] = complexityInsertion;
    cout << endl;
    delete[] ArrayInsertion;
    ArrayInsertion = nullptr;
    
    int complexityShell = 0;
    int* ArrayShell = CopyArray(OriginalArray, n);
    cout << endl << "ShellSort: ";
    ShellSort(ArrayShell, n, complexityShell);
    arr[3] = complexityShell;
    cout << endl;
    delete[] ArrayShell;
    ArrayShell = nullptr;
    
    int complexityQuicksort = 0;
    int* ArrayQuicksort = CopyArray(OriginalArray, n);
    cout << endl << "Quicksort: ";
    QuickSort(ArrayQuicksort, 0,n-1, complexityQuicksort,n);
    arr[4] = complexityQuicksort;
    PrintArray(ArrayQuicksort, n);
    cout << "Complexity of quick sorting:" << complexityQuicksort << endl;
    cout << endl;
    delete[] ArrayQuicksort;
    ArrayQuicksort = nullptr;
    
    int complexityMerge = 0;
    int* ArrayMerge = CopyArray(OriginalArray, n);
    cout << endl << "Mergesort: ";
    MergeSort(ArrayMerge, 0,n-1, complexityMerge,n);
    arr[5] = complexityMerge;
    PrintArray(ArrayMerge, n);
    cout << "Complexity of Merge sorting:" << complexityMerge << endl;
    cout << endl;
    delete[] ArrayMerge;
    ArrayMerge = nullptr;
    
    int complexityHeap = 0;
    int* ArrayHeap = CopyArray(OriginalArray, n);
    cout << endl << "Heapsort: ";
    HeapSort(ArrayHeap, n, complexityHeap);
    arr[6] = complexityHeap;
    PrintArray(ArrayHeap, n);
    cout << "Complexity of Heap sorting:" << complexityHeap << endl;
    cout << endl;
    delete[] ArrayHeap;
    ArrayHeap = nullptr;
    
    /*int minComplexity=0;
    for(int i=0; i < 7; i++)
    {
        //int position=0;
        if(arr[minComplexity]>arr[i]) minComplexity =i;
        //minComplexity = position;
    }
    */
    delete[] OriginalArray;
    OriginalArray=nullptr;
    return 0;
}
