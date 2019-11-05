#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void* rand_arr(int size);
void msort(int *arr,int size);
void* sorted(int size);
void* reverse(int size);
void print_arr(int *arr);

int comp2=0;
int main(){
    int cnt,num;
    srand(time(NULL));
    int *arr1 = rand_arr(100), *arr2 =sorted(100), *arr3 = reverse(100);

    printf("1) Filled by rand() \n");
    print_arr(arr1);
    msort(arr1,100);
    printf("MERGE-SORT is finished. The number of comparision is %d \n",comp2);
    print_arr(arr1);
    comp2=0;

    printf("2) Already sorted\n");
    print_arr(arr2);
    msort(arr2,100);
    printf("MERGE-SORT is finished. The number of comparision is %d \n",comp2);
    print_arr(arr2);
    comp2=0;

    printf("3) Reversely sorted\n");
    print_arr(arr3);
    msort(arr3,100);
    printf("MERGE-SORT is finished. The number of comparision is %d \n",comp2);
    print_arr(arr3);

    free(arr1);
    free(arr2);
    free(arr3);
    return 0;
}
void print_arr(int *arr) {
    int cnt;
    for(cnt=0;cnt<100;cnt++) {
        if(cnt%40==0&&cnt!=0) printf("\n");
        printf("%4d",arr[cnt]);
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
    for(cnt=0;cnt<size; cnt++) result[cnt]=rand()%1000;
    return result;
}
void msort(int *arr, int size) {
    if(size==1) return;
    int *part1 = malloc(sizeof(int)*size/2), 
        *part2 = malloc(sizeof(int)*(size-size/2)),cnt0;
    for(cnt0=0;cnt0<size;cnt0++) {
        if(cnt0<size/2) part1[cnt0] = arr[cnt0];
        else part2[cnt0-size/2] = arr[cnt0];
    }
    msort(part1,size/2);
    msort(part2,size-size/2);
    int cnt=0,cnt2=0,cnt3=0;
    while(cnt3<size) {
        if(cnt2 >= size-size/2) arr[cnt3] = part1[cnt++];//part2 is sold
        else if(cnt<size/2 && part1[cnt]<part2[cnt2]) arr[cnt3] = part1[cnt++];
        //part1이 남아있고 part1의 숫자가 충분히 작을떄가져옴
        else arr[cnt3] = part2[cnt2++];//part2가 남아있고더작은가보다
        cnt3++;
    }
    comp2++;
    free(part1);
    free(part2);
}
