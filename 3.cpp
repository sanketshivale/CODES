#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

void parallelMin(vector<int> arr, int n) {
    int min = arr[0];
    #pragma omp parallel reduction(min: min)
    for (int i = 0; i < n; i++) {
        if (min > arr[i])
            min = arr[i];
    }
    
    cout << "Parallel Min: " << min << endl;
}

void parallelMax(vector<int> arr, int n) {
    int max = arr[0];
    #pragma omp parallel reduction(max: max)
    for (int i = 0; i < n; i++) {
        if (max < arr[i])
            max = arr[i];
    }
    
    cout << "Parallel Max: " << max << endl;
}

void parallelSum(vector<int> arr, int n) {
    int sum = 0;
    #pragma omp parallel reduction (+: sum)
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    
    cout << "Parallel Sum: " << sum << endl;
}

void parallelAvg(vector<int> arr, int n) {
    int sum = 0;
    #pragma omp parallel reduction (+: sum)
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    
    cout << "Parallel Average: " << double(sum / n) << endl;
}

int main() {
    vector<int> arr = {1, 26, 41, 48, 57, 59, 55, 74, 15, 96};
    int n = arr.size();
    
    parallelMin(arr, n);
    parallelMax(arr, n);
    parallelSum(arr, n);
    parallelAvg(arr, n);
    
    return 0;
}