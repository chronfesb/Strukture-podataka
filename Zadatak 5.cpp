/* Za dvije sortirane liste L1 i L2 (mogu se proèitati iz datoteke ili unijeti ruèno, bitno je
samo da su sortirane), napisati program koji stvara novu vezanu listu tako da raèuna:
a) L1?L2,
b) L1?L2.
Liste osim pokazivaèa na slijedeæu strukturu imaju i jedan cjelobrojni element, po
kojem su sortirane.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct _lista;
typedef struct _lista* Position;
typedef struct _lista{
	int broj;
	Position next;
}lista;

int ReadFromFile(Position);
int PrintList(Position);
int Unija(Position,Position,Position);
int Presjek(Position,Position,Position);

int main()
{
	lista p1,p2,u,p;
	p1.next=NULL;
	p2.next=NULL;
	u.next=NULL;
	p.next=NULL;

	ReadFromFile(&p1);
	ReadFromFile(&p2);

	printf("Ispis prve liste: ");
	PrintList(p1.next);
	printf("Ispis druge liste: ");
	PrintList(p2.next);

	Unija(p1.next,p2.next,&u);
	printf("Ispis unije liste: ");
	PrintList(u.next);

	Presjek(p1.next,p2.next,&p);
	printf("Ispis presjek liste: ");
	PrintList(p.next);

	printf("\nGotov program!\n");
	return 0;
}

int ReadFromFile(Position p)
{
	char *ime_dat=NULL;
	FILE *pf=NULL;
	Position q=NULL;
	Position temp=NULL;

	ime_dat=(char*)malloc(sizeof(char)*128);
	if(ime_dat==NULL)
		return -1;

	printf("Upisite ime datoteke: ");
	scanf("%s",ime_dat);

	if(strrchr(ime_dat,'.')==0)
		strcat(ime_dat,".txt");

	pf=fopen(ime_dat,"r");
	if(pf==NULL)
		return -1;

	while(!feof(pf))
	{
		q=(Position)malloc(sizeof(lista));
		if(q==NULL)
			return -1;

		fscanf(pf,"%d",&q->broj);

		temp=p;

		while(temp->next!=NULL && temp->next->broj > q->broj)
			temp=temp->next;

		if(temp->next!=NULL && temp->next->broj == q->broj)
			free(q);
		else
		{
			q->next=temp->next;
			temp->next=q;
		}
	}
	free(ime_dat);
	return 0;
}

int PrintList(Position p)
{
	if(p==NULL)
		return -1;

	while(p!=NULL)
	{
		printf(" %d",p->broj);
		p=p->next;
	}
	puts("");
	return 0;
}

int Unija(Position pol1,Position pol2,Position un)
{
	Position q=NULL;
	Position temp=NULL;

	while(pol1!=NULL && pol2!=NULL)
	{
		q=(Position)malloc(sizeof(lista));
		if(q==NULL)
			return -1;

		if(pol1->broj > pol2->broj)
		{
			q->broj=pol1->broj;
			pol1=pol1->next;
		}
		else if(pol1->broj < pol2->broj)
		{
			q->broj=pol2->broj;
			pol2=pol2->next;
		}
		else
		{
			q->broj=pol1->broj;
			pol1=pol1->next;
			pol2=pol2->next;
		}

		q->next=un->next;
		un->next=q;
		un=q;
	}

	if(pol1!=NULL)
		temp=pol1;
	else
		temp=pol2;

	while(temp!=NULL)
	{
		q=(Position)malloc(sizeof(lista));
		if(q==NULL)
			return -1;

		q->broj=temp->broj;
		q->next=un->next;
		un->next=q;
		un=q;

		temp=temp->next;
	}

}

int Presjek(Position pol1,Position pol2,Position pr)
{
	Position q=NULL;
	
	while(pol1!=NULL && pol2!=NULL)
	{
		if(pol1->broj > pol2->broj)
		{
			pol1=pol1->next;
		}
		else if(pol1->broj < pol2->broj)
		{
			pol2=pol2->next;
		}
		else
		{
			q=(Position)malloc(sizeof(lista));
		    if(q==NULL)
			   return -1;

			q->broj=pol1->broj;
			pol1=pol1->next;
			pol2=pol2->next;

			q->next=pr->next;
		    pr->next=q;
		    pr=q;
		}
	}
	return 0;
}