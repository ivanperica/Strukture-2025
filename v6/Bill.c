#define _CRT_SECURE_NO_WARNINGS

#include "Bill.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int PrintBill(BillPosition p)
{
	printf("%s \n", p->date.datestring);
	while (p->articleHead.nextArticle != NULL)
	{
		printf("%s %d %f \n", p->articleHead.name, p->articleHead.quantity, p->articleHead.price);
		p = p->nextBill;
	}
	return EXIT_SUCCESS;
}

BillPosition CreateAndInsertBill(BillPosition head, int year, int month, int day, const char* string)
{
	BillPosition new = CreateBill(year, month, day, string);
	SortedInsertBill(head, new);
	return new;
}

BillPosition CreateBill(int year, int month, int day, const char* string)
{
	BillPosition new = NULL;
	new = (BillPosition)malloc(sizeof(Bill));

	new->date.YY = year;
	new->date.MM = month;
	new->date.DD = day;
	strcpy(new->date.datestring, string);

	new->articleHead.name[0] = "0";
	new->articleHead.quantity = 0;
	new->articleHead.price = 0.0;
	new->articleHead.nextArticle = NULL;

	new->nextBill = NULL;
	return new;
}

int SortedInsertBill(BillPosition head, BillPosition new)
{
	BillPosition temp = head;

	while (temp->nextBill != NULL && DateCompare(temp->nextBill->date, new->date) < 0)
	{
		temp = temp->nextBill;
	}

	InsertAfterBill(temp, new);
	return EXIT_SUCCESS;
}
int InsertAfterBill(BillPosition position, BillPosition new)
{
	new->nextBill = position->nextBill;
	position->nextBill = new;
	return EXIT_SUCCESS;
}

int FreeBills(BillPosition head)
{
	while (head->nextBill != NULL)
	{
		free(head->nextBill);
	}
	return EXIT_SUCCESS;
}

int ReadBillFromFile(BillPosition head, const char* filepath)
{
	

	int year, month, day;
	char datestring[MAX_DATE_LENGTH];

	FILE* file = fopen(filepath, "r");
	if (file == NULL)
	{
		printf("neuspjesno otvaranje datoteke\n");
		return EXIT_FAILURE;
	}

	
	if (fgets(datestring, sizeof(datestring), file) == NULL)
	{
		printf("Prazna datoteka: %s\n", filepath);
		fclose(file);
		return EXIT_FAILURE;
	}



	if (sscanf(datestring, "%d-%d-%d", &year, &month, &day) != 3)
	{
		printf("Neispravan format datuma u %s\n", filepath);
		fclose(file);
		return EXIT_FAILURE;
	}

	BillPosition newBill = CreateAndInsertBill(head, year, month, day, datestring);
	
	
	char buffer[1024];
	while (fgets(buffer, sizeof(buffer), file))
	{
		

		char name[50];
		int quantity;
		float price;

		
		if (sscanf(buffer, "%s %d %f", name, &quantity, &price) == 3)
		{
			CreateAndInsertArticle(&newBill->articleHead, name, quantity, price);
		}
		else
		{
			printf("Neispravan format artikla: %s\n", buffer);
		}
	}

	fclose(file);
	return EXIT_SUCCESS;
}


int ReadBillSheet(BillPosition head, const char* filepath)
{
	FILE* file = fopen(filepath, "r");
	if (file == NULL)
	{
		printf("neuspjesno otvaranje datoteke\n");
		return EXIT_FAILURE;
	}

	char buffer[1024] = { 0 };
	while (fgets(buffer, sizeof(buffer), file) != NULL)
	{
		buffer[strcspn(buffer, "\n")] = '\0';

		if (buffer[0] == '\0')
			continue;

		ReadBillFromFile(head, buffer);
	}
	
	
	fclose(file);
	return EXIT_SUCCESS;
}