#include "naryTree.h"
#include "bloom.h"
#include<stdio.h>
#include <stdlib.h>
#include <inttypes.h>
int main(){
    //printf("ret");
    parse();
    tree t=generate(23);
    // printf("%s\n",t->data);
    // printf("%s\n",t->child->data);
    //char *k=t->child->child->child->next->data;
    //printf("%s\n",t->child->child->next->data);
    //printf("bef\n");
    
    char **arr=(char **)malloc(sizeof(char *)*10);
    for(int i=0;i<10;i++){
        arr[i]=(char *)malloc(sizeof(char)*100);
    }
    char *key="azerbaijan";
    search_withoutBloom(t,key,arr,0);
    return 0;
}