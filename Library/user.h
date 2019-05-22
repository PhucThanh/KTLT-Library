#pragma once
#ifndef USER_H
#define USER_H
#include "library.h"

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



//Cac ham chuyen doi tu string sang struct va nguoc lai
//Chuyen tu _;_;_ thanh struct va nguoc lai
USER stringToUser(char *line);
char * userToString(USER user);


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
void execute(USER &user, int c, int n);
#endif
