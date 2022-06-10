typedef struct ele{
    tree t;
    struct ele *next;
}ele;
typedef ele *SNode;
void init_s(SNode *st);
void push_s(SNode *st,tree n);
tree pop_s(SNode *st);
int size_s(SNode st);