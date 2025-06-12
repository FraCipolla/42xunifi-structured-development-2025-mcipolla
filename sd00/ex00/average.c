#include "average.h"

float average(const int *arr, int size) {
    float sum = 0;
    int valid_numbers = 0;

    for (int i = 0; i < size; i++) {
        if (arr[i] >= 0 && arr[i] <= 100) {
            valid_numbers++;
            sum += arr[i];
        }
    }
    return (sum / valid_numbers);
}


#if TEST
    #include <stdio.h>
    int main(void) {
        const int array[] = {23, 54, 100, 123, 2, 54, 643, 123, 12, 42};

        printf("average: %f\n", average(array, sizeof(array) / sizeof(int)));
    }
#endif