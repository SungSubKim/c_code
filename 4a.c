#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int TerneryData;

typedef struct _terneryTreeNode {
	TerneryData item;
	struct _terneryTreeNode *left_child;
	struct _terneryTreeNode *middle_child;
	struct _terneryTreeNode *right_child;
} TerneryTreeNode;

TerneryTreeNode *CreateNode(TerneryData item);

void DestroyNode(TerneryTreeNode *node);

void CreateLeftSubtree(TerneryTreeNode *root, TerneryTreeNode *left);

void CreateMiddleSubtree(TerneryTreeNode *root, TerneryTreeNode *middle);

void CreateRightSubtree(TerneryTreeNode *root, TerneryTreeNode *right);

void PrintTreeNode(TerneryTreeNode *node);

void Tester();


/* Modify from here */

/* Modify to here */

int main() {
	TerneryTreeNode *node1 = CreateNode(1);
	TerneryTreeNode *node2 = CreateNode(2);
	TerneryTreeNode *node3 = CreateNode(3);
	TerneryTreeNode *node4 = CreateNode(4);
	TerneryTreeNode *node5 = CreateNode(5);
	TerneryTreeNode *node6 = CreateNode(6);
	TerneryTreeNode *node7 = CreateNode(7);

	CreateLeftSubtree(node1, node2);
	CreateMiddleSubtree(node1, node3);
	CreateRightSubtree(node1, node4);

	CreateLeftSubtree(node2, node5);
	CreateMiddleSubtree(node2, node6);

	CreateLeftSubtree(node3, node7);

	PrintTreeNode(node1);
	PrintTreeNode(node2);
	PrintTreeNode(node3);
	PrintTreeNode(node4);
	PrintTreeNode(node5);
	PrintTreeNode(node6);
	PrintTreeNode(node7);

	DestroyNode(node1);
	DestroyNode(node2);
	DestroyNode(node3);
	DestroyNode(node4);
	DestroyNode(node5);
	DestroyNode(node6);
	DestroyNode(node7);

	// Tester();
	/*
		7
		6
		l 1 2
		m 1 3
		r 1 4
		l 2 5
		m 2 6
		l 3 7
	*/
	return 0;
}

void Tester() {
	int n, m, root, child;
	char type;
	TerneryTreeNode **Array;

	scanf("%d", &n);
	Array = (TerneryTreeNode**)malloc(sizeof(TerneryTreeNode*)*n);
	for (int i = 0; i < n; i++)
		Array[i] = CreateNode(i + 1);

	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		while(getchar()!='\n'); // = fflush(stdin) = __fpurge(stdin)
		scanf("%c %d %d", &type, &root, &child);
		if (type == 'l') CreateLeftSubtree(Array[root - 1], Array[child - 1]);
		else if (type == 'm') CreateMiddleSubtree(Array[root - 1], Array[child - 1]);
		else if (type == 'r') CreateRightSubtree(Array[root - 1], Array[child - 1]);
		else exit(1);
	}

    for (int i = 0; i < n; i++)
		PrintTreeNode(Array[i]);

	for (int i = 0; i < n; i++)
		DestroyNode(Array[i]);

	free(Array);
}

void PrintTreeNode(TerneryTreeNode *node) {
	printf("%d: ", node->item);
	node->left_child == NULL ? printf("null ") : printf("%d ", node->left_child->item);
	node->middle_child == NULL ? printf("null ") : printf("%d ", node->middle_child->item);
	node->right_child == NULL ? printf("null\n") : printf("%d\n", node->right_child->item);
}

/* Modify from here */
TerneryTreeNode* CreateNode(TerneryData item){
	TerneryTreeNode *node = (TerneryTreeNode*) malloc(sizeof(TerneryTreeNode));
	node->item = item;
	node->left_child=NULL;
	node->middle_child=NULL;
	node->right_child=NULL;
	return node;
}

void DestroyNode(TerneryTreeNode *node){
	free(node);
}

void CreateLeftSubtree(TerneryTreeNode *root, TerneryTreeNode *left){
	if (root->left_child != NULL){
		printf("CL_ERR\n");
		exit(1);
	}
	root->left_child = left;
}

void CreateMiddleSubtree(TerneryTreeNode *root, TerneryTreeNode *middle){
	if (root->middle_child != NULL){
		printf("CM_ERR\n");
		exit(1);
	}
	root->middle_child = middle;
}

void CreateRightSubtree(TerneryTreeNode *root, TerneryTreeNode *right){
	if (root->right_child != NULL){
		printf("CR_ERR\n");
		exit(1);
	}
	root->right_child = right;
}

/* Modify to here */
