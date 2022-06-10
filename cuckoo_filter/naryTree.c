#include "naryTree.h"
#include "queue.h"
#include "stack.h"
#include "cuckoo.h"
#include "hashutil.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
char *words[10000];
void parse(){
    FILE *fptr;
    fptr=fopen("words.txt","r");
    words[0]=(char *)malloc(sizeof(char)*100);
    int i=0;
    while(fgets(words[i],100,fptr)!=NULL){
        if(words[i][strlen(words[i])-1]=='\n'){
            words[i][strlen(words[i])-1]='\0';
        }
        i++;
        words[i]=(char *)malloc(sizeof(char)*100);
    }
    fclose(fptr);
}
d* merge_ll(d* h1,d* h2){
    d* p=(d*)malloc(sizeof(d));
    p->data=h1->data;
    h1=h1->next;
    d *q=p;
    p->next=NULL;
    while(h1){
        d *temp=(d *)malloc(sizeof(d));
        temp->data=h1->data;
        temp->next=NULL;
        q->next=temp;
        q=temp;
        h1=h1->next;
    }
    while(h2){
        d *temp=(d *)malloc(sizeof(d));
        temp->data=h2->data;
        temp->next=NULL;
        q->next=temp;
        q=temp;
        h2=h2->next;
    }
    return p;
}
tree generate(int h){
    //srand(time(NULL));
    FILE *fptr;
    fptr=fopen("aaa.txt","w");
    int o=h;
    tree t=(tree)malloc(sizeof(node));
    t->contents=(d*)malloc(sizeof(d));
    t->contents->data=words[rand()%10000];
    t->contents->next=NULL;
    t->n_child=rand()%10+1;
    t->next=NULL;
    t->child=NULL;
    t->c=(cuckoo_filter *)malloc(sizeof(cuckoo_filter));
    t->c=cuckoo_init(16,4,512,murmurhash,fingerprint);
    cuckoo_insert(t->c,t->contents->data,strlen(t->contents->data));
    Qnode f=(Qnode)malloc(sizeof(element));
    Qnode r=(Qnode)malloc(sizeof(element));
    SNode top;
    SNode top1;
    init_s(&top);
    init_s(&top1);
    init_Q(&f,&r);
    push(&f,&r,t);
    push_s(&top,t);
    push_s(&top1,t);
    fprintf(fptr,"%s\n",t->contents->data);
    //printf("%d\n",t->n_child);
    if(h==0){
        return NULL;
    }
    h--;
    int c=1;
    while(h && size(f,r)){
        int z=size(f,r);
        while(z--){
            tree n=pop(&f,&r);
            node *p,*q;
            if(n->n_child==0){
                continue;
            }
            node *temp=(node *)malloc(sizeof(node));
            temp->contents=(d*)malloc(sizeof(d));
            temp->contents->data=words[rand()%10000];
            temp->contents->next=NULL;
            temp->n_child=rand()%10+1;
            temp->next=NULL;
            temp->child=NULL;
            temp->c=(cuckoo_filter *)malloc(sizeof(cuckoo_filter));
            temp->c=cuckoo_init(16,4,512,murmurhash,fingerprint);
            cuckoo_insert(temp->c,temp->contents->data,strlen(temp->contents->data));
            p=temp;
            q=temp;
            push(&f,&r,temp);
            push_s(&top,temp);
            push_s(&top1,temp);
            c++;
            fprintf(fptr,"%s\n",temp->contents->data);
            //printf("%d\n",temp->n_child);
            for(int i=1;i<n->n_child;i++){
                node *l=(node *)malloc(sizeof(node));
                l->contents=(d*)malloc(sizeof(d));
                l->contents->data=words[rand()%10000];
                l->contents->next=NULL;
                l->n_child=rand()%10+1;
                l->next=NULL;
                l->child=NULL;
                l->c=cuckoo_init(16,4,512,murmurhash,fingerprint);
                cuckoo_insert(l->c,l->contents->data,strlen(l->contents->data));
                fprintf(fptr,"%s\n",l->contents->data);
                q->next=l;
                q=l;
                push(&f,&r,l);
                push_s(&top,l);
                push_s(&top1,l);
                c++;
            }
            n->child=p;
        }
        h--;
    }
    printf("No: %d\n",c);
    while(size_s(top)){
        if(top->t->child==NULL){
            top->t->n_child=0;
        }
        else{
            tree n=top->t->child;
            while(n){
                top->t->contents=merge_ll(top->t->contents,n->contents);
                n=n->next;
            }
        }
        pop_s(&top);
    }
    while(size_s(top1)){
        tree n=top1->t;
        d *w=n->contents;
        w=w->next;
        while(w){
            cuckoo_insert(n->c,w->data,strlen(w->data));
            w=w->next;
        }
        pop_s(&top1);
    }
    fclose(fptr);
    return t;
}

void search(tree root,char *key,char **arr,int i){
    if(root==NULL){
        return;
    }
    if(strcmp(root->contents->data,key)==0){
        arr[i]=root->contents->data;
        for(int j=0;j<=i;j++){
            printf("%s->",arr[j]);
        }
        printf("\n");
        return;
    }
    else if(cuckoo_lookup(root->c,key,strlen(key))){
        arr[i]=root->contents->data;
        i++;
        tree p=root->child;
        while(p){
            search(p,key,arr,i);
            p=p->next;
        }
    }
    else{
        return;
    }
}

void search_withoutCuckoo(tree root,char *key,char **arr,int i){
    if(root==NULL){
        return;
    }
    if(strcmp(root->contents->data,key)==0){
        arr[i]=root->contents->data;
        for(int j=0;j<=i;j++){
            printf("%s->",arr[j]);
        }
        printf("\n");
        return;
    }
    else{
        arr[i]=root->contents->data;
        i++;
        tree p=root->child;
        while(p){
            search_withoutCuckoo(p,key,arr,i);
            p=p->next;
        }
    }
    return;
}