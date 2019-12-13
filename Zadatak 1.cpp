/* Napisati program koji prvo pročita koliko redaka ima datoteka, tj. koliko ima studenata zapisanih u datoteci.
Nakon toga potrebno je dinamički alocirati prostor za niz struktura studenata (ime, prezime, bodovi) i učitati iz datoteke sve zapise.
Na ekran ispisati ime, prezime,apsolutni i relativni broj bodova. 
Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova/max_br_bodova*100 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct{
	char *ime;
	char *prezime;
	int bodovi;
	double rel_bodovi;
}student;

int Counter(FILE *fp);
int PrintMenu();
int PrintStudents(student *s,int);
int ReadStudents(student *s,int,char *);

int main()
{
	student *st=NULL;
	int counter=0;
	int i=0;
	char *ime_dat=NULL;
	FILE *pf=NULL;

	PrintMenu();

	ime_dat=(char*)malloc(sizeof(char)*127);
	if(ime_dat==NULL){
		printf("Greska prilikom alociranja niza\n");
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

	counter=Counter(pf);
	if(counter==0)
	{
		printf("Datoteka je prazna\n");
		return -1;
	}
	else{
		printf("Ukupno je %d studenata u datoteci. \n",counter);
		st=(student*)malloc(sizeof(student)*counter);
		if(st==NULL)
		{
			printf("Greska pri alociranju\n");
			return -1;
		}
		else
		{
			ReadStudents(st,counter,ime_dat);
		}
	}
	
    PrintStudents(st,counter);
	printf("\nGotov program\n");
	return 0;
}

int PrintMenu()
{
	printf("\n***************\n");
	printf("*****VJEZBA 1*****\n");
	printf("\n***************\n");

	return 0;
}

int Counter(FILE *fp)
{

	char *niz=NULL;
	int brojac=0;

	niz=(char*)malloc(sizeof(char)*127);
	if(niz==NULL)
	{
		printf("Pogresno alociran niz\n");
		return -1;
	}

	while(!feof(fp))
	{
		fgets(niz,126,fp);
		if(isalnum(niz[0]))
		   brojac++;
	}

	free(niz);
	return brojac;
}

int ReadStudents(student *s,int br,char *ime)
{
	FILE *pff=NULL;
	int i=0;

	pff=fopen(ime,"r");
	if(pff==NULL)
	{
		printf("Pogresno otovrena datoteka\n");
		return -1;
	}

	for( ;i<br;i++)
	{
		(s+i)->ime=(char*)malloc(sizeof(char)*127);
		(s+i)->prezime=(char*)malloc(sizeof(char)*127);

		fscanf(pff,"%s",s[i].ime);
		fscanf(pff,"%s",s[i].prezime);
		fscanf(pff,"%d",&s[i].bodovi);
		s[i].rel_bodovi=(double)s[i].bodovi/1.5;
	}

	fclose(pff);
	return 0;
}

int PrintStudents(student *s,int br)
{
	int i=0;
	for( ;i<br;i++)
	{
		//printf("Ispis %d. studenta:\n",i+1);
		printf("%s %s %d %lf\n\n",(s+i)->ime,(s+i)->prezime,(s+i)->bodovi,(s+i)->rel_bodovi);
	}
	return 0;
}