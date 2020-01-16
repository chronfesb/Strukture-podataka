#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _tree;
typedef struct _tree* Position;
typedef struct _tree
{
	char* name;
	Position child;
	Position next;
}Tree;

struct _stack;
typedef struct _stack* position;
typedef struct _stack
{
	Position tree;
	position Next;
}Stack;

Position AllocationTree();
position AllocationStack();
Position ChangeDirectory(Position, position, char*);
Position pop(position);
int push(Position, position);
int MakeDirectory(Position, char*);
int printDirectory(Position);
int GarbageCollector(Position);

int main()
{
	Position root=(Position)malloc(sizeof(Tree));
	Position curretDir = root;
	position head = AllocationStack();
	char *name;
	int i = -1;

	name = (char*)malloc(21 * sizeof(char));
	root->child = NULL;
	root->next= NULL;
	root->name = (char*)malloc(5 * sizeof(char));
	strcpy(root->name, "root");
	head->Next = AllocationStack();
	head->Next->tree = root;
	head->Next->Next = NULL;

	while (i != 0)
	{
		printf("\n\nNalazite se u %s direktoriju:\n", curretDir->name);
		printf("Odaberite radnju:\n");
		printf("1. md (Make directory)\n");
		printf("2. cd (Change directory)\n");
		printf("3. cd.. (Previous directory)\n");
		printf("4. dir (List directories)\n");
		printf("0. exit\n");
		printf("Vas odabir: ");
		scanf(" %d", &i);

		switch (i)
		{
		case 1:
			printf("md ");
			scanf(" %s", name);
			MakeDirectory(curretDir, name);
			break;
		case 2:
			printf("cd ");
			scanf(" %s", name);
			curretDir = ChangeDirectory(curretDir, head, name);
			break;
		case 3:
			printf("cd..\n");
			curretDir = pop(head);
			break;
		case 4:
			printf("dir\n");
			printDirectory(curretDir);
			break;
		case 0:
			break;
		default:
			printf("Nepoznata naredba!!\n");
			break;
		}
	}

	GarbageCollector(root);
	free(name);
	return 0;
}
Position AllocationTree()
{
	Position q = (Position)malloc(sizeof(Tree));
	
	if (q == NULL)
	{
		printf("Memorija nije alocirana!!\n");
		return NULL;
	}

	q->child = NULL;
	q->next = NULL;

	return q;
}

position AllocationStack()
{
	position q = (position)malloc(sizeof(Stack));
	
	if (q == NULL)
	{
		printf("Memorija nije alocirana!!\n");
		return NULL;
	}

	return q;
}

int MakeDirectory(Position Tree, char* name)
{
	Position q = AllocationTree();
	Position x = Tree->child;
	q->name = (char*)malloc(strlen(name) + 1);
	strcpy(q->name, name);
	
	printf("\nDirektorij %s je napravljen!!\n", name);
	
	if (Tree->child == NULL)
	{
		Tree->child = q;
		return 0;
	}

	else if (strcmp(q->name, x->name) < 0)
	{ 
		q->next = x;
		Tree->next= q;
		return 0;
	}

	else
	{
		while (x->next != NULL && strcmp(q->name, x->next->name) > 0)
			x = x->next;

		q->next = x->next;
		x->next = q;
	}
	return 0;
}

Position ChangeDirectory(Position curretDir, position stack, char* name)
{
	Position x = curretDir->child;

	while (x != NULL && strcmp(x->name, name) != 0)
		x = x->next;

	if (x == NULL)
	{
		printf("\nNe postoji taj direktorij!!\n");
		return curretDir;
	}

	push(curretDir, stack);

	return x;
}

Position pop(position stack)
{
	position tmp = stack->Next;
	
	if (tmp->Next == NULL)
		printf("\nVec se nalazite u root direktoriju!!\n");

	else
		stack->Next = tmp->Next;

	return tmp->tree;
}

int push(Position tree, position stack)
{
	position q = AllocationStack();

	q->tree = tree;
	q->Next = stack->Next;
	stack->Next = q;

	return 0;
}
int printDirectory(Position tree)
{
	Position x = tree->child;

	if (x == NULL)
	{
		printf("\nDirektorij je prazan!!\n");
		return -1;
	}

	printf("\nLista direktorija:\n");
	while (x != NULL)
	{
		printf("%s\n", x->name);
		x = x->next;
	}

	return 0;
}

int GarbageCollector(Position P)
{
	if (P == NULL)
		return -1;

	else if (P->child != NULL)
		GarbageCollector(P->child);

	else if (P->next != NULL)
		GarbageCollector(P->next);

	free(P->name);
	free(P);

	return 0;
}