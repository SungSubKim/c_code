#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {false, true} bool;

/* Modify from here */

typedef struct _Node {
	const char* item;
	struct _Node* next;
} Node;

/* Modify to here */

typedef struct {
	Node* head;
	int len;
} LinkedList;


void InitList(LinkedList* plist);
bool IsEmpty(LinkedList* plist);
void InsertMiddle(LinkedList* plist, int pos, const char* item);
void MergeTwoList(LinkedList* plist_a, LinkedList* plist_b, LinkedList* plist_c);
void PrintList(LinkedList* plist);
/* Modify from here */

void SortList(LinkedList* plist); 
Node* PopMiddle(LinkedList* plist, int pos);
int SearchPos(LinkedList* plist, Node* nodeA);
bool Smaller(Node* nodeA,Node* nodeB);

/* Modify to here */


int main() {
	LinkedList list_a, list_b, list_c;
	char ch1[100];

	fflush(stdin);
	char ss[30] = " ";
	char ss2[30] = " ";
	InitList(&list_a);
	InitList(&list_b);
	InitList(&list_c);

	fgets(ss,sizeof(ss),stdin);
	ss[strlen(ss)-1]=0;
	char* ptr= strtok(ss, " ");


	while (ptr != NULL)
	{
		InsertMiddle(&list_a, 0, ptr);
		ptr = strtok(NULL, " ");
	}


	fgets(ss2, sizeof(ss2), stdin);
	ss2[strlen(ss2)-1]=0;
	ptr = strtok(ss2, " ");

	while (ptr != NULL)
	{
		InsertMiddle(&list_b, 0, ptr);
		ptr = strtok(NULL, " ");
	}


	MergeTwoList(&list_a, &list_b, &list_c);
	PrintList(&list_a);
	PrintList(&list_b);
	PrintList(&list_c);



	return 0;
}

void PrintList(LinkedList * plist) {

	for (Node* cur = plist->head->next; cur != NULL; cur = cur->next) {
		printf("%s ", cur->item);
	}
	printf("\n");
}

/* Modify from here */


void InitList(LinkedList* plist) {
    // Create a dummy node;
    plist->head = (Node*)malloc(sizeof(Node));
    plist->head->next = NULL;
    plist->len = 0;
}
bool IsEmpty(LinkedList* plist) {
    return plist->len == 0;
}
void InsertMiddle(LinkedList* plist, int pos, const char* item) {
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
void MergeTwoList(LinkedList* plist_a, LinkedList* plist_b, LinkedList* plist_c) {
    if(plist_a->head->next==NULL||plist_b->head->next==NULL) {
        printf("Mergeerr:pa x\n");
        exit(1);
    }
    Node* cur = plist_a->head->next;
    while(cur->next!=NULL) cur = cur->next;
    cur = plist_a->head->next;
    while(1) {
        InsertMiddle(plist_c,plist_c->len,cur->item);
        cur = cur->next;
        if(plist_c->len==plist_a->len) cur = plist_b->head->next;
        else if(cur==NULL) break;
    }
    SortList(plist_a);
    SortList(plist_b);
    SortList(plist_c);

}
void SortList(LinkedList* plist) {
    LinkedList listA;
    InitList(&listA);
    Node *cur, *min,*tmp;
    int pos;
    while(plist->head->next!=NULL) {
        cur=plist->head->next;
        min=cur;
        while(1) {
            if(Smaller(cur,min)) {
                min = cur;
            }
            if(cur->next==NULL)break;
            else cur = cur->next;
        }
        pos = SearchPos(plist,min);    
        tmp = PopMiddle(plist,pos);
        InsertMiddle(&listA,listA.len,tmp->item);
        free(tmp);
    }
    while(listA.head->next!=NULL) {
        tmp = PopMiddle(&listA,0);
        InsertMiddle(plist,plist->len,tmp->item);
        free(tmp);
    }
    free(listA.head);
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
bool Smaller(Node* nodeA,Node* nodeB) {
    char comp[4]={nodeA->item[0], nodeA->item[1],
        nodeB->item[0],nodeB->item[1]};
    bool result=false;
    /*
    for(int cnt=0;cnt<4;cnt++) {
        if(comp[cnt]>64) comp[cnt]-=55;
        else comp[cnt]-=48;
    }*/
    if(comp[0]<comp[2]||(comp[0]==comp[2]&&comp[1]<comp[3])) result = true;
    return result;
}


/* Modify to here */
