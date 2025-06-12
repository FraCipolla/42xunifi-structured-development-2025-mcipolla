#include "segmented_runs.h"

int condition(const int *arr, int size) {
    if (size < 3) return 0;

    int sequence = 1;
    for (int i = 1; i < size; i++) {
        if (arr[i] < arr[i - 1]) {
            sequence = 0;
        }
        sequence++;
        if (sequence >= 3) {
            return 1;
        }
    }
    return 0;
}

int count_segments(const int *arr, int size) {
    int segments = 0;
    int len = 0;
    int i = 0;

    while (i < size) {
        if (arr[i] == -1) {
            segments += condition(&arr[i - len], len);
            len = 0;
        } else {
            len++;
        }
        i++;
    }
    
    return (segments += condition(&arr[i - len], len));
}

#if TEST
#include <stdio.h>
int main(void) {
    int sequence[] = {2, 3, 4, -1, 5, 6, -1, 1, 5, 3, 4, -1, 2, 4, 1, 6};

    printf("%d\n", count_segments(sequence, sizeof(sequence) / sizeof(int)));
}
#endif