#pragma once
#include "library.h"
struct BOOK 
{
	char ISBN[14];
	char name[TEXT_LENGTH];
	char author[TEXT_LENGTH];
	char publisher[TEXT_LENGTH];
	int year;
	char category[TEXT_LENGTH];
	int price;
	int stock;//So luong
};

//Converter
BOOK stringToBOOK(char line[]);
char * BOOKtoString(BOOK book);
//CPP
void BookList();
void printBook(BOOK b);
void addBook();
void deleteBook();
bool checkISBN(char id[]);
void updateBookInfo(BOOK b);
void saveBook(BOOK b);

void findISBN();
char * getISBN(char line[]);
void findname();
char *getname(char line[]);