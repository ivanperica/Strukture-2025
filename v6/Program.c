#include "Bill.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main()
{
    
    BillPosition allBills = (BillPosition)malloc(sizeof(Bill));
    allBills->nextBill = NULL;

    
    ReadBillSheet(allBills, "bills.txt");

    
    BillPosition p = allBills->nextBill;
    while (p) {
        printf("Datum: %s\n", p->date.datestring);

        ArticlePosition a = p->articleHead.nextArticle; 
        while (a) {
            printf("  %s %d %.2f\n", a->name, a->quantity, a->price);
            a = a->nextArticle;
        }
        printf("\n");
        p = p->nextBill;
    }

    free(allBills); 
    return 0;
}