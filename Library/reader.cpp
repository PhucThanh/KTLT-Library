#include "reader.h"
void printReader(READER reader) 
{
	printf("ID : %s\n", reader.id);
	printf("Name : %s\n", reader.name);
	printf("ID number : %s\n", reader.idNumber);

	char time[12];
	strcpy(time, DATEToString(reader.dob));
	printf("Day of birth : %s\n",time );

	if (reader.gender)
		printf("Gender : male\n");
	else
		printf("Gender : female\n");
	printf("Email : %s\n", reader.email);
	printf("Address : %s\n", reader.address);

	strcpy(time, DATEToString(reader.start));
	printf("Start day : %s\n", time);

	strcpy(time, DATEToString(reader.end));
	printf("End day : %s\n", time);
}
void listReaders() //print list of reader
{
	char line[LINE_LENGTH];
	char tmp[LINE_LENGTH];
	char *tok = (char*)malloc(TEXT_LENGTH);
	printf("%-13s%-20s%-15s%-11s%-10s%-20s%-20s%-15s%-15s\n", "ID", "Name", "ID number", "Birth", "Gender","Email","Address","Start day","End day");
	FILE *fp = fopen("reader.csv", "r");
	while (fgets(line, LINE_LENGTH, fp)) 
	{
		strcpy(tmp, line);
		tok = strtok(tmp, ";");
		printf("%-13s", tok);

		tok = strtok(NULL, ";");
		printf("%-20s", tok);

		tok = strtok(NULL, ";");
		printf("%-15s", tok);

		tok = strtok(NULL, ";");
		printf("%-11s", tok);

		tok = strtok(NULL, ";");
		printf("%-10s", tok);

		tok = strtok(NULL, ";");
		printf("%-20s", tok);

		tok = strtok(NULL, ";");
		printf("%-20s", tok);

		tok = strtok(NULL, ";");
		printf("%-15s", tok);

		tok = strtok(NULL, ";");
		printf("%s", tok);
	}
	fclose(fp);
}
int lastID() 
{
	FILE *fp = fopen("reader.csv", "r");
	int id;
	char line[LINE_LENGTH];
	while (fgets(line, LINE_LENGTH, fp)) 
	{
		id = atoi(strtok(line, ";"));
	}
	fclose(fp);
	return id;
}
void addReader() 
{
	printf("[ NEW READER ]\n");
	char line[LINE_LENGTH] = "", input[TEXT_LENGTH];
	const char *text[6];
	text[0] = "Name : ";
	text[1] = "ID Number : ";
	text[2] = "Day of birth(dd/mm/yy) : ";
	text[3] = "Gender (1-male 0-female) : ";
	text[4] = "Email : ";
	text[5] = "Address : ";

	//Get lastest ID
	int lastId = lastID();
	//Lastest ID to string so we can strcat
	char buffer[12];
	_itoa(lastId + 1,buffer, 10);
	//Get current day, add to string time
	char time[12];
	DATE date = getCurrentTime(0, 0, 0);
	strcpy(time,DATEToString(date));
	
	strcpy(line, buffer);	//Add lastest ID to line
	strcat(line, ";");
	getchar();
	for (int i = 0;i < 6;i++)
	{
		printf("%s", text[i]);
		gets_s(input, TEXT_LENGTH);
		strcat(line, input);
		strcat(line, ";");
	}
	//Add current time (start day)
	strcat(line, time);	
	strcat(line, ";");
	//add 4 more year to date (end day)
	date = getCurrentTime(0, 0, 4);	
	strcat(line, DATEToString(date));
	strcat(line, "\n");
	printf("%s", line);
	FILE*fp = fopen("reader.csv", "a+");
	fputs(line, fp);
	fclose(fp);
}
void deleteReader() 
{
	char id[TEXT_LENGTH];
	printf("Write the ID of reader you want to delete : ");
	scanf("%s", &id);
	if (checkReaderID(id))
	{
		FILE *fp = fopen("reader.csv", "r");
		FILE *fptmp = fopen("temp", "w");

		char line[LINE_LENGTH];
		char tmp[LINE_LENGTH];//protect line from strtok
		char* tok = (char*)malloc(TEXT_LENGTH);

		while (fgets(line, LINE_LENGTH, fp))
		{
			strcpy(tmp, line);
			tok = strtok(tmp, ";");//get ID
			if (strcmp(tok, id) == 0)
			{
				//Skip because deleted
			}
			else
			{
				//Write normally
				fputs(line, fptmp);
			}
		}
		printf("Deleted reader %s\n", id);
		fclose(fp);
		fclose(fptmp);
	}
	else
	{
		printf("Can't find reader with that ID\n");
	}
}
bool checkReaderID(char id[]) 
{
	FILE*fp = fopen("reader.csv", "r");
	char line[LINE_LENGTH];
	char *tok;
	while (fgets(line, LINE_LENGTH, fp))
	{
		tok = strtok(line, ";");
		if (strcmp(tok, id) == 0)
		{
			fclose(fp);
			return true;
		}
	}
	fclose(fp);
	return false;
}
void findReaderByIdNumber() 
{
	printf("Write ID number of the reader you want to find : ");
	char input[TEXT_LENGTH];
	scanf("%s", &input);
	FILE *fp = fopen("reader.csv", "r");

	char line[LINE_LENGTH];
	char idHolder[TEXT_LENGTH];
	char tmp[LINE_LENGTH];

	while (fgets(line, LINE_LENGTH, fp)) 
	{
		strcpy(tmp, line);
		strcpy(idHolder, getReaderIdNumber(tmp));
		if (strcmp(input, idHolder) == 0) 
		{
			printReader(stringToReader(line));
			break;
		}
	}
}
char * getReaderIdNumber(char line[]) 
{
	char *tok;
	tok = strtok(line, ";");
	tok = strtok(NULL, ";");
	tok = strtok(NULL, ";");
	return tok;
}

/*void updateReader(READER reader) 
{
	char buffer[TEXT_LENGTH];
	_itoa(reader.id, buffer, 10);
	if (checkReaderID(buffer)) {

		printf("[ UPDATE READER INFORMATION ] \n");
		char input[TEXT_LENGTH];

		//getchar();
		printf("Name : ");
		gets_s(reader.name, TEXT_LENGTH);

		printf("id Number : ");
		gets_s(reader.idNumber, TEXT_LENGTH);

		printf("Date of birth (dd/mm/yy) : ");
		char buffer[TEXT_LENGTH];
		gets_s(buffer, TEXT_LENGTH);
		reader.dob = stringToDATE(buffer);

		printf("Gender (1-male,0-female) : ");
		scanf("%d", &reader.gender);
		getchar();
		printf("Email : ");
		gets_s(reader.email, TEXT_LENGTH);

		printf("Adress : ");
		gets_s(reader.address, TEXT_LENGTH);

		saveReader(reader);
	}
	else
	{
		printf("Reader %d doesn't exist\n", reader.id);
	}
}*/
void updateReader() 
{
	char input[TEXT_LENGTH];
	printf("Write Reader's ID you want to update : ");
	scanf("%s", &input);
	FILE *fp = fopen("reader.csv", "r");

	char line[LINE_LENGTH];
	char idHolder[TEXT_LENGTH];
	char tmp[LINE_LENGTH];
	bool check=false;
	getchar();
	while (fgets(line, LINE_LENGTH, fp))
	{
		strcpy(tmp, line);
		strcpy(idHolder, strtok(tmp,";"));
		if (strcmp(input, idHolder) == 0)
		{
			check = true;
			READER reader = stringToReader(line);
			printf("[ UPDATE READER #%s]\n", input);
			printf("Name : ");
			gets_s(reader.name, TEXT_LENGTH);
			printf("Id Number : ");
			gets_s(reader.idNumber, TEXT_LENGTH);
			printf("Date of birth : ");
			char buffer[TEXT_LENGTH];
			gets_s(buffer, TEXT_LENGTH);
			reader.dob = stringToDATE(buffer);
			printf("Email : ");
			gets_s(reader.email, TEXT_LENGTH);
			printf("Address : ");
			gets_s(reader.address, TEXT_LENGTH);

			saveReader(reader);
			break;
		}
	}
	if (!check) 
	{
		printf("Can't find user with that ID\n");
	}
}
void saveReader(READER reader)
{
	FILE *fp = fopen("reader.csv", "r");
	FILE *fptmp = fopen("temp", "w");

	char line[LINE_LENGTH];
	char tmp[LINE_LENGTH];
	char* tok;

	while (fgets(line, LINE_LENGTH, fp))
	{
		strcpy(tmp, line);
		tok = strtok(tmp, ";");
		if (strcmp(tok, reader.id) == 0)
		{
			char str[LINE_LENGTH];
			strcpy(str, readerToString(reader));
			fputs(str, fptmp);
		}
		else
		{
			fputs(line, fptmp);
		}
	}
	fclose(fp);
	fclose(fptmp);
}