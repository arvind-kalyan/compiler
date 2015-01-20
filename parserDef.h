	// KEVIN CHITTINAPPILY SEBASTIAN - 2011A7PS131P
	// ARVIND K - 2011C6PS666P

#ifndef PARSERDEF_H_INCLUDED
#define PARSERDEF_H_INCLUDED

typedef struct treenode
{
	int tokenID;
	char lexeme[100];
	int line_no;
	int no_children;
	int ruleno;
	int opID;
	int type;
	char scope[21];
	struct treenode *parent;
	struct treenode *children[10];
}treenode;

typedef struct tree
{
	treenode *root;
	int size;
}tree;

typedef struct node
{
	int symbolID;

	struct treenode *pointer;
	struct node *link;
}node;

typedef struct stack
{
	int size;
	node *top;
}stack;


typedef struct bucket{

    char lexeme[25];
    int type;
    char scope[21];
    char value[120];
    int tokenID;
    int size1,size2;
    struct bucket* next;
}bucket;

typedef struct pair
{
	char var[25];
	int type;
}pair;

typedef bucket * Link;

typedef struct hashtable{
    Link head;
    int count;

}Hashtable;


int TableSize,noFunctions;

Hashtable *hashTable;

typedef enum {FALSE,TRUE} bool;
char line[100]; // temporary buffer
char map_function[100][21];
pair var_table[100];
int novars;

int function_table[500][500];
int ruleno; // number of rules
int maxnt; // max. value of a non terminal state
typedef int Table; // PARSE TABLE

typedef struct // FIRST AND FOLLOW SETS
{
    int nt;  // number of the non terminal
    int first[65]; // first set
    int follow[65]; // follow set
    bool ft[65];   // temp
    bool fw[65]; // temp
    int firstno; // no of elements in first set
    int followno;  // no of elements in follow set
    bool eps;  // if there is a nullable prodn.

} sets;

typedef struct // GRAMMAR
{
    int nt;   // non terminal
    int ruleNumber; // ruleno
    int list[20]; // RHS of this nt.
    int listno;  // no of elements in RHS.

} grammar;
tree T,AST;

typedef struct codegen
{
	int opID;
	int type;
	int ifbl;
	int elsebl;
	char op1[22];
	char op2[22];
	char res[23];
}codegen;
	

	
	
/*
100: <mainFunction>
101: <StmtandFunctiondefs>
102: <stmtorFucntiondef>
103: <stmt>
104: <declarationstmt>
105: <assignmentstmt_type1>
106: <assignmentstmt_type2>
107: <ifstmt>
108: <iostmt>
109: <funcallstmt>
110: <functionDef>
111: <parameter_list>
112: <type>
113: <remaining_list>
114: <var_list>
115: <more_ids>
116: <lefthandside_singlevar>
117: <righthandside_type1>
118: <lefthandside_listvar>
119: <righthandside_type2>
120: <arithmetic_expression>
121: <sizeexpression>
122: <yy>
123: <booleanexpression>
124: <otherstmts>
125: <extra>
126: <input_parameterlist>
127: <var>
128: <list_var>
129: <arithmeticterm>
130: <operator_lowprecedence>
131: <factor>
132: <operator_highprecedence>
133: <logicalop>
134: <constrained_var>
135: <relationalop>
136: <matrixelement>
137: <matrix>
138: <rows>
139: <row>
140: <remainingcolelements>
141: <x>
142: <y>
143: <z>
*/
#endif
