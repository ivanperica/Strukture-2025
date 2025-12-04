#pragma once


typedef struct _article* ArticlePosition;
typedef struct _article {
	char name[30];
	int quantity;
	float price;
	ArticlePosition nextArticle;
}Article;

int CreateAndInsertArticle(ArticlePosition head, const char* name, int quantity, float price);
ArticlePosition CreateArticle(const char* name, int quantity, float price);
int SortedInsertArticle(ArticlePosition head, ArticlePosition new);
int InsertAfterArticle(ArticlePosition position, ArticlePosition new);

FreeArticles(ArticlePosition head);