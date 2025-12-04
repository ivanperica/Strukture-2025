#define _CRT_SECURE_NO_WARNINGS

#include "Article.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int CreateAndInsertArticle(ArticlePosition head, const char* name, int quantity, float price) 
{
	ArticlePosition new = CreateArticle(name, quantity, price);
	SortedInsertArticle(head, new);
	return EXIT_SUCCESS;
}

ArticlePosition CreateArticle(const char* name, int quantity, float price)
{
	ArticlePosition new = NULL;
	new = (ArticlePosition)malloc(sizeof(Article));
	strcpy(new->name, name);
	new->quantity = quantity;
	new->price = price;
	new->nextArticle = NULL;
	return new;
}

int SortedInsertArticle(ArticlePosition head, ArticlePosition new)
{
    ArticlePosition temp = head;
    while (temp->nextArticle != NULL && strcmp(temp->nextArticle->name, new->name) < 0)
    {
        temp = temp->nextArticle;
    }
	InsertAfterArticle(temp, new);
    return EXIT_SUCCESS;
}

int InsertAfterArticle(ArticlePosition position, ArticlePosition new)
{
	new->nextArticle = position->nextArticle;
	position->nextArticle = new;
	return EXIT_SUCCESS;
}

int FreeArticles(ArticlePosition head)
{
	while (head->nextArticle != NULL)
	{
		free(head->nextArticle);
	}
	return EXIT_SUCCESS;
}