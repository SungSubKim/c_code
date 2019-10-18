#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TMAX ((unsigned)(-1)>>1) 
typedef struct Node {
	struct Node *left, *right, *parent;
	int key;
} node;
typedef struct Tree {
	node *root;
	int height;
} tree;
//1.Program the following functions.
node* tree_insert(tree *t, int x);
node* tree_search(tree *t, int x);
node* nearest_neighbor(tree *t, int x);
node* tree_delete(tree *t, int x);
void print_bst(tree *t);

node* suc(node *cur);
node* min(node *cur);
node* pre(node *cur);
node* max(node *cur);
node* node_search(node *cur,int x);
node* node_search2(node *cur,int x);
tree* make_tree();
void print_node(node *node);
void tree_free(tree *t);
void node_free(node *cur);

int main() {
	srand(time(NULL));
	tree *t= make_tree();
	node *searched;
	int x,cnt,A[20];
    printf("2.TREE-INSERT\n");
    for(cnt=0;cnt<20;cnt++) A[cnt]=rand()%50;
	for(cnt=0;cnt<20;cnt++) tree_insert(t,A[cnt]);
	print_bst(t);
    printf("3.TREE-SEARCH (10,9,15)\n");
    tree_search(t,10);
    tree_search(t,9);
    tree_search(t,15);
    printf("4.NEAREST-NEIGHBOR (5,9,17)\n%d %d %d\n",nearest_neighbor(t,5)->key,
            nearest_neighbor(t,9)->key,
            nearest_neighbor(t,17)->key);
    printf("5.TREE-INSERT (6,29,17,21)\n");
    if(tree_insert(t,6)!=NULL) print_bst(t);
    if(tree_insert(t,29)!=NULL) print_bst(t);
    if(tree_insert(t,17)!=NULL) print_bst(t);
    if(tree_insert(t,21)!=NULL) print_bst(t);
    printf("6.TREE-DELETE (6,17,21,7)\n");
    tree_delete(t,6);
    print_bst(t);
    tree_delete(t,17);
    print_bst(t);
    tree_delete(t,21);
    print_bst(t);
    tree_delete(t,7);
    print_bst(t);
/*	while(1) {
		scanf("%d",&x);
		if(x==-1) break;
        searched = tree_delete(t,x);
        if(searched==NULL) continue;
        printf("%d is deleted.\n",searched->key);
        print_bst(t);
        free(searched);
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
	}*/
	tree_free(t);
	return 0;
}

node* tree_insert(tree *t, int x) {
	node *cur=t->root, *new=malloc(sizeof(node));
	if(t->root==NULL) {
		t->root=new;
		return new;
	}
	new->left=NULL,new->right=NULL, new->key=x;
	while(1) {
		if(x<cur->key) {
			if(cur->left==NULL) {
				cur->left = new;
				new->parent = cur;
				break;
			}
			else cur=cur->left;
		}
		else if(cur->key<x){
			if(cur->right ==NULL) {
				cur->right=new;
				new->parent=cur;
				break;
			}
			else cur=cur->right;
		}
	    else {
            free(new);
            new=NULL;
            break; //존재시 skip
        }
	}
	return new;
}
node* tree_search(tree *t, int x) {
	if(t->root==NULL) {
		printf("it's null tree\n");
		return NULL;
	}
    node *result = node_search(t->root,x);
    printf("\n");
    return result;
}
node* nearest_neighbor(tree *t, int x){
	if(t->root==NULL) {
		printf("it's null:nn\n");
		return NULL;
	}
	int cand[2]={0,},min;
	node *searched = node_search2(t->root,x),*result;
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
	return result;
}
node* tree_delete(tree *t, int x) {
    if(t->root==NULL) {
        printf("It's null tree\n");
        return NULL;
    }
    if(node_search2(t->root,x)->key != x) {
        printf("There is no %d\n",x);
        return NULL;
    }
    node *nodeX = node_search2(t->root,x),*nodeY,*nodeZ=NULL;
    int tmp;
    if(nodeX->left!=NULL && nodeX->right!= NULL) nodeY = suc(nodeX); //자식두개
    else nodeY = nodeX;                                       //자식1개,자식0개

    if(nodeY->left!=NULL) nodeZ = nodeY->left;
    else if(nodeY->right!=NULL) nodeZ = nodeY->right;

    if(nodeZ!=NULL) nodeZ->parent=nodeY->parent;//nodeY무시하고 다른 부모 섬기기//nodeZ없으면 건드리면 안되겟지?

    if(nodeY->parent == NULL) t->root = nodeZ;   //
    else {
        if(nodeY->parent->left == nodeY) nodeY->parent->left = nodeZ;
        else nodeY->parent->right = nodeZ;
    }
    
    if(nodeX != nodeY) {
        tmp = nodeX->key;
        nodeX->key = nodeY->key;
        nodeY->key = tmp;
    }
    return nodeY;
}
void print_bst(tree *t) {
	node *cur=t->root;
	if(t->root==NULL) {
		printf("print_bst_err:It's NULL tree\n");
		return;
	}
	print_node(cur);
	printf("\n");
	return;
}

node* suc(node *cur) {
	node *r;
	if(cur->right) return min(cur->right);
	else {
		while(1) {
			if(cur->parent==NULL) {
				return NULL;
			}
			r = cur;
			cur = cur->parent;
			if(r!=cur->right) break;
		}
		r= cur;
	}
	return r;
}
node* min(node *cur) {
	node *result;
	if(cur->left) result=min(cur->left);
	else result = cur;
	return result;
}
node* pre(node *cur) {
	node *l;
	if(cur->left) return max(cur->left);
	else {
		while(1) {
			if(cur->parent==NULL) {
				return NULL;
			}
			l = cur;
			cur = cur->parent;
			if(l!=cur->left) break;
		}
		l= cur;
	}
	return l;
}
node* max(node *cur) {
	node *result;
	if(cur->right) result=max(cur->right);
	else result = cur;
	return result;
}
node* node_search(node *cur, int x) {
	node *result=NULL;
    printf("%d ",cur->key);
	if(x < cur->key) {
		if(cur->left!=NULL) result = node_search(cur->left,x);
		else result = cur;
	}
	else if(x == cur->key) result = cur;
	else {
		if(cur->right!=NULL) result = node_search(cur->right,x);
		else result = cur;
	}
	return result;
}
node* node_search2(node *cur, int x) {
	node *result=NULL;
    //printf("%d ",cur->key);
	if(x < cur->key) {
		if(cur->left!=NULL) result = node_search2(cur->left,x);
		else result = cur;
	}
	else if(x == cur->key) result = cur;
	else {
		if(cur->right!=NULL) result = node_search2(cur->right,x);
		else result = cur;
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

	//if(cur->left) printf("left:%-2d  ",cur->l->key);
    //else printf("left:x   ");
	//if(cur->r)printf("right:%-2d  ",cur->r->key);
    //else printf("right:x   ");
    //printf("\n");
	print_node(cur->left);
	printf("%-2d ",cur->key);
	print_node(cur->right);
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
	node *l=cur->left, *r=cur->right;
	node_free(l);
	node_free(r);
	free(cur);
	return;
}
