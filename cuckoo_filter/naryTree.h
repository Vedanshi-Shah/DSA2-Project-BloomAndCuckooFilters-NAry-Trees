#include "cuckoo.h"

typedef struct d{
    char *data;
    struct d *next;
}d;
typedef struct node{
    d *contents;
    char *data;
    struct node* child;
    struct node * next;
    int n_child;
    cuckoo_filter *c;
}node;
typedef node *tree;
void parse();
tree generate(int h);
void search(tree root,char *key,char **arr,int i);
void search_withoutCuckoo(tree root,char *key,char **arr,int i);
void delete_node(tree root,char *key);
//void delete(tree *root,char *key, SNode *top,tree *prev,tree *curr,tree parent);