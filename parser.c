	// KEVIN CHITTINAPPILY SEBASTIAN - 2011A7PS131P
	// ARVIND K - 2011C6PS666P

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"parserDef.h"

#include"LexerDef.h"


sets S[150];
int Gno;
grammar G[150];

char token_table[40][20]={
             {' '},
		     {'I','D'},
		     {'F','U','N','I','D'},
		     {'N','U','M'},
		     {'R','N','U','M'},
		     {'S','T','R'},
		     {'E','N','D'},
		     {'E','L','S','E'},
		     {'E','N','D','I','F'},
		     {'I','N','T'},
		     {'R','E','A','L'},
		     {'S','T','R','I','N','G'},
		     {'M','A','T','R','I','X'},
		     {'_','M','A','I','N'},
		     {'['},
		     {']'},
		     {'('},
		     {')'},
		     {'S','E','M','I','C','O','L','O','N'},
		     {'C','O','M','M','A'},
		     {'I','F'},
		     {'E','P','S','I','L','O','N'},
		     {'F','U','N','C','T','I','O','N'},
		     {'R','E','A','D'},
		     {'P','R','I','N','T'},
		     {'P','L','U','S'},
		     {'M','I','N','U','S'},
		     {'M','U','L'},
		     {'D','I','V'},
		     {'S','I','Z','E'},
		     {'A','N','D'},
		     {'O','R'},
		     {'N','O','T'},
		     {'L','T'},
		     {'L','E'},
		     {'E','Q'},
		     {'G','T'},
		     {'G','E'},
		     {'N','E'},
		     {'A','S','S','I','G','N','O','P'}};

//***************************************LIST OF NON-TERMINALS***********************************



char non_terminal_table[44][30]={
    {'<','m','a','i','n','F','u','n','c','t','i','o','n','>'},
    {'<','S','t','m','t','A','n','d','F','u','n','c','D','e','f'},
    {'<','s','t','m','t','O','r','F','u','n','c','D','e','f'},
    {'<','s','t','m','t','>'},
    {'d','e','c','l','a','r','a','t','i','o','n','s','t','m','t'},
    {'<','a','s','s','g','n','s','t','m','t','-','t','1','>'},
    {'<','a','s','s','g','n','s','t','m','t','-','t','2','>'},
    {'<','i','f','s','t','m','t','>'},
    {'<','i','o','s','t','m','t','>'},
    {'<','f','u','n','c','a','l','l','s','t','m','t','>'},
    {'<','F','u','n','c','D','e','f','>'},
    {'p','a','r','a','m','l','i','s','t'},
    {'t','y','p','e'},
    {'r','e','m','l','i','s','t'},
    {'v','a','r','l','i','s','t'},
    {'m','o','r','e','-','i','d','s'},
    {'l','e','f','t','s','i','d','e','S','i','n','g','l','e','V','a','r'},
    {'r','i','g','h','t','s','i','d','e','t','y','p','e','1'},
    {'l','e','f','t','s','i','d','e','L','i','s','t','V','a','r'},
    {'r','i','g','h','t','s','i','d','e','t','y','p','e','2'},
    {'a','r','i','t','h','E','x','p'},
    {'s','i','z','e','E','x','p'},
    {'y','y'}, //
    {'B','o','o','l','E','x','p'},
    {'o','t','h','e','r','S','t','m','t','s'},
    {'e','x','t','r','a'},
    {'i','n','p','P','a','r','a','m','L','i','s','t'},
    {'v','a','r'},
    {'L','i','s','t','V','a','r'},
    {'a','r','i','t','h','T','e','r','m'},
    {'o','p','L','o','w','P'},
    {'f','a','c','t','o','r'},
    {'o','p','H','i','g','h','P'} ,
     {'L','o','g','O','p'},
     {'c','o','n','s','v','a','r'},
     {'r','e','l','o','p'},
     {'m','a','t','e','l','e','m'},
     {'m','a','t','r','i','x'},
     {'r','o','w','s'},
     {'r','o','w'},
      {'r','e','m','C','o','l','E','l','e','m'},
      {'X'},
      {'Y'},
      {'Z'}
      };


stack push(stack s,int val[],int n,treenode *parent,char *str,int l,int ruleno)
{
	node *temp;
	treenode *t;

	int i,j;

	for(i=n-1;i>=0;i--)
	{
		temp=(node *)malloc(sizeof(node));
		t=(treenode *)malloc(sizeof(treenode));
		t->tokenID=val[i];
		t->opID=0;
		t->parent=parent;
		t->ruleno=ruleno;
		strcpy(t->lexeme,str);
		//strcpy(t->scope,"MAIN");
		t->line_no=l;
		for(j=0;j<9;j++)
		{
			t->children[j]=NULL;
			
		}
		t->no_children=0;
		
		temp->symbolID=val[i];
		temp->link=s.top;
		temp->pointer=t;
		parent->children[i]=t;
		parent->no_children++;
		s.top=temp;
		s.size++;
	}



	return s;

}

int top_stack(stack s)
{
	return s.top->symbolID;
}

stack pop(stack s,int a[],int n,char *str,int line,int ruleno)
{
	int i;
	treenode *parent,*child;
	node *temp;

	if(s.size>0)
	{
	parent=(treenode *)malloc(sizeof(treenode));
	parent=s.top->pointer;
	temp=s.top;
	if(n==0)
        {
		strcpy(parent->lexeme,str);
		parent->line_no=line;
	}
	s.top=s.top->link;
        
        	
	s=push(s,a,n,parent,str,line,ruleno);
	free(temp);
	s.size--;
	}
	return s;
}

void print(stack s)
{
	node *temp;
	temp=s.top;
	while(temp!=NULL)
	{
	   printf("%d ",temp->symbolID);
	   temp=temp->link;
	}
	return;
}

void printt(treenode *t)
{
	if(t==NULL){return;}
	treenode *temp;
	temp=t;
	int i,k=0;
	if(temp!=NULL)
	{
		if(temp->tokenID>=40){printf("(%d ",temp->tokenID);}
		else {printf("(%s ",token_table[temp->tokenID]);}
		for(i=0;i<t->no_children;i++)
		{
			printt(t->children[i]);
		}
		printf(")");

	}
	return;
}

void print_dfs(treenode *t,treenode *p)
{
	if(t==NULL){return;}
	treenode *temp;
	int i;
	double x=-1;
	temp=t;
	if(temp!=NULL)
	{
		if(temp->tokenID<40)
		{
			if(temp->tokenID==3){x=atof(t->lexeme);}
			if(temp->tokenID==4){x=atof(t->lexeme);}

			printf("%-25s   %-5d  %-15s %-15f   %-15s  %-10s   %-10s \n",t->lexeme,t->line_no,token_table[t->tokenID],x,non_terminal_table[p->tokenID-100],"YES","------");
			
		}
		else
		{
			printf("%-25s   %-5d   %-15s  %-15lf  %-15s  %-10s  %-10s \n","----",t->line_no,"-----",x,non_terminal_table[p->tokenID-100],"NO",non_terminal_table[t->tokenID-100]);
		}
		for(i=0;i<t->no_children;i++)
		{
			print_dfs(t->children[i],t);
		}
	}
	return;
}


void print_Parsetree(char *outfile)
{
	FILE *f=fopen(outfile,"w");
	if(f==NULL){printf("Error opening grammar\n");return ;}
	printf("\n\nLEXEME                LINENO          TOKEN          VALUE         PARENT_SYMBOL    isLEAFNODE     NODE_SYMBOL \n");
	printf("************************************************************************************************************ \n");
	//print_dfs(T.root,f,T.root);
	generate_AST(T);
	print_dfs(AST.root,AST.root);
	return;
}

bool isTerminal(int s)//returns true if given symbol is terminal
{
    if( s <= 39) return 1;
    return 0;
}

void populateGrammar(char str[],int ruleno)
{
        char *pch;
        int k=0;
        int listno=0;
        pch = strtok (str," ");
        while (pch != NULL)
        {
            int d = atoi(pch);
            if(d>maxnt) maxnt=d;
            G[ruleno].ruleNumber = ruleno;
            if(k==0) {G[ruleno].nt = d; k++;}
            else if(d != 0) G[ruleno].list[listno++] = d;
            pch = strtok (NULL, " ");
        }
        G[ruleno].listno=listno;
}

void populateFollow(char str[])
{
        char *pch;
        int k=0;
        int ntname;
        int listno=0;
        //printf("pop\n");
        pch = strtok (str," ");
        while (pch != NULL)
        {
           // printf("ennada\n");
            int d = atoi(pch);
            if(d==0) {}
            else
            {
                 if(k==0){ ntname=d;k=1;}
                else
                {
                S[ntname].follow[listno++]=d;
                }
            }

            pch = strtok (NULL, " ");
        }
        S[ntname].followno=listno;
}


void followSets()
{
    FILE *f = fopen("INPUT-Follow Sets.txt","r");
    char temp[100];
    while(fgets(temp,100,f) != NULL)
    {
        populateFollow(temp);
    }
    fclose(f);

}

int createGrammar(FILE *fp,grammar G[])  // main func to create grammar
{
    ruleno=1;
    while(fgets(line,70,fp) != NULL)
    {
        if(line[0]=='/') continue;
        populateGrammar(line,ruleno);
        ruleno++;
    }
    return ruleno;
}

void addNullable(int s)
{
     if(S[s].eps ==1)
        {
            S[s].first[S[s].firstno++]=21; // epsilon is 21
        }


}
//Generating first and follow sets
//.....................................................................................................................
void firstSets(int s, int Gno)
{

    int i,j,k;
    bool flag = 0;
    if(S[s].firstno > 0)return;
    for(i=1;i<Gno;i++)
    {
        if(s==G[i].nt)
        {
            flag = 0;
            if(G[i].list[0]==21)
            {
                S[s].eps=1;
                addNullable(s);
                continue;
            }
            for(j=0;!isTerminal(G[i].list[j])&& j < G[i].listno;j++)
            {
                firstSets(G[i].list[j],Gno);
                for(k=0;k<=60;k++)
                    if(S[G[i].list[j]].ft[k]==1 && S[s].ft[k]==0)
                    {
                        S[s].ft[k] = 1;
                        S[s].first[S[s].firstno++] = k;
                        printf("");
                    }
                if(S[G[i].list[j]].eps==0)
                    {
                        flag =1;
                        break;
                    }

            }
            if(flag==0&&j<G[i].listno)
            {
                S[s].ft[G[i].list[j]] = 1;
                S[s].first[S[s].firstno++] = G[i].list[j];
            }
        }
    }
}

void initTerminalSets(sets S[])
{
    int i;
    for(i=1;i<=39;i++)
    {
        S[i].nt = i;
        S[i].first[0]=i;
        S[i].firstno=1;
    }
}

void initSets(int Gno)
{

    int i,j,x;
    for(i=100;i<=maxnt;i++)
    {
        S[i].nt = i;
        S[i].firstno=0;
        S[i].followno=0;
        for(j=0;j<=60;j++)S[i].ft[j]=0;
        for(j=0;j<=60;j++)S[i].fw[j]=0;
        S[i].eps=0;
    }
    initTerminalSets(S);  // TERMINALS

    for(i=100;i <=maxnt;i++)
        firstSets(i,Gno);  // FIRST sets

    followSets(); // FOLLOW SETS


}
void printFirst(sets S[])
{
    FILE *fp = fopen("OUTPUT-First Sets.txt","w");
    if(fp==NULL) { printf("Some error in printing First sets !\n"); return; }
    int i,j;
    for(i=1;i<=39;i++)
    {
        fprintf(fp,"%d ",S[i].nt);
        for(j=0;j<S[i].firstno;j++)
            fprintf(fp, "%d ", S[i].first[j]);

        fprintf(fp,"\n");
    }
    for(i=100;i<=maxnt;i++)
    {
        fprintf(fp,"%d ",S[i].nt);
        for(j=0;j<S[i].firstno;j++)
            fprintf(fp, "%d ", S[i].first[j]);

        fprintf(fp,"\n");
    }
    fclose(fp);
}
void printFollow(sets S[])
{
    FILE *fp = fopen("OUTPUT-Follow Sets.txt","w");
    if(fp==NULL) { printf("Some error in printing Follow sets !\n"); return; }
    int i,j;
    for(i=100;i<=maxnt;i++)
    {
        fprintf(fp,"%d : ",S[i].nt);
       for(j=0;j<S[i].followno;j++)
          fprintf(fp, "%d ", S[i].follow[j]);
        fprintf(fp,"\n");
    }

}






void addtoTable(int nt, int t, int ruleno, Table T[][45])//insert rule in table
{
    T[nt][t]=ruleno;
}
void initTable(Table T[][45])
{
    int i,j;
    for(i=0;i<150;i++)
        for(j=0;j<45;j++)
        T[i][j]=-1;
}

void createParseTable(Table T[][45],int Gno) // create parse table
{
    int i,j;
    for(i=1;i<Gno;i++)
    {
        for(j=0;j<S[G[i].list[0]].firstno;j++)
            {  if(S[G[i].list[0]].first[j] != 21)
                    addtoTable(G[i].nt,S[G[i].list[0]].first[j],i,T);
            }
        if(S[G[i].list[0]].eps ==1)
        {
            for(j=0;j<S[G[i].list[0]].followno;j++)
                 addtoTable(G[i].nt,S[G[i].list[0]].follow[j],i,T);
        }
        if(S[G[i].nt].eps == 1)
        {
            for(j=0;j<S[G[i].nt].followno;j++)
                 addtoTable(G[i].nt,S[G[i].nt].follow[j],i,T);
        }
    }
}

void printTable(Table T[][45])//print parser table
{
    int i,j;
    FILE *fp = fopen("OUTPUT-ParseTable.txt","w");
    if(fp==NULL) { printf("Some error in printing Parse Table !\n"); return; }
    for(i=100;i<=maxnt;i++)
    {
        for(j=1;j<=39;j++)
            fprintf(fp,"%d ",T[i][j]);
        fprintf(fp,"\n");
    }
    fclose(fp);
}

void parseInputSourceCode()
{
	int l,n,x,flag=0,loc,sz,j,i;
	FILE *f1 = fopen("INPUT-Grammar.txt","r");
       if(f1== NULL) {printf("Error opening grammar\n");return ;}
         Gno = createGrammar(f1,G);  // create grammar.
       initSets(Gno); // generate first, follow sets.
         printFirst(S); // printing first sets
       printFollow(S); // printing follow sets
        Table Parse_Table[150][45]; // T[i][j] will give the rule for ith non terminal and jth terminal.
                      //i = 100 - 143, j = 1 - 41.
    initTable(Parse_Table);
    createParseTable(Parse_Table,Gno);
	
	
	/**************************/
	
    	/****************************/
	stack s;
	s.size=1;
	
	int sym[10];
	
	treenode *t;
	node *top;
	top=(node *)malloc(sizeof(node));
	
	t=(treenode *)malloc(sizeof(treenode));
	t->parent=t;
	t->ruleno=0;
	t->opID=0;
	T.size=1;
	for(i=0;i<9;i++){t->children[i]=NULL;}
	t->tokenID=100;
	t->no_children=0;
	//strcpy(t->scope,"MAIN");
	T.root=t;
	strcpy(t->lexeme,"empty");

	top->symbolID=100;
	top->pointer=T.root;
	top->link=NULL;
	s.top=top;
	
	
	for(i=0;i<SIZE;i++)
	{
		x=Token[i].name;
		
		while(1)
		{
		if(s.size<=0)
		{
			printf("Syntax Error The token %s does not match the expected token at line %d\n",Token[i].s,Token[i].line);flag=1;break;
		}
		if(top_stack(s)<100 && x!=top_stack(s))
		{
			printf("Syntax Error The token %s does not match the expected token at line %d\n",Token[i].s,Token[i].line);flag=1;break;
			

		}
		if(top_stack(s)<100 && x==top_stack(s))
		{
			s=pop(s,sym,0,Token[i].s,Token[i].line,loc);
			break;
		}
		else
		{
			j=1;sz=0;
			loc=Parse_Table[top_stack(s)][x];
if(loc==-1){printf("Syntax Error The token %s does not match the expected token at line %d\n",Token[i].s,Token[i].line);flag=1;break;}
			for(j=0;j<G[loc].listno;j++)
			{
				sym[j]=G[loc].list[j];
				sz++;
				
			}
			if(sym[sz-1]==21)
			{s=pop(s,sym,sz-1,Token[i].s,Token[i].line,loc);}
			else
			{s=pop(s,sym,sz,Token[i].s,Token[i].line,loc);}
		}
		}


		if(flag==1){break;}
	}
	if(s.size>0 && flag==0)
	{
		flag=1;
		printf("Syntax error!! more tokens expected \n");
	}
	
	printf("\n");
	if(flag==0){
	printf("The code is syntactically correct\n");
	//printt(T.root);
	}
	printf("\n");
	
    return ;
}

