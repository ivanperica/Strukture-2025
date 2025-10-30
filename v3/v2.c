#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define N 30

typedef struct _person* Position;
typedef struct _person{
	char name[N];
	char surname[N];
	int year;
	Position Next;
}Person;

int AddFirst(Position p);
int PrintList(Position p);
int AddLast(Position p);
Position FindPerson(Position p);
int DeletePerson(Position h, Position p);
Position FindLast(Position p);
Position FindPrevious(Position h, Position p);

int AddAfterPerson(Position h);
int AddBeforePerson(Position h);
int SortList(Position h);
int PrintListInFile(Position h, const char* text);
int ReadListFromFile(Position h, const char* text);

int AddLastF(char n[], char s[], int y, Position h);

int main()
{
	Person Head = { "", "", 0, NULL };
	
	AddFirst(&Head);
	AddLast(&Head);
	PrintList(&Head);

	AddAfterPerson(&Head);
	AddBeforePerson(&Head);
	PrintList(&Head);

	printf("\n");
	SortList(&Head);
	PrintList(&Head);
	printf("\n");

	const char* text = "List.txt";
	PrintListInFile(&Head, text);
	
	ReadListFromFile(&Head, text);
	PrintList(&Head);

	return 0;
}

int AddFirst(Position p)
{
	Position q;
	q = (Position)malloc(sizeof(Person));
	printf("Unesite ime, prezime i godinu rodenja:\n");
	scanf("%s %s %d", q->name, q->surname, &q->year);

	q->Next = p->Next;
	p->Next = q;
	return 0;
}

int PrintList(Position p)
{
	
	while (p->Next != NULL)
	{
		p = p->Next;
		printf("%s %s %d \n", p->name, p->surname, p->year);
	}
		return 0;
}

int AddLast(Position p)
{
	Position q;
	q = (Position)malloc(sizeof(Person));
	printf("Unesite ime, prezime i godinu rodenja:\n");
	scanf("%s %s %d", q->name, q->surname, &q->year);
	
	p = FindLast(p);

	q->Next = p->Next;
	p->Next = q;
	return 0;
}

Position FindPerson(Position p)
{
	char s[N];
	printf("Unesite prezime zeljene osobe:\n");
	scanf("%s", s);

	Position q = p->Next; 

	while (q != NULL)
	{
		if (strcmp(q->surname, s) == 0)
			return q;
		q = q->Next;
	}

	return NULL;
}

int DeletePerson(Position h, Position p)
{
	Position q;
	q = FindPrevious(h, p);
	q->Next = p->Next;
	free(p);

	return 0;
}

Position FindLast(Position p)
{
	while (p->Next != NULL)
		p = p->Next;
	return p;
}

Position FindPrevious(Position h, Position p)
{
	while (h->Next != NULL && h->Next != p)
		h = h->Next;
	return h;
}

int AddBeforePerson(Position h)
{
	Position p, prev, q;
	q = (Position)malloc(sizeof(Person));
	if (!q)
	{
		printf("Neuspjela alokacija memorije!\n");
		return EXIT_FAILURE;
	}

	printf("Unesite ime, prezime i godinu rodenja nove osobe:\n");
	scanf("%s %s %d", q->name, q->surname, &q->year);

	p = FindPerson(h);
	if (p == NULL)
	{
		printf("Osoba nije pronadena\n");
		free(q);
		return EXIT_FAILURE;
	}

	prev = FindPrevious(h, p);
	if (prev == NULL)
	{
		printf("prethodni element nije pronaden\n");
		free(q);
		return -1;
	}

	q->Next = p;
	prev->Next = q;

}

int AddAfterPerson(Position h)
{
	Position p, q;
	q = (Position)malloc(sizeof(Person));
	if (!q)
	{
		printf("Neuspjela alokacija memorije\n");
		return EXIT_FAILURE;
	}

	printf("Unesite ime, prezime i godinu rodenja nove osobe:\n");
	scanf("%s %s %d", q->name, q->surname, &q->year);

	p = FindPerson(h);
	if (p == NULL)
	{
		printf("Osoba nije pronadena\n");
		free(q);
		return EXIT_FAILURE;
	}

	q->Next = p->Next;
	p->Next = q;

	return 0;
}

int SortList(Position h)
{
	Position j, prev_j, temp, end;

	end = NULL;
	while (h->Next != end)
	{
		prev_j = h;
		j = h->Next;
		while (j->Next != end)
		{
			if (strcmp(j->surname, j->Next->surname) > 0)
			{
				temp = j->Next;
				prev_j->Next = temp;
				j->Next = temp->Next;
				temp->Next = j;

				j = temp;
			}
			prev_j = j;
			j = j->Next;
		}
		end = j;
	}
	return 0;
}

int PrintListInFile(Position h, const char* text)
{
	FILE* file = fopen(text, "w");
	if (file == NULL)
	{
		printf("neuspjesno otvaranje datoteke '%s'\n", text);
		return EXIT_FAILURE;
	}
	while (h->Next != NULL)
	{
		h = h->Next;
		fprintf(file, "%s %s %d \n", h->name, h->surname, h->year);
	}
	fclose(file);
	return EXIT_SUCCESS;
}

int ReadListFromFile(Position h, const char* text)
{
	FILE* file = fopen(text, "r");
	if (file == NULL)
	{
		printf("neuspjesno otvaranje datoteke '%s'\n", text);
		return EXIT_FAILURE;
	}

	char n[N], s[N];
	int y;
	while (fscanf(file, "%s %s %d", n, s, &y) == 3)
	{
		AddLastF(n, s, y, h);
	}
	fclose(file);
	return EXIT_SUCCESS;
}
int AddLastF(char n[], char s[], int y, Position h)
{
	Position q;
	q = (Position)malloc(sizeof(Person));
	strcpy(q->name, n);
	strcpy(q->surname, s);
	q->year = y;

	h = FindLast(h);

	q->Next = h->Next;
	h->Next = q;
	return EXIT_SUCCESS;
}
