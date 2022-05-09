/*
GIOANI BRAUNI DIT 18131

MEROS 1

Gia tin anazitisi sto telos
-1 sta if ean ektelestei se linux
kanonika ean ektelestei se windows
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int length,z=0;

struct dictionary 
{
    char *data;
};
 
struct dictionary *array;


unsigned int hash(const char *key) {
    unsigned long int value = 0;
    unsigned int key_len = strlen(key);
    int i;

    for (i=0; i < key_len; ++i) 
	{	
        value = value+key[i];
    }
    
    value = value % length ;

    return value;
}


void init_array()
{
    int i;
    for (i = 0; i < length; i++) 
    {
		array[i].data=NULL;
    }
}

int insert(char *value)
{
    int index = hash(value);
    int i = index;
    int k;
    z++;
    //Empty slot
    if(array[i].data==NULL)
    {
    	printf("Item:%d has successfully been inserted in the hash table\nLocation:%d\n",z,i);
    	array[i].data=(char*)malloc(strlen(value)*sizeof(char)+1);
        for(k=0; k<strlen(value); k++)
        {
            array[i].data[k]=value[k]; 
        }
        array[i].data[k]='\0';
        printf("Value:%s\n",array[i].data);
        printf("\n");
	}
	
	else
	{
    	printf("Slot in location:%d has already been filled with value:%s\n",i,array[i].data);
		printf("Searching second half of hash table\n");
    	printf("\n");
    	//Searching for second half of the hash table for a empty slot
		while(i<length)
		{
			if(array[i].data==NULL)
    		{
    			printf("Item:%d has successfully been inserted in the hash table\nLocation:%d\n",z,i);
    			array[i].data=(char*)malloc(strlen(value)*sizeof(char)+1);
        		for(k=0; k<strlen(value); k++)
        		{
            		array[i].data[k]=value[k]; 
        		}
       			 array[i].data[k]='\0';
        		printf("Value:%s\n",array[i].data);
        		printf("\n");
    			return 0;
			}
			i++;
			//Search reach the end of the hash table
			if(i==length)
			{
			
				printf("Empty slot not found in second half of hash table\n");
				printf("Searching first half of hash table\n");
        		printf("\n");
				i=index;
				//Searching for the first half of the hash table for a empty slot
				while(i>=0)
				{
					if(array[i].data==NULL)
    				{
    					printf("Item:%d has successfully been inserted in the hash table\nLocation:%d\n",z,i);
    					array[i].data=(char*)malloc(strlen(value)*sizeof(char)+1);
        				for(k=0; k<strlen(value); k++)
        				{
            				array[i].data[k]=value[k]; 
        				}
        				 array[i].data[k]='\0';
        				printf("Value:%s\n",array[i].data);
        				printf("\n");
    					return 0;
					}
					i--;
				}
			}
		}
	}
} 

int main()
{
	int i,j,flag=0;
	char *array2,ch;
	FILE *dictionary;
	printf("How many words do you want to be inserted into the dictionary?\n");
	scanf("%d",&length);
	array =(struct dictionary*)malloc(length *sizeof(struct dictionary));
	init_array();
	dictionary=fopen("dictionary.txt","r");
	if (!dictionary)
	{
		printf("Error opening \"dictionary.txt\"\n");
		exit(EXIT_FAILURE);	
	}
	array2=(char*)malloc(sizeof(char));
	j=0;
	//Reading char from the file
	for(i=0; i<length; i++)
	{
		ch=fgetc(dictionary);
		while(ch!='\n')
		{
			array2[j]=ch;
			j++;
			array2 = (char *) realloc(array2, j+1);
			ch=fgetc(dictionary);
		}
		array2[j]='\0';
		insert(array2);
		j=0;
		free(array2);
		array2=(char*)malloc(sizeof(char));
	}
	free(array2);
	j=0;
	//Searching for string given by the user in the hash table
	printf("Give string\n");
	array2=(char*)malloc(sizeof(char));
	ch=getchar();
	ch=getchar();
	while(ch!='\n')
	{
		array2[j]=ch;
		j++;
		array2 = (char *) realloc(array2, j+1);
		ch=getchar();
	}
	array2[j]='\0';
	printf("Searching for:%s in the hash table\n",array2);
	i = hash(array2);
	printf("\n");
	z=0;
	char ch1,ch2;
	int k=0;
  for(j=0; j<strlen(array[i].data); j++)
  {
     if(array[i].data[j]==array2[j])
     {
       z++;
     }
  }
  if(z==strlen(array[i].data))
  {
    	printf("String %s found succcessfully\n",array2);
    	printf("Result of hash function: %d\n",i = hash(array2));
  }
	else
	{
		printf("Searching second half of hash table\n");
    	printf("\n");
    	//Searching for second half of the hash table for a empty slot
		while(i<length)
		{
			z=0;
			if(array[i].data==NULL)
    		{
    			printf("Slot is empty\n");
    			printf("Exiting\n");
			}
			printf("Searching %d slot\n",i);
			for(j=0; j<strlen(array[i].data); j++)
      		{
                ch1=array[i].data[j];
           		ch2=array2[j];
           		if(ch1==ch2)
           		{
                    z++;
           		}
      		}
      		printf("\n");
			if(z==(strlen(array[i].data)))
 		  	{
    			flag=1;
    		  	printf("String %s found succcessfully\n",array2);
    		  	printf("Result of hash function: %d\n",i = hash(array2));
          		break;
			}
			i++;
			if(i==length-1)
			{
				printf("String %s not found succcessfully in the hash table\n",array2);
				printf("Searching first half of hash table\n");
        		printf("\n");
				i=hash(array2);
				//Searching for the first half of the hash table for a empty slot
				while(k<i)
				{
					z=0;
					if(array[k].data==NULL)
    				{
    					printf("Slot is empty\n");
    					printf("Exiting\n");
					}
					printf("Searching %d slot\n",k);
					for(j=0; j<strlen(array[k].data); j++)
      				{
               			 ch1=array[k].data[j];
           				ch2=array2[j];
           				if(ch1==ch2)
           				{
                    		z++;
           				}
      				}
      				printf("\n");
					if(z==(strlen(array[k].data)))
 		  			{
    					flag=1;
    		  			printf("String %s found succcessfully\n",array2);
          				break;
					}
					k++;
				}
			}
			if(k==i)	
				break; 
		}
		//User entered wrong string 
		if(flag==0)
		{
			printf("You entered wrong string,try again\n");
		}
	}
	printf("\n");
	printf("Exiting\n");
    free(array);
    free(array2);
	return 0;
}
