#include "bloom.h"
typedef struct node{
    char *data;
    struct node *child;
    struct node *next;
    int n_child;
    bloom_filter *b;
}node;
typedef node *tree;
void parse();
tree generate(int h);
void search(tree root,char *key,char **arr,int i);
void search_withoutBloom(tree root,char *key,char **arr,int i);