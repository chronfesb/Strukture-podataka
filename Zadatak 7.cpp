/* Napisati program koji iz datoteke čita postfiks izraz i zatim korištenjem stoga računa rezultat.
Stog je potrebno realizirati preko vezane liste. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct _lista;
typedef struct _lista* Position;
typedef struct _lista{
	int el;
	Position next;
}lista;

int PrintMenu();
int Push(Position,int);
int Pop(Position,int*);
int Calculate(int, int ,char);

int main()
{
	FILE *pf=NULL;
	lista head;
	head.next=NULL;
	char *izbor=NULL;
	char *niz=NULL;

	PrintMenu();

	niz = (char*)malloc(sizeof(char)*128);
	if(niz==NULL)
	{
		printf("Pogresno alociran pomocni niz koji cita postfix izraz\n");
		return -1;
	}

	izbor=(char*)malloc(sizeof(char)*128);
	if(izbor==NULL)
	{
		printf("Pogresno alociran niz\n");
		return -1;
	}

	printf("Upisite ime datoteke: ");
	scanf("%s",izbor);

	if(strrchr(izbor,'.')==0)
		strcat(izbor,".txt");

	pf=fopen(izbor,"r");
	if(pf==NULL)
	{
		printf("Pogresno otvorena datoteka...");
		return -1;
	}
	
	while(!feof(pf))
	{
		fscanf(pf,"%s",niz);
		if(isdigit(niz[0]))
		{
			Push(&head,atoi(niz));
		}
		else
		{
			int x=0,y=0,rez=0;
			Pop(&head,&y);
			Pop(&head,&x);
			rez=Calculate(x,y, *niz);
			Push(&head,rez);
			printf("REz je: %d\n",rez);
		}
	}

	printf("Rezultat je: %d\n",head.next->el);
	free(niz);
	free(izbor);
	fclose(pf);
	return 0;
}

int PrintMenu()
{
	printf("\t****************************************\r\n");
	printf("\t***   VJEZBA BR. 07  -  Posfix izraz ***\r\n");
	printf("\t****************************************\r\n");
	printf("\r\n");
	return 0;
}

int Push(Position p,int x)
{
	Position q=NULL;
	q=(Position)malloc(sizeof(lista));
	if(q==NULL)
		return -1;
	q->el=x;
	printf("x je: %d\n",q->el);
	q->next=p->next;
	p->next=q;

	return 0;
}

int Pop(Position p,int *x)
{
	Position q=NULL;
	q=p->next;
	if(q!=NULL)
	{
		p->next=q->next;
		*x=q->el;
		free(q);
	}
	return 0;
}

int Calculate(int a,int b,char zn)
{
	int rezult=0;
	switch(zn)
	{
	   case '+': 
		   rezult=a+b;
		   break;
	   case '-':
		   rezult = a-b;
		   break;
	   case '*':
		   rezult=a*b;
		   break;
	   case '/':
		   if(b!=0)
		   {
			   rezult=a/b;
			   break;
		   }
		   else
			   rezult=0;
	}
	return rezult;
}