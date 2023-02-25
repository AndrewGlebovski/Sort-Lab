#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>


typedef int data_t;

typedef data_t (*pivot_t)(data_t *begin, data_t* end);


data_t get_pivot(data_t *begin, data_t* end);

data_t *partition(data_t *begin, data_t* end, data_t pivot);

void quick_sort(data_t *begin, data_t* end, pivot_t pivot_func);

data_t bubble_sort(data_t *begin, data_t *end, int step);

data_t get_median_median(data_t *begin, data_t *end, int step);

data_t median_median_pivot(data_t *begin, data_t* end);

data_t random_pivot(data_t *begin, data_t* end);

data_t center_pivot(data_t *begin, data_t* end);

data_t three_median_pivot(data_t *begin, data_t* end);

double test(data_t *arr, int size, pivot_t pivot_func);



int main() {
    srand(time(NULL));

    FILE *mm_output = fopen("mm.time", "w"), *m3_output = fopen("m3.time", "w"), *ra_output = fopen("ra.time", "w"), *ce_output = fopen("ce.time", "w");

    data_t *origin = (data_t *) calloc(10000000, sizeof(data_t));
    data_t *arr = (data_t *) calloc(10000000, sizeof(data_t));

    for (int size = 1000; size <= 10000000; size += 100000) {
        double mm_time = 0, m3_time = 0, ra_time = 0, ce_time = 0;

        printf("%i\n", size);

        for (int j = 1; j <= 5; j++) {
            for (int i = 0; i < size; i++) {
                origin[i] = rand();
                arr[i] = origin[i];
            }

            mm_time += test(arr, size, median_median_pivot);

            for (int i = 0; i < size; i++) arr[i] = origin[i];

            m3_time += test(arr, size, three_median_pivot);

            for (int i = 0; i < size; i++) arr[i] = origin[i];

            ra_time += test(arr, size, random_pivot);

            for (int i = 0; i < size; i++) arr[i] = origin[i];

            ce_time += test(arr, size, center_pivot);
        }

        fprintf(mm_output, "%.2f\n", mm_time / 5);
        fprintf(m3_output, "%.2f\n", m3_time / 5);
        fprintf(ra_output, "%.2f\n", ra_time / 5);
        fprintf(ce_output, "%.2f\n", ce_time / 5);
    }

    free(origin);
    free(arr);

    fclose(mm_output);
    fclose(m3_output);
    fclose(ra_output);
    fclose(ce_output);

    return 0;
}


inline data_t *min(data_t *a, data_t *b) {
    if (a <= b) return a;
    return b;
}


data_t bubble_sort(data_t *begin, data_t *end, int step) {
	for (data_t *i = begin; i <= end - step; i += step) {
        int flag = 1;

        for (data_t *j = i; j <= end - (i - begin + step); j += step) {
            if (*(j + step) < *j) {
                data_t swap = *(j + step);
                *(j + step) = *j;
                *j = swap;

                flag = 0;
            }
        }

        if (flag) break;
    }

    return *min(begin + step * 2, end);
}


data_t get_median_median(data_t *begin, data_t *end, int step) {
    int range = step * 5;

    if (end - begin < range) return bubble_sort(begin, end, step);

    for (data_t *i = begin; i <= end; i += range)
        bubble_sort(i, min(i + range - 1, end), step);

    return get_median_median(begin + step * 2, end, range);
}


data_t median_median_pivot(data_t *begin, data_t* end) {
    return get_median_median(begin, end, 1);
}


data_t random_pivot(data_t *begin, data_t* end) {
    return begin[rand() % (end - begin + 1)];
}


data_t center_pivot(data_t *begin, data_t* end) {
    return begin[(end - begin + 1) / 2];
}


inline void swap(data_t *a, data_t *b) {
    data_t tmp = *a;
    *a = *b;
    *b = tmp;
}


data_t three_median_pivot(data_t *begin, data_t* end) {
    if (*begin > *end) swap(begin, end);
    if (*begin > begin[(end - begin + 1) / 2]) swap(begin, begin + (end - begin + 1) / 2);
    if (begin[(end - begin + 1) / 2] > *end) swap(end, begin + (end - begin + 1) / 2);

    return begin[(end - begin + 1) / 2];
}


data_t *partition(data_t *begin, data_t* end, data_t pivot) {
    while (begin <= end) {
        while (*begin < pivot) begin++;
        while (*end > pivot) end--;

        if (begin > end) return end;

        data_t swap = *begin;
        *begin = *end;
        *end = swap;

        begin++;
        end--;
    }

    return end;
}


void quick_sort(data_t *begin, data_t* end, pivot_t pivot_func) {
    if (begin >= end) return;

    data_t *delim = partition(begin, end, (*pivot_func)(begin, end));

    quick_sort(begin, delim, pivot_func);
    quick_sort(delim + 1, end, pivot_func);
}


double test(data_t *arr, int size, pivot_t pivot_func) {
    clock_t t1 = clock();
    quick_sort(arr, arr + size - 1, pivot_func);
    clock_t t2 = clock();
    return 1000.0 * (t2 - t1) / CLOCKS_PER_SEC;
}
