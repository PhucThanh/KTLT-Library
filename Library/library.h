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

struct DATE
{
	int day;
	int month;
	int year;
};
DATE stringToDATE(char *line);
char * DATEToString(DATE date);
DATE getCurrentTime(int d,int m,int y);//Cong them d m y, leave 0 if no increasement
#endif
