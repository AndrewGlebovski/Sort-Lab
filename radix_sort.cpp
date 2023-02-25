#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>


typedef int data_t;
const int LABELS_SIZE = 256;
typedef void (*sort_t)(data_t **arr, int size);


void lsd_sort(data_t **arr, int size);

void msd_sort(data_t **arr, int size);

data_t *counting_sort(data_t *arr, int size, int shift);

double test(data_t **arr, int size, sort_t sort);


int main() {
    srand(time(NULL));

    FILE *lsd_output = fopen("lsd.time", "w"), *msd_output = fopen("msd.time", "w");

    data_t *origin = (data_t *) calloc(10000000, sizeof(data_t));

    for (int size = 1000; size <= 10000000; size += 100000) {
        double lsd_time = 0, msd_time = 0;

        printf("%i\n", size);

        for (int j = 1; j <= 5; j++) {
            data_t *arr = (data_t *) calloc(size, sizeof(data_t));

            for (int i = 0; i < size; i++) {
                origin[i] = rand();
                arr[i] = origin[i];
            }

            lsd_time += test(&arr, size, &lsd_sort);

            free(arr);

            arr = (data_t *) calloc(size, sizeof(data_t));

            for (int i = 0; i < size; i++) arr[i] = origin[i];

            msd_time += test(&arr, size, &msd_sort);

            free(arr);
        }

        fprintf(lsd_output, "%.2f\n", lsd_time / 5);
        fprintf(msd_output, "%.2f\n", msd_time / 5);
    }

    free(origin);

    fclose(lsd_output);
    fclose(msd_output);

    return 0;
}


void lsd_sort(data_t **arr, int size) {
    for (int i = 0; i < 4; i++) *arr = counting_sort(*arr, size, i * 8);
}


void msd_sort(data_t **arr, int size) {
    for (int i = 3; i >= 0; i--) *arr = counting_sort(*arr, size, i * 8);
}


data_t *counting_sort(data_t *arr, int size, int shift) {
    unsigned int *labels = (unsigned int *) calloc(LABELS_SIZE, sizeof(int));
    data_t *sorted = (data_t *) calloc(size, sizeof(data_t));

    for (int i = 0; i < size; i++) labels[(arr[i] >> shift) & 0xFF]++;

    for (int i = 1; i < LABELS_SIZE; i++) labels[i] += labels[i - 1];

    for (int i = size - 1; i >= 0; i--) {
        labels[(arr[i] >> shift) & 0xFF]--;
        sorted[labels[(arr[i] >> shift) & 0xFF]] = arr[i];
    }

    free(labels);
    free(arr);

    return sorted;
}


double test(data_t **arr, int size, sort_t sort) {
    clock_t t1 = clock();
    (*sort)(arr, size);
    clock_t t2 = clock();
    return 1000.0 * (t2 - t1) / CLOCKS_PER_SEC;
}
