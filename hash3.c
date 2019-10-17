#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Record{
    int key;
    char name[20];
} record;
typedef struct Node{
    int key,hashvalue;
    struct Node *next;
} node;
int w=7,r=3;
node *start, *start2;

void insert(node *head,int key,int val);
void delete(node *head,int key);
int peek(node* head,int key);
void free_list(node *head);
int h1(int k);
int h2(int k);
int double_hashing(int k, int i);
int gcd(int a, int b);

int main() {
    srand(time(NULL));
    int k,i,cnt;
    record *table[1<<r];
    start = malloc(sizeof(node));
    start->key =0;
    start2 = malloc(sizeof(node));
    start2->key =0;
    for(k=1;k<=10;k++) {
        for(i =0;i<1<<r;i++)
            printf("%2d ",double_hashing(k,i));
        printf("\n");
    }
    for(cnt=0;cnt<1<<r;cnt++) table[cnt] = malloc(sizeof(record));

    for(cnt=0;cnt<1<<r;cnt++) free(table[cnt]);
    free_list(start);
    free_list(start2);
    return 0;
}
int h1(int k) {
    if(peek(start,k)!=-1) return peek(start,k);
    int result,A;
    A=rand()%(1<<(w-1));
    if(A%2==0) A++;
    A+=1<<(w-1);
    result = ((A*k)%(1<<w))>>(w-r);
    insert(start,k,result);
    return result;
}
int h2(int k) {
    if(peek(start2,k)!=-1) return peek(start2,k);
    int result,A;
    do {
    A=rand()%(1<<(w-1));
    if(A%2==0) A++;
    A+=1<<(w-1);
    result = ((A*k)%(1<<w))>>(w-r);
    } while(gcd(result,1<<r)>1);
    insert(start2,k,result);
    return result;
}
int double_hashing(int k, int i){
    return (h1(k)+i*h2(k))%(1<<r);
}
void insert(node *head,int key,int val) {
    node *new = malloc(sizeof(node)),*cur = head;
    new->key= key;
    new->hashvalue= val;
    while(cur->next!=NULL) cur = cur->next;
    cur->next = new;
    return;
}
void delete(node* head, int key) {
    node *prev = head, *cur;
    if(head->next==NULL) {
        printf("delete can be executed\n");
        return;
    }
    cur = prev->next;
    if(cur->key == key) {
        free(cur);
        prev->next =NULL;
    }
    while(cur->next!=NULL) {
        prev = prev->next;
        cur = prev->next;
        if(cur->key == key) {
            prev->next =cur->next;
            free(cur);
            break;
        }
    }
    return;
}
int peek(node *head,int key) {
    node *cur;
    int result = -1;
    if(head->next==NULL) {
        printf("Err: peek can be executed\n");
        return -1;
    }
    cur=head->next;
    if(cur->key == key) result = cur->hashvalue;
    while(cur->next!=NULL) {
        cur = cur->next;
        if(cur->key == key) {
            result = cur->hashvalue;
            break;
        }
    }
    return result;
}

void free_list(node *head) {
    node *prev,*cur = head;
    prev = cur;
    while(cur = cur->next) {
        free(prev);
        prev=cur;
    }
    free(cur);
    return; 
}
int gcd(int a, int b) {
    int result;
    while(a>0 && b>0){
        if(b>a) b= b%a;
        else a = a%b;
    }
    if(a==0) result=b;
    else result =a;
    return result;
}
