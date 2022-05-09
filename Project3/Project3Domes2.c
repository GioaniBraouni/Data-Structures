/*
GIOANI BRAUNI DIT 18131

MEROS 2

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define length 100

int z=0;

struct node
{
	char *string;
	struct node* next;
};


struct hashtable
{
	char *sorted_key;
	struct node *hashtable_slot;
};

struct hashtable *array;

void insert_node(struct node** head,char *new_string)
{
	int k,j=0;
	struct node* new_node=malloc(sizeof(struct node));
	new_node->string=(char*)malloc(sizeof(char));
	for(k=0; k<strlen(new_string); k++)
    {
        j++;
            					 new_node->string[k]=new_string[k];
                      new_node->string = (char *) realloc(new_node->string, j+1);  
     	
    }
    new_node->string[k]='\0';
    new_node->next=NULL;
    
    if(*head==NULL)
    {
    	*head=new_node;
	}
	else
	{
		struct node* current=*head;
		while(current->next!=NULL)
		{
			current=current->next;
		}
		current->next=new_node;
	}
}

void merge(char *arr, int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
    char *L, *R; 
  	L=(char*)malloc(n1*sizeof(char));
  	R=(char*)malloc(n2*sizeof(char));
    for (i = 0; i < n1; i++)
    {
    	L[i] = arr[l + i]; 	
	}
    for (j = 0; j < n2; j++)
    {
    	R[j] = arr[m + 1+ j];	
	}
    i = 0; 
    j = 0; 
    k = l; 
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
}
void mergeSort(char *arr, int l, int r) 
{ 
    if (l < r) 
    { 
       
        int m = l+(r-l)/2; 
  
        
        mergeSort(arr, l, m); 
        mergeSort(arr, m+1, r); 
  
        merge(arr, l, m, r); 
    } 
}

unsigned int hash(const char *key) 
{
    unsigned long int value = 0;
    unsigned int key_len = strlen(key);
    int i;
    char ch;

    for (i=0; i < key_len; ++i) 
	{
        value = value+key[i];
        ch=key[i];
    }
    
    value = value % length ;

    return value;
}

void init_array()
{
    int i;
    for (i = 0; i < length; i++) 
    {
		array[i].sorted_key=NULL;
    }
}

int insert(char *value)
{
	char *sorted_value;
	int k,l=0,flag=0,j=0;
	sorted_value=(char*)malloc(sizeof(char));
	for(k=0; k<strlen(value); k++)
    {
      j++;
            					sorted_value[k] = value[k];
                      sorted_value = (char *) realloc(sorted_value, j+1);  
     	
    }
    sorted_value[k]='\0';
	mergeSort(sorted_value, 0,strlen(sorted_value)-1);
    int index = hash(sorted_value);
    int i = index;
    z++;
    //Empty Slot
    if(array[i].sorted_key==NULL)
    {
    	printf("Item:%d has successfully been inserted in the hash table\nLocation:%d\n",z,i);
    	array[i].sorted_key=(char*)malloc(sizeof(char));
     j=0;
        for(k=0; k<strlen(sorted_value); k++)
        {
            j++;
            					array[i].sorted_key[k]=sorted_value[k];
                      array[i].sorted_key = (char *) realloc(array[i].sorted_key, j+1);  
        }
        array[i].sorted_key[k]='\0';
        printf("Sorted Key:%s with value:",array[i].sorted_key);
        struct node* head= NULL;
        
        insert_node(&head,value);
        array[i].hashtable_slot=head;
        printf("%s\n",value);      
	}
	else
	{
		//Searching for matches
		for(j=0; j<strlen(array[i].sorted_key); j++)
    	{
    		if(array[i].sorted_key[j]==sorted_value[j])
    	  	{
     	   		l++;
     	 	}
  		}
   		if(l==strlen(array[i].sorted_key))
  		{
    		flag=1;
		}
		//Match found 
		if(flag==1)
		{
			printf("Key:%s matches with the slot of the hash table\n",array[i].sorted_key);
			struct node* head=array[i].hashtable_slot;
			insert_node(&head,value);
			array[i].hashtable_slot=head;
			printf("Item:%d has successfully been inserted in the hash table\nLocation:%d\n",z,i);
			 printf("Sorted Key:%s with value:",array[i].sorted_key);
			 printf("%s\n",value); 
		}
		//Sorted key doesnt match with the current slot
		else
		{
			printf("Slot in location:%d has already been filled\n",i);
			printf("Searching second half of hash table\n");
    		printf("\n");
    		//Searching for second half of the hash table for a empty slot
			while(i<length)
			{
				if(array[i].sorted_key==NULL)
    			{
    				printf("Item:%d has successfully been inserted in the hash table\nLocation:%d\n",z,i);
	    			array[i].sorted_key=(char*)malloc(sizeof(char));
             		j=0;
    	    		for(k=0; k<strlen(value); k++)
        			{
            			j++;
            					array[i].sorted_key[k]=sorted_value[k];
                      array[i].sorted_key = (char *) realloc(array[i].sorted_key, j+1);  
        			}
              array[i].sorted_key[k]='\0';
        			printf("Value:%s\n",array[i].sorted_key);
        			printf("\n");
        			struct node* head= NULL;
        			insert_node(&head,value);
        			array[i].hashtable_slot=head;
        			printf("Sorted Key:%s with value:",array[i].sorted_key);
			 		printf("%s\n",value); 
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
						if(array[i].sorted_key==NULL)
    					{
    						printf("Item:%d has successfully been inserted in the hash table\nLocation:%d\n",z,i);
    						array[i].sorted_key=(char*)malloc(sizeof(char));
                  j=0;
        					for(k=0; k<strlen(value); k++)
        					{
                      j++;
            					array[i].sorted_key[k]=sorted_value[k];
                      array[i].sorted_key = (char *) realloc(array[i].sorted_key, j+1); 
        					}
                  array[i].sorted_key[k]='\0';
        					printf("Value:%s\n",array[i].sorted_key);
        					printf("\n");
        					struct node* head= NULL;
	        				insert_node(&head,value);
    	    				array[i].hashtable_slot=head;
    	    				printf("Sorted Key:%s with value:",array[i].sorted_key);
							printf("%s\n",value);
    						return 0;
						}
						i--;
					}
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
	array =(struct hashtable*)malloc(length *sizeof(struct hashtable));
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
		printf("\n");
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
	while(ch!='\n')
	{
		array2[j]=ch;
		j++;
		array2 = (char *) realloc(array2, j+1);
		ch=getchar();
	}
  	array2[j]='\0';
	printf("String %s has successfuly been read\n",array2);
	printf("\n");
	printf("Sorting the string\n");
	mergeSort(array2, 0,strlen(array2)-1);
	printf("Searching for:%s in the hash table\n",array2);
	i = hash(array2);
	printf("\n");
	z=0;
	//Slot is empty exiting
	if(array[i].sorted_key==NULL)
 {
   printf("Slot:%d is empty\n",i);
   printf("Exiting\n");
   return 0;
 }
  for(j=0; j<strlen(array2); j++)
  {
     if(array[i].sorted_key[j]==array2[j])
     {
       z++;
     }
  }
  //String matches with the sorted key from the hash table
  if(z==(strlen(array2)))
  {
  		printf("Result of hash function: %d\n",hash(array2));
    	printf("String %s found succcessfully in position %d of the hash table\n",array[i].sorted_key,i);
    	printf("With values:\n");
    	while(array[i].hashtable_slot!=NULL)
    	{
    		printf("%s\n",array[i].hashtable_slot->string);
    		array[i].hashtable_slot=array[i].hashtable_slot->next;
		}
	}
	//String doesnt match,searching for next slot
	else
	{
		printf("String %s not found in position %d of the hash table\n",array2,i);
		printf("Searching the hash table\n");
    	char ch1,ch2;
		for(i=0; i<length; i++)
		{
            printf("Searching %d slot\n",i);
            z=0;
        		if(array[i].sorted_key==NULL)
         		{
             		printf("Slot:%d is empty\n",i);
                printf("\n");
        	 	}
         		else
         		{
  		 		     for(j=0; j<strlen(array[i].sorted_key); j++)
      				 {
                  ch1=array[i].sorted_key[j];
                  ch2=array2[j];
           				if(ch1==ch2)
           				{
                     		z++;
           				}
      				}
      				printf("\n");
					    if(z==(strlen(array[i].sorted_key))-1)
 		  			  {
    				  	flag=1;
    					  printf("String %s found succcessfully in position %d of the hash table\n",array2,i);
    					  while(array[i].hashtable_slot!=NULL)
    					  {
    					  	printf("%s",array[i].hashtable_slot->string);
    						  array[i].hashtable_slot=array[i].hashtable_slot->next;
						    }
						    printf("Result of hash function: %d\n",hash(array2));
          				break;
					    }
      			} 
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

