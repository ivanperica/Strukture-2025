#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <string.h>

typedef struct _Element* Position;
typedef struct _Element {
	float number;
	Position next;
}Element;

float EvaluatePostfix(Position head, char postfix[]);
int ReadFromFile(char postfix[], const char* text);
float PerformOperation(Position head, char operation);
Position CreateElement(float number);
int Push(Position head, float number);
int DeleteAfter(Position head);
float pop(Position head);

int main()
{
	Element Head = { 0, NULL };
	const char* text = "postfix.txt";
	char postfix[100];

	ReadFromFile(postfix, text);
	printf("Postfix izraz: %s\n", postfix);

	float rezultat = EvaluatePostfix(&Head, postfix);
	printf("Rezultat: %.2f\n", rezultat);

	return EXIT_SUCCESS;
}

float EvaluatePostfix(Position head, char postfix[])
{
	char* token = NULL;
	float number = 0.0f;
	float result = 0.0f;

	token = strtok(postfix, " ");
	while (token != NULL)
	{
		if (sscanf(token, "%f", &number) == 1)
		{
			Push(head, number);
		}
		else if (strlen(token) == 1 && strchr("+-*/", token[0]))
		{
			result = PerformOperation(head, token[0]);
		}
		else
		{
			printf("Nepoznat token: %s\n", token);
		}

		token = strtok(NULL, " ");
	}

	
	if (head->next != NULL)
		result = head->next->number;
	else
		printf("stog je prazan!\n");

	return result;
}

int ReadFromFile(char postfix[], const char* text)
{
	FILE* file = fopen(text, "r");
	if (file == NULL)
	{
		printf("neuspjesno otvaranje datoteke\n");
		return EXIT_FAILURE;
	}
	fgets(postfix, 100, file);
	fclose(file);
	return EXIT_SUCCESS;
}

Position CreateElement(float number)
{
	Position q = NULL;
	q = (Position)malloc(sizeof(Element));
	q->number = number;
	q->next = NULL;
	return q;
}

int Push(Position head, float number)
{
	Position q = CreateElement(number);
	q->next = head->next;
	head->next = q;

	return EXIT_SUCCESS;
}

int DeleteAfter(Position head)
{
	Position q = head->next;
	head->next = q->next;
	q->next = NULL;
	free(q);

	return EXIT_SUCCESS;
}

float pop(Position head)
{
	float number;
	Position q = head->next;
	number = q->number;

	DeleteAfter(head);
	return number;
}

float PerformOperation(Position head, char operation)
{
	float operand2 = pop(head);
	float operand1 = pop(head);
	float result = 0.0f;
	switch (operation)
	{
	case '-':
		result = operand1 - operand2;
		Push(head, result);
		break;

	case '+':
		result = operand1 + operand2;
		Push(head, result);
		break;

	case '*':
		result = operand1 * operand2;
		Push(head, result);
		break;

	case '/':
		if (operand2 == 0)
		{
			printf("nemoguce djeljenje s 0\n");
			return EXIT_FAILURE;
		}
		result = operand1 / operand2;
		Push(head, result);

		break;

	default:
		printf("error\n");
		break;
	}

	return result;
}