#include "first_last.h"

void first_last(int arr[], int size, int target, int *first, int *last) {
    *first = -1;
    *last = -1;
    for (int i = 0; i < size; i++) {
        if (arr[i] == target && *first == -1) {
            *first = i;
        } else if (arr[(size - 1) - i] == target && *last == -1) {
            *last = size -1 - i;
        }
        if (*first != -1 && *last != -1) {
            return;
        } else if (i > (size / 2)) {
            *last &= *first;
            *first &= *last;
            return;
        }
    }
}

#if TEST
    #include <stdio.h>
    int main(void) {
        int arr[] = {1, 2, 3, 4, 5, 6, 7, 2};
        int first;
        int last;

        first_last(arr, sizeof(arr) / sizeof(int), 2, &first, &last);
        printf("first: %d last: %d\n", first, last);
    }
#endif