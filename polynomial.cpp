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
    srand(time(NULL));

    FILE *bubble_output = fopen("bubble.time", "w"), *insert_output = fopen("insertion.time", "w"), *select_output = fopen("selection.time", "w");

    data_t *origin = (data_t *) calloc(1000000, sizeof(data_t));
    data_t *arr = (data_t *) calloc(1000000, sizeof(data_t));

    for (int size = 100000; size <= 1000000; size += 100000) {
        double bubble_time = 0, insert_time = 0, select_time = 0;

        printf("%i\n", size);

        for (int j = 1; j <= 1; j++) {
            for (int i = 0; i < size; i++) {
                origin[i] = rand();
                arr[i] = origin[i];
            }

            bubble_time += test(arr, size, &bubble_sort);

            for (int i = 0; i < size; i++) arr[i] = origin[i];

            insert_time += test(arr, size, &insertion_sort);

            for (int i = 0; i < size; i++) arr[i] = origin[i];

            select_time += test(arr, size, &selection_sort);
        }

        fprintf(bubble_output, "%.2f\n", bubble_time / 5);
        fprintf(insert_output, "%.2f\n", insert_time / 5);
        fprintf(select_output, "%.2f\n", select_time / 5);
    }

    free(origin);
    free(arr);

    fclose(bubble_output);
    fclose(insert_output);
    fclose(select_output);

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
