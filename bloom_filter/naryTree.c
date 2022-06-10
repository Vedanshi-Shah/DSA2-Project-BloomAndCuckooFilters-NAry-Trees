#include "naryTree.h"
#include "queue.h"
#include "stack.h"
#include "bloom.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
char* words[10000];
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
tree generate(int h){
    //srand(time(NULL));
    FILE *fptr;
    fptr=fopen("aaa.txt","w");
    int o=h;
    tree t=(tree)malloc(sizeof(node));
    t->data=words[rand()%10000];
    t->n_child=rand()%4+1;
    t->next=NULL;
    t->child=NULL;
    t->b=(bloom_filter*)malloc(sizeof(bloom_filter));
    t->b=bloom_filter_new_default(1024);
    bloom_filter_put_str(t->b,t->data);
    Qnode f=(Qnode)malloc(sizeof(element));
    Qnode r=(Qnode)malloc(sizeof(element));
    SNode top;
    init_s(&top);
    init(&f,&r);
    push(&f,&r,t);
    push_s(&top,t);
    fprintf(fptr,"%s\n",t->data);
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
            temp->data=words[rand()%10000];
            temp->n_child=rand()%4;
            temp->next=NULL;
            temp->child=NULL;
            temp->b=(bloom_filter*)malloc(sizeof(bloom_filter));
            temp->b=bloom_filter_new_default(1024);
            bloom_filter_put_str(temp->b,temp->data);
            p=temp;
            q=temp;
            push(&f,&r,temp);
            push_s(&top,temp);
            c++;
            fprintf(fptr,"%s\n",temp->data);
            for(int i=1;i<n->n_child;i++){
                node *l=(node *)malloc(sizeof(node));
                l->data=words[rand()%10000];
                l->n_child=rand()%4;
                l->next=NULL;
                l->child=NULL;
                l->b=(bloom_filter*)malloc(sizeof(bloom_filter));
                l->b=bloom_filter_new_default(1024);
                fprintf(fptr,"%s\n",temp->data);
                bloom_filter_put_str(l->b,l->data);
                q->next=l;
                q=l;
                push(&f,&r,l);
                push_s(&top,l);
                c++;
            }
            n->child=p;
        }
        h--;
    }
    printf("No. %d\n",c);
    while(size_s(top)){
        if(top->t->child==NULL){
            top->t->n_child=0;
        }
        else{
            tree n=top->t->child;
            while(n!=NULL){
                for(int i=0;i<32;i++){
                    top->t->b->vect->mem[i]=(top->t->b->vect->mem[i])|(n->b->vect->mem[i]);
                }
                n=n->next;
            }
        }
        pop_s(&top);
    }
    fclose(fptr);
    return t;
}
void search(tree root,char *key,char **arr,int i){
    if(root==NULL){
        return;
    }
    if(strcmp(root->data,key)==0){
        arr[i]=root->data;
        for(int j=0;j<=i;j++){
            printf("%s->",arr[j]);
        }
        printf("\n");
        return;
    }
    else if(bloom_filter_test_str(root->b,key)){
        arr[i]=root->data;
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
void search_withoutBloom(tree root,char *key,char **arr,int i){
    if(root==NULL){
        return;
    }
    if(strcmp(root->data,key)==0){
        arr[i]=root->data;
        for(int j=0;j<=i;j++){
            printf("%s->",arr[j]);
        }
        printf("\n");
        return;
    }
    else{
        arr[i]=root->data;
        i++;
        tree p=root->child;
        while(p){
            search_withoutBloom(p,key,arr,i);
            p=p->next;
        }
    }
    return;
}