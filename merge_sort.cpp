#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>


typedef int data_t;


void merge_sort(data_t *org, data_t* dest, int left, int right);

double test(data_t *arr, int size);


int main() {
    srand(time(NULL));

    FILE *merge_output = fopen("merge.time", "w");

    data_t *arr = (data_t *) calloc(10000000, sizeof(data_t));

    for (int size = 1000; size <= 10000000; size += 100000) {
        double merge_time = 0;

        printf("%i\n", size);

        for (int j = 1; j <= 5; j++) {
            for (int i = 0; i < size; i++) arr[i] = rand();
            
            merge_time += test(arr, size);
        }

        fprintf(merge_output, "%.2f\n", merge_time / 5);
    }

    free(arr);

    fclose(merge_output);

    return 0;
}


void merge_sort(int *org, int* dest, int left, int right) {
    if (left == right) {
        dest[left] = org[left];
        return;
    }

    int middle = left + (right - left) / 2;

    merge_sort(org, dest, left, middle);
    merge_sort(org, dest, middle + 1, right);

    int left_index = left, right_index = middle + 1;

    for (int i = left; i <= right; i++) {
        if (left_index <= middle && right_index <= right) {
            if (org[left_index] <= org[right_index]) {
                dest[i] = org[left_index];
                left_index++;
            }
            else {
                dest[i] = org[right_index];
                right_index++;
            }
        }
        else if (left_index <= middle) {
            dest[i] = org[left_index];
            left_index++;
        }
        else if (right_index <= right) {
            dest[i] = org[right_index];
            right_index++;
        }
    }

    for (int i = left; i <= right; i++) org[i] = dest[i];
}


double test(data_t *arr, int size) {
    clock_t t1 = clock();
    
    data_t *buffer = (data_t *) calloc(size, sizeof(data_t));

    merge_sort(arr, buffer, 0, size - 1);
    
    free(buffer);
    
    clock_t t2 = clock();
    return 1000.0 * (t2 - t1) / CLOCKS_PER_SEC;
}
