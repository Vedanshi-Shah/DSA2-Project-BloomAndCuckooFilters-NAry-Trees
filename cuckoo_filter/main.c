#include "naryTree.h"
#include "cuckoo.h"
#include "hashutil.h"
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <time.h>
int main(){
    parse();
    tree t=generate(8);
    struct timespec begin, end;
    char **arr=(char **)malloc(sizeof(char *)*12);
    for(int i=0;i<10;i++){
        arr[i]=(char *)malloc(sizeof(char)*100);
    }
    //search(t,"neighborhood",arr,0);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin);
    delete_node(t,"neighborhood");
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    long seconds = end.tv_sec - begin.tv_sec;
    long nanoseconds = end.tv_nsec - begin.tv_nsec;
    double elapsed = seconds + nanoseconds*1e-9;
    printf("Time to delete: %.7f\n",elapsed);
    printf("%d\n",cuckoo_lookup(t->c,"neighborhood",strlen("neighborhood")));
    search(t,"neighborhood",arr,0);
    // //char **arr=(char **)malloc(sizeof(char *)*12);
    // for(int i=0;i<10;i++){
    //     arr[i]=(char *)malloc(sizeof(char)*100);
    // }
    // search(t,"neighborhood",arr,0);
    //printf("%s\n",t->child->child->data);
    //printf("%d\n",cuckoo_lookup(t->child->c,"arrested",strlen("arrested")));
    
    // char **arr2=(char **)malloc(sizeof(char *)*12);
    // for(int i=0;i<10;i++){
    //     arr2[i]=(char *)malloc(sizeof(char)*100);
    // }
    // char *key="neighborhood";
    // struct timespec begin, end;
    // clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin);
    // search(t,key,arr,0);
    // clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    // long seconds = end.tv_sec - begin.tv_sec;
    // long nanoseconds = end.tv_nsec - begin.tv_nsec;
    // double elapsed = seconds + nanoseconds*1e-9;
    // printf("Time 1:%.7f\n",elapsed);
    // clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin);
    // search_withoutCuckoo(t,key,arr2,0);
    // clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    // seconds = end.tv_sec - begin.tv_sec;
    // nanoseconds = end.tv_nsec - begin.tv_nsec;
    // elapsed = seconds + nanoseconds*1e-9;
    // printf("Time 2:%.7f\n",elapsed);
    return 0;
}