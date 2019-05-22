#include "user.h"
#include "reader.h"
#include "book.h"
#include "borrow.h"
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
	clear();
	printf(" ______________________________________\n");
	printf("|                                      |\n");
	printf("|               [LOGIN]                |\n");
	printf("|______________________________________|\n");
	printf("|                                      |\n");
	printf("|   Username:                          |\n");
	printf("|   Password:                          |\n");
	printf("|                                      |\n");
	printf("|______________________________________|\n");

	char nameInput[TEXT_LENGTH], passInput[TEXT_LENGTH];	
	gotoxy(6, 14);
	scanf("%s", &nameInput);
	gotoxy(7, 14);
	scanf("%s", &passInput);
	gotoxy(10, 0);

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
				printf("Dang nhap thanh cong!\n");
				user=stringToUser(line);
				//printUser(user);
				printf("Xin chao %s\n", user.name);
				break;
			}
			else
			{
				printf("Dang nhap that bai, kiem tra lai ten dang nhat hoac password\n");
			}
			break;
		}
	}
	if (!check) 
	{
		printf("Dang nhap that bai, kiem tra lai ten dang nhat hoac password\n");
	}
	fclose(fp);
	free(line);
	free(tmp);
	// WHY CAN'T FREE TOKEN
	system("pause");
	system("cls");
	return user;
}

void printUser(USER user) 
{
	printf("Username : %s\n",user.userName);

	printf("Password : %s\n",user.passWord);

	printf("Name : %s\n",user.name);

	printf("Date of birth : %d/%d/%d\n",user.dob.day,user.dob.month,user.dob.year);

	printf("Address : %s\n",user.address);

	if (user.gender)
		printf("Gender : male\n");
	else
		printf("Gender : female\n");
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
	scanf("%d", &user.gender);

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
	text[6] = "Gender (0-male 1-female) : ";
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
		printf("Da tao nguoi dung moi\n");
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

void printMenu(USER &user,int &n) 
{
	// Choose which menu to print
	if (user.type==0) 
		user = login();
	switch(user.type)
	{
	case 0:
		
		break;
	case 1:
		printf(" ______________________________________\n");
		printf("|                                      |\n");
		printf("|            [ADMIN MENU]              |\n");
		printf("|______________________________________|\n");

		break;
	case 2:
		printf(" ______________________________________\n");
		printf("|                                      |\n");
		printf("|           [QUAN LY MENU]             |\n");
		printf("|______________________________________|\n");

		break;
	case 3:
		printf(" ______________________________________\n");
		printf("|                                      |\n");
		printf("|         [CHUYEN VIEN MENU]           |\n");
		printf("|______________________________________|\n");
		
		break;
	}
	if (user.status == 1) 
	{
		printf("|                                      |\n");
		printf("|     1. Quan ly nguoi dung            |\n");
		printf("|     2. Quan ly doc gia               |\n");
		printf("|     3. Quan ly sach                  |\n");
		printf("|     4. Quan ly phieu muon/tra        |\n");
		printf("|     5. Thong ke                      |\n");
		printf("|     0. Dang xuat                     |\n");
		printf("|                                      |\n");
		printf("|     Moi nhap so :                    |\n");
		printf("|______________________________________|\n");
	}
	else
	{
		printf("|                                      |\n");
		printf("|    TAI KHOAN CUA BAN DA BI KHOA      |\n");
		printf("|      LIEN HE ADMIN DE MO KHOA        |\n");
		printf("|                                      |\n");
		printf("|   Bam bat ky phim nao de dang xuat   |\n");
		printf("|______________________________________|\n");
	}
	if ((user.type != 0) && (user.status==1)) 
	{
		gotoxy(13, 20);
		scanf("%d", &n);
		if ((n >0) && (n<=5)) {
			printSubMenu(user, n);
		}
		else
		{
			logOut(user);
		}
		
	}
	if (user.status == 0 && user.type!=0) 
	{
		system("pause");
		logOut(user);
	}
	
	//system("pause");
	//system("cls");
}
void printSubMenu(USER &user, int &n) 
{
	clear();
	bool permission[24];
	for (int i = 0;i < 24;i++) 
	{
		permission[i] = true;
	}

	switch (user.type)
	{
	case 1://admin
		break;
	case 2://quan ly
		permission[2] = false;
		permission[3] = false;
		break;
	case 3://Chuyen vien
		permission[2] = false;
		permission[3] = false;
		permission[7] = false;
		permission[10] = false;
		permission[11] = false;
		permission[12] = false;
		permission[13] = false;
		permission[18] = false;
		permission[19] = false;
		permission[20] = false;
		permission[21] = false;
		break;
	}
	/*
	//0Mat khau
	//1Thong tin ca nhan
	//2Tao nguoi dung
	//3Phan quyen nguoi dung
	//4Xem doc gia list
	//5Them doc gia
	//6Chinh sua 
	//7Xoa
	//8TIm theo id
	//9Tim theo name
	//10booklist
	//11Add book
	//12Edit book
	//13Remove book
	//14FInd by ISBN
	//15Find by name
	//16Lap phieu muon
	//17Lap phieu tra
	//4 cai thong ke
	//2 thong ke cuoi
	*/
	const char *text[24];
	text[0] = "Thay doi mat khau";
	text[1] = "Cap nhat thong tin ca nhan";
	text[2] = "Tao nguoi dung";
	text[3] = "Phan quyen nguoi dung";
	text[4] = "Xem danh sach doc gia";
	text[5] = "Them doc gia";
	text[6] = "Chinh sua doc gia";
	text[7] = "Xoa doc gia";
	text[8] = "Tim doc gia theo CMND";
	text[9] = "Tim doc gia theo ten";
	text[10] = "Xem danh sach sach";
	text[11] = "Them sach";
	text[12] = "Chinh sua sach";
	text[13] = "Xoa sach";
	text[14] = "Tim sach theo ISBN";
	text[15] = "Tim sach theo ten sach";
	text[16] = "Lap phieu muon";
	text[17] = "Lap phieu tra";
	text[18] = "";
	text[19] = "";
	text[20] = "";
	text[21] = "";
	text[22] = "";
	text[23] = "";

	int j = 1;
	switch (n) 
	{
	case 1://Quan ly nguoi dung
		printf(" ______________________________________\n");
		printf("|                                      |\n");
		printf("|         [QUAN LY NGUOI DUNG]         |\n");
		printf("|______________________________________|\n");
		printf("|                                      |\n");
		for (int i = 0;i <= 3;i++) 
		{
			if (permission[i]) 
			{
				printf("|    %d.%-32s|\n",j, text[i]);
			}
			else
			{
				printf("|   [X]%-32s|\n", text[i]);
			}
			j++;
		}
		break;
	case 2://Quan ly doc gia
		printf(" ______________________________________\n");
		printf("|                                      |\n");
		printf("|         [QUAN LY DOC GIA]            |\n");
		printf("|______________________________________|\n");
		printf("|                                      |\n");
		for (int i = 4;i <= 9;i++)
		{
			if (permission[i])
			{
				printf("|    %d.%-32s|\n", j, text[i]);
			}
			else
			{
				printf("|   [X]%-32s|\n", text[i]);
			}
			j++;
		}
		break;
	case 3://Quan ly sach
		printf(" ______________________________________\n");
		printf("|                                      |\n");
		printf("|          [QUAN LY SACH]              |\n");
		printf("|______________________________________|\n");
		printf("|                                      |\n");
		for (int i = 10;i <= 15;i++)
		{
			if (permission[i])
			{
				printf("|    %d.%-32s|\n", j, text[i]);
			}
			else
			{
				printf("|   [X]%-32s|\n", text[i]);
			}
			j++;
		}
		break;
	case 4:
		printf(" ______________________________________\n");
		printf("|                                      |\n");
		printf("|         [QUAN LY PHIEU]              |\n");
		printf("|______________________________________|\n");
		printf("|                                      |\n");
		for (int i = 16;i <= 17;i++)
		{
			if (permission[i])
			{
				printf("|    %d.%-32s|\n", j, text[i]);
			}
			else
			{
				printf("|   [X]%-32s|\n", text[i]);
			}
			j++;
		}
		break;
	case 5:
		printf(" ______________________________________\n");
		printf("|                                      |\n");
		printf("|             [THONG KE]               |\n");
		printf("|______________________________________|\n");
		printf("|                                      |\n");
		for (int i = 18;i <= 23;i++)
		{
			if (permission[i])
			{
				printf("|    %d.%-32s|\n", j, text[i]);
			}
			else
			{
				printf("|   [X]%-32s|\n", text[i]);
			}
			j++;
		}
		break;
	}
	printf("|    0.Tro ve                          |\n");
	printf("|______________________________________|\n");
	printf("|_Chon hanh dong : ");
	int c;
	scanf("%d", &c);
	clear();
	if (c != 0) {
		switch (n)
		{
		case 1:
			if (permission[c - 1])
			{
				switch (c)
				{
				case 1:
					changePassword(user);
					break;
				case 2:
					updateUser(user);
					break;
				case 3:
					addUser();
					break;
				case 4:
					printf("Tinh nang chua hoan tat");
					break;
				}
			}
			else
			{
				printf("Ban khong co quyen thuc hien lenh nay\n");
				system("pause");
			}
			break;
		case 2:
			if (permission[c + 3])
			{
				switch (c)
				{
				case 1:
					listReaders();
					break;
				case 2:
					addReader();
					break;
				case 3:
					updateReader();
					break;
				case 4:
					deleteReader();
					break;
				case 5:
					findReaderByIdNumber();
					break;
				case 6:
					printf("TINH NANG DANG LAM\n");
					break;
				}
			}
			else
			{
				printf("Ban khong co quyen thuc hien lenh nay\n");
				system("pause");
			}
			break;
		case 3:

			if (permission[c + 8])
			{
				switch (c)
				{
				case 1:
					BookList();
					break;
				case 2:
					addBook();
					break;
				case 3:
					//updateBookInfo();
					break;
				case 4:
					deleteBook();
					break;
				case 5:
					findISBN();
					break;
				case 6:
					findname();
					break;
				}
			}
			else
			{
				printf("Ban khong co quyen thuc hien lenh nay\n");
				system("pause");
			}
			break;
		case 4:
			if (permission[c + 15]) 
			{
				switch (c) 
				{
				case 1:
					addBorrow();
					break;
				case 2:
					returnBook();
					break;
				}
			}
			break;
		case 5:
			break;
		case 6:
			break;
		}
		system("pause");
	}
	clear();
}