	// KEVIN CHITTINAPPILY SEBASTIAN - 2011A7PS131P
	// ARVIND K - 2011C6PS666P

#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

extern bool isTerminal(int symbol);
extern void populateGrammar(char str[],int ruleno);
extern int createGrammar(FILE *fp,grammar G[]);
extern void addNullable(int s);
extern void firstSets(int symbol, int Gno);
extern void initSets(int Gno);
extern void printFirst(sets S[]);
extern void printFollow(sets S[]);
extern void initTerminalSets(sets S[]);
extern void followSets();
extern void populateFollow(char str[]);
extern void initTable(Table T[][45]);
extern void addtoTable(int nt, int t, int ruleno, Table T[][45]);
extern void createParseTable(Table T[][45],int Gno);
extern void printTable(Table T[][45]);
extern stack push(stack s,int val[],int n,treenode *parent);
extern int top_stack(stack s);
extern stack pop(stack s,int a[],int n);
extern void print(stack s);
extern void printt(treenode *t);
extern void print_dfs(treenode *t,FILE *f,treenode *p);
extern void print_Parsetree(tree T,char * outfile);
extern void Parse();

#endif

