#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n-1; i++)
        for (j = 0; j < n-i-1; j++)
            if (arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    int j;
    for (j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void fillArray(int arr[], int n) {
  int i;
    for (i = 0; i < n; i++) {
        arr[i] = rand() % 10000;
    }
}

double measureTime(void (*sortFunc)(int[], int), int arr[], int n) {
    clock_t start, end;
    start = clock();
    sortFunc(arr, n);
    end = clock();
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

// Function to measure time for Quick Sort
double measureTimeQuickSort(void (*sortFunc)(int[], int, int), int arr[], int low, int high) {
    clock_t start, end;
    start = clock();
    sortFunc(arr, low, high);
    end = clock();
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

// Function to measure time for Merge Sort
double measureTimeMergeSort(void (*sortFunc)(int[], int, int), int arr[], int l, int r) {
    clock_t start, end;
    start = clock();
    sortFunc(arr, l, r);
    end = clock();
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

void runTests(int n) {
    int *arr = (int *)malloc(n * sizeof(int));
    int trials = 5;
    int i;
    double insertionTime = 0.0, bubbleTime = 0.0, quickTime = 0.0, mergeTime = 0.0;

    for (i = 0; i < trials; i++) {
        fillArray(arr, n);
        int *temp = (int *)malloc(n * sizeof(int));

        memcpy(temp, arr, n * sizeof(int));
        insertionTime += measureTime(insertionSort, temp, n);

        memcpy(temp, arr, n * sizeof(int));
        bubbleTime += measureTime(bubbleSort, temp, n);

        memcpy(temp, arr, n * sizeof(int));
        quickTime += measureTimeQuickSort(quickSort, temp, 0, n - 1);

        memcpy(temp, arr, n * sizeof(int));
        mergeTime += measureTimeMergeSort(mergeSort, temp, 0, n - 1);

        free(temp);
    }

    free(arr);
    printf("n = %d:\n", n);
    printf("Insertion Sort: %.5f seconds\n", insertionTime / trials);
    printf("Bubble Sort: %.5f seconds\n", bubbleTime / trials);
    printf("Quick Sort: %.5f seconds\n", quickTime / trials);
    printf("Merge Sort: %.5f seconds\n", mergeTime / trials);
}

int main() {
    srand(time(0));

    int sizes[] = {1000, 2000, 4000, 8000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    int i;
    for (i = 0; i < numSizes; i++) {
        runTests(sizes[i]);
    }

    return 0;
}
