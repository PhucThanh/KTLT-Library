#include "library.h"
READER stringToReader(char *line) 
{
	READER reader;
	char tmp[LINE_LENGTH];
	char *tok = (char*)malloc(TEXT_LENGTH);
	strcpy(tmp, line);	//GIU AN TOAN CHO LINE

	tok = strtok(tmp, ";");//ID
	strcpy(reader.id, tok);
	tok = strtok(NULL, ";");
	strcpy(reader.name, tok);
	tok = strtok(NULL, ";");
	strcpy(reader.idNumber, tok);

	tok = strtok(NULL, ";");
	// DATE OF BIRTH FUNCTION
	reader.dob = stringToDATE(tok);

	tok = strtok(NULL, ";");
	reader.gender = atoi(tok);
	tok = strtok(NULL, ";");
	strcpy(reader.email, tok);
	tok = strtok(NULL, ";");
	strcpy(reader.address, tok);
	
	tok = strtok(NULL, ";");
	reader.start = stringToDATE(tok);
	tok = strtok(NULL, ";");
	reader.end = stringToDATE(tok);
	return reader;
}

char * readerToString(READER reader) 
{
	char line[LINE_LENGTH];
	char buffer[TEXT_LENGTH];
	strcpy(line, reader.id);
	strcat(line, ";");
	strcat(line, reader.name);
	strcat(line, ";");
	strcat(line, reader.idNumber);
	strcat(line, ";");
	strcat(line, DATEToString(reader.dob));
	strcat(line, ";");
	_itoa(reader.gender, buffer, 10);
	strcat(line, buffer);
	strcat(line, ";");
	strcat(line, reader.email);
	strcat(line, ";");
	strcat(line, reader.address);
	strcat(line, ";");
	strcat(line, DATEToString(reader.start));
	strcat(line, ";");
	strcat(line, DATEToString(reader.end));
	strcat(line, "\n");
	return line;//line=ten;ast;asf;
}