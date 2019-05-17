//CHUA CAC HAM CHUYEN DOI
#include "user.h"
USER stringToUser(char *line)
{
	// Chuyen ; ; ; ; thanh USER
	USER user;
	char tmp[LINE_LENGTH];
	char *tok = (char*)malloc(TEXT_LENGTH);

	strcpy(tmp, line);	//GIU AN TOAN CHO LINE
	tok = strtok(tmp, ";");//Get username
	strcpy(user.userName, tok);
	tok = strtok(NULL, ";");
	strcpy(user.passWord, tok);
	tok = strtok(NULL, ";");
	strcpy(user.name, tok);
	tok = strtok(NULL, ";");
	// DATE OF BIRTH FUNCTION
	user.dob = stringToDATE(tok);

	tok = strtok(NULL, ";");
	strcpy(user.id, tok);
	tok = strtok(NULL, ";");
	strcpy(user.address, tok);
	tok = strtok(NULL, ";");
	user.sex = atoi(tok);
	tok = strtok(NULL, ";");
	user.status = atoi(tok);
	tok = strtok(NULL, ";");
	user.type = atoi(tok);
	return user;
}
char * userToString(USER user)
{
	char line[LINE_LENGTH];
	strcpy(line, user.userName);//First is cpy not cat
	strcat(line, ";");
	strcat(line, user.passWord);
	strcat(line, ";");
	strcat(line, user.name);
	strcat(line, ";");
	//GET DAY
	strcat(line, DATEToString(user.dob));

	strcat(line, ";");
	strcat(line, user.address);
	strcat(line, ";");
	char buffer[TEXT_LENGTH];
	_itoa(user.sex, buffer, 10);
	strcat(line, buffer);
	strcat(line, ";");
	_itoa(user.status, buffer, 10);
	strcat(line, buffer);
	strcat(line, ";");
	_itoa(user.type, buffer, 10);
	strcat(line, buffer);
	strcat(line, "\n");
	return line;
}
