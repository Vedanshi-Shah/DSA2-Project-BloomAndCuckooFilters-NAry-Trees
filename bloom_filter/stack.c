#include "naryTree.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

void init_s(SNode *st){
    *st=NULL;
}
void push_s(SNode *st,tree n){
    SNode temp=(SNode)malloc(sizeof(ele));
    temp->t=n;
    temp->next=NULL;
    if(*st==NULL){
        *st=temp;
        return;
    }
    temp->next=*st;
    *st=temp;
    return;
}

tree pop_s(SNode *st){
    if(*st==NULL){
        return NULL;
    }
    tree n=(*st)->t;
    (*st)=(*st)->next;
}

int size_s(SNode st){
    if(st==NULL){
        return 0;
    }
    int count=1;
    SNode p=st;
    while(p){
        count++;
        p=p->next;
    }
    return count;
}
