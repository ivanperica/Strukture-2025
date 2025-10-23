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

int AddFirst(char n[], char s[], int y, Position p);
int PrintList(Position p);
int AddLast(char n[], char s[], int y, Position p);
Position FindPerson(char sname[], Position p);
int DeletePerson(Position h, Position p);
Position FindLast(Position p);
Position FindPrevious(Position h, Position p);

int main()
{
	Person Head = { "", "", 0, NULL };
	
	AddFirst("Ivan", "Perica", 2005, &Head);
	AddFirst("Ivica", "Puljak", 1899, &Head);
	AddLast("Matko", "Tren", 2003, &Head);
	AddLast("Ivi", "Patrik", 1999, &Head);
	AddLast("Josko", "Branka", 2016, &Head);
	PrintList(&Head);
	printf("\n");
	Position t = FindPerson("Tren", &Head);
	DeletePerson(&Head, t);
	PrintList(&Head);

	return 0;
}

int AddFirst(char n[], char s[], int y, Position p)
{
	Position q;
	q = (Position)malloc(sizeof(Person));
	
	strcpy(q->name, n);
	strcpy(q->surname, s);
	q->year = y;

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

int AddLast(char n[], char s[], int y, Position p)
{
	Position q;
	q = (Position)malloc(sizeof(Person));
	strcpy(q->name, n);
	strcpy(q->surname, s);
	q->year = y;
	
	p = FindLast(p);

	q->Next = p->Next;
	p->Next = q;
	return 0;
}

Position FindPerson(char s[], Position p)
{
	Position q = p;
	while (q->Next != NULL)
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
	while (h->Next != p)
		h = h->Next;
	return h;
}