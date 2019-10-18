#include <stdio.h>
#include <stdlib.h>
typedef enum {false, true} bool;

typedef struct _Node {
	char item;
    int num;
	struct _Node* next;
} Node;
typedef struct {
	Node* head;
	int len;
} LinkedList;
typedef struct {
    char item[200];
    int top;
} stack;
//stack function
stack* make_stack();
bool is_full(stack *pstack);
bool is_empty(stack *pstack);
void push(stack *pstack, char item);
char pop(stack *pstack);
char peek(stack *pstack);
bool is_palin(char *input);
//linked list function
void InitList(LinkedList* plist);
bool IsEmpty(LinkedList* plist);
void InsertMiddle(LinkedList* plist, int pos, const char item);
void AddToList(LinkedList* plist,const char item);
void CleanList(LinkedList* plist); 
void PrintList(LinkedList* plist);
Node* PopMiddle(LinkedList* plist, int pos);
int SearchPos(LinkedList* plist, Node* nodeA);
void strcat2(char* str,char c);
stack* GetTwin(LinkedList* plist,char* str); 

int main() {
    LinkedList listA;
    InitList(&listA);
    stack* stackA;
    int cnt;
    char input[200],result[200]="",*cur = input;
    scanf("%s",input);
    while(*cur!='\0') {
        AddToList(&listA,*cur); // addtolist를 통해 각각의 character가 몇개씩있는지 링크드
        cur++;                  //리스트로 파악
    }
    //PrintList(&listA);
    stackA=GetTwin(&listA,result);//getTwin은 한쌍의 캐릭터를 하나는 stack으로 하나는 string에 바로 출력
    if(listA.head->next!=NULL) strcat2(result,listA.head->next->item);//gettwin을 거치고도 남은 solo character가 있으면 중앙에 반영
    while(!is_empty(stackA)) strcat2(result,pop(stackA));//이제 stack에 담긴 쌍의 나머지의 character를 pop하며 string에 출력
    free(stackA);
    CleanList(&listA);
    printf("%s\n",result);
    return 0;
}
void strcat2(char* str,char c){
    char *cur = str;
    while(*cur!='\0') cur++;
    *(cur+1) = *cur;
    *cur = c;
}
int SearchPos(LinkedList* plist, Node* nodeA) {
    int cnt=0;
    Node *cur = plist->head->next;
    while(cur!=NULL) {
        if(cur==nodeA) break;
        else cnt++;
        cur=cur->next;
    }

    return cnt;
}
Node* PopMiddle(LinkedList* plist, int pos) {
    //checking& declare
    Node *cur, *result;
    if(pos<0|| pos>plist->len) {
        printf("POPerr\n");
        exit(1);
    }
    // Move the cur pointer to the k-1 th position.
    cur = plist->head;
    for(int i =0; i<pos;i++) cur=cur->next;
    result = cur->next;
    cur->next = cur->next->next;
    result->next==NULL;
    plist->len--;
    return result;
}
stack* GetTwin(LinkedList* plist,char* str) {
    stack* stackA = make_stack();
    int cnt,pos;
    Node *cur = plist->head->next;
    while(cur!=NULL) {
        if(cur->num>1) {
            for(cnt=0;cnt<cur->num/2;cnt++) {
                push(stackA,cur->item);
                strcat2(str,cur->item);
            }
            if(cur->num%2==0) {
                pos = SearchPos(plist,cur);
                free(PopMiddle(plist,pos));
            }
            else cur->num=1;
        }
        cur = cur->next;
    }
    return stackA;
}
void PrintList(LinkedList* plist) {

	for (Node* cur = plist->head->next; cur != NULL; cur = cur->next) {
		printf("char:%c num:%d ", cur->item,cur->num);
	}
	printf("\n");
}
void CleanList(LinkedList* plist) {
    Node *cur,*prev;
    cur = plist->head;
    while(cur!=NULL) {
        prev = cur;
        cur=cur->next;
        free(prev);
    }
}
void AddToList(LinkedList* plist,const char item) {
    int cnt=0;
    Node *cur = plist->head;
    while(1) {
        if(cur->item==item) {
            cur->num++;
            break;
        }
        if(cur->next==NULL) {
            InsertMiddle(plist,plist->len,item);
            cur->next->num=1;
            break;
        }
        else cur = cur->next;
    }
}
bool is_palin(char *input) {
    char *now,*now2, item,comp[200],cnt=0;
    bool result=true;
    stack *stackA=make_stack();
    now = input;
    while(*now!='\0') push(stackA,*now++);
    while(is_empty(stackA)==false) {
        comp[cnt++] = pop(stackA);
    }
    cnt = 0, now = input, now2= comp;
    while(*now!='\0') if(*now++!=*now2++) result=false;
    free (stackA);
    return result;
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

void InitList(LinkedList* plist) {
    // Create a dummy node;
    plist->head = (Node*)malloc(sizeof(Node));
    plist->head->next = NULL;
    plist->len = 0;
}
bool IsEmpty(LinkedList* plist) {
    return plist->len == 0;
}
void InsertMiddle(LinkedList* plist, int pos, char item) {
    //checking& declare
    Node *cur, *newNode;
    if(pos<0|| pos>plist->len) {
        printf("IMerr\n");
        exit(1);
    }
    //create a new node
    newNode = (Node *)malloc(sizeof(Node));
    newNode->item = item;
    newNode->next = NULL;
    // Move the cur pointer to the (k-1)-th position.
    cur = plist->head;
    for (int i = 0; i<pos;i++) cur=cur->next;
    // Insert the new node to the k-th position
    newNode->next = cur->next;
    cur->next = newNode;
    plist->len++;
}
