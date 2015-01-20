	// KEVIN CHITTINAPPILY SEBASTIAN - 2011A7PS131P
	// ARVIND K - 2011C6PS666P


//#ifndef LEXER_H_INCLUDED
//#define LEXER_H_INCLUDED

extern void assign(char *st, int pos, int tokenid);
extern void addtoToken(int pos,char *st);
extern void addfToken(int pos,char *st);
extern int checknext(int index);
extern int checkalp(char c,int index,char* st,int pos);
extern int checknum(char c,int index,char* st,int pos);
extern int checkchar(char c,int index,char* st,int pos);
extern void tokenize(Buffer b,int ct);
extern void append(char* s, char c);
extern void set1(char *ar);
extern FILE * getStream(FILE *fp, buffersize k);
extern void PrintTokenList()

//#endif
