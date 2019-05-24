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
	date = dateFix(date);
	return date;
}

DATE dateFix(DATE date) 
{
	switch (date.month) 
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		if (date.day > 31) 
		{
			date.day -= 31;
			date.month++;
		}
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		if (date.day > 30)
		{
			date.day -= 30;
			date.month++;
		}
		break;
	case 2:
		if (((date.year % 4 == 0) && (date.year % 100 != 0)) || (date.year % 400 == 0)) 
		{
			if (date.day > 29) 
			{
				date.day -= 29;
				date.month++;
			}
		}
		else
		{
			if (date.day > 28)
			{
				date.day -= 28;
				date.month++;
			}
		}
	}
	if (date.month > 12) 
	{
		date.month -= 12;
		date.year++;
	}
	return date;
}
int dateBetween(DATE date1, DATE date2) //Chi danh cho nhieu nhat 2 nam lien tiep nhau
{
	int d=0;
	if (date1.year == date2.year)
	{
		if (date1.month != date2.month) 
		{
			if (((date1.year % 4 == 0) && (date1.year % 100 != 0)) || (date1.year % 400 == 0))
			{
				int m[] = { 0, 31,29,31,30,31,30,31,31,30,31,30,31 };
				d += m[date1.month] - date1.day;
				d += date2.day;
				for (int i = date1.month + 1;i <= date2.month - 1;i++)
				{
					d += m[i];
				}
			}
			else
			{
				int m[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
				d += m[date1.month] - date1.day;
				d += m[date2.month] - date2.day;
				for (int i = date1.month + 1;i <= date2.month - 1;i++)
				{
					d += m[i];
				}
			}
		}
		else
		{
			d = date2.day - date1.day;
		}
	}
	if (date1.year < date2.year)
	{
		DATE tmp;
		tmp.day = 31;
		tmp.month = 12;
		tmp.year = date1.year;
		d += dateBetween(date1, tmp);

		tmp.day = 1;
		tmp.month = 1;
		tmp.year = date2.year;
		d += dateBetween(tmp, date2);
	}
	return d;
}