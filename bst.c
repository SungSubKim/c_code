#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	struct Node *l, *r, *p;
	int key;
} node;
typedef struct Tree {
	node *root;
	int height;
} tree;

tree* make_tree();
void tree_insert(tree *t, int x);
int pop(tree *t, int key);
void printree(tree *t);
void printree2(node *node);
void tree_free(tree *t);
void node_free(node *cur);

int main() {
	tree *t= make_tree();
	int x;
	while(1) {
		scanf("%d",&x);
		if(x==-1) break;
		tree_insert(t,x);
		printree(t);
	}
	free(t);
	return 0;
}

tree* make_tree(){
	tree *result = malloc(sizeof(tree));
	result->height = 1;
	result->root =NULL;
	return result;
}
void tree_insert(tree *t, int x) {
	node *cur=t->root, *new=malloc(sizeof(node));
	new->l=NULL,new->r=NULL, new->key=x;
	if(t->root==NULL) {
		t->root=new;
		return;
	}
	while(1) {
		if(x<cur->key) {
			if(cur->l==NULL) {
				cur->l = new;
				new->p = cur;
				break;
			}
			else cur=cur->l;
		}
		else if(cur->key<x){
			if(cur->r ==NULL) {
				cur->r=new;
				new->p=cur;
				break;
			}
			else cur=cur->r;
		}
		else {
			printf("x is already in tree.\n");
			break;
		}
	}
	return;
}
void printree(tree *t) {
	node *cur=t->root;
	if(t->root==NULL) {
		printf("It's NULL tree\n");
		return;
	}
	printree2(cur);
	printf("\nprintree end\n");
	return;
}
void printree2(node *cur) {
	if(cur==NULL) return;
	printree2(cur->l);
	printf("%d ",cur->key);
	printree2(cur->r);
	return;
}
void free_tree(tree *t) {
	node *cur = t->root;
	node_free(cur);
	free(t);
	return;
}
void node_free(node *cur) {
	if(cur==NULL) return;
	node *l=cur->l, *r=cur->r;
	node_free(l);
	node_free(r);
	free(cur);
	return;
}
