#pragma once

#include "Article.h"
#include "Date.h"

typedef struct _bill* BillPosition;
typedef struct _bill {
	Date date;
	Article articleHead;
	BillPosition nextBill;
}Bill;

int PrintBill(BillPosition position);

BillPosition CreateAndInsertBill(BillPosition head, int year, int month, int day, const char* string);
BillPosition CreateBill(int year, int month, int day, const char* string);
int SortedInsertBill(BillPosition head, BillPosition new);
int InsertAfterBill(BillPosition position, BillPosition new);

int ReadBillFromFile(BillPosition head, const char* file);
int ReadBillSheet(BillPosition head, const char* filepath);

int FreeBills(BillPosition head);