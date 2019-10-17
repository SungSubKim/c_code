#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node{
    int key;
    char data;
} record;

int hashing(int k, int w, int r);
int main() {
    srand(time(NULL));
    int r=3, cnt;
    record *table[1<<r];
    for(cnt=0;cnt<100;cnt++)printf("hello %d\n",hashing(100,7,3));
    for(cnt=0;cnt<1<<r;cnt++) table[cnt] = malloc(sizeof(record));

    for(cnt=0;cnt<1<<r;cnt++) free(table[cnt]);
}
int hashing(int k, int w, int r) {
    int A=rand()%(1<<(w-1));
    if(A%2==0) A++;
    A+=1<<(w-1);
    return ((A*k)%(1<<w))>>(w-r);
}
