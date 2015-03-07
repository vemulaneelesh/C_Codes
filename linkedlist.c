#include <stdio.h>
#include <stdlib.h>

struct node
{
	int data;
	node *next;
};

void insertIntoList(node **head,int value)
{
	node *node1,*cur;
	node1 = (node *)malloc(sizeof(node));

	for(cur = *head;cur->next!=NULL;cur=cur->next);
	cur->next=node1;
	node1->data = value;
	node1->next = NULL;
	//*temp->next = node1;
}

void printList(node **head)
{
	node *cur;
	int i =0;
	for(cur = *head;cur->next!=NULL;cur=cur->next)
	{
		printf("The %d element is %d\n", i,cur->data);
		i++;
	}
	printf("The %d element is %d\n", i,cur->data);
}
mynode* reverse_recurse(mynode *root) 
{ 
	if(root->next!=(mynode *)0) 
		{ 
			reverse_recurse(root->next);
			root->next->next=root; 
			return(root); 
		} 
	else 
		{ 
			head=root; 
		} 
}


int main()
{
	node *head;
	head->data = 2;
	head->next = NULL;
	insertIntoList(&head,6);
	insertIntoList(&head,4);
	printList(&head);
}

