#ifndef GRADE_MAP_H
#define GRADE_MAP_H

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    PLUSMINUS,
    PASSFAIL,
    STANDARD
}   GradeMapper;

typedef struct s_node {
    short   grade;
    int     count;
    struct s_node  *next;
}   GradeNode;

void map_scores(const int *scores, int size, GradeMapper mapper, const char **mapped_grades);
GradeNode *compute_distribution(const char **mapped_grades, int size);
void print_distribution(GradeNode *head);
void free_distribution(GradeNode *head);

#endif