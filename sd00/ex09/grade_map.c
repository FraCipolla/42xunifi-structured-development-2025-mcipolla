#include "grade_map.h"
#include <stdio.h>

static char *grade_table[] = {
    "A+",
    "A",
    "A-",
    "B+",
    "B",
    "B-",
    "C+",
    "C",
    "C-",
    "D+",
    "D",
    "D-",
    "F",
    "P"
};

char *grade_plusminus(int score) {
    switch (score) {
        case 0 ... 59: return grade_table[12];
        case 60 ... 62: return grade_table[11];
        case 63 ... 66: return grade_table[10];
        case 67 ... 69: return grade_table[9];
        case 70 ... 72: return grade_table[8];
        case 73 ... 76: return grade_table[7];
        case 77 ... 79: return grade_table[6];
        case 80 ... 82: return grade_table[5];
        case 83 ... 86: return grade_table[4];
        case 87 ... 89: return grade_table[3];
        case 90 ... 92: return grade_table[2];
        case 93 ... 96: return grade_table[1];
        case 97 ... 100: return grade_table[0];
    }
}

char *grade_passfail(int score) {
    switch (score) {
        case 0 ... 59: return grade_table[12];
        case 60 ... 100: return grade_table[13];
    }
}

char *grade_standard(int score) {
    switch (score) {
        case 0 ... 59: return grade_table[12];
        case 60 ... 69: return grade_table[10];
        case 70 ... 79: return grade_table[7];
        case 80 ... 89: return grade_table[4];
        case 90 ... 100: return grade_table[1];
    }
}

void map_scores(const int *scores, int size, GradeMapper mapper, const char **mapped_grades) {
    static char* (*function_ptr[])(int) = {
        &grade_plusminus,
        &grade_passfail,
        &grade_standard
    };
    for (int i = 0; i < size; i++) {
        mapped_grades[i] = function_ptr[mapper](scores[i]);
    }
}

#if TEST
int main(void) {
    const int scores[] = {66, 42, 36, 78, 100};
    const char **mapped_grades = malloc(sizeof(char *) * 6);

    map_scores(scores, 5, PLUSMINUS, mapped_grades);
    
    GradeNode *node = compute_distribution(mapped_grades, 5);
    print_distribution(node);
    free_distribution(node);

    free(mapped_grades);
}
#endif