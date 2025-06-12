#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <stddef.h>


typedef struct s_node {
    char            *name;
    int             size;
    struct s_node   *parent;
    struct s_node   *next;
    struct s_node   *children;
}   FSNode;

FSNode *create_file(const char *name, int size);
FSNode *create_folder(const char *name);
void add_child(FSNode *parent, FSNode *child);
FSNode *get_children(const FSNode *parent);
FSNode *get_sibling(const FSNode *node);

#endif