#include "user.h"
//CAC HAM CHUC NANG
USER login() 
{
	FILE *fp = fopen("user.csv", "r");
	static USER user;
	user.type = 0;
	if (fp == NULL) 
	{
		printf("NO FILE. CREATING NEW ADMIN\n");
		return user;
	}
	//Dien username va pass
	char nameInput[TEXT_LENGTH], passInput[TEXT_LENGTH];
	printf("Nhap username : ");
	scanf("%s", &nameInput);
	printf("Nhap password : ");
	scanf("%s", &passInput);

	char *line = (char*)malloc(LINE_LENGTH);	//Giu 1 line
	char *tmp = (char*)malloc(LINE_LENGTH);
	char *token = (char*)malloc(TEXT_LENGTH);	//Giu 1 khoang giua 2 dau ;


	bool check = false;//KIEM TRA CO TIM THAY USERNAME KHONG

	while (fgets(line, LINE_LENGTH, fp)) //Get 1 line
	{
		strcpy(tmp, line);	//GIU AN TOAN LINE, vi strtok(line,...) se lam thay doi line
		token = strtok(tmp, ";");	//Get username
		if (strcmp(token, nameInput) == 0) 
		{
			check = true;
			token = strtok(NULL, ";");	//Get password
			if (strcmp(token, passInput) == 0)
			{
				printf("Login successfully!\n");
				user=stringToUser(line);
				printUser(user);
				break;
			}
			else
			{
				printf("Wrong password or username\n");
			}
			break;
		}
	}
	if (!check) 
	{
		printf("Khong tim thay username\n");
	}
	fclose(fp);
	free(line);
	free(tmp);
	// WHY CAN'T FREE TOKEN
	return user;
}

void printUser(USER user) 
{
	printf("Username : %s\n",user.userName);

	printf("Password : %s\n",user.passWord);

	printf("Name : %s\n",user.name);

	printf("Date of birth : %d/%d/%d\n",user.dob.day,user.dob.month,user.dob.year);

	printf("Address : %s\n",user.address);

	if (user.sex)
		printf("Sex : male\n");
	else
		printf("Sex : female\n");
	if (user.type == 1)
	{
		printf("ADMINSTRATOR\n");
	}
	else
		printf("NOT ADMIN\n");
}
void logOut(USER &user)
{
	user.type = 0;
	strcpy(user.userName, "");
	strcpy(user.passWord, "");
	printf("YOU HAVE BEEN LOGGED OUT\n");
}

void changePassword(USER &user) 
{
	char input[TEXT_LENGTH];
	printf("Nhap password hien tai : ");
	
	//getchar();
	scanf("%s", &input);

	if (strcmp(user.passWord, input) == 0) 
	{
		printf("Nhap password moi : ");
		scanf("%s", &input);
		char input2[TEXT_LENGTH];
		printf("Nhap lai password moi : ");
		scanf("%s", &input2);
		if (strcmp(input, input2) == 0) 
		{
			strcpy(user.passWord, input);
			saveUser(user);
		}
		else 
		{
			printf("Password khong giong\n");
		}
	}
	else
	{
		printf("Nhap sai password hien tai\n");
	}
}

void saveUser(USER user) 
{
	FILE *fp = fopen("user.csv", "r");
	FILE *fptmp = fopen("temp", "w");

	char line[LINE_LENGTH];
	char tmp[LINE_LENGTH];//protect line from strtok
	char* tok = (char*)malloc(TEXT_LENGTH);

	while (fgets(line, LINE_LENGTH, fp)) 
	{
		strcpy(tmp, line);
		tok = strtok(tmp, ";");//get username
		if (strcmp(tok, user.userName) == 0) 
		{
			char str[LINE_LENGTH];
			strcpy(str,userToString(user));
			fputs(str, fptmp);
			//fprintf(fptmp,"\n");
		}
		else 
		{
			fputs(line, fptmp);
		}
	}
	fclose(fp);
	fclose(fptmp);
}

void updateUser(USER &user) 
{
	printf("[ UPDATE INFORMATION ]\n");
	char input[TEXT_LENGTH];

	getchar();
	printf("First and last name : ");
	gets_s(user.name, TEXT_LENGTH);

	printf("Date of birth (dd/mm/yy) : ");
	gets_s(input, TEXT_LENGTH);
	user.dob = stringToDATE(input);

	printf("ID : ");
	gets_s(user.id, TEXT_LENGTH);

	printf("Address : ");
	gets_s(user.address, TEXT_LENGTH);

	printf("Sex (0-male 1-female) : ");
	scanf("%d", &user.sex);

	printf("Status (0-blocked 1-active) : ");
	scanf("%d", &user.status);

	printf("User type (2-manager 3-producer) : ");
	scanf("%d", &user.type);
	saveUser(user);
}

void addUser() 
{
	printf("[ NEW USER ]\n");
	char line[LINE_LENGTH] = "", input[TEXT_LENGTH];
	const char *text[9];
	text[0] = "Username : ";
	text[1] = "Password : ";
	text[2] = "First and last name : ";
	text[3] = "Date of birth (dd/mm/yy) :";
	text[4] = "ID : ";
	text[5] = "Address : ";
	text[6] = "Sex (0-male 1-female) : ";
	text[7] = "Status (0-blocked 1-active) : ";
	text[8] = "User type (2-manager 3-producer) : ";
	getchar();
	int i;
	for (i = 0;i < 9;i++)
	{
		printf("%s", text[i]);
		gets_s(input, TEXT_LENGTH);
		if (i == 0) 
		{
			if (!checkUserName(input)) 
			{
				printf("Username already exist\n");
				break;
			}
		}

		strcat(line, input);
		if (i < 8)
			strcat(line, ";");
	}
	strcat(line, "\n");
	if (i > 1)
	{
		printf("NEW USER CREATED");
		FILE*fp = fopen("user.csv", "a+");
		fputs(line, fp);
		fclose(fp);
	}
}
bool checkUserName(char name[]) 
{
	FILE*fp = fopen("user.csv", "r");
	char line[LINE_LENGTH];
	char *tok;
	while (fgets(line, LINE_LENGTH, fp)) 
	{
		tok = strtok(line, ";");
		if (strcmp(tok, name) == 0) 
		{
			fclose(fp);
			return false;
		}
	}
	fclose(fp);
	return true;
}