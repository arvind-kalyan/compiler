#include<stdio.h>
#include<ctype.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include"LexerDef.h"
#include"parserDef.h"


int type_flag,aflag,type,flags;

//check if correct type is used in assignment statements
void typechecking_arith(treenode *t,int index)
{
	int j,f1=0,f2=0;
	if(type_flag==1){return;}
	if(t==NULL){return ;}
	
			
			
	
	if(t->tokenID==123||t->tokenID==105||t->tokenID==106||t->tokenID==129||t->tokenID==120)
	{
		if(flags==1){flags=0;}
		aflag=1;
		type=-1;
		for(j=0;j<t->no_children;j++)
		{
			if(t->children[j]!=NULL && t->children[j]->tokenID==121){flags=1;}
			typechecking_arith(t->children[j],j);
		}
		
		for(j=0;j<t->no_children;j++)
		{
			
			if(t->children[j]!=NULL && t->children[j]->type>0)
			{
				if(type==-1){type=t->children[j]->type;
				continue;
				}
				else
				{
				if(t->children[j]->type!=type && t->children[j]->opID!=29 && flags==0)
	{printf("line %d: type mismatch error\n",t->line_no);}
					
				}
				
				if(t->children[j]->type==2)
				{
		if(t->opID!=25 && t->opID!=39 && t->opID!=0){type_flag=1;printf("line %d: invalid operation on data type\n",t->line_no);}
				}
				if(t->children[j]->type==4)
				{
		if(t->opID!=39 && t->opID!=25 && t->opID!=26){type_flag=1;printf("line %d: invalid operation on data type\n",t->line_no);break;}
				}
			}
		}
		//printf("\n");
		if(t->tokenID!=120 && t->tokenID!=129){aflag=0;}
		else 
		{
			t->type=type;
		}	
			type_flag=0;return;
	}
	
				
			
	else
	{
		
	if(t->tokenID==1 && aflag>0)
	{
		if(aflag!=3)
		{
			
			if(CHECK_DECLARED(t->lexeme,t->scope)==0){
			printf("line %d: variable %s is not declared\n",t->line_no,t->lexeme);
				type_flag=1;
				
			}
			
					
			
		
		}
		else
		{
		if(type==-1){type=t->type;}
		}
				
	}
	else
	{
	if(t->tokenID==121){
		aflag=3;
		for(j=0;j<t->no_children;j++)
		{
			typechecking_arith(t->children[j],j);
		}
		aflag=1;
	}
	else
	{
		
	for(j=0;j<t->no_children;j++)
		{
			typechecking_arith(t->children[j],j);
		}
	}
	}
	}
	return;
}


void type_checker()
{
	type_flag=0;int i;
	flags=0;
	type=-1;
	aflag=0;
	typechecking_arith(AST.root,-1);
	//generate_code();
	
	return;
}
	
	
