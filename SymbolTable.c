#include<stdio.h>
#include<ctype.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include"LexerDef.h"
#include"parserDef.h"

/*
type int 1
type string 2
type real 3
type matrix 4
*/

unsigned hashFunc(char* s) {

    unsigned hval = 0;
    while (*s != '\0') {
        hval = (hval << 4) + *s;
        s++;
    }
    return hval;
}
Link CREATE(char *lexeme, int type, char *scope, int size1,int size2, int tokenID,char *val) // Creates a new bucket to be inserted.
{
    Link Temp;
    Temp = (Link) malloc(sizeof(bucket));
    strcpy(Temp -> lexeme,lexeme);
    strcpy(Temp -> value,val);
    Temp -> type = type;
    strcpy(Temp -> scope,scope);
    Temp -> size1 = size1;
    Temp -> size2 = size2;
    Temp -> tokenID = tokenID;
    Temp -> next = NULL;
    return Temp;
}

void INSERT(char *lexeme,int type,char *scope, int size1,int size2, int tokenID,char *val) // insert into hashtable
{
    int hashIndex = hashFunc(lexeme)%TableSize;
    Link newbucket = CREATE(lexeme,type,scope,size1,size2,tokenID,val);
    if(!hashTable[hashIndex].head)
    {
        hashTable[hashIndex].head = newbucket;
        hashTable[hashIndex].count = 1;
        return;
    }
    newbucket->next = (hashTable[hashIndex].head);
    hashTable[hashIndex].head = newbucket;
    hashTable[hashIndex].count++;
    return;

}

int LOOKUP(char *lexeme,char *scope) // Looking up a lexeme.
{
    int hashIndex = hashFunc(lexeme)%TableSize;
    Link mybucket;
    int found=0;
    mybucket = hashTable[hashIndex].head;
    if(!mybucket)
    {
        return 0;
    }
    while(mybucket != NULL)
    {
        if(!strcmp(mybucket->lexeme,lexeme) && !strcmp(mybucket->scope,scope))
        {
            return mybucket->type;
        }
        mybucket = mybucket->next;
    }
    return 0;
}

void display() { // display hashtable contents.

        struct bucket *mybucket;
        int i;
        printf("\n\n\t\t\t ***** SYMBOL TABLE *****\n\n");
        for (i = 0; i < TableSize; i++) {
                if (hashTable[i].count == 0)
                        continue;
                mybucket = hashTable[i].head;
                if (!mybucket)
                        continue;
                //printf("\nIndex: %d",i);
                printf("\nIdentifier-name    scope      type    offset\n\n");
                while (mybucket != NULL) {
                        printf("%-10s     ", mybucket->lexeme);
                        
                        printf("%-10s  ", mybucket->scope);
                        printf("%-10d  ", mybucket->type);
                        
                        if(mybucket->type == 4) printf("%-10d  ", (mybucket->size1)*(mybucket->size2));
                        else printf("%-10d  ", mybucket->size1);                 
                        
                        
                       // printf("%-10d \n", mybucket->tokenID);
                        mybucket = mybucket->next;
                }
        }
        return;
  }

int flag,flag1,flagerr,xtype;


int CHECK_DECLARED(char *lexeme,char *scope)
{
	int funcid=-1,i;
	char s[120];
	for(i=0;i<=noFunctions;i++)
	{
		if(strcmp(map_function[i],scope)==0){funcid=i;break;}
	}
	for(i=0;function_table[funcid][i]!=-1;i++)
	{
		if(LOOKUP(lexeme,map_function[function_table[funcid][i]])>0)
		{
			return 1;
		}
	}
	return 0;
}
	
		

void fill_table(treenode *t,int type)
{
	int i,type1=0,x,j;
	t->type=type;
	//if(flagerr==1){return;}
	if(t==NULL){return;}
	if(t->tokenID==5){t->type=2;}
	if(t->tokenID==3){t->type=1;}
	if(t->tokenID==4){t->type=3;}
		
	if(t->tokenID==104||t->tokenID==111)
	{
		flag=1;
		for(i=0;i<t->no_children;i++)
		{
			if(t->children[i]!=NULL && t->children[i]->tokenID==9)
			{
				type1=1;
			}
			if(t->children[i]!=NULL && t->children[i]->tokenID==11)
			{
				type1=2;
			}
			if(t->children[i]!=NULL && t->children[i]->tokenID==10)
			{
				type1=3;
			}
			if(t->children[i]!=NULL && t->children[i]->tokenID==12)
			{
				type1=4;
			}
			t->type=type1;
			if(t->children[i]!=NULL)
			{
			fill_table(t->children[i],type1);
			}
		}
		flag=0;
	}
	
	if(t->tokenID==1 && flag==1)
	{
		x=CHECK_DECLARED(t->lexeme,t->scope);
		if(x==1){flagerr=x;}
		if(x==1)
		{
			printf("line %d : The variable %s is declared more than once\n",t->line_no,t->lexeme);
			flagerr=1;
			return;
		}
		if(type == 1 || type == 3){INSERT(t->lexeme,type,t->scope,4,0,t->tokenID,"NULL");}
				
		char s1[23];
		strcpy(s1,t->lexeme);
		strcpy(var_table[novars].var,s1);
		var_table[novars].type=t->type;
		novars++;
		return;
	}
	if(t->tokenID==1 && flag==0)
	{
		for(j=0;j<novars;j++)
		{
			if(strcmp(var_table[j].var,t->lexeme)==0)
			{
				t->type=var_table[j].type;
				break;
			}
		}
	}
	if(t->tokenID!=104 && t->tokenID!=111)
	{
	for(i=0;i<t->no_children;i++)
	{
		if(t->children[i]!=NULL)
		{
			fill_table(t->children[i],type);
		}
	}
	}
	if(t->tokenID==129 || t->tokenID==120 || t->tokenID==123)
		{
			for(j=0;j<t->no_children;j++)
			{
		if(t->children[j]!=NULL && t->children[j]->type>1 && t->children[j]->tokenID==1 ){t->type=LOOKUP(t->children[j]->lexeme,t->children[j]->scope);break;}
			}
		}
	return;
}	

void UpdateMatrixSize(char *lexeme, char *scope,int m,int n)
{
	int hashIndex = hashFunc(lexeme)%TableSize;
    Link mybucket;
    int found=0;
    mybucket = hashTable[hashIndex].head;
    if(!mybucket)
    {
        return;
    }
    while(mybucket != NULL)
    {
        if(strcmp(mybucket->lexeme,lexeme)==0 && strcmp(mybucket->scope,scope)==0)
        {
        
            mybucket->size1 = m;
            mybucket->size2 = n;
            
            break;
        }
        mybucket = mybucket->next;
    }
    return;

}					
	

int LOOKUP1(char *lexeme,char *scope) // Looking up a lexeme.
{
    int hashIndex = hashFunc(lexeme)%TableSize;
    Link mybucket;
    int found=0;
    mybucket = hashTable[hashIndex].head;
    if(!mybucket)
    {
        return 0;
    }
    while(mybucket != NULL)
    {
        if(!strcmp(mybucket->lexeme,lexeme) && !strcmp(mybucket->scope,scope))
        {
            return mybucket->size1;
        }
        mybucket = mybucket->next;
    }
    return 0;
}

int LOOKUP2(char *lexeme,char *scope) // Looking up a lexeme.
{
    int hashIndex = hashFunc(lexeme)%TableSize;
    Link mybucket;
    int found=0;
    mybucket = hashTable[hashIndex].head;
    if(!mybucket)
    {
        return 0;
    }
    while(mybucket != NULL)
    {
        if(!strcmp(mybucket->lexeme,lexeme) && !strcmp(mybucket->scope,scope))
        {
            return mybucket->size2;
        }
        mybucket = mybucket->next;
    }
    return 0;
}

int LOOKUPSIZE(char *lexeme) // Looking up a lexeme.
{
    int hashIndex = hashFunc(lexeme)%TableSize;
    Link mybucket;
    int found=0;
    mybucket = hashTable[hashIndex].head;
    if(!mybucket)
    {
        return 0;
    }
    while(mybucket != NULL)
    {
        if(!strcmp(mybucket->lexeme,lexeme))
        {
            return mybucket->size1;
        }
        mybucket = mybucket->next;
    }
    return 0;
}

void DELETE(char *lexeme,char *scope) 
{
	int hashIndex = hashFunc(lexeme)%TableSize;
	Link mybucket= hashTable[hashIndex].head;
	if(!mybucket)
    	{
        return ;
   	}
   	if(!strcmp(mybucket->lexeme,lexeme))
   	{
   		hashTable[hashIndex].head=mybucket->next;
   		free(mybucket);return;
   	}
   	while(mybucket != NULL)
    {
        if(!strcmp(mybucket->next->lexeme,lexeme) && !strcmp(mybucket->scope,scope))
        {
            	mybucket->next=mybucket->next->next;
            	
   		free(mybucket);return;
        }
        mybucket = mybucket->next;
    }
    return ;
}

void showSymbolTable()
{
	printf("Success!\n");display(); // display hash table contents
}


void fill_symbol_table()
{
    TableSize = 20;
    novars=0;
    xtype=0;
    flag=0;flag1=0;
    flagerr=0;
    hashTable  = (Hashtable*) calloc(TableSize,sizeof(Hashtable));
    
    fill_table(AST.root,0);
    
    
    //printf("\n\n");
    
    return ;

}



