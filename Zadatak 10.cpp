/*
Napisati program koji iz datoteke èita posfiks izraz i zatim stvara stablo proraèuna. Iz
gotovog stabla proraèuna upisati u datoteku infiks izraz.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

enum _TREE_PRINT{ INORDER = 1, PREORDER, POSTORDER};

struct Stablo;
typedef struct Stablo *Position;
struct Stablo {
	char *El;
	Position R;
	Position L;
};

struct Stack;
typedef struct Stack *Pos;
struct Stack {
	Position NElement;
	Pos Next;
};

int PrintError(char *);
void PrintMenu();
int CreateNewStackNode(Pos *);
int Push(Pos, Position);
int Pop(Position, Pos *);
int Print(int, Position);
int CreateTree(char *, Pos, Position *);
int DeleteStack(Pos);
int DeleteTree(Position);
int GarbageCollector(Pos, Position);


int main()
{
	int rez = 0;
	char *fName= NULL;
	Pos stack=NULL;
	Position root= NULL;

	PrintMenu();
	
	rez = CreateNewStackNode(&stack);
	if(rez) 
	{
		PrintError("Pogreska pri alokaciji memorije->stack\n");
		return rez;
	}
	
	fName=(char*)malloc(sizeof(char)*1024);
	if(fName == NULL) 
	{
		PrintError("Pogreska pri alokaciji memorije->fName\n");
		return -1;
	}

	printf("Unesite ime datoteke iz koje zelite procitati podatke:\n");
	scanf("%s", fName);

	if(strrchr(fName, '.')==0)
		strcat(fName, ".txt");

	rez = CreateTree( fName, stack, &root);
	if(!rez) 
	{
		PrintError("********************************************");
		printf("\r\nPreorder:\t");
		Print(PREORDER, root);


		PrintError("********************************************");
		printf("\r\nInorder:\t");
		Print(INORDER, root);


		PrintError("********************************************");
		printf("\r\nPostorder:\t");
		Print(POSTORDER, root);
	}
	PrintError("************************************************");

	GarbageCollector(stack, root);
	return rez;

}

void PrintMenu()
{
	printf("\r\n");
	printf("\t*******************************************\r\n");
	printf("\t***   VJEZBA BR. 10  -  Expression tree ***\r\n");
	printf("\t*******************************************\r\n");
	printf("\r\n");

}

int PrintError(char *m)
{
	if(m == NULL || strlen(m) == 0)
	{
		printf("Pogreska.\n");
	}
	else {
		printf("%s", m);
	}
	return 0;
}

int CreateNewStackNode( Pos *S)
{
	Pos q=NULL;
	q=(Pos)malloc(sizeof(struct Stack));
	if(q==NULL) return -1;

	q->NElement = NULL;
	q->Next= NULL;
	*S=q;
	return 0;
}

int Push( Pos S, Position N) 
{
	Pos q=NULL;
	if(CreateNewStackNode(&q)) return -1;

	q->NElement = N;
	q->Next= S->Next;
	S->Next = q;
	return 0;
}


int Pop (Pos S, Position *el) 
{
	Pos tmp=NULL;
	Position q =NULL;

	if(S ==NULL) return -1;

	tmp = S->Next;
	if(tmp == NULL) return -1;

	S->Next = tmp->Next;
	q = tmp->NElement;

	free(tmp);
	*el = q;

	return 0;
}

int CreateNewTreeNode( Position *N)
{
	Position q=NULL;

	q=(Position)malloc(sizeof(struct Stablo));
	if(q==NULL) return -1;

	q->El = NULL;
	q->R = NULL;
	q->L = NULL;

	*N= q;
	return 0;
}

int CreateTree( char *fileN, Pos stack, Position *root)
{
	int result=0;
	int br = 0;
	int nCount = 0;
	char *buff = NULL;
	Position q =NULL;
	FILE *fp= NULL;

	buff=(char*)malloc(sizeof(char)*1024);
	if(buff ==NULL) 
	{
		PrintError("Pogreska pri alokaciji memorije->buffer\n");
		return -1;
	}
	memset(buff, '\0', 1024);

	fp=fopen(fileN, "r");
	if(fp==NULL)
	{
		printf("Pogreska pri otvaranju datoteke.\n");
		return -1;
	}

	while(!feof(fp))
	{
		memset(buff, '\0', 1024);

		result = CreateNewTreeNode(&q);
		if(result) break;
		
		fscanf(fp, "%s", buff);
		if(buff == NULL || strlen(buff) == 0) continue;

		nCount = strlen(buff);
		nCount ++;

		q->El = (char*)malloc(sizeof(char)*nCount);
		if(q->El ==NULL) 
		{
			PrintError("Pogreska pri alokaciji ->element\n");
			free(q);
			result= -1;
			break;
		}
		memset(q->El, '\0', nCount);
		nCount -- ;

		strncpy(q->El, buff, nCount) ;
		q->L = NULL;
		q->R = NULL;

		nCount = sscanf(buff, "%d", &br);
		  
		if(nCount == EOF || nCount <= 0)
		{
			result = Pop(stack, &q->R); 
			if(result) break;
			
			result= Pop(stack, &q->L);
			if(result) break;

		}
		
		result = Push(stack, q);
		if(result) break;
	}
	fclose(fp);

	free(buff) ; 
	if(!result)
	{
		result=Pop(stack, &q);
		*root = q;
	}
	return result;
}

int Print(int type, Position P)
{
	switch(type)
	{
	case INORDER:
		{
			if(P !=NULL) 
			{
				if(P->L !=NULL)
					printf(" ( ");
				Print(type, P->L);
				printf("%s", P->El);
				Print(type, P->R);
				if(P->R !=NULL) 
					printf(" ) ");
			}
		}
		break;
	case PREORDER:
		{
			if (P != NULL)
			{
				printf(" %s", P->El);
				Print(type, P->L);
				Print(type, P->R);
			}
		}
		break;
	case POSTORDER:
		{
			if (P != NULL)
			{
				Print(type, P->L);
				Print(type, P->R);
				printf(" %s", P->El);
			}
		}
		break;
	}

	return 0;
}

int GarbageCollector(Pos S, Position root) 
{
	DeleteStack(S);
	DeleteTree(root);
	return 0;
}

int DeleteStack(Pos S)
{
	if( S==NULL) return 0;

	DeleteStack(S->Next);
	
	DeleteTree(S->NElement);
	free(S);

	return 0;
}

int DeleteTree(Position N) 
{
	if( N==NULL) return 0;
	DeleteTree(N->L);
	DeleteTree(N->R);
	free(N);
	return 0;
}