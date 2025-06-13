#include "filesystem.h"

#include <stdlib.h>
#include <stdio.h>

int compute_total_size(FSNode *node) {
    if (!node) {
        return 0;
    }

    int size = 0;
    FSNode *child = node->children;
    while (child) {
        if (child->size == 0) { // case folder
            size += compute_total_size(child);
        } else {
            size += child->size;
        }
        child = child->next;
    }
    return size;
}

void print_structure(const FSNode *node, int indent) {
    if (!node) {
        return ;
    }
    printf("%*s%s\n", indent, "", node->name);
    FSNode *child = node->children;
    while (child) {
        if (child->size == 0) { // case folder
            print_structure(child, indent + 2);
        } else {
            printf("%*s%s\n", indent + 2, "", child->name);
        }
        child = child->next;
    }
}

void free_filesystem(FSNode *node) {
    if (!node) return;

    FSNode *child = node->children;
    while(child) {
        FSNode *tmp = child;
        child = child->next;
        if (tmp->size == 0) { // case folder
            free_filesystem(tmp);
        } else {
            free(tmp->name);
            free(tmp);
        }
    }
    free(node->name);
    free(node);
}