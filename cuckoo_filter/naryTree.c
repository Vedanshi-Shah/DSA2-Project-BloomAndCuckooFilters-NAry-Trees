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
int pot(int n){
    int t=n;
    int count=0;
    while(n!=0){
        n>>=1;
        count++;
    }
    if(t && !(t&(t-1))){
        return count-1;
    }
    return count;
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
    t->data=t->contents->data;
    t->contents->next=NULL;
    t->n_child=rand()%8+1;
    t->next=NULL;
    t->child=NULL;
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
            temp->data=temp->contents->data;
            temp->contents->next=NULL;
            temp->n_child=rand()%8+1;
            temp->next=NULL;
            temp->child=NULL;
            p=temp;
            q=temp;
            push(&f,&r,temp);
            push_s(&top,temp);
            push_s(&top1,temp);
            c++;
            fprintf(fptr,"%s\n",temp->contents->data);
            for(int i=1;i<n->n_child;i++){
                node *l=(node *)malloc(sizeof(node));
                l->contents=(d*)malloc(sizeof(d));
                l->contents->data=words[rand()%10000];
                l->data=l->contents->data;
                l->contents->next=NULL;
                l->n_child=rand()%8+1;
                l->next=NULL;
                l->child=NULL;
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
    int e=c;
    while(size_s(top)){
        if(c%10000==0){
            printf("hehe: %d\n",c);
        }
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
        c--;
    }
    while(size_s(top1)){
        if(e%10000==0){
            printf("lol: %d\n",e);
        }
        tree n=top1->t;
        d *w=n->contents;
        d *b=n->contents;
        int count=0;
        while(b){
            count++;
            b=b->next;
        }
        int count2=count/0.75;
        n->c=(cuckoo_filter*)malloc(sizeof(cuckoo_filter));
        n->c=cuckoo_init(pot(count2),4,512,murmurhash,fingerprint);
        while(w){
            cuckoo_insert(n->c,w->data,strlen(w->data));
            w=w->next;
        }
        pop_s(&top1);
        e--;
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
    else if(cuckoo_lookup(root->c,key,strlen(key))){
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

void search_withoutCuckoo(tree root,char *key,char **arr,int i){
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
            search_withoutCuckoo(p,key,arr,i);
            p=p->next;
        }
    }
    return;
}

void delete(tree *root,char *key, SNode top,int *f,tree oroot){
    if(*root==NULL){
        return;
    }
    else if(strcmp((*root)->data,key)==0){
        printf("%s\n",(*root)->data);
        *f=1;
        d* temp;
        d *temp2=(*root)->contents;
        while(size_s(top)){
            temp=temp2;
            while(temp){
                cuckoo_delete(top->t->c,temp->data,strlen(temp->data));
                temp=temp->next;
            }
            pop_s(&top);
        }
        if(*root==oroot){
            root=NULL;
        }
    }
    else if(cuckoo_lookup((*root)->c,key,strlen(key))){
        push_s(&top,*root);
        tree curr=(*root)->child;
        tree prev=(tree)malloc(sizeof(node));
        prev=NULL;
        while(curr){
            *f=0;
            delete(&curr,key,top,f,oroot);
            if(*f==0){
                prev=curr;
                curr=curr->next;
            }
            else{
                if(prev){
                    prev->next=curr->next;
                }
                else{
                    (*root)->child=curr->next;
                }
                tree b=curr;
                curr=curr->next;
                free(b);
            }
        }
    }
    return;
}

void delete_node(tree root,char *key){
    SNode top;
    init_s(&top);
    int f=0;
    delete(&root,key,top,&f,root);
}