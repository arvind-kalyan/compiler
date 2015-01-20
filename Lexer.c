	// KEVIN CHITTINAPPILY SEBASTIAN - 2011A7PS131P
	// ARVIND K - 2011C6PS666P

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include"LexerDef.h"

void assign(char *st, int pos, int tokenid)
{
	if(tokenid==18)
	{
	strcpy(st,";");
	}
	   strncpy(Token[loc].s,st,pos+1);
    	Token[loc].name=tokenid;
    	Token[loc].line=ct;
    	loc++;
}

void addtoToken(int pos,char *st)
{

        assign(st,pos,1);
}

void addfToken(int pos,char *st)
{
	assign(st,pos,2);
}

int checknext(int index)
{
	if(!isalpha(b.str[index+1]) && !isdigit(b.str[index+1])){return 1;}
	return 0;
}

int checkalp(char c,int index,char* st,int pos)
{
    if(state==300)
    {
        if(islower(c))
        {
            /*if(b.str[index+1]=='"')
            {
                assign(st,pos,5);
                return 300;
            }
            else
            {*/
                return 300;
            //}
        }
        return -1;
    }

	if(isdigit(b.str[index+1]) && (state==0 || state==100 || (state>=400 && state<=406))){return 100;}
	if(isdigit(b.str[index+1]) && (state==101 || (state>=200 && state<203))){return 101;}

	//function
	if(state==400)
	{
		if(c=='u' && checknext(index)==0){return 401;}
		else {
		if(checknext(index)==0)
		{
		return 100;
		}
		else
		{
		assign(st,pos,1);return 0;
		}
		}
	}
	if(state==401)
	{
		if(c=='n' && checknext(index)==0){return 402;}
		else {
		if(checknext(index)==0)
		{
		return 100;
		}
		else
		{
		assign(st,pos,1);return 0;
		}
		}
	}
	if(state==402)
	{
		if(c=='c' && checknext(index)==0){return 403;}
		else
		{
		if(checknext(index)==0)
		{
		return 100;
		}
		else
		{
		assign(st,pos,1);return 0;
		}
		}
	}
	if(state==403)
	{
		if(c=='t' && checknext(index)==0){return 404;}
		else
		{
		if(checknext(index)==0)
		{
		return 100;
		}
		else
		{
		assign(st,pos,1);return 0;
		}
		}
	}
	if(state==404)
	{
		if(c=='i' && checknext(index)==0){return 405;}
		else
		{
		if(checknext(index)==0)
		{
		return 100;
		}
		else
		{
		assign(st,pos,1);return 0;
		}
		}
	}
	if(state==405)
	{
		if(c=='o' && checknext(index)==0){return 406;}
		else
		{
		if(checknext(index)==0)
		{
		return 100;
		}
		else
		{
		assign(st,pos,1);return 0;
		}
		}
	}
	if(state==406)
	{
		if(c=='n' && !isalpha(b.str[index+1]) && !isdigit(b.str[index+1])){assign(st,pos,22);return 0;}
		else {
		if(checknext(index)==0)
		{
		return 100;
		}
		else
		{
		assign(st,pos,1);return 0;
		}
		}
	}

    if(state==100)
    {
    if(!isalpha(b.str[index+1]) && !isdigit(b.str[index+1]))
    {
      assign(st,pos,1);
    	return 0;
    }
    else {return 100;}
    }

	//and or not
    if(state==60)
    {
        if(c=='a'){return 61;}
        if(c=='o'){return 64;}
        if(c=='n'){return 66;}
        return -1;
    }
    if(state==61)
    {
        if(c=='n'){return 62;}
        return -1;
    }
    if(state==62)
    {
        if(c=='d'){return 63;}
        return -1;
    }
    if(state==64)
    {
        if(c=='r'){return 65;}
        return -1;
    }
    if(state==66)
    {
      if(c=='o'){return 67;}
      return -1;
    }
    if(state==67)
    {
        if(c=='t'){return 68;}
        return -1;
    }
    //end of and,or
    //**************************************************************

	if(state==101)
	{
	if(!isdigit(b.str[index+1]) && !isalpha(b.str[index+1])){assign(st,pos,2);return 0;}
	return 101;
	}

    //main function
    if(state==200)
    {
        if(!(isalpha(b.str[index+1])) && (!isdigit(b.str[index+1])))
        {
        addfToken(pos,st);
        return 0;
    	}

        if(c=='m'){return 201;}
    	else
    	{
    	return 101;
    	}
    }
    if(state==201)
    {
        if(!(isalpha(b.str[index+1])) && (!isdigit(b.str[index+1])))
        {
        addfToken(pos,st);
        return 0;
    	}
        if(c=='a'){return 202;}

    	else
    	{
    	return 101;
    	}
    }
    if(state==202)
    {
        if(!(isalpha(b.str[index+1])) && (!isdigit(b.str[index+1])))
        {
        addfToken(pos,st);
        return 0;
    	}
        if(c=='i'){return 203;}

    	else
    	{
    	return 101;
    	}
    }
    if(state==203)
    {
        if(c=='n')
        {
      	if(!isalpha(b.str[index+1]) && !isdigit(b.str[index+1])){assign(st,pos,13);return 0;}

    	return 101;
    	}
        if(!(isalpha(b.str[index+1])) && (!isdigit(b.str[index+1])))
        {
        addfToken(pos,st);
        return 0;
    	}
    	else
    	{
    	return 101;
    	}
    }

    //endof main function
    //*********************************************************8
    if(isdigit(b.str[index+1])){return 100;}

    if(state==100 && checknext(index)==1){assign(st,pos,1);return 0;}
    if(state==100 && checknext(index)==0){return 100;}

    if(state==25 && checknext(index)==1){assign(st,pos,20);return 0;}
    if(state==0)
    {
        if(c=='i' && checknext(index)==0 && b.str[index+1]!='f'){return 1;}
        if(c=='i' && checknext(index)==0 && b.str[index+1]=='f'){return 25;}



        if(checknext(index)==1)
        {
        	assign(st,pos,1);
        	return 0;
        }

        if(c=='e'){return 27;}
        if(c=='m'){return 14;}
        if(c=='p'){return 20;}
        if(c=='r'){return 9;}
        if(c=='s'){return 3;}
        if(c=='f'){return 400;}
        return 100;
    }
    //int
    if(state==1 && checknext(index)==0 && c=='n'){return 2;}
    if(state==1 && checknext(index)==0 && c!='n'){return 100;}
    if(state==1 && checknext(index)==1){assign(st,pos,1);return 0;}

    if(state==2 && checknext(index)==0){return 100;}
    if(state==2 && checknext(index)==1 && c=='t'){assign(st,pos,9);return 0;}
    if(state==2 && checknext(index)==1 && c!='t'){assign(st,pos,1);return 0;}

    //matrix
    if(state==14 && checknext(index)==0 && c=='a'){return 15;}
    if(state==14 && checknext(index)==0 && c!='a'){return 100;}
    if(state==14 && checknext(index)==1){assign(st,pos,1);return 0;}

    if(state==15 && checknext(index)==0 && c=='t'){return 16;}
    if(state==15 && checknext(index)==0 && c!='t'){return 100;}
    if(state==15 && checknext(index)==1 ){assign(st,pos,1);return 0;}

    if(state==16 && checknext(index)==0 && c=='r'){return 17;}
    if(state==16 && checknext(index)==0 && c!='r'){return 100;}
    if(state==16 && checknext(index)==1 ){assign(st,pos,1);return 0;}

    if(state==17 && checknext(index)==0 && c=='i'){return 18;}
    if(state==17 && checknext(index)==0 && c!='i'){return 100;}
    if(state==17 && checknext(index)==1 ){assign(st,pos,1);return 0;}

    if(state==18 && checknext(index)==0){return 100;}
    if(state==18 && checknext(index)==1 && c=='x'){assign(st,pos,12);return 0;}
    if(state==18 && checknext(index)==1 && c!='x'){assign(st,pos,1);return 0;}

    //end,endif,else

    if(state==27 && checknext(index)==0 && c=='n'){return 28;}
    if(state==27 && checknext(index)==0 && c=='l'){return 32;}
    if(state==27 && checknext(index)==0 && c!='n' && c!='l'){return 100;}
    if(state==27 && checknext(index)==1 ){assign(st,pos,1);return 0;}

    if(state==28 && checknext(index)==1 && c=='d'){assign(st,pos,6);return 0;}
    if(state==28 && checknext(index)==0 && c=='d'){return 29;}
    if(state==28 && checknext(index)==0 && c!='d' ){return 100;}
    if(state==28 && checknext(index)==1 && c!='d' ){assign(st,pos,1);return 0;}

    if(state==29 && checknext(index)==0 && c=='i'){return 30;}
    if(state==29 && checknext(index)==0 && c!='i'){return 100;}
    if(state==29 && checknext(index)==1 ){assign(st,pos,1);return 0;}

    if(state==30 && checknext(index)==1 && c=='f'){assign(st,pos,8);return 0;}
    if(state==30 && checknext(index)==0){return 100;}
    if(state==30 && checknext(index)==1 && c!='f'){assign(st,pos,1);return 0;}

    if(state==32 && checknext(index)==0 && c=='s'){return 33;}
    if(state==32 && checknext(index)==0 && c!='s'){return 100;}
    if(state==32 && checknext(index)==1 ){assign(st,pos,1);return 0;}

    if(state==33 && checknext(index)==1 && c=='e'){assign(st,pos,7);return 0;}
    if(state==33 && checknext(index)==0){return 100;}
    if(state==33 && checknext(index)==1 ){assign(st,pos,1);return 0;}

    //string

    if(state==3 && checknext(index)==0 && c=='t'){return 4;}
    if(state==3 && checknext(index)==0 && c!='t'){return 100;}
    if(state==3 && checknext(index)==1 ){assign(st,pos,1);return 0;}

    if(state==4 && checknext(index)==0 && c=='r'){return 5;}
    if(state==4 && checknext(index)==0 && c!='r'){return 100;}
    if(state==4 && checknext(index)==1 ){assign(st,pos,1);return 0;}

    if(state==5 && checknext(index)==0 && c=='i'){return 6;}
    if(state==5 && checknext(index)==0 && c!='i'){return 100;}
    if(state==5 && checknext(index)==1 ){assign(st,pos,1);return 0;}

    if(state==6 && checknext(index)==0 && c=='n'){return 7;}
    if(state==6 && checknext(index)==0 && c!='n'){return 100;}
    if(state==6 && checknext(index)==1 ){assign(st,pos,1);return 0;}

    if(state==7 && checknext(index)==1 && c=='g'){assign(st,pos,11);return 0;}
    if(state==7 && checknext(index)==0 ){return 100;}
    if(state==7 && checknext(index)==1 ){assign(st,pos,1);return 0;}

    //read/real

    if(state==9 && checknext(index)==0 && c=='e'){return 10;}
    if(state==9 && checknext(index)==0 && c!='e'){return 100;}
    if(state==9 && checknext(index)==1 ){assign(st,pos,1);return 0;}

    if(state==10 && checknext(index)==0 && c=='a'){return 11;}
    if(state==10 && checknext(index)==0 && c!='a'){return 100;}
    if(state==10 && checknext(index)==1 ){assign(st,pos,1);return 0;}

    if(state==11 && checknext(index)==0){return 100;}
    if(state==11 && checknext(index)==1 && c=='d'){assign(st,pos,23);return 0;}
    if(state==11 && checknext(index)==1 && c=='l'){assign(st,pos,10);return 0;}
    if(state==11 && checknext(index)==1){assign(st,pos,1);return 0;}

    //print

    if(state==20 && checknext(index)==0 && c=='r'){return 21;}
    if(state==20 && checknext(index)==0 && c!='r'){return 100;}
    if(state==20 && checknext(index)==1 ){assign(st,pos,1);return 0;}

    if(state==21 && checknext(index)==0 && c=='i'){return 22;}
    if(state==21 && checknext(index)==0 && c!='i'){return 100;}
    if(state==21 && checknext(index)==1 ){assign(st,pos,1);return 0;}

    if(state==22 && checknext(index)==0 && c=='n'){return 23;}
    if(state==22 && checknext(index)==0 && c!='n'){return 100;}
    if(state==22 && checknext(index)==1 ){assign(st,pos,1);return 0;}

    if(state==23 && checknext(index)==0){return 100;}
    if(state==23 && checknext(index)==1 && c=='t'){assign(st,pos,24);return 0;}
    if(state==23 && checknext(index)==1){assign(st,pos,1);return 0;}

    return -1;

}

int checknum(char c,int index,char* st,int pos)
{
	
	if(isalpha(b.str[index+1])){return -1;}
    if(state==300)
	{
		//append(st,c);
		return -1;

	}
    if(state==100)
    {
    	if(!isdigit(b.str[index+1]) && !isalpha(b.str[index+1])){assign(st,pos,1);return 0;}
    	return -1;
    }
    if(state==101)
    {
    	if(!isdigit(b.str[index+1]) && !isalpha(b.str[index+1])){assign(st,pos,2);return 0;}
    	return -1;
    }

    if(state==0 ||state==51)
    {


    if(!isdigit(b.str[index+1]) && (b.str[index+1]!='.'))
    {

      assign(st,pos,3);
    	return 0;
    }
    else {return 51;}
    }

    if(state==52)
    {
    if(!isdigit(b.str[index+1]))
    {
    if(b.str[index+1]=='|')
    {

     return -1;
    }
    else
    {
    return -1;
    }
    }
    else
    {
    return 53;
    }
    }
    if(state==53)
    {
    if(!isdigit(b.str[index+1]))
    {
	if(!isalpha(b.str[index+1]))
	{
	
	assign(st,pos,4);return 0;
	}
	else
	{
	return -1;
	}
      
    
    }
    else {return 54;}
    }
    else {return 51;}
    if(state==54){return -1;}
    return -1;
}

int checkchar(char c,int index,char* st,int pos)
{
	if(state==51 && c=='.'){return 52;}
	if(state==300)
	{
		if(c=='"'){assign(st,pos,5);return 0;}
		if(c==32){

            return 300;
        }
		return -1;

	}
	if(state==51)
	{
		return 52;
	}
    if(state==0)
    {
    	if(c=='"'){return 300;}
        if(c=='.'){if(!isalpha(b.str[index+1])){return -1;}else {return 60;}}
        if(c=='_'){return 200;}
        if(c=='[')
        {

       assign(st,pos,14);
    	return 0;
        }
        if(c==']')
        {

      assign(st,pos,15);
    	return 0;
        }
        if(c=='(')
        {

      assign(st,pos,16);
    	return 0;
    	}
        if(c==')')
        {

      assign(st,pos,17);
    	return 0;
    	}
        if(c==';')
        {

      assign(st,pos,18);
    	return 0;
    	}
        if(c==',')
        {

      assign(st,pos,19);
    	return 0;
    	}
        if(c=='+')
        {

      assign(st,pos,25);
    	return 0;
    	}
        if(c=='-')
        {

      assign(st,pos,26);
    	return 0;
    	}
        if(c=='*')
        {

     assign(st,pos,27);
    	return 0;
    	}
        if(c=='/')
        {

      assign(st,pos,28);
    	return 0;
    	}
        if(c=='@')
        {

     assign(st,pos,29);
    	return 0;
    	}
        if(c=='=')
        {
        if(b.str[index+1]!='=' && b.str[index+1]!='/')
        {

      assign(st,pos,39);
      return 0;
    	}
    	else
    	{
    	return 151;
    	}
    	}


        if(c=='>')
        {
        if(b.str[index+1]!='=')
        {

      assign(st,pos,36);
    	return 0;
    	}
    	else{return 155;}
    	}
        if(c=='<')
        {
        if(b.str[index+1]!='=')
        {

      assign(st,pos,33);
    	return 0;
    	}
    	else{return 157;}
    	}
    }
    if(state==151)
    {
        if(c=='=')
        {


      assign(st,pos,35);
    	return 0;

        }
        if(c=='/'){return 153;}
    }

    if(state==153)
    {
        if(c=='=')
        {

      assign(st,pos,38);
    	return 0;
    	}
        return -1;
    }
    if(state==155)
    {
        if(c=='=')
        {


      assign(st,pos,37);
    	return 0;
    	}
    }
    if(state==157)
    {
        if(c=='=')
        {
      assign(st,pos,34);
    	return 0;
    	}
    }
    if(state==63)
    {
    if(c=='.')
        {
      assign(st,pos,30);
    	return 0;
    	}
    else{

    return -1;}
    }

   if(state==65)
    {
    if(c=='.')
        {
      assign(st,pos,31);
    	return 0;
    	}
    else{return -1;}
    }

    if(state==68)
    {
    if(c=='.')
        {
      assign(st,pos,32);
    	return 0;
    	}
    else{return -1;}
    }
//****************************
    return -1;
}

void tokenize(Buffer b,int ct)    // Tokenize each line of the source file which is stored in Buffer b
{
    int i=0;
    //state=0;
    char st[80];
    pos=0;
    while( i<strlen(b.str))
    {
    	ctalloc++;
    	if(b.str[i]=='$')
    	{
    		if(state!=0){flag_err=1;printf("\nLexical Error!! unknown character or pattern %c at line %d \n",b.str[i-1],ct);error2[e2].line=ct;error2[e2].lexeme=b.str[i-1];e2++; state=0; }  // changed.
    		else {break;}
    	}
    	//printf("0\n");
    	if(ctalloc >= changeGlobally) {
           // printf("\n **reallocating** \n");
            Tok TempToken;
            TempToken = calloc(sizeofTokenInfo+changeGlobally,sizeof(tokenInfo));
            TempToken = (Tok) realloc(Token,(sizeofTokenInfo+changeGlobally)*sizeof(tokenInfo));
            if(TempToken != NULL) Token=TempToken;
            else printf("Out of memory!!!\n");
            sizeofTokenInfo+=changeGlobally;
            ctalloc=0;
        }
    	if(b.str[i]=='|'){if(state!=0){flag_err=1;printf("\nLexical Error!! unknown character or pattern %c at line %d \n",b.str[i-1],ct);error3[e3].line=ct;error3[e3].lexeme=b.str[i-1];e3++;}state=0;i++;pos=0;continue;}
	
    	{
    	if(b.str[i]==';'){pos=0;st[0]=';';}
    	else {st[pos]=b.str[i];}
    	}

        if(isalpha(b.str[i]))
        {
            state=checkalp(b.str[i],i,st,pos);


        }
        if(isdigit(b.str[i]))
        {

        state=checknum(b.str[i],i,st,pos);
        }

        if(!isdigit(b.str[i]) && !isalpha(b.str[i]))
        {

            state=checkchar(b.str[i],i,st,pos);

        }
        
        if(state==-1){flag_err=1;printf("\nLexical Error!! unknown character or pattern %c at line %d \n",b.str[i-1],ct);error3[e3].line=ct;error3[e3].lexeme=b.str[i-1];e3++; state=0; return;}   // changed.
        if(state==0)                                            
        { pos=0;
            SIZE++;
            
          strncpy(st,"",sizeof(st));
          
        }
        else {pos++;}
        
        i++;
    }

}

void append(char* s, char c) // for appending a char 'c' to the end of a string 's'

{
        int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
}

void set1(char *ar)
{
    int i;
    int stringflag=0;
    for(i=0;i<strlen(ar);i++)
        {
            if(ar[i]=='#') { ar[i]='\0'; break;}
            if(ar[i]==34 && !stringflag) {stringflag=1;}
            else if(ar[i]==34 && stringflag) {stringflag=0;}
            if((ar[i]<=32 || ar[i]>=127) && stringflag ) {}
            if((ar[i]<=32 || ar[i]>=127)&& !stringflag) ar[i]='|';
        }
    return;
}


FILE * getStream(FILE *fp, buffersize k)   // 1st function

{
	e2=0;e3=0;
	char line[250];  // temp array to store each line
	state=0;
	if(fp == NULL) {printf("Error in getStream\n"); return 0;}
    	while(fgets(line,sizeof(line),fp) != NULL )
    	{
    		ct++;    		
    		if(line[0]=='#'){continue;}    		
                append(line,'$');  // appends it with end symbol.
    		set1(line);    		
    		strcpy(b.str,line);
    		tokenize(b,ct); // tokenize the buffer
    	}
	return fp;
}

void PrintTokenList(char *filename)
{
    int i;flag_err=0;
    FILE *fp = fopen(filename,"r");
    if(fp == NULL) {printf("File doesn't exist\n"); return ;}
    sizeofTokenInfo=10;  // INITIAL VALUE, CAN BE CHANGED
    changeGlobally = sizeofTokenInfo;
    Token = ( Tok ) malloc (sizeofTokenInfo* sizeof(tokenInfo) ); // allocated dynamically
    fp = getStream(fp,k);
    printf("\n");
    char semi[]=";";
    if(flag_err==0)
    {
    printf("The contents are : \n\n");
    printf("Line no.  Token   Lexeme\n");
    }
    for(i=0;i<SIZE;i++)
   {
        if(Token[i].s=="")
        {
           
    if(Token[i].name==18) strcpy(Token[i].s,semi);
        }
        if(strlen(Token[i].s)>20 && Token[i].name!=5)
        {
        printf("Lexical Error the size of identifier at line %d exceeds 20 characters\n",Token[i].line);break;
        }
        if(flag_err==0)
        {
        printf("%d       %d         %s\n",Token[i].line,Token[i].name,Token[i].s);
        }
    }
    
}
