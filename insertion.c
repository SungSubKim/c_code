#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void* rand_arr(int size);
int isort(int *arr, int len);
void msort(int *arr,int size);
void* sorted(int size);
void* reverse(int size);
void print_arr(int *arr);

int comp2=0;
int main(){
    int cnt,num;
    srand(time(NULL));
    int *arr1 = rand_arr(300), *arr2 =sorted(300), *arr3 = reverse(300);
    
    printf("1) Filled by rand() \n");
    print_arr(arr1);
    num = isort(arr1,300);
    print_arr(arr1);

    printf("2) Already sorted\n");
    print_arr(arr2);
    num = isort(arr2,300);
    print_arr(arr2);

    printf("3) Reversely sorted\n");
    print_arr(arr3);
    num = isort(arr3,300);
    print_arr(arr3);

    free(arr1);
    free(arr2);
    free(arr3);
    return 0;
}
void print_arr(int *arr) {
    int cnt;
    for(cnt=0;cnt<300;cnt++) {
        if(cnt%25==0&&cnt!=0) printf("\n");
        printf("%7d",arr[cnt]);
    }
    printf("\n\n");
}
void* sorted(int size) {
    int *result = malloc(sizeof(int)*size),cnt;
    for(cnt=0;cnt<size; cnt++)result[cnt]=cnt+1;
    return result;
}
void* reverse(int size) {
    int *result = malloc(sizeof(int)*size),cnt;
    for(cnt=0;cnt<size; cnt++)result[cnt]=300-cnt;
    return result;
}
void* rand_arr(int size) {
    int *result = malloc(sizeof(int)*size),cnt;
    for(cnt=0;cnt<size; cnt++)result[cnt]=rand()%10000;
    return result;
}
int isort(int *arr,int len) {
    int cnt,cnt2,key,comp=0;
    for(cnt=1;cnt<len;cnt++) {
        key = arr[cnt];
        cnt2 = cnt-1;
        comp++;
        while(arr[cnt2]<key && cnt2>=0) {
            arr[cnt2+1] = arr[cnt2];
            cnt2--;
            comp++;
        }
        arr[cnt2+1] = key;
    }
    printf("INSERTION-SORT is finished. The number of comparision is %d \n",comp);
    return comp;
}
