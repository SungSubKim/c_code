#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TMAX ((unsigned)(-1)>>1) 
typedef struct Node {
	struct Node *l, *r, *p;
	int key;
} node;
typedef struct Tree {
	node *root;
	int height;
} tree;

void tree_insert(tree *t, int x);
node* tree_search(tree *t, int x);
node* nearest_neighbor(tree *t, int x);
node* tree_delete(tree *t, int key);
void print_bst(tree *t);

node* suc(node *cur);
node* min(node *cur);
node* pre(node *cur);
node* max(node *cur);
node* node_search(node *cur,int x);
tree* make_tree();
void print_node(node *node);
void tree_free(tree *t);
void node_free(node *cur);

int main() {
	srand(time(NULL));
	tree *t= make_tree();
	node *searched;
	int x,cnt;
	for(cnt=0;cnt<30;cnt++) {
		tree_insert(t,rand()%100);
	}
	print_bst(t);
	while(1) {
		scanf("%d",&x);
		if(x==-1) break;
		searched=tree_search(t,x);
		if(searched==NULL) {
			printf("tree doens't have anything\n");
			continue;
		}
		printf("val: %d searched: %d ",x,searched->key); 
		if(pre(searched)!=NULL) printf("pre: %2d ",pre(searched)->key);
		else printf("pre: no ");
		if(suc(searched)!=NULL) printf("suc: %2d ",suc(searched)->key);
		else printf("suc: no ");
		if(nearest_neighbor(t,x)!=NULL) printf("nearest: %d\n",nearest_neighbor(t,x)->key);
		else printf("neighbor err\n");

	}
	tree_free(t);
	return 0;
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
			printf("%2d is already in tree.\n",x);
			break;
		}
	}
	return;
}
node* tree_search(tree *t, int x) {
	if(t->root==NULL) {
		printf("it's null tree\n");
		return NULL;
	}
	return node_search(t->root,x);
}
node* nearest_neighbor(tree *t, int x){
	if(t->root==NULL) {
		printf("it's null:nn\n");
		return NULL;
	}
	int cand[2]={0,},min;
	node *searched = tree_search(t,x),*result;
	if(searched->key < x) {		// pre | searched | x | suc
		cand[0] = x - (searched->key);
		if(suc(searched)==NULL) cand[1]=TMAX;
		else cand[1]=(suc(searched)->key) - x;
		result = searched;
		if(cand[1]<min) result = suc(searched);
	}
	else {						// pre | x | searched | suc
		if(pre(searched)==NULL) cand[0] = TMAX;
		else cand[0] = x - (pre(searched)->key);
		cand[1] = (searched->key) - x;
		result = pre(searched);
		if(cand[1]<cand[0]) result = searched;
	}
	printf("\n");
	for(int cnt=0;cnt<2;cnt++) printf("%d ",cand[cnt]);
	printf("\n");
	return result;
}
void print_bst(tree *t) {
	node *cur=t->root;
	if(t->root==NULL) {
		printf("It's NULL tree\n");
		return;
	}
	print_node(cur);
	printf("\nprintree end\n");
	return;
}

node* suc(node *cur) {
	node *r;
	if(cur->r) return min(cur->r);
	else {
		while(1) {
			if(cur->p==NULL) {
				return NULL;
			}
			r = cur;
			cur = cur->p;
			if(r!=cur->r) break;
		}
		r= cur;
	}
	return r;
}
node* min(node *cur) {
	node *result;
	if(cur->l) result=min(cur->l);
	else result = cur;
	return result;
}
node* pre(node *cur) {
	node *l;
	if(cur->l) return max(cur->l);
	else {
		while(1) {
			if(cur->p==NULL) {
				return NULL;
			}
			l = cur;
			cur = cur->p;
			if(l!=cur->l) break;
		}
		l= cur;
	}
	return l;
}
node* max(node *cur) {
	node *result;
	if(cur->r) result=max(cur->r);
	else result = cur;
	return result;
}
node* node_search(node *cur, int x) {
	node *result=NULL;
	if(x < cur->key) {
		if(cur->l) result = node_search(cur->l,x);
		else {
		//	printf("tree_search: %d doesn't exists in the tree.\n",x);
			result = cur;
		}
	}
	else if(x == cur->key) {
		//printf("tree_search: %d exists in the tree.\n",cur->key);
		result = cur;
	}
	else {
		if(cur->r) result = node_search(cur->r,x);
		else {
		//	printf("tree_search: %d doesn't exists in the tree.\n",x);
			result = cur;
		}
	}
	return result;
}
tree* make_tree(){
	tree *result = malloc(sizeof(tree));
	result->height = 1;
	result->root =NULL;
	return result;
}
void print_node(node *cur) {
	if(cur==NULL) return;

	printf("%2d ",cur->key);
	if(cur->l) printf("left:%2d ",cur->l->key);
	if(cur->r)printf("right:%2d ",cur->r->key);
	printf("\n");
	print_node(cur->l);
	print_node(cur->r);
	return;
}
void tree_free(tree *t) {
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
