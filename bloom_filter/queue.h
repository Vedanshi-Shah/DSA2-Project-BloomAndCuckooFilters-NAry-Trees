typedef struct element{
    tree ele;
    struct element *next;
}element;
typedef element *Qnode;
void init(Qnode *f,Qnode *r);
void push(Qnode *f,Qnode *r,tree node);
tree pop(Qnode *f,Qnode *r);
int size(Qnode f,Qnode r);
