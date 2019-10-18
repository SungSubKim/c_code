#include <stdio.h>
#include <stdlib.h>
typedef enum {false, true} bool;

typedef struct {
    char item[200];
    int top;
} stack;

stack* make_stack();
bool is_full(stack *pstack);
bool is_empty(stack *pstack);
void push(stack *pstack, char item);
char pop(stack *pstack);
char peek(stack *pstack);

int main() {
    char input[200],*now,*now2, item,comp[200],cnt=0,cnt2=0;
    stack *stackA=make_stack();
    scanf("%s",input);
    now = input;
    while(*now!='\0') push(stackA,*now++);
    while(is_empty(stackA)==false) {
        printf("%c",peek(stackA));
        comp[cnt++] = pop(stackA);
    }
    cnt = 0, now = input, now2= comp;
    while(*now!='\0') if(*now++!=*now2++) cnt2++;
    printf("\n%d\n",cnt2);
    free (stackA);
    return 0;
}
stack* make_stack() {
    stack *stackA = malloc(sizeof(stack));
    stackA->top = -1;
    return stackA;
}
bool is_full(stack *pstack) {
    return pstack->top == (200-1);
}
bool is_empty(stack *pstack) {
    return pstack->top == -1;
}
char peek(stack *pstack) {
    if(is_empty(pstack)) {
        printf("peek_err\n");
        exit(1);
    }
    return pstack->item[pstack->top];
}
char pop(stack *pstack) {
    if(is_empty(pstack)) {
        printf("pop_err\n");
        exit(1);
    }
    return pstack->item[pstack->top--];
}
void push(stack *pstack,char item) {
    if(is_full(pstack)) {
        printf("push_err\n");
        exit(1);
    }
    pstack->item[++(pstack->top)] = item;
}
