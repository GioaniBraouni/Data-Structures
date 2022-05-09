#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct BstNode
{
	char data[8];
	struct BstNode *left;
	struct BstNode *right;
};
struct BstNode *GetNewNode(char data)
{
	int k=0;
	struct BstNode *newNode=(struct BstNode*)malloc(sizeof(struct BstNode));
	for(k=0; k<8; k++)
	{
		newNode->data[k]=data;
	}
	newNode->left=newNode->right=NULL;
	return newNode;
}

struct BstNode* InsertLevelOrder(char arr[], struct BstNode* root, int i,int n) 
{  
    if (i<n) 
    { 
        struct BstNode* temp = GetNewNode(arr[i]); 
        root = temp;  
        root->left = InsertLevelOrder(arr,root->left,2*i+1, n);  
        root->right = InsertLevelOrder(arr,root->right,2*i+2,n); 
    } 
    return root; 
} 
void printGivenLevel(struct BstNode* root, int level) 
{
	int k; 
    if (root == NULL)
	{
		return;	
	}  
    if (level == 1)
    {
    	
		for(k=0; k<8; k++)
		{
			 printf("%c", root->data[k]); 
		}
		printf("%\n");
	}
    else if (level > 1) 
    { 
        printGivenLevel(root->left, level-1); 
        printGivenLevel(root->right, level-1); 
    } 
} 

int height(struct BstNode* node) 
{ 
    if (node==NULL) 
        return 0; 
    else
    { 
        int lheight = height(node->left); 
        int rheight = height(node->right); 
        if (lheight > rheight) 
            return(lheight+1); 
        else return(rheight+1); 
    } 
}
void printLevelOrder(struct BstNode* root) 
{ 
    int h = height(root); 
    int i; 
    for (i=1; i<=h; i++)
	{
		printGivenLevel(root, i); 
		printf("\n");
	}
}
  
int main(void)
{
	int heigh;
	FILE *myFile;
	char BinaryInput[256][8],GrayOutput[256][8],BinaryToGray[17],c;
	int i=0,j=0,k=0;
	myFile=fopen("BinarytoGray.txt","r");
	if (!myFile)
 		printf("Error opening \"BinarytoGray.txt\"\n");
 	else
 	{
 		printf("\"BinarytoGray.txt\" opened successfully\n");
 		while(i!=256)
 		{
 			c=fgetc(myFile);
			while(c!='\n')
			{
				BinaryToGray[j]=c;
				j++;
				c=fgetc(myFile);
			}
			for(j=0; j<8; j++)
			{
				BinaryInput[i][j]=BinaryToGray[j];
			}
			for(j=9; j<17; j++)
			{
				GrayOutput[i][k]=BinaryToGray[j];
				k++;
			}
			k=0;
			i++;
			j=0;	
		}
	}
	struct BstNode* rootPtr,*tree;
	j=pow(2,9);
	char arr[j-1];
	for(i=0; i<j-1; i++)
	{
		arr[i]='5';
	}
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("%d\n",n);	
	rootPtr = InsertLevelOrder(arr, rootPtr,0, n);
	printf("%d\n",rootPtr);
	for(i=0; i<256; i++)
	{
		tree=rootPtr;
		for(j=0; j<8; j++)
		{
			if(BinaryInput[i][j]=='0')
			{
				tree=tree->left;	
			}
			else
			{
				tree=tree->right;	
			}		
		}
		for(j=0; j<8; j++)
		{
			if(BinaryInput[i][j]=='0')
			{
				tree=tree->left;	
			}
			else
			{
				tree=tree->right;	
			}		
		}
		for(j=0; j<8; j++)
		{
			tree->data[j]=GrayOutput[i][j];
		}
	}
	printLevelOrder(rootPtr);
	printf("%d\n",rootPtr);
	return 0;
}
