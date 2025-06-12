#include "critical_windows.h"

static float average(const int *arr, int size) {
    float sum = 0;
    int valid_numbers = 0;

    for (int i = 0; i < size; i++) {
        valid_numbers++;
        sum += arr[i];
    }
    return (sum / valid_numbers);
}

int greater(int n, int max) {
    return n > max;
}

static void last_match(
    const int arr[],
    int size,
    typeof(int (const int, const int)) *compar,
    int *last,
    int value) {
    *last = -1;
    for (int i = size; i > 0; i--) {
        if (compar(arr[i], value) && *last == -1) {
            *last = i;
            return;
        }
    }
}

static int count_segments(const int *arr, int size) {
    int segments = 0;
    int len = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] >= 70) {
            len++;
        }
    }
    return (len > 2);
}

int count_critical_windows(const int *readings, int size) {
    int count = 0;
    int i = 0;
    int last;
    while (size > 5) {
        last_match(readings, 5, greater, &last, 150);
        if (last == -1) {
            if (average(readings, 5) >= 90 && count_segments(readings, 5)) {
                count++;
            }
            readings += 5;
            size -= 5;
        } else {
            size -= last + 1;
            readings += last + 1;
        }
    }
    return count;
}

#if TEST
    #include <stdio.h>
    int main(void) {
        const int r[] = {12, 54, 177, 777, 123, 56, 90, 393, 135, 76, 90, 86, 123, 78, 100, 89, 90, 140};
        printf("%d\n",count_critical_windows(r, sizeof(r) / sizeof(int)));
    }
#endif