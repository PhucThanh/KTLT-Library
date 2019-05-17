#include "book.h"
void printBook(BOOK b)
{
	printf("ISBN : %s\n", b.ISBN);
	printf("Name : %s\n", b.name);
	printf("Author : %s\n", b.author);
	printf("Publisher : %s\n", b.publisher);
	printf("Category : %s\n", b.category);
	printf("Year : %d\n", b.year);
	printf("Price : %d\n", b.price);
	printf("Count: %d\n", b.stock);
}
void BookList()
{
	char line[LINE_LENGTH];
	char tmp[LINE_LENGTH];
	char *tok;
	printf("%-15s%-20s%-15s%-15s%-15s%-10s%-20s%-10s\n", "ISBN", "Name", "Author", "Publisher", "Category", "Year", "Price", "Count");
	FILE *fp = fopen("book.csv", "r");
	while (fgets(line, LINE_LENGTH, fp))
	{
		strcpy(tmp, line);
		tok = strtok(tmp, ";");
		printf("%-15s", tok);

		tok = strtok(NULL, ";");
		printf("%-20s", tok);

		tok = strtok(NULL, ";");
		printf("%-15s", tok);

		tok = strtok(NULL, ";");
		printf("%-15s", tok);

		tok = strtok(NULL, ";");
		printf("%-15s", tok);

		tok = strtok(NULL, ";");
		printf("%-10s", tok);

		tok = strtok(NULL, ";");
		printf("%-20s", tok);

		tok = strtok(NULL, ";");
		printf("%s", tok);

	}
	fclose(fp);
}
void addBook()
{
	printf("[ NEW BOOK ]\n");
	char line[256] = "", input[30];
	const char *text[8];
	text[0] = "ISBN : ";
	text[1] = "Name : ";
	text[2] = "Author : ";
	text[3] = "Publisher : ";
	text[4] = "Catergory : ";
	text[5] = "Year : ";
	text[6] = "Price: ";
	text[7] = "Count: ";
	getchar();
	for (int i = 0; i < 8; i++)
	{
		printf("%s", text[i]);
		gets_s(input, 30);
		strcat(line, input);
		if (i < 7)
			strcat(line, ";");
	}
	strcat(line, "\n");
	printf("%s", line);
	FILE*fp = fopen("book.csv", "a+");
	fputs(line, fp);
	fclose(fp);
}
void deleteBook()
{
	char id[TEXT_LENGTH];
	printf("Write the ISBN of the book you want to delete : ");
	scanf("%s", &id);
	if (checkISBN(id))
	{
		FILE *fp = fopen("book.csv", "r");
		FILE *fptmp = fopen("temp", "w");

		char line[LINE_LENGTH];
		char tmp[LINE_LENGTH];
		char* tok;
		while (fgets(line, LINE_LENGTH, fp))
		{
			strcpy(tmp, line);
			tok = strtok(tmp, ";");
			if (strcmp(tok, id) == 0)
			{

			}
			else
			{
				fputs(line, fptmp);
			}
		}
		printf("Deleted Book ISBN : %s\n", id);
		fclose(fp);
		fclose(fptmp);
	}
	else
	{
		printf("Can't find Book with that ISBN\n");
	}
}
bool checkISBN(char id[])
{
	FILE*fp = fopen("book.csv", "r");
	char line[256];
	char *tok;
	while (fgets(line, 256, fp))
	{
		tok = strtok(line, ";");
		if (strcmp(tok, id) == 0)
		{
			fclose(fp);
			return true;
		}
	}
	fclose(fp);
	return false;
}

void updateBookInfo(BOOK b)
{
	printf("[ UPDATE BOOK INFORMATION ] \n");
	char input[TEXT_LENGTH];

	getchar();
	printf("Name : ");
	gets_s(b.name, TEXT_LENGTH);

	printf("Author : ");
	gets_s(b.author, TEXT_LENGTH);

	printf("Publisher : ");
	gets_s(b.publisher, TEXT_LENGTH);

	printf("Category : ");
	gets_s(b.category, TEXT_LENGTH);

	printf("Year : ");
	scanf("%d", &b.year);

	printf("Price : ");
	scanf("%d", &b.price);

	printf("Count : ");
	scanf("%d", &b.stock);

	saveBook(b);
}

void saveBook(BOOK b)
{
	FILE *fp = fopen("book.csv", "r");
	FILE *fptmp = fopen("temp", "w");

	char line[LINE_LENGTH];
	char tmp[LINE_LENGTH];
	char* tok;

	while (fgets(line, LINE_LENGTH, fp))
	{
		strcpy(tmp, line);
		tok = strtok(tmp, ";");
		if (strcmp(tok, b.ISBN) == 0)
		{
			char str[LINE_LENGTH];
			strcpy(str, BOOKtoString(b));
			fputs(str, fptmp);
		}
		else
		{
			fputs(line, fptmp);
		}
	}
	fclose(fp);
	fclose(fptmp);
}

void findISBN()
{
	printf("Write ISSBN of the book you want to find\n");
	char input[TEXT_LENGTH];
	scanf("%s", &input);
	FILE *fp = fopen("book.csv", "r");

	char line[LINE_LENGTH];
	char idHolder[TEXT_LENGTH];
	char tmp[LINE_LENGTH];

	while (fgets(line, LINE_LENGTH, fp))
	{
		strcpy(tmp, line);
		strcpy(idHolder, getISBN(tmp));
		if (strcmp(input, idHolder) == 0)
		{
			printBook(stringToBOOK(line));
			break;
		}
	}
	fclose(fp);
}

char * getISBN(char line[])
{
	char *tok;
	tok = strtok(line, ";");
	return tok;
}

void findname()
{
	printf("Write the name of the book you want to find\n");
	char input[TEXT_LENGTH];
	//scanf("%s", &input);
	getchar();
	gets_s(input, TEXT_LENGTH);
	FILE *fp = fopen("book.csv", "r");

	char line[LINE_LENGTH];
	char nameHolder[TEXT_LENGTH];
	char tmp[LINE_LENGTH];

	while (fgets(line, LINE_LENGTH, fp))
	{
		strcpy(tmp, line);
		strcpy(nameHolder, getname(tmp));
		if (strcmp(input, nameHolder) == 0)
		{
			printBook(stringToBOOK(line));
			break;
		}
	}
	fclose(fp);
}

char *getname(char line[])
{
	char *tok;
	tok = strtok(line, ";");
	tok = strtok(NULL, ";");
	return tok;
}