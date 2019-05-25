#include "library.h"
char* BORROWToString(BORROW borrow)
{
	char line[LINE_LENGTH];
	strcpy(line, borrow.reader);
	strcat(line, ";");
	strcat(line, DATEToString(borrow.start));
	strcat(line, ";");
	strcat(line, DATEToString(borrow.end));
	strcat(line, ";");

	char *bookList = (char*)malloc(LINE_LENGTH);
	strcpy(bookList, "");
	ref p;
	for (p = borrow.bookList;p;p = p->next)
	{
		strcat(bookList, p->isbn);
		strcat(bookList, ",");
	}
	strcat(line, bookList);
	strcat(line, "\n");
	return line;
}

char* RETURNTICKETToString(RETURNTICKET r)
{
	char line[LINE_LENGTH];
	strcpy(line, r.reader);
	strcat(line, ";");
	strcat(line, DATEToString(r.start));
	strcat(line, ";");
	strcat(line, DATEToString(r.end));
	strcat(line, ";");
	strcat(line, DATEToString(r.returnDay));
	strcat(line, ";");
	char buffer[TEXT_LENGTH];
	_itoa(r.money, buffer, 10);
	strcat(line, buffer);
	strcat(line, ";");
	char *bookList = (char*)malloc(LINE_LENGTH);
	strcpy(bookList, "");
	ref p;
	for (p = r.bookList;p;p = p->next)
	{
		strcat(bookList, p->isbn);
		strcat(bookList, ",");
	}
	strcat(line, bookList);
	strcat(line, "\n");
	return line;
}
BORROW stringToBORROW(char *line)
{
	BORROW b;
	b.bookList = NULL;
	char *tok;
	tok = strtok_s(line, ";", &line);
	strcpy(b.reader, tok);

	tok = strtok_s(NULL, ";", &line);
	DATE tmp = stringToDATE(tok);
	b.start = tmp;

	tok = strtok_s(NULL, ";", &line);
	tmp = stringToDATE(tok);
	b.end = tmp;

	tok = strtok_s(NULL, "\n", &line);
	char *tok2;
	tok2 = strtok_s(tok, ",", &tok);
	while (tok2 != NULL)
	{
		addLast(b.bookList, tok2);
		tok2 = strtok_s(NULL, ",", &tok);
	}
	return b;
}