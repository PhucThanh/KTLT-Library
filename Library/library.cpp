#include "library.h"
DATE stringToDATE(char *line)
{
	DATE date;
	//CHUYEN dd/mm/yy thanh DATE
	char *tok = (char*)malloc(5);
	tok = strtok_s(line, "/", &line);	//strtok_s tranh conflict voi strtok o ngoai
	date.day = atoi(tok);
	tok = strtok_s(NULL, "/", &line);
	date.month = atoi(tok);
	tok = strtok_s(NULL, "", &line);
	date.year = atoi(tok);
	return date;
}
char * DATEToString(DATE date)
{
	//DOI DATE THANH dd/mm/yy
	char str[TEXT_LENGTH];
	char buffer[TEXT_LENGTH];

	_itoa(date.day, buffer, 10);
	strcpy(str, buffer);//First is cpy not catch
	strcat(str, "/");

	_itoa(date.month, buffer, 10);
	strcat(str, buffer);
	strcat(str, "/");

	_itoa(date.year, buffer, 10);
	strcat(str, buffer);
	return str;
}
DATE getCurrentTime(int d, int m, int y)
{
	time_t time_raw_format;
	struct tm * ptr_time;
	char buffer[12];
	time(&time_raw_format);
	ptr_time = localtime(&time_raw_format);
	strftime(buffer, 12, "%d/%m/%Y", ptr_time);
	DATE date;
	date = stringToDATE(buffer);
	date.day += d;
	date.month += m;
	date.year += y;
	return date;
}