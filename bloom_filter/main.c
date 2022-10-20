#include "naryTree.h"
#include "bloom.h"
#include<stdio.h>
#include <stdlib.h>
#include <inttypes.h>
int main(){
    parse();
    tree t=generate(25);
    char **arr=(char **)malloc(sizeof(char *)*10);
    for(int i=0;i<10;i++){
        arr[i]=(char *)malloc(sizeof(char)*100);
    }
    char *key="azerbaijan";
    search_withoutBloom(t,key,arr,0);
    return 0;
}