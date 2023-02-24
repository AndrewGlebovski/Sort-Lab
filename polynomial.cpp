#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>


typedef int data_t;

typedef void (*sort_t)(data_t *arr, int size);


void swap(data_t *a, data_t *b);

void bubble_sort(data_t *arr, int size);

void insertion_sort(data_t *arr, int size);

void selection_sort(data_t *arr, int size);

double test(data_t *arr, int size, sort_t sort);


int main() {
    int n = 0;
    assert(scanf("%i", &n) && "Invalid array size!\n");

    srand(time(NULL));

    data_t *arr = (data_t *) calloc(n, sizeof(data_t));
    
    for (int i = 0; i < n; i++) arr[i] = rand() % 100;
    
    printf("Time: %.2f ms\n", test(arr, n, &insertion_sort));
    
    for (int i = 0; i < n; i++) printf("%i ", arr[i]);
    putchar('\n');

    free(arr);

    return 0;
}


void swap(data_t *a, data_t *b) {
    data_t swap = *a;
    *a = *b;
    *b = swap;
}


void bubble_sort(data_t *arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        int flag = 1;

        for (int j = 0; j < size - i; j++) {
            if (arr[j + 1] < arr[j]) {
                swap(arr + j + 1, arr + j);
                flag = 0;
            }
        }

        if (flag) break;
    }
}


void insertion_sort(data_t *arr, int size) {
    for (int i = 1; i < size; i++) {
        int key = arr[i], j = i - 1;

        while (j >= 0 && key < arr[j]) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}


void selection_sort(data_t *arr, int size) {
    for (int i = 0; i < size; i++) {
        int min_index = i;

        for (int j = min_index + 1; j < size; j++) {
            if (arr[j] < arr[min_index]) min_index = j;
        }

        swap(arr + min_index, arr + i);
    }
}


double test(data_t *arr, int size, sort_t sort) {
    clock_t t1 = clock();
    (*sort)(arr, size);
    clock_t t2 = clock();
    return 1000.0 * (t2 - t1) / CLOCKS_PER_SEC;
}
