#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int m=37,c1=1,c2=3;

int h1(int k);
int h2(int k);
int l_probing(int k, int i);
int q_probing(int k, int i);
int double_hashing(int k, int i);

int main() {
    srand(time(NULL));
    int k,i,cnt,cnt2,index,num,sum,size,max;//26가지
    int (*hashing)(int k,int i);
    char key[30][4],table[m][4];
    printf("1.Linear probing\n2.Quadratic probing\n3.Double Hashing\n-1.Exit\n");
    while(1) {        
        printf("What's your choice? ");
        scanf("%d",&num);
        switch(num%3) {
            case 1:
                printf("1.Linear prboing\n");
                hashing=l_probing;
                break;
            case 2:
                printf("2.Quadratic proboing\n");
                hashing=q_probing;
                break;
            case 0:
                printf("3.Double hashing\n");
                hashing=double_hashing;
                break;
            default:
                break;
        }
        if(num==-1) break;
        for(cnt=0;cnt<m;cnt++) table[cnt][0] = 0;
        for(cnt=0;cnt<30;cnt++) {
            for(cnt2=0;cnt2<3;cnt2++) key[cnt][cnt2] = rand()%26+97;
            key[cnt][3]='\0';
        }
        sum=0;
        for(cnt=0;cnt<30;cnt++) {
            i=0;
            while(1){
                k=key[cnt][0]+key[cnt][1]+key[cnt][2];
                index = hashing(k,i++);
                if(table[index][0]==0) {
                   //printf("T[%2d]    %s     %3d    %2d \n",index,key[cnt],k,i);
                   strcpy(table[index],key[cnt]);
                   break;
                }
            }
            sum+=i;
        }
        size =0;
        max=0;
        for(cnt=0;cnt<m;cnt++) {           
            if(table[cnt][0]>0) {
                printf("T[%2d] : %s\n",cnt,table[cnt]);
                size++;
            }
            else {
                printf("T[%2d] : \n",cnt);
                size=0;
            }
            if(size>max) max = size;
        }
        printf("Average number of probes: %2.2f\n",sum/30.0);
        printf("Size of Largest cluster : %2d\n\n",max);
    }

    return 0;
}
int h1(int k) {
    return k%m;
}
int h2(int k) {
    return 1+(k%(m-1));
}
int l_probing(int k, int i){
    return (h1(k)+i)%m;
}
int q_probing(int k, int i) {
    return (h1(k)+c1*i+c2*i*i)%m;
}
int double_hashing(int k, int i){
    return (h1(k)+i*h2(k))%m;
}
