#pragma once
#ifndef LIBRARY_H
#define LIBRARY_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define TEXT_LENGTH 30//Length between ; username,pass...
#define LINE_LENGTH 256//Length of 1 line in CSV
#define gotoxy(x,y) printf("\033[%d;%dH", (x), (y))

struct DATE
{
	int day;
	int month;
	int year;
};
struct USER
{
	char userName[TEXT_LENGTH];
	char passWord[TEXT_LENGTH];
	char name[TEXT_LENGTH];
	DATE dob;
	char id[12];
	char address[TEXT_LENGTH];
	bool gender; //0-female 1-male
	bool status; //1-activated 0-block
	int type;
	//0-Chua dang nhap
	//1-admin
	//2-quan ly
	//3-chuyen vien
};
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
struct BOOK
{
	char ISBN[14];
	char name[TEXT_LENGTH];
	char author[TEXT_LENGTH];
	char publisher[TEXT_LENGTH];

	char category[TEXT_LENGTH];
	int year;
	int price;
	int stock;//So luong sach tong cong
	int borrowing = 0;//So luong dang muon
};
typedef struct node *ref;
struct node
{
	char isbn[TEXT_LENGTH];
	ref next;
};

struct BORROW
{
	char reader[TEXT_LENGTH];//ID of reader
	DATE start;
	DATE end;
	ref begin;
};
DATE stringToDATE(char *line);
char * DATEToString(DATE date);
DATE getCurrentTime(int d,int m,int y);//Cong them d m y, leave 0 if no increasement
DATE dateFix(DATE date);
int dateBetween(DATE date1, DATE date2);

//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////USER///////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
USER login();
void printUser(USER user);
void logOut(USER &user);
void changePassword(USER &user);
void updateUser(USER &user);
void addUser();
//Ham save tu dong. Tao mot file tmp.csv va copy nhung user tu file user.csv sang file tmp.csv
//Toi user hien tai thi copy theo user moi, skip user cu trong file
void saveUser(USER user);
bool checkUserName(char name[]);//return true if user name don't exist
void printMenu(USER &user, int &n);
void printSubMenu(USER &user, int &n);
void changePermission();
//void execute(USER &user, int c, int n);
void createAdmin();

//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////READER/////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
READER stringToReader(char *line);
char * readerToString(READER reader);
void printReader(READER reader);
void listReaders();
void addReader();
void updateReader();
void saveReader(READER reader);	//Ham thong minh, tu dong tim thay user can save va save
int lastID();
void deleteReader();
bool checkReaderID(char id[], READER &reader);//Find reader and store it to &reader
void findReaderByIdNumber();
char * getReaderIdNumber(char line[]);
char * getReaderName(char line[]);
void findBookByName();

//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////BOOK///////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
BOOK stringToBOOK(char line[]);
char * BOOKtoString(BOOK book);
void BookList();
void printBook(BOOK b);
void addBook();
void deleteBook();
void updateBookInfo();
void saveBook(BOOK b);
void findISBN();
int checkISBN(char[], BOOK &book);// Return 0 : Doesn't exist, 1:Good,-1 : Out of stock. Tra book ra ngoai neu tim dc
char * getISBN(char line[]);
void findname();
char *getname(char line[]);

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////BORROW//////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
void addBorrow();
ref getNode(char text[]);
void add(ref &S, char text[]);
char* BORROWToString(BORROW borrow);
bool checkReaderBorrowing(char[]); //check whenever reader is in borrow.csv
void printfBorrow(BORROW borrow);
void returnBook();
void deleteBorrow(char id[]);
int dateBetween(DATE date1, DATE date2);
#endif
