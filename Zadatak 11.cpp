/*Napisati kod koji za zadane podatke studenata (matièni broj, ime i prezime) pravi
hash tablicu sa zasebnim redovima. Tablica ima 11 mjesta, a funkcija za preslikavanje
kljuè raèuna da se zbraja ASCII vrijednost prvih pet slova prezimena i zatim raèuna
ostatak cjelobrojnog dijeljenja te vrijednosti s velièinom tablice. Studenti s istim
kljuèem se pohranjuju u vezanu listu sortiranu po prezimenima i imenima.
Kada se tablica izgradi treba ispisati cijelu tablicu (naglasiti na kojem kljuèu se nalaze
koji podaci) te ponuditi moguænost da se za odreðenog studenta (prezime i ime) ispiše
njegov matièni broj.*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define HASH_SIZE 11

struct student;
typedef struct student *pos;
typedef struct student {
	int matBr;
	char ime[16];
	char prezime[16];
	pos next;
}_student;

pos createNew();
int readFromF( char fileName[], pos hash[]);
int calculate(char surname[], int *hashIndex);
int insertToHash(pos p, pos hash[]);
int compare(pos p1, pos p2);
int printStudent(char name[], char surname[], pos hash[]);
int printH(pos hash[]);

int main()
{
	pos hash[HASH_SIZE];
	char ime[16];
	char prez[16];
	char izbor;
	int i=0;

	for(i=0; i<HASH_SIZE; i++)
	{
		hash[i]=NULL;
	}
	readFromF("hash.txt", hash);
	printH(hash);

	while(1) {
		printf("Zelite li ispisati maticni broj odredenog studenta? (y/n)\n");
		scanf("%c", &izbor);
		if(izbor=='y') {
			printf("Unesite ime i prezime:\n");
			scanf("%s %s", ime, prez);
			printStudent(ime,prez,hash);
		}
		else 
			break;
	}
	return 0;
}

pos createNew()
{
	pos q=(pos)malloc(sizeof(struct student));
	if(q==NULL) {
		printf("Pogreska pri alociranju memorije!\n");
		return NULL;
	}
	q->next=NULL;
	q->ime[0]= '\0';
	q->prezime[0]='\0';
	q->matBr=-1;
	return q;
}

int Calculate(char surname[], int* hashInd)
{
	int n=0;
	int suma=0;
	while(n<5 && surname[n]!='\0') {
		suma+=surname[n];
	}
	*hashInd=suma%HASH_SIZE;
	return 0;
}

int compare(pos p1, pos p2)
{
	int rez=0;
	rez=strcmp(p1->prezime, p2->prezime);
	if(rez==0) {
		rez=strcmp(p1->ime, p2->ime);
	}
	if(rez==0) {
		if(p1->matBr > p2->matBr) {
			rez=1;
		}
		else if(p1->matBr < p2->matBr) {
			rez=-1;
		}
	}
	return rez;
}

int insertToHash(pos p, pos hash[])
{
	int index= -1;
	calculate(p->prezime, &index);

	if(hash[index] ==NULL) {
		hash[index]=p;
	}
	else if(compare(hash[index], p)>0) {
		p->next=hash[index];
	}
	else {
		pos q=hash[index];
		while(q->next!=NULL && compare(q->next,p)<0) {
			q=q->next;
		}
		p->next= q->next;
		q->next= p;
	}
	return 0;
}

int readFromF(char fileName[], pos hash[])
{
	pos p=NULL;
	FILE *dat=fopen(fileName, "r");
	if(dat==NULL) {
		printf("Pogreska pri otvaranju datoteke!\n");
		return -1;
	}
	while(!feof(dat)) {
		p=createNew();
		if(p==NULL) return 1;

		fscanf(dat, "%s %s %d\n", p->ime, p->prezime, &p->matBr);
		insertToHash(p, hash);
	}
	fclose(dat);
	return 0;
}

int printH(pos hash[])
{
	int n=0;
	pos q=NULL;
	printf("PREZIME      IME\t       MBR\n");
	for(n=0;n<HASH_SIZE; n++) 
	{
		q=hash[n];
		while(q!=NULL) {
			printf("%s %s %d\thash: %d\n", q->prezime, q->ime, q->matBr, n);
			q=q->next;
		}
	}
	return 0;
}

int printSudent(char ime[], char prez[], pos hash[])
{
	int index=-1;
	pos q=NULL;
	calculate(prez, &index);
	q=hash[index];
	while(q!=NULL && (strcmp(ime,q->ime)!=0 || strcmp(prez, q->prezime)!=0)) 
	{
		q=q->next;
	}
	if(q==NULL)
		printf("Ne postoji\n");
	else 
		printf("Maticni broj: %d\n", q->matBr);
	return 0;
}
