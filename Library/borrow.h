#include "library.h"
#include "book.h"
#include "reader.h"
typedef struct node *ref;
struct node
{
	char isbn[TEXT_LENGTH];
	ref next;
};

struct BORROW 
{
	//char ID[TEXT_LENGTH];//ID of borrow ticket
	char reader[TEXT_LENGTH];//ID of reader
	DATE start;
	DATE end;
	ref begin;
	//BOOK book[3];
};

void addBorrow();
ref getNode(char text[]);
void add(ref &S, char text[]);
char* BORROWToString(BORROW borrow);
void saveBorrow(BORROW borrow);
bool checkReaderBorrowing(char[]);//check whenver reader is in borrow.csv
void printfBorrow(BORROW borrow);

void returnBook();
void deleteBorrow(char id[]);