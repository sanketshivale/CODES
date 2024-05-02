#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

class Sort {
    public:
        void bubbleSort(int arr[], int n);
        void display(int arr[], int n);
        void mergeSort(int arr[], int low, int high);
        void merge(int arr[], int low, int mid, int high);
};

void Sort::bubbleSort(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        #pragma omp parallel shared(arr)
        for (int j = 0; j < n; j++) {
            if (arr[i] < arr[j])
                swap(arr[i], arr[j]);
        }
    }
}

void Sort::merge(int arr[], int low, int mid, int high) {
    int n = high - low + 1;
    vector<int> temp(n);
    int i = low, j = mid+1, k = 0;
    
    while (i <= mid && j <= high) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    
    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    
    while (j <= high) {
        temp[k++] = arr[j++];
    }
    
    for (int p = 0; p < n; p++) {
        arr[low + p] = temp[p];
    }
}

void Sort::mergeSort(int arr[], int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                this->mergeSort(arr, low, mid);
            }
            
            #pragma omp section
            {
                this->mergeSort(arr, mid+1, high);
            }
        }
        this->merge(arr, low, mid, high);
    }
}

void Sort::display(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}


int main()
{
    int arr[] = {23,34,2,45,12,5};
    int n = sizeof(arr)/sizeof(arr[0]);
    
    Sort s;
    
    // double start = omp_get_wtime();
    // s.bubbleSort(arr, n);
    // double end = omp_get_wtime();
    // cout << "Parallel Bubble sort duration: " << (end - start) << endl;
    
    double start = omp_get_wtime();
    s.mergeSort(arr, 0, n-1);
    double end = omp_get_wtime();
    cout << "Parallel Merge sort duration: " << (end - start) << endl;
    
    s.display(arr, n);
    
    return 0;
}