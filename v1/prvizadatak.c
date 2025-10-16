#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>

typedef struct _student
{
	char name[50];
	char surname[50];
	int points;
}student;

int number(const char *text) {
	FILE *file;
	student s = { .name = "", .surname = "", .points = 0 };
	int number = 0;
	file = fopen(text, "r");
	if (file == NULL)
		printf("error!\n");
	while (fscanf(file, " %s %s %d", s.name, s.surname, &s.points) == 3) {
		number++;
	}
	fclose(file);
	return  number;
}

int read(const char *text, student *s, int number) {
	FILE* file;
	int i = 0;
	file = fopen(text, "r");
	if (file == NULL)
		printf("error!\n");
	for (i; i < number; i++) {
		fscanf(file, "%s %s %d", s[i].name, s[i].surname, &s[i].points);
	}
	fclose(file);
	return 0;

}

int print(student *s, int number) {
	int i = 0;
	printf("popis studenata:\n");
	for (i; i < number; i++) {
		printf("%s %s %d %f\n", s[i].name, s[i].surname, s[i].points, ((float)s[i].points/80.0f)*100);
	}
	return 0;
}

int main()
{
	const char* text = "studenti.txt";
	int num = number(text);
	int i = 0;
	student s[10];
	read(text, s, num);
	print(s, num);
	
	return 0;
}