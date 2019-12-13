/* Definirati strukturu osoba (ime, prezime, godina rodenja) i napisati program koji:
a) dinamicki dodaje novi element na pocetak liste,
b) ispisuje listu,
c) dinamicki dodaje novi element na kraj liste,
d) pronalazi element u listi (po prezimenu),
e) brise odredeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable. ------OVO JE DRUGI ZADATAKKK */

/* Prethodnom zadatku dodati funkcije:
a) dinamicki dodaje novi element iza odredenog elementa,
b) dinamicki dodaje novi element ispred odredenog elementa,
c) sortira listu po prezimenima osoba,
d) upisuje listu u datoteku,
e) cita listu iz datoteke.-------OVO JE TRECI ZADATAK*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct lista;
typedef struct lista* Position;
typedef struct lista{
	char ime[128];
	char prezime[128];
	int godina_rodenja;
	Position next; // ekvivalentno: struct lista* Next;
}student;

//zadatak drugi funkcije
int Insert(Position);   //insert na pocetak
int Print(Position);  //printanje liste
int InsertData(Position); //umetanje podataka
void InsertEnd(Position);  //insert na kraj
Position FindLast(Position); //trazenje posljednjeg cvora
Position FindSurname(Position);  //pronalazak odredenog cvora (po prezimenu)
int DeletePrez(Position);  //brisanje odredenog cvora
Position FindBeforeSurname(Position);   //pronalazak cvora prije odredenog cvora (po prezimenu)
void PrintMenu();  //obicni menu

//zadatak treci funkcije i moje nadodane
int InsertAfter(Position);  //umetanje poslije nekog odredenog cvora
int InsertBefore(Position);  // -||- prije -||-
int SortList(Position); //sortiranje vec postojece liste
Position FindPlace_Sort(Position,char*);  //funkcija za pronalazenje mjesta na kojem ce se vrsiti sortirani unos
int SortInsert(Position);  //sortirani unos
void SortInsertData(Position);  //unos podataka prilikom sortiranog unosa 
int WriteToFile(Position);  //upisivanje u file
int ReadFromFile(Position);  //citanje iz filea
int DeleteFromBeginning(Position);  //brisanje liste od pocetka
int DeleteFromEnd(Position);       //brisanje liste od kraja
int SortLinkedList(Position); //Sortiranje vec kreirane liste ovisno o npr godini rodenja 
int CountNodes(Position); //broji cvorrove liste


int main()
{
	Position head=NULL;   //dinamicko alociranje head cvora
	Position cvor=NULL;   //pomocni cvor koji ce trebat kod nekih funkcija
	head=(Position)malloc(sizeof(student)); 
	head->next=NULL;

	char izbor=0;
	int brojac=0;

	while(toupper(izbor)!='K')
	{
		PrintMenu();

		scanf("%c",&izbor);
		if(izbor=='1')
		{
			Insert(head);
		}
		else if(izbor=='2')
		{
			Print(head->next);
		}
		else if(izbor=='3')
		{
			InsertEnd(head);
		}
		else if(izbor=='4')
		{
			cvor=FindSurname(head->next);
			if(cvor!=NULL)
			{
				printf("Trazeni student jest: %s %s  %d\n\n",cvor->ime,cvor->prezime,cvor->godina_rodenja);
			}
		}
		else if(izbor=='5')
		{
			DeletePrez(head);
			Print(head->next);
		}
		else if(izbor=='6')
		{
			InsertAfter(head);
			Print(head->next);
		}
		else if(izbor=='7')
		{
			InsertBefore(head);
			Print(head->next);
		}
		else if(izbor=='8')
		{
			SortList(head);
			Print(head->next);
		}
		else if(izbor=='9')
		{
			SortInsert(head);
			Print(head->next);
		}
		else if(izbor=='B' || izbor=='b')
		{
			DeleteFromBeginning(head);
		}
		else if(izbor=='E' || izbor=='e')
		{
			DeleteFromEnd(head);
		}
		else if(izbor=='W' || izbor=='w')
		{
			WriteToFile(head->next);
			Print(head->next);
		}
		else if(izbor=='R'|| izbor=='r')
		{
			ReadFromFile(head);
			Print(head->next);
		}
		else if(izbor=='S'|| izbor=='s')
		{
			SortLinkedList(head);
			Print(head->next);
		}
		else if(izbor=='C'|| izbor=='c')
		{
			brojac=CountNodes(head);
			printf("Broj cvorova jest: %d\n\n",brojac);
			Print(head->next);
		}
		else if(izbor=='K'|| izbor=='k')
		{
			break;
		}
		else
		{
			printf("Pogresan unos: %c. Odaberite ponovo.\n\n",izbor);
		}
	}
    return 0;
}

void PrintMenu()
{
	printf("****************************************\r\n");
		printf("***   VJEZBA BR. 02  -  Vezane liste ***\r\n");
		printf("****************************************\r\n");
		printf("\r\n\r\n");
		printf("\t1. Unos\r\n");
		printf("\t2. Ispis\r\n");
		printf("\t3. Unos na kraj\r\n");
		printf("\t4. Pronadji po prezimenu\r\n");
		printf("\t5. Izbrisi po prezimenu\r\n");
		printf("\t6. Unos nakon studenta\r\n");
		printf("\t7. Unos prije studenta\r\n");
		printf("\t8. Sortiraj\r\n");
		printf("\t9. Sortirani unos\r\n");
		printf("\tR. Ucitaj listu iz datoteke\r\n");
		printf("\tW. Ispisi listu u datoteku\r\n");
		printf("\tS. Sortiraj preko godine rodenja\r\n");
		printf("\tE. Brisi od kraja\r\n");
		printf("\tB. Brisi od pocetka\r\n");
		printf("\tC. Broji cvorove liste\r\n");
		printf("\tK. Izlaz iz programa\r\n");
		printf("\r\n\tIzbor : ");

}

int Insert(Position p)
{
	Position q=NULL;
	q=(Position)malloc(sizeof(student));
	if(q==NULL){
		printf("Pogresno alociran cvor");
		return -1;
	}
	InsertData(q);
	q->next=p->next;
	p->next=q;

	return 0;
}

int InsertData(Position p)
{
	if(p==NULL)
	{
		return -1;
	}
	else
	{
		printf("Unesite ime,prezime i godinu rodenja studenta.\n");
		scanf("%s %s %d",p->ime,p->prezime,&p->godina_rodenja);
		return 0;
	}
}

int Print(Position p)  //funkcija prima head->next element jer u headu nema nista
{
	if(p==NULL)
	{
		printf("Lista je prazna!\n\n");
		return -1;
	}
	else
	{
		while(p!=NULL)
		{
			printf("%s %s  %d\n",p->ime,p->prezime,p->godina_rodenja);
			p=p->next;
		}
	}
	return 0;
}

void InsertEnd(Position p)
{
	Position last=NULL;
	last=FindLast(p);
	Insert(last);
}

Position FindLast(Position p)
{
	while(p->next!=NULL)
	{
		p=p->next;
	}
	return p;
}

Position FindSurname(Position p)
{

	char *prezime;
	prezime=(char*)malloc(sizeof(char)*128);

	printf("Unesite prezime koje zelite pronaci: ");
	scanf("%s",prezime);

	while(p!=NULL && strcmp(p->prezime,prezime)!=NULL)
		p=p->next;

	if(p==NULL)
	{
		printf("Takvo prezime ( %s ) ne postoji!\n\n",prezime);
	}
	free(prezime);
	return p;
}

int DeletePrez(Position p)
{
	Position current=NULL;
	p=FindBeforeSurname(p);
	if(p==NULL)
	{
		printf("Trazeno prezime se ne nalazi u listi!\n\n");
		return -1;
	}
	else{
		current=p->next;
		if(current!=NULL)
		{
			printf("Iz liste se brise element sa podatcima: %s %s  %d\n\n",current->ime,current->prezime,current->godina_rodenja);
			p->next=current->next;
			free(current);
		}
	}
	return 0;
}

Position FindBeforeSurname(Position p)
{
	char *prezime=NULL;
	prezime=(char*)malloc(sizeof(char)*128);
	
	printf("Napisite koje prezime zelite izbrisati: ");
	scanf("%s",prezime);

	while(p->next!=NULL && strcmp(p->next->prezime,prezime)!=0)
		p=p->next;

	if(p->next==NULL)
		p=NULL;

	free(prezime);
	return p;
}

int InsertAfter(Position p)
{
	p=FindSurname(p);
	if(p==NULL)
		return -1;

	Insert(p);
	return 0;
}

int InsertBefore(Position p)
{
	p=FindBeforeSurname(p);
	if(p==NULL)
		return -1;

    Insert(p);
	return 0;
}

int SortList(Position p)  //nisam bas skontao , prepisao sam od crnjca
{
	Position i = p;
	Position j = NULL;
	Position prev_j = NULL;
	Position end = NULL;

	while (i->next != end)
	{
		prev_j = i;
		j = prev_j->next;

		while (j->next != end)
		{
			if (strcmp(j->prezime, j->next->prezime) > 0)
			{
				prev_j->next = j->next;
				j->next = j->next->next;
				prev_j->next->next = j;
				j = prev_j->next;
			}
			prev_j = j;
			j = j->next;
		}
		end = j;
	}

	return 0;
}

Position FindPlace_Sort(Position p,char *prez)
{
	while(p->next!=NULL && strcmp(prez,p->next->prezime)>0)
	{
		p=p->next;
	}
	return p;
}

int SortInsert(Position p)
{
	char *prezime=NULL;
	Position q=NULL;

	prezime=(char*)malloc(sizeof(char)*128);
	if(prezime==NULL)
		return NULL;

	printf("Unesite prezime studenta prema kojem ce se vrsiti sortirani unos\n");
	scanf("%s",prezime);
	p=FindPlace_Sort(p,prezime);

	q=(Position)malloc(sizeof(student));
	if(q==NULL)
		return -1;

	SortInsertData(q);
	strcpy(q->prezime,prezime);

	q->next=p->next;
	p->next=q;

	free(prezime);
    return 0;
}

void SortInsertData(Position p)
{
	printf("Unesite jos ime i godinu rodenja studenta: ");
	scanf("%s %d",p->ime,&p->godina_rodenja);
}

int WriteToFile(Position p)
{
	FILE *fp=NULL;
	char *ime_dat=NULL;
	ime_dat=(char*)malloc(sizeof(char)*128);
	if(ime_dat==NULL)
		return -1;

	printf("Upisite ime datoteke u koju zelite upisati listu: ");
	scanf("%s",ime_dat);

	if(strrchr(ime_dat,'.')==0)
		strcat(ime_dat,".txt");

	fp=fopen(ime_dat,"w");
	if(fp==NULL)
	{
		puts("Pogresno otvorena datoteka!\n");
		return -1;
	}

	while(p!=NULL)
	{
		fprintf(fp,"%s %s   %d\n",p->ime,p->prezime,p->godina_rodenja);
		p=p->next;
	}

	fclose(fp);
	free(ime_dat);
	return 0;
}

int ReadFromFile(Position p)
{
	FILE *fp=NULL;
	Position q=NULL;
	char *ime_dat=NULL;
	ime_dat=(char*)malloc(sizeof(char)*128);
	if(ime_dat==NULL)
		return -1;

	printf("Upisite ime datoteke iz koje zelite ucitati listu: ");
	scanf("%s",ime_dat);

	if(strrchr(ime_dat,'.')==0)
		strcat(ime_dat,".txt");

	fp=fopen(ime_dat,"r");
	if(fp==NULL)
	{
		puts("Pogresno otvorena datoteka!\n");
		return -1;
	}

	while(!feof(fp))
	{
		q=(Position)malloc(sizeof(student));
		fscanf(fp,"%s %s %d",q->ime,q->prezime,&q->godina_rodenja);
		q->next=p->next;
		p->next=q;
	}

	free(ime_dat);
	fclose(fp);
	return 0;
}

int DeleteFromBeginning(Position p)
{
	Position q=NULL;
	while(p->next!=NULL)
	{
		q=p->next;    //postaje prvi clan liste
		p->next=p->next->next;  //prvi clan liste pokazuje na drugi clan
		free(q); //prvi clan je izbrisan tako da drugi clan je sada prvi
	}
	return 0;
}

int DeleteFromEnd(Position p)
{
       Position start=p;  // zauzet ce prvu poziciju u listi
	   Position temp=p;   //setat ce po listi uvijek do predzadnjeg cvora 

	   while(start->next!=NULL)
	   {
		   while(p->next!=NULL)  //p seta uvijek do zadnjeg i onda se brise, temp postaje privremeno zadnji
		   {
			   temp=p;
			   p=p->next;    
		   }
		   free(p);
		   temp->next=NULL;
		   p=start;
	   }
	   return 0;
}

int SortLinkedList(Position p)
{
	Position i = p;
	Position j = NULL;
	Position prev_j = NULL;
	Position end = NULL;

	while (i->next != end)
	{
		prev_j = i;
		j = prev_j->next;

		while (j->next != end)
		{
			if (j->godina_rodenja > j->next->godina_rodenja)
			{
				prev_j->next = j->next;
				j->next = j->next->next;
				prev_j->next->next = j;
				j = prev_j->next;
			}
			prev_j = j;
			j = j->next;
		}
		end = j;
	}

	return 0;
}

int CountNodes(Position p)
{
	int brojac=0;
	while(p->next!=NULL)
	{
		p=p->next;
		brojac++;
	}
	return brojac;
}



// nevazno
 /*switch(izbor)
		{
		case '1':
			Insert(head);
			break;
		case '2':
			Print(head->next);
			break;
		case '3':
			InsertEnd(head);
			break;
		case '4':
			cvor=FindSurname(head->next);
			if(cvor!=NULL)
			{
				printf("Trazeni student jest: %s %s  %d\n\n",cvor->ime,cvor->prezime,cvor->godina_rodenja);
			}
			break;
		case '5':
			DeletePrez(head);
			break;
		case '6':
			InsertAfter(head);
			break;
		case '7':
			InsertBefore(head);
			break;
		case '8':
			SortList(head);
			break;
		case '9':
			SortInsert(head);
			break;
		case 'R':
		case 'r':
			ReadFromFile(head);
			break;
		case 'W':
		case 'w':
			WriteToFile(head);
			break;
		case 'b':
		case 'B':
			DeleteFromBeginning(head);
			break;
		case 'E':
		case 'e':
			DeleteFromEnd(head);
			break;
		case 'S':
		case 's':
			SortLinkedList(head);
			break;
		case 'c':
		case 'C':
			brojac=CountNodes(head);
			printf("Broj cvorova jest: %d\n\n",brojac);
			break;
		case 'K':
		case 'k':
			break;
		default:
			printf("Pogresan izbor, pokusajte ponovo.\n\n");
			break;
		} */