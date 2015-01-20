	// KEVIN CHITTINAPPILY SEBASTIAN - 2011A7PS131P
	// ARVIND K - 2011C6PS666P
	
#ifndef LEXERDEF_H_INCLUDED
#define LEXERDEF_H_INCLUDED

typedef struct buffer
{
	char str[2000];

}Buffer;

typedef struct error
{
	int line;
	char lexeme;
}error;

typedef struct tokeninfo
{
	int name; // name
	int line; // line in which token appears
	char s[100];  // lexeme

}tokenInfo;

typedef tokenInfo * Tok;
typedef int buffersize;
int sizeofTokenInfo;
int changeGlobally ;
int ct; // to store line number
int SIZE;
Tok Token;  // dynamic array
Tok Token1;
Buffer b;  // Buffer declared globally
buffersize k ; // a constant
int state,loc,pos; // initial values
int ctalloc;
error error2[50],error3[30];
int e2,e3;
int flag_err;
#endif

