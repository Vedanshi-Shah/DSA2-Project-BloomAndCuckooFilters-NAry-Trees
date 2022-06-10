#include "naryTree.h"
#include "cuckoo.h"
#include "hashutil.h"
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
int main(){
    parse();
    tree t=generate(6);
    char **arr=(char **)malloc(sizeof(char *)*10);
    for(int i=0;i<10;i++){
        arr[i]=(char *)malloc(sizeof(char)*100);
    }
    char *key="forced";
    search(t,key,arr,0);
    //printf("%d\n",cuckoo_lookup(t->c,"aaazzz",strlen("aaazzz")));
    return 0;
}