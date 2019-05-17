#include "book.h"
BOOK stringToBOOK(char line[]) //line = ___;___;____
{
	BOOK b;
	char *tok;
	char tmp[LINE_LENGTH];
	strcpy(tmp, line);
	tok = strtok(tmp, ";");
	strcpy(b.ISBN, tok);
	tok = strtok(NULL, ";");
	strcpy(b.name, tok);
	tok = strtok(NULL, ";");
	strcpy(b.author, tok);
	tok = strtok(NULL, ";");
	strcpy(b.publisher, tok);
	tok = strtok(NULL, ";");
	strcpy(b.category, tok);
	tok = strtok(NULL, ";");
	b.year = atoi(tok);
	tok = strtok(NULL, ";");
	b.price = atoi(tok);
	tok = strtok(NULL, ";");
	b.stock = atoi(tok);
	return b;
}

char * BOOKtoString(BOOK b) 
{
	char line[LINE_LENGTH];
	char buffer[TEXT_LENGTH];
	strcpy(line, b.ISBN);
	strcat(line, ";");
	strcat(line, b.name);
	strcat(line, ";");
	strcat(line, b.author);
	strcat(line, ";");
	strcat(line, b.publisher);
	strcat(line, ";");
	strcat(line, b.category);
	strcat(line, ";");
	_itoa(b.year, buffer, 10);
	strcat(line, buffer);
	strcat(line, ";");
	_itoa(b.price, buffer, 10);
	strcat(line, buffer);
	strcat(line, ";");
	_itoa(b.stock, buffer, 10);
	strcat(line, buffer);
	strcat(line, "\n");
	//.....
	return line;
}