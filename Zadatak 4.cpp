/*Napisati program za zbrajanje i množenje polinoma. Koeficijenti i eksponenti se
èitaju iz datoteke.
Napomena: Eksponenti u datoteci nisu nužno sortirani. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct _lista;
typedef struct _lista* Position;
typedef struct _lista{
	int koef;
	int eks;
	Position next;
}lista;

int ReadFromFile(Position);
int PrintMenu();
int PrintPoly(Position);
int AddPoly(Position,Position,Position);
int MultyPoly(Position,Position,Position);

int main()
{
	lista p1,p2,s,m;
	p1.next=NULL;
	p2.next=NULL;
	s.next=NULL;
	m.next=NULL;

	PrintMenu();

	ReadFromFile(&p1);
	ReadFromFile(&p2);

	printf("Ispis prvog polinoma: ");
	PrintPoly(p1.next);
	printf("Ispis drugog polinoma: ");
	PrintPoly(p2.next);

	AddPoly(p1.next,p2.next,&s);
	printf("Ispis sumiranog polinoma: ");
	PrintPoly(s.next);

	MultyPoly(p1.next,p2.next,&m);
	printf("Ispis pomnozenog polinoma: ");
	PrintPoly(m.next);

	printf("\n\nGOTOV PROGRAM!\n\n"); 
	return 0;
}

int PrintMenu()
{
	printf("\r\n\t************************************");
	printf("\r\n\t***   VJEZBA BR. 04  -  Polinomi ***");
	printf("\r\n\t************************************");
	printf("\r\n\r\n");

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
	{
		printf("Pogresno alociran niz...\n");
		return -1;
	}

	printf("Upisite ime datoteke: ");
	scanf("%s",ime_dat);

	if(strrchr(ime_dat,'.')==0)
		strcat(ime_dat,".txt");

	pf=fopen(ime_dat,"r");
	if(pf==NULL)
	{
		printf("Pogresno otvorena datoteka\n");
		return -1;
	}

	while(!feof(pf))
	{
		q=(Position)malloc(sizeof(lista));
		if(q==NULL)
		{
			printf("Pogresno alociran cvor\n");
			return -1;
		}

		fscanf(pf,"%d %d",&q->koef,&q->eks);

		temp=p;

		while(temp->next!=NULL && temp->next->eks > q->eks)
			temp=temp->next; 

		if(temp->next!=NULL && temp->next->eks == q->eks)
		{
			temp->next->koef += q->koef;
			free(q);
		}
		else
		{
		   q->next=temp->next;
		   temp->next=q;
		}
	}

	free(ime_dat);
	fclose(pf);
	return 0;
}

int PrintPoly(Position p)
{
	while(p!=NULL)
	{
		if(p->koef >=0)
		{
			printf(" +%dX^%d",p->koef,p->eks);
		}
		else
			printf(" %dX^%d",p->koef,p->eks);

		p=p->next;
	}

	printf("\n");
	return 0;
}

int AddPoly(Position pol1,Position pol2,Position sum)
{
	Position temp=NULL;
	Position q=NULL;
	
	while(pol1!=NULL && pol2!=NULL)
	{
		q=(Position)malloc(sizeof(lista));
		if(q==NULL)
		{
			printf("Pogresno alociran cvor.\n");
			return -1;
		}

		if(pol1->eks > pol2->eks)
		{
			q->eks = pol1->eks;
			q->koef= pol1->koef;
			pol1=pol1->next;
		}
		else if(pol1->eks < pol2->eks)
		{
			q->eks = pol2->eks;
			q->koef= pol2->koef;
			pol2=pol2->next;
		}
		else
		{
			q->eks = pol2->eks;
			q->koef= pol1->eks + pol2->koef;
			pol1=pol1->next;
			pol2=pol2->next;
		}

		q->next=sum->next;
		sum->next = q;
		sum=q;
	}

		if(pol1!= NULL)
			temp=pol1;
		else
			temp=pol2;

		while(temp!=NULL)
		{
			q=(Position)malloc(sizeof(lista));
		    if(q==NULL)
		    {
			    printf("Pogresno alociran cvor.\n");
			    return -1;
		    }

			q->eks=temp->eks;
			q->koef=temp->koef;

			q->next=sum->next;
		    sum->next = q;
			sum=q;

			temp=temp->next;
		}

	return 0;
}

int MultyPoly(Position pol1,Position pol2 ,Position mul)
{
	Position i=pol1;
	Position j=NULL;
	Position q=NULL;
	Position temp=NULL;

	while(i!=NULL)
	{
		j=pol2;

		while(j!=NULL)
		{
			q=(Position)malloc(sizeof(lista));
		    if(q==NULL)
		    {
			    printf("Pogresno alociran cvor.\n");
			    return -1;
		    }

			q->eks = i->eks + j->eks;
			q->koef= i->koef * j->koef;

			temp=mul;
			while(temp->next!=NULL && temp->next->eks > q->eks)
				temp=temp->next;

			if(temp->next!=NULL && temp->next->eks == q->eks)
			{
				temp->next->koef += q->koef;
				free(q);
			}
			else
			{
			   q->next=temp->next;
			   temp->next=q;
			}
			j=j->next;

		}
		i=i->next;
	}
	return 0;
}