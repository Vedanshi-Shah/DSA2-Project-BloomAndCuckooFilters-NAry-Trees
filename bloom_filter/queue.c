#include "naryTree.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
void init(Qnode *f,Qnode *r){
    *f=NULL;
    *r=NULL;
}

void push(Qnode *f,Qnode *r,tree node){
    Qnode new=(Qnode)malloc(sizeof(element));
    new->ele=node;
    new->next=NULL;
    if(*f==NULL){
        (*f)=new;
        (*r)=new;
        return;
    }
    (*r)->next=new;
    (*r)=new;
    return;
}

tree pop(Qnode *f,Qnode *r){
    if((*f)==NULL){
        printf("Empty\n");
        return NULL;
    }
    tree res=(*f)->ele;
    (*f)=(*f)->next;
    return res;
}
int size(Qnode f,Qnode r){
    if(f==NULL){
        return 0;
    }
    if(f==r){
        return 1;
    }
    int count=1;
    while(f && f!=r){
        count++;
        f=f->next;
    }
    return count;
}