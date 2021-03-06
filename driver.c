	// KEVIN CHITTINAPPILY SEBASTIAN - 2011A7PS131P
	// ARVIND K - 2011C6PS666P
/*

FIRST SET IS FULLY AUTOMATED
BOTH LEXICAL AND SYNTAX ANALYZER MODULES DEVELOPED
MODULES WORK WITH ALL TESTCASES
PARSE TREE CAN BE CONSTRUCTED
AST CAN BE CONSTRUCTED
SYMBOL TABLE AND SEMANTIC CHECKING WORKS
CODE GENERATION WORKS FOR INTEGER OPERATIONS



*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<malloc.h>
#include "LexerDef.h"
//#include "Lexer.h"
//#include "parserDef.h"
//#include "parser.h"



int main(int argc, char* argv[])
{
	int flag=0,SIZE=0,ct=0,loc=0,pos=0,ctalloc=0,k=1000,changeGlobally=0,sizeofTokenInfo=0;
	//char semi[]=";";
	printf("LEVEL 3: Symbol Table,AST,Semantic rules and Type checking work,Code Generation works partially\n\n");
    if(argc !=3) {printf("Please enter three arguments!\n"); return 0;}
	char filename[50]; // source file name
	char parseTreefile[50];
	 // specified through CLI
	char outputfile[60];
	strcpy(filename,argv[1]);
	strcpy(parseTreefile,"outputAST.txt");
	strcpy(outputfile,argv[2]);
	int option;

	
	char c;
    

    	do
    	{
	printf("    ***** Welcome *****\n\n");
	printf("Please select an option from below : \n");
	printf("\t1. Print Token List\n");
	printf("\t2. Verify Syntactic correctness\n");
	printf("\t3. Generate Abstract Syntax Tree(will be printed on screen in depth first format)\n");
	printf("\t4. Print the Symbol Table\n");
	printf("\t5. Semantic and type checking\n");
	printf("\t6. Assembly Code Generation\n");
	printf("\tEnter option : ");
	scanf("%d",&option);
	int parsed=0;
	
	
	switch(option)
	{
	    case 1 : PrintTokenList(filename); break;
	    case 2 : parseInputSourceCode(); break; ++parsed;
            case 3 : print_Parsetree(parseTreefile); break;
            case 4 : showSymbolTable();break;
            case 5 : errorchecking();break;
            case 6: generate_code(outputfile);break;
	    default: break;
	}
	printf("\nDo you want to continue?(y/n): ");
	scanf(" %c",&c);
	}while((c=='y')||(c=='Y'));
    return 0;
	


}





