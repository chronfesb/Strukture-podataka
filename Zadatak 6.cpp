/*Napisati program koji pomoću vezanih listi simulira rad:
a) stoga,
b) reda.
Napomena: Funkcija "push" sprema cijeli broj, slučajno generirani u opsegu od 10 -100. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

struct _lista;
typedef struct _lista* Position;
typedef struct _lista{
	int broj;
	Position next;
}lista;

int PushS(Position,int);
int PushR(Position,int);
int Pop(Position);
int RandomNumber(int,int);
int IsThere(Position,int);
int PrintMenu();
int PrintList(Position);

int main()
{
	char *odabir=NULL;
	Position stog=NULL;
	Position red=NULL;
	stog=(Position)malloc(sizeof(lista));
	red=(Position)malloc(sizeof(lista));
	red->next=NULL;
	stog->next=NULL;
	int slucajni=0;

	odabir=(char*)malloc(sizeof(char)*128);
	if(odabir==NULL)
		return -1;
	memset(odabir,0,128);

	while(strcmp(odabir,"kraj")!=0)
	{
		PrintMenu();
		scanf("%s",odabir);

		if(strcmp(odabir,"1")==0)
		{
			while(slucajni==0 || IsThere(stog,slucajni))
				slucajni=RandomNumber(10,100);

			PushS(stog,slucajni);
			printf("Stog: ");
			PrintList(stog->next);
			slucajni=0;
		}
		else if(strcmp(odabir,"2")==0)
		{
			while(slucajni==0 || IsThere(red,slucajni))
				slucajni=RandomNumber(10,100);

			PushR(red,slucajni);
			printf("Red: ");
			PrintList(red->next);
			slucajni=0;
		}
		else if(strcmp(odabir,"3")==0)
		{
			Pop(stog);
			printf("Stog: ");
			PrintList(stog->next);
		}
		else if(strcmp(odabir,"4")==0)
		{
			Pop(red);
			printf("Red: ");
			PrintList(red->next);
		}
		else
			printf("Pogresan upis...Ponovite\n\n");
	}
	return 0;
}

int PrintMenu()
{
	printf("Odaberite ste zelite:\n");
	printf("1. PushStog\n");
	printf("2. PushRed\n");
	printf("3. PopStog\n");
	printf("4. PopRed\n");
	printf("Odabir: ");
	return 0;
}

int PrintList(Position p)
{
	while(p!=NULL)
	{
		printf(" %d",p->broj);
		p=p->next;
	}
	puts("\n");
	return 0;
}

int PushS(Position p,int x)
{
	Position q=NULL;
	q=(Position)malloc(sizeof(lista));
	if(q==NULL)
		return -1;

	q->broj=x;
	q->next=p->next;
	p->next=q;

	return 0;
}

int PushR(Position p,int x)
{
	Position q=NULL;
	q=(Position)malloc(sizeof(lista));
	if(q==NULL)
		return -1;

	while(p->next!=NULL)
		p=p->next;

	q->broj=x;
	q->next=p->next;
	p->next=q;

	return 0;
}

int Pop(Position p)
{
	Position temp=NULL;
	if(p->next==NULL)
	{
		printf("Lista je prazna vec\n");
	}
	else
	{
		temp=p->next;
	    if(temp!=NULL)
	    {
		   p->next=temp->next;
		   free(temp);
	    }
	}
	return 0;
}

int RandomNumber(int a,int b)
{
	//srand(time(0));
	srand((unsigned) time(NULL));
	int random=0;
	random=rand()%(b-a+1)+a;
	return random;
}

int IsThere(Position p,int x)
{
	int rezult=0;
	while(p!=NULL)
	{
		if(p->broj == x)
		{
			rezult=1;
			break;
		}
		else
			p=p->next;
	}
	return rezult;
	/*while(p!=NULL && p->broj != x)
	{
		p=p->next;
	}
	if(p==NULL)
		return 0;
	else
		return 1; */
}
