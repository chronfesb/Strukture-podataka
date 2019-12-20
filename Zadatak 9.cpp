/*Napisati program koji omoguæava rad s binarnim stablom pretraživanja. 
Treba omoguæiti unošenje novog elementa u stablo, ispis elemenata, brisanje
i pronalaženje nekog elementa. */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

enum _TREE_PRINT { INORDER = 1, PREORDER, POSTORDER };

struct Stablo;
typedef struct Stablo *Position;
struct Stablo {
	int El;
	Position R;
	Position L;
};

int PrintError(char*);
int PrintMenu();
int RandomGenerateInteger(int,int,int *);
int InsertInt(int *);
Position Insert(Position, int);
int Print(int, Position);
Position FindMin(Position);
Position FindMax(Position);
Position Delete(Position, int);
Position Find(Position, int);

int main()
{
	int Result =0;
	Position root = NULL;
	Position Found = NULL;
	char izbor = 0;
	int N = 0;
	
	
	printf("\r\n");
	printf("\r\n");

	while(toupper(izbor)!= 'K') 
	{
		PrintMenu();
		scanf("%s", izbor);

		if((izbor,"1") == 0) 
		{
			Result = RandomGenerateInteger(0, 1000, &N);
			if(Result == 0)
			{
				printf("Potrebno dodati: %d\n", N);
				root= Insert(root,N);
			}
			else {
				PrintError("Pogreska pri generiranju.\n");
			}
		}
		else if ((izbor, "2") == 0)
		{
			printf("\r\n\t");
			if (root == NULL)
				PrintError("Tree is empty");
			else
				Print(INORDER, root);
			printf("\r\n");
		}
		else if ((izbor, "3") == 0)
		{
			printf("\r\n\t");
			if (root == NULL)
				PrintError("Tree is empty");
			else
				Print(PREORDER, root);
			printf("\r\n");
		}
		else if ((izbor, "4") == 0)
		{
			printf("\r\n\t");
			if (root == NULL)
				PrintError("Tree is empty");
			else
				Print(POSTORDER, root);
			printf("\r\n");
		}
		else if ((izbor, "5") == 0)
		{
			if (root == NULL)
				PrintError("Tree is empty");
			else
			{
				printf("\r\n\tDelete");
				Result = InsertInt(&N);
				if (Result)
				{
					root = Delete(root, N);
				}
			}
		}
		else if ((izbor, "6") == 0)
		{
			if (root == NULL)
				PrintError("Tree is empty");
			else
			{
				printf("\r\n\tFind");
				Result = InsertInt(&N);
				if (Result)
				{
					Found = Find(root, N);
					if (Found != NULL)
						printf("\r\n\tElement: %d found at address: 0x%xh.", Found->El, (unsigned int)Found);
					else
						printf("\r\n\tElement: %d not found.", N);
				}
			}
		}
		else if ((izbor, "K") == 0)
		{
			printf("\r\n\Izlaz iz programa.\r\n");
		}
		else
		{
			printf("\r\Pogresan unos: %c. Izaberite ponovo.", izbor);
		}
	}

	return Result;
}

int PrintMenu()
{
	printf("\r\n");
	printf("\t***************************************\r\n");
	printf("\t***   VJEZBA BR. 09  -  Binary tree ***\r\n");
	printf("\t***************************************\r\n");
	printf("\r\n");
	printf("\t\t1.\tInsert element\r\n");
	printf("\t\t2.\tPrint tree - infix\r\n");
	printf("\t\t3.\tPrint tree - prefix\r\n");
	printf("\t\t4.\tPrint tree - posfix\r\n");
	printf("\t\t5.\tDelete element\r\n");
	printf("\t\t6.\tFind element\r\n");
	printf("\t\texit.\tExit program\r\n");
	printf("\tIzbor : ");

	return 0;
}

int RandomGenerateInteger(int Min, int Max, int *Br) //Generiranje random broja
{
	int range=Max-Min;
	if(range == 0) return -1;
	*Br= rand()%range + Min;
	return 0;
}


int InsertInt( int *n) 
{
	int result = -1;
	while(result <0) 
	{
		printf("Unesi broj:\n");
		result = scanf("%d", n);
	}
	return 0;
}

Position Insert(Position P, int N) 
{
	if(P == NULL) 
	{
		P=(Position)malloc(sizeof(struct Stablo));
		if(P ==NULL) 
		{
			printf("Pogreska pri alociranju.\n");
			return P;
		}

		P->El = N;
		P->L=NULL;
		P->R=NULL;
	}
	else if( P->El < N) 
		P->R= Insert(P->R, N);
	else if(P->El > N) 
		P->L= Insert(P->L, N);
	else 
		PrintError("Element vec postoji.\n");

	return P;
}

int Print( int type, Position P) //Ispis stabla na 3 nacina
{
	switch(type)
	{
	case INORDER:
		{
			if(P !=NULL)
			{
				Print(type, P->L);
				printf("%d", P->El);
				Print(type, P->R);
			}
		}
		break;
	case PREORDER:
		{
			if(P!=NULL) 
			{
				printf("%d", P->El);
				Print(type, P->L);
				Print(type, P->R);
			}
		}
		break;
	case POSTORDER:
		{
			if(P!=NULL) 
			{
				Print(type, P->L);
				Print(type, P->R);
				printf("%d", P->El);

			}
		}
		break;
	}

	return 0;
}


Position FindMin(Position P) //Minimalna vrijednost
{
	if(P ==NULL) return P;

	while(P->L !=NULL) 
		P=P->L;
	return P;
}

Position FindMax(Position P) //Maksimalna vrijednost
{
	if(P ==NULL) return P;

	while(P->R !=NULL) 
		P=P->R;
	return P;
}

Position Find(Position P, int N) //Trazenje nekog elementa u stablu
{
	if(P == NULL) return P;

	if(P->El > N) 
		return Find(P->L, N);
	else if(P->El < N) 
		return Find(P->R, N);
	else
		return P;
}

Position Delete(Position P, int N) 
{
	Position tmp;
	if(P == NULL) 
	{
		printf("Element nije pronaden.\n");
	}
	else if (P->El > N) 
		P->L = Delete(P->L, N);
	else if(P->El < N) 
		P->R = Delete(P->R, N);
	else 
	{
		if(P->L!=NULL && P->R!=NULL)
		{
			tmp=FindMin(P->R);
			P->El = tmp->El;
			P->R = Delete(P->R, tmp->El);

		}
		else
		{
			tmp = P;
			if(P->L == NULL)
				P= P->R;
			else 
				P=P->R;
			free(tmp);
		}
	}

	return P;
}

int PrintError( char *message)
{
	if(message ==NULL || strlen(message) ==0)
	{
		printf("Unknown error!\n");
	}
	else 
	{
		printf("\r\n\t%s", message);
	}
	printf("\r\n");
	return 0;
}