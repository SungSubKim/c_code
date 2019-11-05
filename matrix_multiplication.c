#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void *shuffled_array(int size);
void free_array(int **pr, int size);
void print_array(int **arr,int size);
void *multiply0(int **arr1, int **arr2,int size);
void *multiply(int **arr1, int**arr2,int size,int trim);
void *add(int **arr1,int **arr2,int size,int trim);
void *subtract(int **arr1,int **arr2,int size,int trim);
void *extract(int **arr,int size,int rows,int cols); 
void var_init();
long computation,num_mul,num_add,num_sub;

int size0,option;
int main() {
    srand(time(NULL));
    int option2,**arr,**arr2,**arr3;
    printf("1) Standard algorithm\n2) Recursion\n3) Strassen's method\n");
    scanf("%d",&option);
    printf("1) 4x4 matrix multiplication\n2) 8x8 matrix multiplication\n");
    scanf("%d",&option2);
    size0 = option2*4;
    arr=shuffled_array(size0);
    arr2=shuffled_array(size0);
    print_array(arr,size0);
    print_array(arr2,size0);
    var_init();
    if (option==1) {
        printf("Standard algorithm, %dx%d matrix multipliation\n",size0,size0);
        arr3= multiply0(arr,arr2,size0);
    }
    else arr3 = multiply(arr,arr2,size0,1);
    printf("The number of total computation\n%ld\nMultiplication\n%ld \nAddition\n%ld \nSubtraction\n%ld\n",
            computation,num_mul,num_add,num_sub);
    free_array(arr3,size0);
}
void var_init() {
    computation = 0,num_mul=0,num_add=0,num_sub=0;
}
void* shuffled_array(int size) {
    int cnt,cnt2;
    int **pr[2][2];
    pr[0][0]= malloc(sizeof(int*)*size);
    for(cnt=0;cnt<size;cnt++) {
        pr[0][0][cnt]=malloc(sizeof(int)*size);
        for(cnt2=0;cnt2<size;cnt2++) pr[0][0][cnt][cnt2] = rand()%1000;
    }
    return pr[0][0];
}

void free_array(int **pr,int size) {
    int cnt;
    for(cnt=0;cnt<size;cnt++) free(pr[cnt]);
    free(pr);
}
void print_array(int **pr,int size) {
    int cnt,cnt2;
    for(cnt=0;cnt<size;cnt++) {
        for(cnt2=0;cnt2<size;cnt2++) printf("%8d ",pr[cnt][cnt2]);
        printf("\n");
    }
    printf("\n");
}
void *multiply0(int **arr1, int **arr2,int size) {
    int cnt,cnt2,cnt3;
    int **result = malloc(sizeof(int*)*size);
    for(cnt=0;cnt<size;cnt++) result[cnt] = malloc(sizeof(int)*size);
    for(cnt=0;cnt<size;cnt++) for(cnt2=0;cnt2<size;cnt2++) {
        result[cnt][cnt2]=0;
        for(cnt3=0;cnt3<size;cnt3++) {
            result[cnt][cnt2]+=arr1[cnt][cnt3]*arr2[cnt3][cnt2];
            computation+=2;
            num_mul++;
            num_add++;
        }
    }
    free_array(arr1,size);
    free_array(arr2,size);
    print_array(result,size);
    return result;
}
void *multiply(int **arr1,int **arr2,int size,int trim) {
    int **part[3][2][2],**result,**tmp,**tmp2,**m[7];
    int cnt0,cnt,cnt2,cnt3;
    result = malloc(sizeof(int*)*size);
    for(cnt=0;cnt<size;cnt++) result[cnt] = malloc(sizeof(int)*size);
    if(size>1) {
        for(cnt=0;cnt<2;cnt++) for(cnt2=0;cnt2<2;cnt2++)
            part[0][cnt][cnt2]=extract(arr1,size,cnt,cnt2);        
        for(cnt=0;cnt<2;cnt++) for(cnt2=0;cnt2<2;cnt2++)
            part[1][cnt][cnt2]=extract(arr2,size,cnt,cnt2);      
        if(option==2) {
            tmp = multiply(part[0][0][0],part[1][0][0],size/2,0);
            tmp2 = multiply(part[0][0][1],part[1][1][0],size/2,0);
            part[2][0][0] = add(tmp,tmp2,size/2,1);
            tmp = multiply(part[0][0][0],part[1][0][1],size/2,0);
            tmp2 = multiply(part[0][0][1],part[1][1][1],size/2,0);
            part[2][0][1] = add(tmp,tmp2,size/2,1);
            tmp = multiply(part[0][1][0],part[1][0][0],size/2,0);
            tmp2 = multiply(part[0][1][1],part[1][1][0],size/2,0);
            part[2][1][0] = add(tmp,tmp2,size/2,1);
            tmp = multiply(part[0][1][0],part[1][0][1],size/2,0);
            tmp2 = multiply(part[0][1][1],part[1][1][1],size/2,0);
            part[2][1][1] = add(tmp,tmp2,size/2,1);
        }
        else {
            tmp = add(part[0][0][0],part[0][1][1],size/2,0);//A11+A22
            tmp2 = add(part[1][0][0],part[1][1][1],size/2,0);//B11+B22
            m[0] = multiply(tmp,tmp2,size/2,1);             //M1
            tmp = add(part[0][1][0],part[0][1][1],size/2,0);//A21+A22
            m[1] = multiply(tmp,part[1][0][0],size/2,2);    //M2,B11
            tmp = subtract(part[1][0][1],part[1][1][1],size/2,0);//B12-B22
            m[2] = multiply(part[0][0][0],tmp,size/2,3);    //M3,A11
            tmp = subtract(part[1][1][0],part[1][0][0],size/2,0);//B21-B11
            m[3] = multiply(part[0][1][1],tmp,size/2,3);    //M4,A22
            tmp = add(part[0][0][0],part[0][0][1],size/2,0);//A11+A12
            m[4] = multiply(tmp,part[1][1][1],size/2,2);    //M5,B22
            tmp = subtract(part[0][1][0],part[0][0][0],size/2,0);//A21-A11
            tmp2 = add(part[1][0][0],part[1][0][1],size/2,0);//B11+B12
            m[5] = multiply(tmp,tmp2,size/2,1);             //M6
            tmp = subtract(part[0][0][1],part[0][1][1],size/2,0);//A12-A22
            tmp2 = add(part[1][1][0],part[1][1][1],size/2,0);//B21+B22
            m[6] = multiply(tmp,tmp2,size/2,1);             //M7
            tmp = add(m[0],m[3],size/2,0);  //M1+M4
            tmp = subtract(tmp,m[4],size/2,2);//M1+M4-M5
            part[2][0][0] = add(tmp,m[6],size/2,2);//M1+M4-M5+M7
            part[2][0][1] = add(m[2],m[4],size/2,0);//M3+M5
            part[2][1][0] = add(m[1],m[3],size/2,0);//M2+M4
            tmp = subtract(m[0],m[1],size/2,0);  //M1-M2
            tmp = add(tmp,m[2],size/2,2);//M1-M2+M3
            part[2][1][1] = add(tmp,m[5],size/2,2);//M1-M2+M3+M6
            for(cnt=0;cnt<7;cnt++) free_array(m[cnt],size/2);

        }
        for(cnt0=0;cnt0<4;cnt0++) {
            for(cnt=0;cnt<size/2;cnt++) {
                for(cnt2=0;cnt2<size/2;cnt2++) {
                    if(cnt0==0) result[cnt][cnt2] = part[2][0][0][cnt][cnt2];
                    else if(cnt0==1) 
                        result[cnt][cnt2+size/2] 
                            = part[2][0][1][cnt][cnt2];
                    else if(cnt0==2) 
                        result[cnt+size/2][cnt2] 
                            = part[2][1][0][cnt][cnt2];
                    else if(cnt0==3) 
                        result[cnt+size/2][cnt2+size/2] 
                            = part[2][1][1][cnt][cnt2];
                }
            }
        }
        for(cnt0=0;cnt0<3;cnt0++) for(cnt=0;cnt<2;cnt++) for(cnt2=0;cnt2<2;cnt2++)
            free_array(part[cnt0][cnt][cnt2],size/2);
    }
    else {
        result[0][0]=arr1[0][0]*arr2[0][0];
    }
    if(trim==1) {
        free_array(arr1,size);
        free_array(arr2,size);
    }
    if(trim==2) free_array(arr1,size);
    if(trim==3) free_array(arr2,size);
    computation++;
    num_mul++;
    if(size==size0) {
        if(option==3) printf("Strassen method, %dx%d matrix multipliation\n",size0,size0);
        else printf("Recursion, %dx%d matrix multipliation\n",size0,size0);
    }
    print_array(result,size);
    return result;
}
void* add(int **arr1,int **arr2,int size,int trim) {
    int cnt,cnt2,**result=malloc(sizeof(int*)*size);
    for(cnt=0;cnt<size;cnt++) {
        result[cnt]=malloc(sizeof(int)*size);
        for(cnt2=0;cnt2<size;cnt2++)
            result[cnt][cnt2] = arr1[cnt][cnt2] + arr2[cnt][cnt2];
    }
    if(trim==1) {
        free_array(arr1,size);
        free_array(arr2,size);
    }
    if(trim==2) free_array(arr1,size);
    if(trim==3) free_array(arr2,size);
    computation++;
    num_add++;
    return result;
}
void* subtract(int **arr1,int **arr2,int size,int trim) {
    int cnt,cnt2,**result=malloc(sizeof(int*)*size);
    for(cnt=0;cnt<size;cnt++) {
        result[cnt]=malloc(sizeof(int)*size);
        for(cnt2=0;cnt2<size;cnt2++)
            result[cnt][cnt2] = arr1[cnt][cnt2] - arr2[cnt][cnt2];
    }
    if(trim==1) {
        free_array(arr1,size);
        free_array(arr2,size);
    }
    if(trim==2) free_array(arr1,size);
    if(trim==3) free_array(arr2,size);
    computation++;
    num_sub++;
    return result;
}
void* extract(int **arr,int size,int rows,int cols) {
    int cnt,cnt2,cnt11,cnt12;
    int **result = malloc(sizeof(int*)*size/2);
    for(cnt=0;cnt<size/2;cnt++) {
        result[cnt]=malloc(sizeof(int)*size/2);
    }
    for(cnt=0;cnt<size/2;cnt++) for(cnt2=0;cnt2<size/2;cnt2++) {
        if(rows==0) {
            if(cols==0) result[cnt][cnt2] = arr[cnt][cnt2];
            else result[cnt][cnt2] = arr[cnt][cnt2+size/2];
        }
        else if(rows==1) {
            if(cols==0) result[cnt][cnt2] = arr[cnt+size/2][cnt2];
            else result[cnt][cnt2] = arr[cnt+size/2][cnt2+size/2];
        }
    }
    return result;
}
