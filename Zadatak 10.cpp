/*10. Napisati program koji iz datoteke cita postfiks izraz i zatim stvara stablo proracuna. Iz
gotovog stabla proraèuna upisati u datoteku infiks izraz.*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _tree;
typedef struct _tree* position;
typedef struct _tree
{
	char operation[11];
	position left;
	position right;
}tree;

struct _list;
typedef struct _list* Position;
typedef struct _list
{
	position element;
	Position next;
}list;


int push(Position, position);
int pop(Position, position);
int readFromFile(char*, Position);
Position listAlocation();
position treeAlocation();
int ispis(position);


int main()
{
	int i=0;
	char name1[30];

	Position head=listAlocation();
	head->next = NULL;

	printf("Unesite ime datoteke: ");
	scanf(" %s", name1);

	i = readFromFile(name1, head);
	ispis(head->next->element);
	return 0;
}

Position listAlocation()
{
	Position q=(Position)malloc(sizeof(list));
	if(q==NULL) 
		return ;

	q->next=NULL;
	q->element=NULL;
	return q;

}
int readFromFile(char *fileName, Position head)
{
	if (head == NULL) return 1;
	int result;
	FILE *f = fopen(fileName, "r");
	if (f == NULL) return 1;

	while (!feof(f)) {
		position q = treeAlocation();
		fscanf(f, " %s", q->operation);
		if (!strcmp(q->operation, "+") || !strcmp(q->operation, "-") ||
			!strcmp(q->operation, "*") || !strcmp(q->operation, "%")) 
		{
			result = pop(head, q->right);
			if (result) {
				printf("Can't pop!\n");
				return 1;
			}
			result = pop(head, q->left);
			if (result) {
				printf("Can't pop!\n");
				return 1;
			}
			push(head, q);
		}
		else {
			push(head, q);
		}
	}
	fclose(f);

	if (head->next == NULL || head->next->next != NULL) {
		printf("Invalid postfiks!\n");
		return 1;
	}
	return 0;
}

position treeAlocation()
{
	position q = (position)malloc(sizeof(tree));
	if (q == NULL)
	{
		printf("Memorija nije alocirana!!\n");
		return NULL;
	}
	q->left = NULL;
	q->right = NULL;

	return q;
}

int push(Position hList, position hTree)
{
	Position q = listAlocation();
	q->element = hTree;
	q->next = hList->next;
	hList->next = q;

	return 0;
}

int Pop (Position S, position *el) 
{
	Position tmp=NULL;
	position q =NULL;

	if(S ==NULL) return -1;

	tmp = S->next;
	if(tmp == NULL) return -1;

	S->next = tmp->next;
	q = tmp->element;

	free(tmp);
	*el = q;

	return 0;
}

int ispis(position h)
{
	if (h != NULL)
	{
		if(h->left!=NULL) 
			printf("(");
		ispis(h->left);

		printf(" %s ", h->operation);
		ispis(h->right);
		if(h->right!=NULL) 
			printf(")");
	}
	return 0;
}
