#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <string.h>

typedef struct _polynomail* Position;
typedef struct _polynomail {
	int coefficient;
	int exponent;
	Position next;
}Polynomail;

int ReadFromFile(Position head1, Position head2, const char* text);
int ReadData(Position head, const char* buffer);

int CreateAndInsert(Position head, int coefficient, int exponent);
Position CreateElement(int coefficient, int exponent);
int SortedInsert(Position head, Position newEl);
int Merge(Position position, Position newEl);
int InsertAfter(Position position, Position newEl);
int DeleteAfter(Position position);
int ClearPoly(Position head);
int PrintPoly(Position head);

int AddPoly(Position result, Position poly1, Position poly2);
int MultiplyPoly(Position result, Position poly1, Position poly2);

int main()
{
	Polynomail poly1 = { .coefficient = 0, .exponent = 0, .next = NULL };
	Polynomail poly2 = { .coefficient = 0, .exponent = 0, .next = NULL };
	Polynomail result1 = { .coefficient = 0, .exponent = 0, .next = NULL };
	Polynomail result2 = { .coefficient = 0, .exponent = 0, .next = NULL };
	
	const char* text = "Polynomail1.txt";
	ReadFromFile(&poly1, &poly2, text);

	PrintPoly(&poly1);
	PrintPoly(&poly2);

	AddPoly(&result1, &poly1, &poly2);
	PrintPoly(&result1);

	MultiplyPoly(&result2, &poly1, &poly2);
	PrintPoly(&result2);

	ClearPoly(&poly1); 
	ClearPoly(&poly2);
	ClearPoly(&result1);
	ClearPoly(&result2);

	return EXIT_SUCCESS;
}

int ReadFromFile(Position head1, Position head2, const char* text)
{
	FILE* file = fopen(text, "r");
	char buffer[1024] = { 0 };

	fgets(buffer, 128, file);
	ReadData(head1, buffer);

	fgets(buffer, 128, file);
	ReadData(head2, buffer);

	fclose(file);
	return EXIT_SUCCESS;
}
int ReadData(Position head, const char* buffer)
{
	int coefficient = 0;
	int exponent = 0;
	int offset = 0;
	while (*buffer != '\0')
	{
		if (sscanf(buffer, " %d %d %n", &coefficient, &exponent, &offset) != 2)
		{
			return EXIT_FAILURE;
		}
		if (coefficient != 0)
		{
			CreateAndInsert(head, coefficient, exponent);
		}
		buffer = buffer + offset;
	}
	return EXIT_SUCCESS;
}


int CreateAndInsert(Position head, int coefficient, int exponent)
{
	if (coefficient != 0)
	{
		Position newEl = CreateElement(coefficient, exponent);
		SortedInsert(head, newEl);
	}
	return EXIT_SUCCESS;
}
Position CreateElement(int coefficient, int exponent)
{
	Position newEl;
	newEl = (Position)malloc(sizeof(Polynomail));
	newEl->coefficient = coefficient;
	newEl->exponent = exponent;
	newEl->next = NULL;
	return newEl;
}
int SortedInsert(Position head, Position newEl)
{
	Position temp = head;
	while (temp->next != NULL && temp->next->exponent > newEl->exponent)
		temp = temp->next;

	Merge(temp, newEl);
	return EXIT_SUCCESS;
}
int Merge(Position position, Position newEl)
{
	Position temp = position;
	int result = 0;
	if (temp->next != NULL && temp->next->exponent == newEl->exponent)
	{
		result = temp->coefficient + newEl->coefficient;
		if (result != 0)
		{
			temp->next->coefficient = result;
		}
		else
		{
			DeleteAfter(temp);
		}
		free(newEl);
	}
	else
	{
		InsertAfter(temp, newEl);
	}
	return EXIT_SUCCESS;
}
int InsertAfter(Position position, Position newEl)
{
	newEl->next = position->next;
	position->next = newEl;
	return EXIT_SUCCESS;
}
int DeleteAfter(Position position)
{
	Position q = position->next;
	position->next = q->next;
	free(q);
	return EXIT_SUCCESS;
}
int ClearPoly(Position head)
{
	Position temp = head;
	if (temp->next == NULL)
		return EXIT_FAILURE;
	while (temp->next != NULL)
		DeleteAfter(head);
	return EXIT_SUCCESS;
}

int AddPoly(Position result, Position poly1, Position poly2)
{
	Position p1 = poly1->next;
	Position p2 = poly2->next;
	
	while (p1 != NULL && p2 != NULL)
	{
		if (p1->exponent == p2->exponent)
		{
			CreateAndInsert(result, p1->coefficient + p2->coefficient, p1->exponent);
			p1 = p1->next;
			p2 = p2->next;
		}
		else if (p1->exponent > p2->exponent)
		{
			CreateAndInsert(result, p1->coefficient, p1->exponent);
			p1 = p1->next;
		}
		else
		{
			CreateAndInsert(result, p2->coefficient, p2->exponent);
			p2 = p2->next;
		}
	}

	Position temp = NULL;
	if (p1 != NULL)
		temp = p1;
	else
		temp = p2;

	while (temp != NULL)
	{
		CreateAndInsert(result, temp->coefficient, temp->exponent);
		temp = temp->next;
	}

	return EXIT_SUCCESS;
}

int MultiplyPoly(Position result, Position poly1, Position poly2)
{
	Position i;
	Position j;
	for (i = poly1->next; i != NULL; i = i->next)
	{
		for (j = poly2->next; j != NULL; j = j->next)
		{
			CreateAndInsert(result, i->coefficient * j->coefficient, i->exponent + j->exponent);
		}
	}
	return EXIT_SUCCESS;
}
int PrintPoly(Position head)
{
	Position temp = head->next;
	while (temp != NULL)
	{
		printf(" %d*x^%d", temp->coefficient, temp->exponent);
		if (temp->next != NULL) 
			printf(" + ");
		temp = temp->next;
	}
	printf("\n");
	return EXIT_SUCCESS;
}