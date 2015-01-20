#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"LexerDef.h"
#include"parserDef.h"


/* OP ID
	+ 25
	- 26
	* 27
	/ 28
	@ 29
	< 33
	<= 34
	== 35
	> 36
	>= 37
	=/= 38
	= 39
*/

/* Unwanted tokens
	; 18
	, 19
	[ 14
	] 15
	( 16
	) 17
	end 6
	endif 8*/
    
//table which shows the scope of each function
int k,flag,flagcall;



int check_unwanted(int x)
{
	if(x==18 || x==19 || x==14 || x==15 || x==16 || x==17 || x==6 || x==8 || x==21){return 1;}
	else {return 0;}
}

int check_op(int x)
{
	if(x==25 || x==26 || x==27 || x==28 || x==29 || x==33 || x==34 || x==35 || x==36 || x==37||x==38||x==39){return 1;}
	else {return 0;}
}

int make_AST(treenode *t,int index)
{
	treenode *temp;int flag=0;
	
	int ind=0;
	int j,cnt=0,i,k1=0,p;
	char s[21];
	if(t==NULL){return 0;}
	//strcpy(t->scope,"MAIN");
	if(t->tokenID<100)   //if the node belongs to a terminal
	{
		//printf("%s ",t->scope);
		
		strcpy(t->scope,t->parent->scope);
		if(t->tokenID==1 && t->type>0){t->parent->type=t->type;}
			
		
		if(check_unwanted(t->tokenID)==1)
		{	
			
			
			t->parent->children[index]=NULL;
			free(t);
			return 0;
		}
		if(check_op(t->tokenID)==1)
		{
		t->opID=t->tokenID;t->parent->opID=t->tokenID;
		return 1;
		}
		return 1;
		
	}
	else  //node is a non-terminal
	{	
	   if(t->tokenID==109)
		{
			for(j=0;j<t->no_children;j++)
			{
				flagcall=0;
				if(t->children[j]!=NULL && t->children[j]->tokenID==2)
				{
					
					for(i=0;i<=noFunctions;i++)
					{
						
						if(strcmp(map_function[i],t->children[j]->lexeme)==0){flagcall=1;break;}
					}
				if(flagcall==0){printf("line %d: semantic error: function call before definition\n",t->line_no);break;}
				}
			}
		}//
		if(t->tokenID==110)
		{
			noFunctions++;
			strcpy(t->scope,t->parent->scope);
			for(j=0;j<t->no_children;j++)
			{
				if(t->children[j]!=NULL && t->children[j]->tokenID==2)
				{
					strcpy(s,t->children[j]->lexeme);flag=1;break;
				}
			}
			//printf("%d ",k);
			strcpy(map_function[k],s);k++;flag=0;
			for(j=0;j<k;j++)
			{
				if(strcmp(map_function[j],t->scope)==0)
				{
					ind=j;break;
				}
			}
			
			j=0;i=1;
			function_table[k-1][0]=k-1;
			
			
			while(function_table[ind][j]>=0)
			{
				function_table[k-1][i]=function_table[ind][j];
				//printf("%d ",function_table[k-1][i]);
				
				i++;j++;
				if(function_table[ind][j]==-1){break;}
			}
			printf("\n");		
			strcpy(t->scope,s);
		}
		else
		{
			strcpy(t->scope,t->parent->scope);
		}
		for(j=0;j<t->no_children;j++)
		{	
			
			if(t->children[j]!=NULL)
			{
			temp=t->children[j];
			//k1++;
			p=make_AST(t->children[j],j);
			
			if(p==1){k1++;}
			
			}
		}
		
		
		if(k1==0)
		{
		t->parent->children[index]=NULL;
		free(t);
		}
		
		if(k1==1|| t->tokenID==127)
		{
			flag=0;
			for(j=0;j<t->no_children;j++)
			{
			    if(t->children[j]!=NULL){flag=j;break;}
			}
			
			
			t->opID=t->children[flag]->opID;
			if(t->children[flag]->type>0){t->type=t->children[flag]->type;}
			t->parent->children[index]=t->children[flag];
			//free(t);
		}
		if(k1>1 && t->tokenID!=127)
		{
			flag=-1;
			for(j=0;j<t->no_children;j++)
			{
			
				if(t->children[j]!=NULL && check_op(t->children[j]->tokenID)==1)
				{
					flag=j;t->opID=t->children[j]->opID;
					if(t->children[j]->type>0){t->type=t->children[j]->type;}
					break;
				}
			}
			if(flag>-1){free(t->children[flag]);t->children[flag]=NULL;}
		}
		
		
	}
	 
	return 1;
}
				
			
void final_AST(treenode *t,int index)
{
     int j,k1=0,q=-1,m;
     treenode *temp;
     if(t->tokenID<100){return;}
     if(t==NULL){return;}
     		
     for(j=0;j<t->no_children;j++)
     {
     	
     	if(t->children[j]!=NULL)
     	{
     		
     		final_AST(t->children[j],j);
     		//if(t->children[j]!=NULL && t->children[j]->tokenID==1 ){t->type=t->children[j]->type;break;}
     		if(t->children[j]!=NULL){k1++;}
     	}
     }
     if(k1==0 && t->opID==0)
     {
		t->parent->children[index]=NULL;
		free(t);
     }
		
    if(k1==1)
    {
			flag=0;
			
			for(j=0;j<t->no_children;j++)
			{
			    if(t->children[j]!=NULL){q=j;flag=1;break;}
			}
			temp=t;
			if(flag==1)
			{
			
			if(t->opID>0){t->parent->opID=t->opID;}
			if(t->type>0){t->parent->type=t->type;}
			t->parent->children[index]=t->children[q];
			//free(temp);
			}flag=0;
						
      }      
	return;
}		

void semantic_checker(treenode *t)
{
	//rule1 in type checking.
	//rule2 in type checking.
	rule3Main(AST.root,map_function,noFunctions);
	rule4main(AST.root,map_function,noFunctions);
	//rule 5 is handled through rule4 itself.
	rule6(AST.root);
	rule7(AST.root,noFunctions,map_function,function_table);
	rule8main(AST.root,map_function,noFunctions);
	rule9(AST.root);	
	rule10(AST.root);
	//rule11 
	//rule12 is done
	//rule13 in type checking.
	rule15(AST.root,noFunctions,map_function,function_table);
	
}				


void generate_AST(tree T)
{
	int i;
	AST.size=0;
	noFunctions=0;
	strcpy(map_function[0],"MAIN");
	memset(function_table,-1,sizeof(function_table));
	function_table[0][0]=0;
	k=1;
	int p;
	flag=0;
	treenode *t;
	t=(treenode*)malloc(sizeof(treenode));
	t=T.root;
	strcpy(t->scope,"MAIN");
	AST.root=t;
	strcpy(AST.root->scope,"MAIN");
	p=make_AST(AST.root,-1);
	final_AST(AST.root,-1);	
	fill_symbol_table();
	
	
	return;
}

void errorchecking()
{
	MatrixDriver(AST.root); // matrix size calculation
	StringSizeDriver(AST.root); // string size calc.
	sizeExp(AST.root);
	type_checker();
	//printt(AST.root);
	int j;
	//for(i=0;i<6;i++){for(j=0;j<6;j++) {printf("%d ",function_table[i][j]);} printf("\n");}
	
	matrixCompatibility(AST.root);
	matrixAssignment(AST.root);
	semantic_checker(AST.root);
	printf("\n\n");return;
}
	

