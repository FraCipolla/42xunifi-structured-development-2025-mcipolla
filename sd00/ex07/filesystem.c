#include "filesystem.h"
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

FSNode *create_file(const char *name, int size) {
    FSNode *new = (FSNode *)malloc(sizeof(FSNode));
    new->name = strdup(name);
    new->size = size;
    new->parent = NULL;
    new->next = NULL;
    new->children = NULL;
    return new;
};

FSNode *create_folder(const char *name) {
    FSNode *new = (FSNode *)malloc(sizeof(FSNode));
    new->name = strdup(name);
    new->size = 0;
    new->parent = NULL;
    new->next = NULL;
    new->children = NULL;
    return new;
};

void add_child(FSNode *parent, FSNode *child) {
    if (!parent || !child) return;

    child->parent = parent;
    if (!parent->children) {
        parent->children = child;
        return ;
    }
    FSNode *tmp = parent->children;
    while (tmp && tmp->next) {
        tmp = tmp->next;
    }
    tmp->next = child;
}

FSNode *get_children(const FSNode *parent) {
    return parent->children;
}

FSNode *get_sibling(const FSNode *node) {
    return node->parent->children;
}

#if TEST
#include <stdio.h>
int main(void) {
    FSNode *head = create_folder("top");
    add_child(head, create_file("file1", 2));
    add_child(head, create_file("file2", 2));
    add_child(head, create_file("file3", 2));
    FSNode *sub1 = create_folder("sub1");
    add_child(sub1, create_file("file1", 2));
    add_child(sub1, create_file("file2", 2));
    add_child(sub1, create_file("file3", 2));
    FSNode *sub2 = create_folder("sub2");
    add_child(sub2, create_file("file1", 2));
    add_child(sub2, create_file("file2", 2));
    add_child(sub2, create_file("file3", 2));
    add_child(sub2, sub1);
    add_child(head, sub2);

    int tot = compute_total_size(head);
    printf("size %d\n", tot);
    print_structure(head, 0);
    free_filesystem(head);
}
#endif