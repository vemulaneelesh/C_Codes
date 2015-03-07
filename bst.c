#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int low;

struct treeNode
{
	int data;
	struct treeNode *left;
	struct treeNode *right;
};

void lowest(treeNode *a)
{
	if(a->left ==NULL)
	{
		low = a->data;
	}
	else
	{
		lowest(a->left);
	}
}

int main()
{
	treeNode *root = (treeNode *)malloc(sizeof(treeNode));
	treeNode *left1 = (treeNode *)malloc(sizeof(treeNode));
	treeNode *right1 = (treeNode *)malloc(sizeof(treeNode));
	treeNode *leftleft1 = (treeNode *)malloc(sizeof(treeNode));
	treeNode *leftright1 = (treeNode *)malloc(sizeof(treeNode));
	root->data = 4;
	root->left = left1;
	root->right = right1;
	left1->data = 2;
	left1->left = leftleft1;
	left1->right = leftright1;
	right1->data = 5;
	right1->left = NULL;
	right1->right = NULL;
	leftleft1->data = 1;
	leftleft1->left = NULL;
	leftleft1->right = NULL;
	leftright1->data = 3;
	leftright1->left = NULL;
	leftright1->right = NULL;

	//printf("The tree data of root is %d \n",root->data);
	//printf("The tree data of left node is %d \n",left1->data);
	//printf("The tree data of right node is %d \n",right1->data);
	lowest(root);
	printf("The lowest value is %d\n",low );
	return 0;
}