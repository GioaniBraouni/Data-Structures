#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct BstNode
{
	char data[9];
	struct BstNode *left;
	struct BstNode *right;
};
struct BstNode2
{
	char data[9];
	struct BstNode2 *left;
	struct BstNode2 *right;
};

struct BstNode *GetNewNode(char data)
{
	int k=0;
	struct BstNode *newNode=(struct BstNode*)malloc(sizeof(struct BstNode));
	for(k=0; k<8; k++)
	{
		newNode->data[k]=data;
	}
	newNode->data[8]='\0';
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

struct BstNode2 *GetNewNode2(char data)
{
	int k=0;
	struct BstNode2 *newNode=(struct BstNode2*)malloc(sizeof(struct BstNode2));
	for(k=0; k<8; k++)
	{
		newNode->data[k]=data;
	}
	newNode->data[8]='\0';
	newNode->left=newNode->right=NULL;
	return newNode;
}

struct BstNode2* InsertLevelOrder2(char arr[], struct BstNode2* root, int i,int n) 
{  
    if (i<n) 
    { 
        struct BstNode2* temp = GetNewNode2(arr[i]); 
        root = temp;  
        root->left = InsertLevelOrder2(arr,root->left,2*i+1, n);  
        root->right = InsertLevelOrder2(arr,root->right,2*i+2,n); 
    } 
    return root; 
}
int main(void)
{
	FILE *myFile,*myFile2,*myFile3,*myFile4,*myFile5,*myFile6;
	char BinaryInput[256][8],GrayOutput[256][8],GrayOutput2[256][8],BinaryToGray[17];
	unsigned char c;
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
	struct BstNode2* rootPtr2,*tree2;
	j=pow(2,9);
	char arr[j-1];
	unsigned char *input;
	int *AsciiToBinaryInput;
	for(i=0; i<j-1; i++)
	{
		arr[i]='5';
	}
    int n = sizeof(arr)/sizeof(arr[0]);	
	rootPtr = InsertLevelOrder(arr, rootPtr,0, n);
	rootPtr2 = InsertLevelOrder2(arr, rootPtr2,0, n);
	myFile4=fopen("BinaryToGrayOutput.txt","w+");
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
			tree->data[j]=GrayOutput[i][j];
		}
		fprintf (myFile4, "%s\n",tree->data);
	}
	printf("Dose ASCII kodika eisodou\n");
	i=0;
	k=0;
	j=0;
	c = fgetc(stdin);
	int input2[8];
	input=(unsigned char*)malloc(sizeof(unsigned char));
	myFile2=fopen("Output.txt","w+");
	while (c!='\n')
	{
		input[i]=c;
		printf("ASCII of character %c is:%d\n",c,c);
		for(j = 7; j >= 0; j-- ) 
		{
    		input2[7-j]=(c >> j ) & 1 ? 1 : 0;
		}
		printf("Binary:");
		for(j = 0; j<=7; j++ ) 
		{
    		printf("%d",input2[j]);
		}
		printf("\n");
		tree=rootPtr;
		for(j=0; j<8; j++)
		{
			if(input2[j]==0)
			{
				tree=tree->left;	
			}
			else
			{
				tree=tree->right;	
			}		
		}
		fprintf(myFile2,"%s\n",tree->data);
		printf("\n");
		i++;
		k++;
		input=realloc(input,k*sizeof(unsigned char));
		c = fgetc(stdin);	
	}
	input[k]='\0';
	fclose(myFile2);
	myFile3=fopen("GrayToBinaryOutput.txt","w+");
	k=0;
	for(i=0; i<256; i++)
	{
		tree2=rootPtr2;
		for(j=0; j<8; j++)
		{
			if(GrayOutput[i][j]=='0')
			{
				tree2=tree2->left;	
			}
			else
			{
				tree2=tree2->right;
			}		 
		}
		for(j=0; j<8; j++)
		{
			tree2->data[j]=BinaryInput[i][j];
		}
		tree2->data[8]='\0';
		fprintf (myFile3, "%s\n",tree2->data);
	}
	myFile6=fopen("BinaryToGray2.txt","r");
	if (!myFile6)
 		printf("Error opening \"BinarytoGray2.txt\"\n");
 	else
 		printf("\"BinarytoGray2.txt\" opened successfully\n");
	myFile5=fopen("Output2.txt","w+");
	i=0;
	k=0;
	j=0;
	while(i!=256)
 	{
 		c=fgetc(myFile6);
		while(c!='\n')
		{
			BinaryToGray[j]=c;
			j++;
			c=fgetc(myFile6);
		}
		for(j=9; j<17; j++)
		{
			GrayOutput2[i][k]=BinaryToGray[j];
			k++;
		}
		k=0;
		i++;
		j=0;	
	}
	for(i=0; i<256; i++)
	{
		tree2=rootPtr2;
		for(j=0; j<8; j++)
		{
			if(GrayOutput2[i][j]=='0')
			{
				tree2=tree2->left;	
			}
			else
			{
				tree2=tree2->right;
			}		 
		}
		fprintf (myFile5, "%s\n",tree2->data);
	}
	return 0;
}
