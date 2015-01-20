#include<stdio.h>
#include<ctype.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include"LexerDef.h"
#include"parserDef.h"


int code_index,flag_code,op;
codegen code[92000];
int ifbl,elsebl;

typedef struct var
{
	int type;
	char lexeme[30];
}var;

var variables[10000];
int no_variables;
char label1[20],label2[20];
int set_label1;


int check(char *lexeme)
{
	int i;
	for(i=0;i<no_variables;i++)
	{
		if(strcmp(variables[i].lexeme,lexeme)==0){return 1;}
	}
	return 0;
}

void add(char *lexeme,int type)
{
	variables[no_variables].type=type;
	strcpy(variables[no_variables].lexeme,lexeme);no_variables++;
	return;
}

void code_generate(treenode *t,int index)
{
	int j;codegen c;int f1=0,f2=0,f3=0;char res[100],s1[100];int type;
	if(t==NULL){return;}
	if(t->tokenID==7){elsebl=1;}
	if(t->tokenID<100){return;}
	if(t->tokenID==107){
	
	ifbl=1;
	for(j=0;j<t->no_children;j++)
	{
		code_generate(t->children[j],j);
	}
	ifbl=0;elsebl=0;
	}
	else
	{
	for(j=0;j<t->no_children;j++)
	{
		code_generate(t->children[j],j);
	}
	}	
	if(t->opID>0)
	{
		
		c.opID=t->opID;
		strcpy(c.op1,"NULL");
		strcpy(c.op2,"NULL");
		for(j=0;j<t->no_children;j++)
		{
			if(t->children[j]!=NULL)
			{
				if(f1==0){type=t->children[j]->type;strcpy(c.op1,t->children[j]->lexeme);f1=1;continue;}
				if(f2==0){strcpy(c.op2,t->children[j]->lexeme);f2=1;continue;}	
			}
		}
		strcpy(res,"t");
		
		c.type=type;
		c.ifbl=ifbl;
		c.elsebl=elsebl;
		sprintf(s1, "%d",(code_index)%15);
		strcat(res,s1);
		if(c.opID!=39){strcpy(c.res,res);}
		else {strcpy(c.res,"NULL");}
		code[code_index]=c;
		
		code_index++;
		if(t->tokenID==120||t->tokenID==123){strcpy(t->lexeme,res);}
		else {strcpy(t->lexeme,res);strcpy(t->parent->lexeme,res);}
	
		
	}
	
}

void disp(FILE *f,codegen code1)
{
	fprintf(f,"\nmov DX,offset %s\n",code1.op1);
	fprintf(f,"mov AH,09H\n");
	fprintf(f,"INT 21H\n");
	fprintf(f,"mov AH,4C00H\n\n");
	return;
}

void input(FILE *f,codegen code1)
{
	fprintf(f,"\nmov DX,offset %s\n",code1.op1);
	fprintf(f,"mov AH,3FH\n");
	fprintf(f,"INT 21H\n");
	fprintf(f,"mov AH,4C00H\n\n");
	return;
}

void concat(FILE *f,codegen code1)
{
}	
	
	
void ifelse(FILE *f,codegen code1,int index)
{
	int i;char s[100];
	
	
	if(code1.elsebl==0)
	{
		if(set_label1==0){strcpy(label1,"L");sprintf(s,"%d",index);strcat(label1,s);set_label1=1;}
		fprintf(f,"mov ax,%s\n",code1.op1);
		fprintf(f,"mov bx,%s\n",code1.op2);
		fprintf(f,"cmp ax,bx\n");
		
		if(code1.opID==33){fprintf(f,"jnl %s\n",label1);}
		if(code1.opID==34){fprintf(f,"jnle %s\n",label1);}
		if(code1.opID==35){fprintf(f,"jne %s\n",label1);}
		if(code1.opID==36){fprintf(f,"jle %s\n",label1);}
		if(code1.opID==37){fprintf(f,"jl %s\n",label1);}
		if(code1.opID==38){fprintf(f,"je %s\n",label1);}
		
		
	}
	else
	{
		fprintf(f,"%s:\n",label1);
	}
	return;
		
}

void printsize(FILE *f,codegen code1)
{
	int size=LOOKUPSIZE(code1.op1);
	
	fprintf(f,"mov AX,%d\n",size);
	fprintf(f,"mov %s,AX\n\n",code1.res);
	return;
}	

//opID,op1,op2,res

void make_asm(char *outputfile)
{
	int i;char s[100];
	FILE *f=fopen(outputfile,"w");
	for(i=0;i<code_index;i++)
	{
		if(code[i].type==4){continue;}
		
		if(check(code[i].op1)==0)
		{
		 	if(code[i].op1[0]!='"'  && !isdigit(code[i].op1[0])){
			add(code[i].op1,code[i].type);
			if(code[i].type==1){fprintf(f,"%s dw 0\n",code[i].op1);}
			if(code[i].type==2){fprintf(f,"%s db 120 dup (0)\n",code[i].op1);}
			if(code[i].type==3){fprintf(f,"%s dw 0\n",code[i].op1);}
			}
		}
		if(check(code[i].op2)==0 && strcmp(code[i].op2,"NULL")!=0 )
		{
			if(code[i].op2[0]!='"' && !isdigit(code[i].op2[0])){
			add(code[i].op2,code[i].type);
			if(code[i].type==1){fprintf(f,"%s dw 0\n",code[i].op2);}
			if(code[i].type==2){fprintf(f,"%s db 120 dup (0)\n",code[i].op2);}
			if(code[i].type==3){fprintf(f,"%s dw 0\n",code[i].op2);}}
		}
		if(strcmp(code[i].res,"NULL")!=0 && check(code[i].res)==0)
		{
			if(code[i].res[0]!='"'  && !isdigit(code[i].res[0])){
			add(code[i].res,code[i].type);
			if(code[i].type==1){fprintf(f,"%s dw 0\n",code[i].res);}
			if(code[i].type==2){fprintf(f,"%s db 120 dup (0)\n",code[i].res);}
			if(code[i].type==3){fprintf(f,"%s dw 0\n",code[i].res);}}
		}
	}
	
	for(i=0;i<code_index;i++)
	{
		if(code[i].opID==29){printsize(f,code[i]);}	
		if(code[i].ifbl==1 && code[i].opID>=33 && code[i].opID<=38)
		{
			ifelse(f,code[i],i);
			continue;
		}
		if(code[i].opID==24)
		{	
			disp(f,code[i]);
			continue;
		}
		if(code[i].opID==23)
		{
			input(f,code[i]);
			continue;
		}
		if(strcmp(code[i].op1,"NULL")!=0){fprintf(f,"mov AX, %s\n",code[i].op1);}
		if(strcmp(code[i].op2,"NULL")!=0){fprintf(f,"mov BX,%s\n",code[i].op2);}
		
		
		if(code[i].opID==39)
		{
			fprintf(f,"mov AX,BX\n");
		}
		if(code[i].opID==25)
		{
			if(code[i].type==1)
			{
			fprintf(f,"add AX,BX\n");
			fprintf(f,"mov CX,AX\n");
			}
			else {concat(f,code[i]);}
		}
		if(code[i].opID==26)
		{
			fprintf(f,"sub AX,BX\n");
			fprintf(f,"mov CX,AX\n");
		}
		if(code[i].opID==27)
		{
			fprintf(f,"imul BX\n");
			fprintf(f,"mov CX,AX\n");
		}
		if(code[i].opID==28)
		{
			fprintf(f,"idiv BX\n");
			fprintf(f,"mov CX,AX\n");
		}
		
			
		
		
		if(strcmp(code[i].res,"NULL")!=0)
		{
			fprintf(f,"mov %s,CX\n",code[i].res);
		}
		else
		{
			fprintf(f,"mov %s,AX\n",code[i].op1);
		}
		if(code[i].elsebl==0 && code[i+1].elsebl==1)
		{
		strcpy(label2,"L");sprintf(s,"%d",i);strcat(label2,s);
		fprintf(f,"jmp %s\n",label2);
		fprintf(f,"%s: \n",label1);
		}
		if(code[i].elsebl==1 && code[i+1].elsebl==0)
		{
		fprintf(f,"%s: \n",label2);set_label1=0;
		}
		if(code[i].ifbl==1 && code[i+1].ifbl==0 && code[i].elsebl==0)
		{
		fprintf(f,"%s: \n",label1);set_label1=0;
		}
		
	}
	
	fprintf(f,"ret\n");	
			
		
		
	
}
	

void generate_code(char *outputfile)
{
	op=0;no_variables=0;
	code_index=0;flag_code=0;
	code_generate(AST.root,-1);
	int i;
	ifbl=0;elsebl=0;
	set_label1=0;
	/* Displays the three address code
	for(i=0;i<code_index;i++)
	{
		printf("%d %s %s %s %d %d %d\n",code[i].opID,code[i].op1,code[i].op2,code[i].res,code[i].type,code[i].ifbl,code[i].elsebl);
	}*/
	make_asm(outputfile);
	return ;
}
	
	
/**/	
	

