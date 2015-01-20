#include<stdio.h>
#include<ctype.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include"LexerDef.h"
#include"parserDef.h"


int rule4val;

// rule 3
int k,l; //  rule 3
int ip[10],op[10]; // rule 3
int ipfcall[10],opfcall[10]; // rule 3
int kf,lf; //  rule 3
int fcallflag; //  rule 3
int input1,input2,output1,output2; // rule 3
int rule3lno[1000],rule3lnofcall[1000];
int lnoo;

char opFuncDef[100][21]; // rule 4
int arrsize; // rule 4
char opStmt[100][21]; // rule 4
int arrsize2; // rule 4
int popline[1000];
// Matrix size calculation.

int M[20],N[20]; // m x n matrix
char MatName[30][21]; //  names of matrices.
char matrixIDs[30][21];
char matrixScope[30][21];
int matid;
int colcheck;
int mattoken;

// String size calculation
char str1[30][21];
int strid;
char strscope[30][21];
int len;
int strtoken;

// rule 15
char funCname[30][21];
int funCline[1000];
char funCscope[30][21];
int K;

int g,h;

int LOL; 

int getline11(treenode *t, char func[])
{
	if(t==NULL) return;
	if(t->tokenID == 110 && strcmp(func,t->children[5]->lexeme) == 0)
	{
		
		LOL=t->line_no;return;
	}	

	int i;
	for(i=0;i< t-> no_children; i++) getline11(t->children[i],func);
}

void rule7(treenode*t, int noFunc,char map_function[100][21],int function_table[500][500]) // function overloading in the same scope is not allowed
{

	
	int i,j;
	for(i = 0;i<= noFunc; i++)
	{
		for(j=i+1;j<= noFunc;j++)
		{
			if(strcmp(map_function[i],map_function[j]) == 0)
			{
				if(function_table[i][1] == function_table[j][1])
					{
						getline11(t,map_function[i]);
					printf("line %d: function overloading is not allowed : function \"%s\"\n",LOL,map_function[i]);
					
					}
			}
		}
	}
	return;	
	
}



void rule9(treenode *t) // two matrices cannot be multiplied or divided.
{
    if(t==NULL) return;
    treenode *temp = t;
    if(temp!= NULL)
    {
        if(temp->opID == 27 || temp->opID == 28 )
        {
            int i;
            for(i=0;i<t->no_children;i++)
            {
                if(t->children[i]->type == 4) { printf("line %d: matrices cannot be multiplied or divided\n",t->children[i]->line_no);  }

            }
        }
        else {int i; for(i=0;i< t->no_children;i++) rule9(t->children[i]);}
    }
    return;

}

void rule10(treenode *t)   // strings cannot be multiplied,subtracted or divided  
{
    if(t==NULL) return;
    treenode *temp = t;
    if(temp!= NULL)
    {
    	//printf("temp->tokenID  = %d, temp->opID = %d \n",temp->tokenID,temp->opID);
        if(temp->opID == 26 || temp->opID == 27 || temp->opID == 28 )
        {
            int i;
            for(i=0;i<t->no_children;i++)
            {
                if(t->children[i]->type == 2) { printf("line %d: strings cannot be multiplied/subtracted/divided\n",t->children[i]->line_no);  }

            }
        }
        else {int i; for(i=0;i< t->no_children;i++) rule10(t->children[i]);}
    }
    return;

}

void rule6(treenode*t) // boolean exp inside an if stmt
{
    if(t==NULL) return;
    treenode *temp;
    temp = t;
    int i;
   // printf("temp->tokenID  = %d, temp->opID = %d \n",temp->tokenID,temp->opID);
    if(temp->tokenID == 107)
        {
        //printf("children - %d\n",t->no_children);
        	if(t->children[2]->tokenID != 123)
        	{
        		//err[esize]->id = 6; err[esize]->L = t->children[2]->line_no; esize++;
        		printf("line %d: invalid expression inside if statement\n",t->children[2]->line_no);
        	}
      /*  int i;
        printf("line no %d\n",t->line_no);
        for(i=0;i< t->no_children; i++)
        {
        	if(t->children[i] == NULL) printf("NULL ");
        	else printf("%d ",t->children[i]->tokenID);
        }
        printf("\n");
         //if(t->children[1]->tokenID != 123) { printf("Semantic error 6  Not boolean exp !! at line no %d\n",t->children[1]->line_no);}
		               // }
            //}

    }
    */
    }
    for(i=0;i<t->no_children;i++)
    {
    	if(t->children[i] != NULL)
    	{
    		rule6(t->children[i]);		
    	}
    }
}

int countParam1(treenode *t)
{
	if(t==NULL) return 0;
	if(t->tokenID == 1) { op[k++]=LOOKUP(t->lexeme,t->scope); return 1;}
	int i;
	int ans=0;
	for(i=0;i< t->no_children; i++) ans += countParam1(t->children[i]);
	return ans;
}
int countParam2(treenode *t)
{
	if(t==NULL) return 0;
	if(t->tokenID == 1) { ip[l++]=LOOKUP(t->lexeme,t->scope); return 1;}
	int i;
	int ans=0;
	for(i=0;i< t->no_children; i++) ans += countParam2(t->children[i]);
	return ans;
}


void rule3(treenode *t,char func[])
{
	if(t == NULL) return;
	if(t->tokenID == 110 && strcmp(func,t->children[5]->lexeme) == 0) // funcDef
	{
		if(t->children[2] == NULL) { ; }
		else
		{
			
			memset(ip,0,sizeof ip);
			memset(op,0,sizeof op);
			k=0,l=0;
			output1 = countParam1(t->children[2]);
			input1 = countParam2(t->children[7]);
			
		/*	
			printf("\nFunctionDef - %s\n",func);
			printf("OP - %d, IP - %d\n",output1,input1);
			int i,j;
			for(i=0;i<output1;i++) printf("%d ",op[i]);
			printf("\n");
			for(j=0;j<input1;j++) printf("%d ",ip[j]);
			
			*/
			
		}
	}
	int i;
	for(i=0;i< t-> no_children; i++) rule3(t->children[i],func);
}

int countParam3(treenode *t)
{
	if(t==NULL) return 0;
	if(t->tokenID == 1) {  ipfcall[lf++]=LOOKUP(t->lexeme,t->scope); return 1;}
	if(t->tokenID == 3) {  ipfcall[lf++]=1; return 1;}
	if(t->tokenID == 4) {  ipfcall[lf++]=3; return 1;}
	if(t->tokenID == 5) {  ipfcall[lf++]=2; return 1;}
	//if(t->tokenID == 1) {  ipfcall[lf++]=t->type; return 1;}
	int i;
	int ans=0;
	for(i=0;i< t->no_children; i++) ans += countParam3(t->children[i]);
	return ans;
}

int countParam4(treenode *t)
{
	if(t==NULL) return 0;
	if(t->tokenID == 1) { opfcall[kf++]=LOOKUP(t->lexeme,t->scope); return 1;}
	int i;
	int ans=0;
	for(i=0;i< t->no_children; i++) ans += countParam4(t->children[i]);
	return ans;
}

void rule3Funcall(treenode *t,char func[])
{
	if(t==NULL) return;
	if(t->tokenID == 109 && strcmp(func,t->children[0]->lexeme)==0 )
	{
		
		rule3lnofcall[lnoo]=t->line_no;
		fcallflag=1;
		lf=0; kf=0;
		memset(ipfcall,0,sizeof(ipfcall));
		memset(opfcall,0, sizeof (opfcall));
		input2 = countParam3(t->children[2]);
		output2 = countParam4(t->parent->parent->children[0]);
		
		if(output2 == 0 && (output1 != output2) && fcallflag == 1) { printf("line %d: function that does not return any value, must be invoked appropriately.\n",t->line_no); }
		/*
		printf("\nFunction call - %s\n",func);
		printf("OP - %d, IP - %d\n",output2,input2);
			int i,j;
			for(i=0;i<output2;i++) printf("%d ",opfcall[i]);
			printf("\n");
			for(j=0;j<input2;j++) printf("%d ",ipfcall[j]);
		printf("\n\n");
		*/
		}	

	int i;
	for(i=0;i< t-> no_children; i++) rule3Funcall(t->children[i],func);
}

// RULE 5 can be incorporated with rule 3

void rule3Main(treenode *t,char map_function[100][21],int N)
{
	treenode *temp =t;
	int i;
	int fflag=0;
	memset(rule3lnofcall,0,sizeof(rule3lnofcall));
	for(i=1;i<=N;i++)
	{
		fcallflag=0;
		rule3(t,map_function[i]);
		lnoo=0;
		rule3Funcall(t,map_function[i]);
		
		//printf("%s - k = %d, kf = %d, l = %d, lf = %d\n",map_function[i],k,kf,l,lf);
		if(((output1 != output2) || (input1!= input2)) && fcallflag == 1) {printf("line %d: number of actual and formal input parameters in function call of %s do not match\n",rule3lnofcall[0],map_function[i]);}
		else
		{
			if(fcallflag == 0) goto here;
			int p,q;
			for(p=0;p<output1;p++)
			{
				if(op[p] != opfcall[p]) { printf("line %d: types of actual and formal input parameters in function call %s do not match\n",rule3lnofcall[0],map_function[i]); fflag=1; break; }
			}
			if(!fflag){
			for(q=0;q<input1;q++)
			{
if(ip[q] != ipfcall[q]) { printf("line %d: types of actual and formal input parameters in function call %s do not match\n",rule3lnofcall[0],map_function[i]); break; }
			}
			
		}
		here: fflag=0;
		
	}
		
}
}


//rule 4 - The output parameters of a  function must be assigned a value within the function definition. If a parameter does not get a value assigned within the function definition, it should be reported as an error.


void populateOP(treenode *t)
{
	if(t==NULL) return;
	if(t->tokenID == 1)
	{
		strcpy(opFuncDef[arrsize],t->lexeme);
		popline[arrsize] = t->line_no;
		arrsize++;
		
	}
	int i;
	for(i=0;i< t->no_children;i++) populateOP(t->children[i]);
}


void rule4(treenode *t,char func[])
{
	
	if(t==NULL) return;
	if(t->tokenID == 110 && strcmp(func,t->children[5]->lexeme)== 0) // functionDef
	{
		int i;
		if(t->children[2] == NULL) {  }
		else {  populateOP(t->children[2]);}	
		return;			
	}	
	int i;
	for(i=0;i<t->no_children;i++)
	{
		if(t->children[i] != NULL) rule4(t->children[i],func);
	}
}

void traverse5(treenode *t)
{
	if(t == NULL) return;	
	
	if(t->tokenID == 1 )
	{
		strcpy(opStmt[arrsize2++],t->lexeme);
	}
	
	int i;
	for(i=0;i< t->no_children;i++) traverse5(t->children[i]);
}

void traverse4(treenode *t)
{
	if(t == NULL) return;	
	
	if(t->tokenID == 105 || t->tokenID == 106)
	{
		if(t->children[0] != NULL) traverse5(t->children[0]);
	}
	
	int i;
	for(i=0;i< t->no_children;i++) traverse4(t->children[i]);
	
}

void checkStmtAndFuncDef(treenode *t,char func[])
{
	if(t == NULL) return;	
	
	
	
	if(t->tokenID == 110 && strcmp(func,t->children[5]->lexeme) == 0)
	{
		traverse4(t->children[9]);	
	}
	
	int i;
	for(i=0;i< t->no_children;i++) checkStmtAndFuncDef(t->children[i],func);
	
}


void rule4main(treenode *t, char map_function[100][21],int N)
{
	treenode *temp = t;
	int i;
	memset(popline,0,sizeof(popline));
	for(i=1;i<=N;i++)
	{
		arrsize=0,arrsize2=0;
		rule4(t,map_function[i]);
		checkStmtAndFuncDef(t,map_function[i]);
		
		int k,j;
		for(k=0;k<arrsize;k++)
		{
			int flag=0;
			for(j=0;j<arrsize2;j++)
			{
				if( strcmp(opFuncDef[k],opStmt[j]) == 0)
				{
					flag=1;
				}
			}
			if(flag == 0) printf("line %d: output parameter %s is not assigned any value throughout the function definition\n",popline[k],opFuncDef[k]);
		}
		
	}	
	
}


// RECURSIVE function call not allowed.

void traverserule8(treenode *t,char func[])
{
	if(t==NULL) return;
	if(t->tokenID == 109 && strcmp(func,t->children[0]->lexeme)==0) { printf("line %d : recursive function definitions are not allowed\n",t->line_no); return;  }
	int i;
	for(i=0;i< t->no_children;i++) traverserule8(t->children[i],func);
}


void rule8(treenode *t,char func[])
{
	if(t==NULL) return;
	if(t->tokenID == 110 && strcmp(func,t->children[5]->lexeme)== 0) // functionDef
	{
		traverserule8(t,func);
	}
	int i;
	for(i=0;i<t->no_children;i++)
	{
		if(t->children[i] != NULL) rule8(t->children[i],func);
	}
}

void rule8main(treenode *t, char map_function[100][21],int N)
{
	treenode *temp = t;
	int i;
	for(i=1;i<=N;i++)
	{
		
		rule8(t,map_function[i]);		

	}
		
}	

// matrix calculations begin.

void computeMatrixIDs(treenode *t)
{
	if(t==NULL) return;
	if(t->tokenID == 1 && t->type == 4)
	{
		strcpy(matrixIDs[matid],t->lexeme);
		strcpy(matrixScope[matid],t->scope);
		mattoken = t->tokenID;
		matid++;
	}
	int i;
	for(i=0;i< t->no_children; i++) computeMatrixIDs(t->children[i]);
	
}

void compMatrix(treenode *t)
{
	if(t==NULL) return;
	if(t->tokenID == 104)
	{
		computeMatrixIDs(t);
	}
	int i;
	for(i=0;i< t->no_children; i++) compMatrix(t->children[i]);
	
}

void checkCol(treenode *t,int k)
{
	if(t== NULL) return;
	if(t->tokenID == 3)
	{
		//printf("updcol\n");
		N[k]++;
	}
	int i;
	for(i=0;i< t->no_children; i++) checkCol(t->children[i],k);
	
}

void checkMatSize2(treenode *t,int k)
{
	if(t == NULL) return;
	if(t->tokenID == 138) // <rows>
	{
		if(t->children[0] != NULL && !colcheck) {  //printf("2 - tokenID = %d\n",t->children[0]->tokenID); 
		colcheck=1; checkCol(t->children[0],k);}
		//if(t->children[1] != NULL) { //printf("2 - tokenID = %d\n",t->children[1]->tokenID); 
		//checkMatSize3(t->children[1],k);}
		M[k]++;
	}
	int i;
	for(i=0;i< t->no_children; i++) checkMatSize2(t->children[i],k);
}


void checkMatSize(treenode *t,char mid[],int k)
{
	if(t == NULL) return;
	if(t->tokenID == 105)
	{
		if(strcmp(t->children[0]->lexeme,mid) == 0)
		{
			//printf("\nhere1\n %s\n",mid);
			//printf("1 - tokenID = %d\n",t->children[2]->tokenID);
			checkMatSize2(t->children[2],k);
		}
	}
	int i;
	for(i=0;i< t->no_children; i++) checkMatSize(t->children[i],mid,k);
}

void MatrixDriver(treenode *t)
{
	matid = 0;
	compMatrix(t);
	int i;
	memset(M,0,sizeof(M));
	memset(N,0,sizeof(N));
	for(i=0;i<matid;i++)
	{
		//printf("Matrix - %s Scope %s\n",matrixIDs[i],matrixScope[i]);
		colcheck=0;
		checkMatSize(t,matrixIDs[i],i);
		INSERT(matrixIDs[i],4,matrixScope[i],M[i],N[i],mattoken,"NULL");
		//printf("For matrix %s , rows = %d, cols = %d\n",matrixIDs[i],M[i],N[i]);
	}
		
}


void computeStringIDs(treenode *t)
{
	if(t==NULL) return;
	if(t->tokenID == 1 && t->type == 2)
	{
		strcpy(str1[strid],t->lexeme);
		strcpy(strscope[strid],t->scope);
		strid++;
		strtoken = t->tokenID;
	}
	int i;
	for(i=0;i< t->no_children; i++) computeStringIDs(t->children[i]);
	
}

void compString(treenode *t)
{
	if(t==NULL) return;
	if(t->tokenID == 104)
	{
		computeStringIDs(t);
	}
	int i;
	for(i=0;i< t->no_children; i++) compString(t->children[i]);
	
}


void checkStrSize2(treenode *t)
{
	if(t == NULL) return;
	if(t->tokenID == 120)
	{
		if(t->children[0] != NULL && t->children[0]->tokenID == 5) { 
			
		len = strlen(t->children[0]->lexeme);
		
		}			
		
	}
	int i;
	for(i=0;i< t->no_children; i++) checkStrSize2(t->children[i]);
}


void checkStrSize(treenode *t,char mid[])
{
	if(t == NULL) return;
	if(t->tokenID == 105)
	{
		if(strcmp(t->children[0]->lexeme,mid) == 0)
		{
			checkStrSize2(t->children[2]);
		}
	}
	int i;
	for(i=0;i< t->no_children; i++) checkStrSize(t->children[i],mid);
}

void StringSizeDriver(treenode *t)
{
	strid=0;
	compString(t);
	int i;
	for(i=0;i<strid;i++)
	{
		len=0;
		checkStrSize(t,str1[i]);
		if(len != 0) len = len-2;
		INSERT(str1[i],2,strscope[i],len,0,strtoken,"NULL");
	}
}

int checkargs(treenode *t)
{
	if(t==NULL) return 0;
	if(t->tokenID == 1 && t->type == 1) { return 1;}
	int i;
	int ans=0;
	for(i=0;i< t->no_children; i++) ans += checkargs(t->children[i]);
	return ans;
}

void checkSize(treenode *t)
{
	if(t== NULL) return;
	if(t->tokenID == 121)
	{
		if(t->children[1] != NULL)
		{
			if(t->children[1]->type == 2)
			{
				//printf("parent : %d\n",t->parent->parent->tokenID);
				if(t->parent->parent->tokenID != 105) // righthandsizetype1
				{
					printf("line %d : string size expression does not match on both sides\n",t->line_no);
				} 
				else
				{
					int x =0;
					//printf("checkargs call %d\n",t->parent->parent->children[0]->tokenID);
					x = checkargs(t->parent->parent->children[0]);
				
					if(x != 1) { printf("line %d : string size expression does not match on both sides\n",t->line_no);
				}
			}
		}
		else if(t->children[1]->type != 4  && t->children[1]->type != 2) { printf("line %d : size expression error\n",t->line_no); }
		
	}	
	}
	int i;
	for(i=0;i< t->no_children;i++) checkSize(t->children[i]);
}

int checkargs2(treenode *t)
{
	if(t==NULL) return 0;
	if(t->tokenID == 1 && t->type == 1) { return 1;}
	int i;
	int ans=0;
	for(i=0;i< t->no_children; i++) ans += checkargs2(t->children[i]);
	return ans;
}

void checkSize2(treenode *t)
{
	if(t== NULL) return;
	if(t->tokenID == 121)
	{
		if(t->children[1] != NULL)
		{
			if(t->children[1]->type == 4)
			{
				//printf("parent : %d\n",t->parent->parent->tokenID);
				if(t->parent->parent->tokenID != 106) // righthandsizetype2
				{
					printf("line %d : matrix size expression does not match on both sides\n",t->line_no);
				} 
				else
				{
					int x =0;
					x = checkargs2(t->parent->parent->children[0]);					
					if(x != 2) { printf("line %d : matrix size expression does not match on both sides\n",t->line_no);
				}
			}
		}
		else if(t->children[1]->type != 2 && t->children[1]->type!=4)
		{printf("line %d : size expression error\n",t->line_no); }
	}	
	}
	int i;
	for(i=0;i< t->no_children;i++) checkSize2(t->children[i]);
}

void sizeExp(treenode *t)
{
	checkSize(t);	
	checkSize2(t);	
		
}

int mat1[10],mat2[10],lineno[10];

void check2(treenode *t)
{
	if(t==NULL) return;
	if(t->tokenID == 1 && t->type == 4)
	{
		
		int i=0;
		for(i=0;i<matid;i++)
		{
			if(strcmp(t->lexeme,matrixIDs[i]) == 0 && strcmp(t->scope,matrixScope[i])==0)
			{
				mat1[g] = M[i];
				mat2[g] = N[i];
				lineno[g] = t->line_no;
				g++;
			}
		}
	}
	int i;
	for(i=0;i< t->no_children; i++) check2(t->children[i]);
}

void check1(treenode *t)
{
	if(t == NULL) return;
	if(t->tokenID == 120)
	{
		//printf("here\n");
		check2(t);
	}
	int i;
	for(i=0;i< t->no_children; i++) check1(t->children[i]);
}


void matrixCompatibility(treenode *t)
{
	memset(mat1,0,sizeof(mat1));
	memset(mat2,0,sizeof(mat2));
	g=0,h=0;
	check1(t);
	int i;
	int err =0;
	int lno;
	int flag=0;
	for(i=1; i< g; i++)
	{
if((mat1[i-1] != mat1[i]) || (mat2[i-1] != mat2[i])) {
	if(i==0) flag=1;
 err=1; lno=lineno[i]; printf("line %d: Operation between matrices of incompatible sizes.\n",lineno[i]);}

		else lineno[i]=-1;
	}
	if(!flag) lineno[0]=-1;
}
int m,n,ff;
void check4(treenode *t)
{
	//printf("h1\n");
	if(t==NULL) return;
	//printf("h2\n");
	if(t->tokenID == 1 && t->type == 4)
	{
		int i;
		ff=0;
		for(i=0;i<g;i++)
		{
			if(lineno[i] == t->line_no) {ff=1;}
		}
		if(!ff)
		{ 
			m = LOOKUP1(t->lexeme,t->scope);			
			n = LOOKUP2(t->lexeme,t->scope);
			
			//UpdateMatrixSize(t->lexeme,t->scope,m,n);
		}
	
	}
	int i;
	for(i=0;i< t->no_children; i++) check4(t->children[i]);
}



void check3(treenode *t)
{
	if(t == NULL) return;
	if(t->tokenID == 120)
	{
		
		check4(t);
		
	}
	int i;
	for(i=0;i< t->no_children; i++) check3(t->children[i]);
}


void matrixAssignment(treenode *t)
{
	check3(t);
	
}

void populateFCall(treenode *t)
{
	if(t==NULL) return;
	if(t->tokenID == 109 )
	{
		
		//printf("%s , scope = %s\n",t->children[0]->lexeme,t->children[0]->scope);
		strcpy(funCname[K],t->children[0]->lexeme);
		int i;
		
		strcpy(funCscope[K],t->children[0]->scope);
		funCline[K] = t->children[0]->line_no;
		K++;
		
	}
	int i;
	for(i=0;i< t-> no_children; i++) populateFCall(t->children[i]);

}

int getScope(char func[], char map_function[100][21],int function_table[500][500],int noFunc)
{
	int i,j;
	for(i=0;i<=noFunc;i++)
	{
		if(strcmp(func,map_function[i]) == 0 )
		{
			int x = function_table[i][1];
			return x;
		}
	}
		
	return -1;
}

int getIndex(char func[], char map_function[100][21],int function_table[500][500],int noFunc)
{
	int i,j;
	for(i=0;i<=noFunc;i++)
	{
		if(strcmp(func,map_function[i]) == 0 )
		{
			return i;
		}
	}
		
	return -1;
}


void rule15(treenode *t,int noFunc,char map_function[100][21],int function_table[500][500])
{	
	K=0;
	populateFCall(t);
	int i,j;
	int KK=0;
		
	for(i=0;i<K;i++)
	{
		int ok=0;
		int Y = getIndex(funCscope[i],map_function,function_table,noFunc); // index of scope of funcall in fun table
		int X = getScope(funCname[i],map_function,function_table,noFunc); // parent scope of fun call
		if(strcmp(funCscope[i],"MAIN")==0) ok=1;
		if(X==-1) { printf("line %d: function definiton of %s is missing\n",funCline[i],funCname[i]);}
	else{
			for(k=0;k<=noFunc;k++) 
			{ 
				if(function_table[Y][k] == X) {   ok=1;}			
			}		
	   if(ok == 0)	{printf("line %d: func. def. for a function being used by another function must preceed the function using it. \n",funCline[i]); ok=0;}	
	   }
	
	}	
 }


