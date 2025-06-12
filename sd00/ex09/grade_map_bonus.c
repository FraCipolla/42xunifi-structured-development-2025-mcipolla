#include "grade_map.h"

#include <stdlib.h>

/*
 * since grades cna have maximum 2 chars, I convert the value to a short int,
 * and check the corresponding bytes value of the score. Than using a table
 * I store for each grade whose value is greater than 0 the corresponding count
*/
GradeNode *compute_distribution(const char **mapped_grades, int size) {
    int count_arr[14] = {0};
    for (int i = 0; i < size; i++) {
        short *byte_map = (short *)mapped_grades[i];
        switch (*byte_map) {
            case 0x50:      count_arr[13]++; break; // case P
            case 0x46:      count_arr[12]++; break; // case F
            case 0x2D44:    count_arr[11]++; break; // case D-
            case 0x44:      count_arr[10]++; break; // case D
            case 0x2B44:    count_arr[9]++;  break; // case D+
            case 0x2D43:    count_arr[8]++;  break; // case C-
            case 0x43:      count_arr[7]++;  break; // case C
            case 0x2B43:    count_arr[6]++;  break; // case C+
            case 0x2D42:    count_arr[5]++;  break; // case B-
            case 0x42:      count_arr[4]++;  break; // case B
            case 0x2B42:    count_arr[3]++;  break; // case B+
            case 0x2D41:    count_arr[2]++;  break; // case A-
            case 0x41:      count_arr[1]++;  break; // case A
            case 0x2B41:    count_arr[0]++;  break; // case A+
        }
    }

    // grade_table. If value is == 0 we skip to the next one. If it's > 0 we get the count as short.
    short grade_table[] = {0x46,0x2D44,0x44,0x2B44,0x2D43,0x43,0x2B43,0x2D42,0x42,0x2B42,0x2D41,0x41,0x2B41};
    GradeNode *ret = NULL;
    for (int i = 0; i < 14; i++) {
        if (count_arr[i] == 0) {
            continue;
        }
        GradeNode *new = malloc(sizeof(GradeNode));
        new->next = NULL;
        new->count = count_arr[i];
        new->grade = grade_table[i];

        if (!ret) {
            ret = new;
        } else {
            GradeNode *tmp = ret;
            while (tmp->next) {
                tmp = tmp->next;
            }
            tmp->next = new;
        }
    }
    return ret;
}

void print_distribution(GradeNode *head) {
    GradeNode *tmp = head;
    while (tmp) {
        printf("Grade: %c%c -> %d\n", tmp->grade & 0XFF, tmp->grade >> 8, tmp->count);
        tmp = tmp->next;
    }
}

void free_distribution(GradeNode *head) {
    if (!head) return;

    GradeNode *tmp = head;
    while (tmp) {
        GradeNode *cpy = tmp;
        tmp = tmp->next;
        free(cpy);
    }
}