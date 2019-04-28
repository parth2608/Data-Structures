#include<stdio.h>
#include<stdlib.h>

struct Node
{
	int key;
	struct Node *left;
	struct Node *right;
	int height;
};

int height(struct Node *N)
{
	if (N==NULL)
    {
        return 0;
    }
	return N->height;
}

int max(int a,int b)
{
	return (a>b)?a:b;
}

struct Node *newNode(int key)
{
	struct Node *node=(struct Node *)malloc(sizeof(struct Node));
	node->key=key;
	node->left=NULL;
	node->right=NULL;
	node->height=1;
	return node;
}

struct Node *rightRotate(struct Node *y)
{
	struct Node *x=y->left;
	struct Node *T2=x->right;
	x->right=y;
	y->left=T2;
	y->height=max(height(y->left),height(y->right))+1;
	x->height=max(height(x->left),height(x->right))+1;
	return x;
}

struct Node *leftRotate(struct Node *x)
{
	struct Node *y=x->right;
	struct Node *T2=y->left;
	y->left=x;
	x->right=T2;
	x->height=max(height(x->left),height(x->right))+1;
	y->height=max(height(y->left),height(y->right))+1;
	return y;
}

int getBalance(struct Node *N)
{
	if(N==NULL)
    {
        return 0;
    }
	return (height(N->left)-height(N->right));
}

struct Node *insert(struct Node *node,int key)
{
	int balance;
	if(node==NULL)
    {
        return(newNode(key));
    }
	if(key<node->key)
    {
		node->left=insert(node->left,key);
    }
	else if(key>node->key)
    {
		node->right=insert(node->right,key);
    }
	else
    {
		return node;
    }
	node->height=1+max(height(node->left),height(node->right));
	balance=getBalance(node);
	if(balance>1 && key<node->left->key)
    {
        return rightRotate(node);
    }
	if(balance<-1 && key>node->right->key)
    {
		return leftRotate(node);
    }
	if(balance>1 && key>node->left->key)
	{
		node->left=leftRotate(node->left);
		return rightRotate(node);
	}
	if(balance<-1 && key<node->right->key)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}
	return node;
}

struct Node *minValueNode(struct Node *node)
{
    struct Node *current=node;
    while(current->left!=NULL)
    {
        current=current->left;
    }
    return current;
}

struct Node *deleteNode(struct Node *root,int key)
{
    int balance;
    if(root==NULL)
    {
        return root;
    }
    if(key<root->key)
    {
        root->left=deleteNode(root->left,key);
    }
    else if(key>root->key)
    {
        root->right=deleteNode(root->right,key);
    }
    else
    {
        if(root->left==NULL)
        {
            struct Node *temp=root->right;
            free(root);
            return temp;
        }
        else if(root->right==NULL)
        {
            struct Node *temp=root->left;
            free(root);
            return temp;
        }
        struct Node *temp=minValueNode(root->right);
        root->key=temp->key;
        root->right=deleteNode(root->right,temp->key);
    }
    root->height=1+max(height(root->left),height(root->right));
    balance=getBalance(root);
    if(balance>1 && getBalance(root->left)>=0)
    {
        return rightRotate(root);
    }
    if(balance>1 && getBalance(root->left)<0)
    {
        root->left=leftRotate(root->left);
        return rightRotate(root);
    }
    if(balance<-1 && getBalance(root->right)<=0)
    {
        return leftRotate(root);
    }
    if(balance<-1 && getBalance(root->right)>0)
    {
        root->right=rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

void inorder(struct Node *root)
{
	if(root!=NULL)
	{
		inorder(root->left);
		printf("%d\t",root->key);
		inorder(root->right);
	}
}

int main()
{
    int ch,val;
    struct Node *root=NULL;
    while(ch!=4)
    {
        printf("\n1) Insert Node");
        printf("\n2) In-Order Traversal");
        printf("\n3) Delete Node");
        printf("\n4) Exit");
        printf("\nEnter Your Choice: ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
                printf("\nEnter value of the new node: ");
                scanf("%d",&val);
                root=insert(root,val);
            break;
            case 2:
                printf("\nIn-Order Traversal:\n");
                inorder(root);
            break;
            case 3:
                printf("Enter the value to be deleted: ");
                scanf("%d",&val);
                root=deleteNode(root,val);
            break;
        }
    }
    return 0;
}
