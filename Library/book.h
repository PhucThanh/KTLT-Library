#pragma once
#include "library.h"
struct BOOK 
{
	char ISBN[14];
	char name[TEXT_LENGTH];
	char author[TEXT_LENGTH];
	char publisher[TEXT_LENGTH];
	
	char category[TEXT_LENGTH];
	int year;
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
//bool checkISBN(char id[]);
void updateBookInfo(BOOK b);
void saveBook(BOOK b);

void findISBN();
int checkISBN(char [],BOOK &book);// Return 0 : Doesn't exist, 1:Good,-1 : Out of stock. Tra book ra ngoai neu tim dc
char * getISBN(char line[]);
void findname();
char *getname(char line[]);