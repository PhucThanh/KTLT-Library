#pragma once
#include "library.h"
struct READER 
{
	char id[TEXT_LENGTH];
	char name[TEXT_LENGTH];
	char idNumber[TEXT_LENGTH];
	DATE dob;
	bool gender; //0-female 1-male
	char email[TEXT_LENGTH];
	char address[TEXT_LENGTH];
	DATE start;
	DATE end;
};

//Cac ham chuyen doi tu string sang struct va nguoc lai
//Chuyen tu _;_;_ thanh struct va nguoc lai
READER stringToReader(char *line);
char * readerToString(READER reader);

void printReader(READER reader);
void listReaders();
void addReader();

//void updateReader(READER reader);
void updateReader();
void saveReader(READER reader);	//Ham thong minh, tu dong tim thay user can save va save
int lastID();
void deleteReader();
bool checkReaderID(char id[],READER &reader);//Find reader and store it to &reader
void findReaderByIdNumber();
char * getReaderIdNumber(char line[]);