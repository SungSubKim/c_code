#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node_struct {
    struct node_struct *next;
    int data;
} node;

void insert(node *lst, int x);
void delete(node *lst, int x);
void print(node *lst);
void free_list(node *lst);
int isort(int *arr, int len);

int main() {
    srand(time(NULL));
    node *lst = malloc(sizeof(node));
    int cnt,num[100];
    for(cnt=0;cnt<100;cnt++) num[cnt]= rand()%20;       //step1
    isort(num,100);
    for(cnt=0;cnt<100;cnt++) insert(lst,num[cnt]);      //step1
    print(lst);                                         //step1
    for(cnt=0;cnt<3;cnt++) {
        delete(lst,num[rand()%100]);                        //step2
        print(lst);                                         //step3
    }
    free_list(lst);
    return 0;
}

int isort(int *arr,int len) {
    int cnt,cnt2,key,comp=0;
    for(cnt=1;cnt<len;cnt++) {
        key = arr[cnt];
        cnt2 = cnt-1;
        comp++;
        while(arr[cnt2]>key && cnt2>=0) {
            arr[cnt2+1] = arr[cnt2];
            cnt2--;
            comp++;
        }
        arr[cnt2+1] = key;
    }
    //printf("INSERTION-SORT is finished. The number of comparision is %d \n",comp);
    return comp;
}
void insert(node *lst, int x) {
    node *new = malloc(sizeof(node));
    new->data= x;
    while(lst->next!=NULL) {
        lst = lst->next;
    }
    lst->next = new;
}

void delete(node *lst, int x) {
    printf("%d will be deleted\n",x);
    node *prev,*tmp;
    prev = lst;
    while((lst=lst->next)!=NULL) {
        if(lst->data==x) {
            prev->next = lst->next;
            free(lst);
            lst=prev;
        }
        else prev = lst;
    }
}
void print(node *lst) {
    node *now=lst, *prev;
    int len=0,cnt=0;
    while(now=now->next) len++;
    now=lst;
    printf("first line\n");
    while((now=now->next)!=NULL) {
        cnt++;
        if(len/2+1==cnt) printf("\nsecond line\n");
        printf("%3d",now->data);
    }
    printf("\nend\n\n");
    return;
}

void free_list(node *lst) {
    node *prev;
    prev = lst;
    while(lst=lst->next) {
        free(prev);
        prev = lst;
    }
    free(lst);
    return;
}


