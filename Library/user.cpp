#include "library.h"
//CAC HAM CHUC NANG
void createAdmin() 
{
	FILE *fp = fopen("user.dat", "wb");
	USER user;
	
	printf("===============================\n");
	printf("> Lan dau chay chuong trinh, tai khoan admin mac dinh duoc tao san\n");
	printf("> username : admin\n");
	printf("> password : pass\n");
	printf("> Sau khi dang nhap vui long cap nhat thong tin\n");
	printf("===============================\n");
	strcpy(user.userName, "admin");
	strcpy(user.passWord, "pass");

	char buffer[TEXT_LENGTH] = "1/1/2000";
	DATE date = stringToDATE(buffer);
	user.dob = date;
	strcpy(user.id, "123456789");
	strcpy(user.name, "Your name");
	strcpy(user.address, "Your Address");
	user.status = 1;
	user.gender = 1;
	user.type = 1;
	fwrite(&user, sizeof(USER), 1, fp);
	system("pause");
	fclose(fp);
}

USER login() 
{
	FILE *fp = fopen("user.dat", "rb");
	USER user;
	//Dien username va pass
	system("cls");
	printf(" ______________________________________\n");
	printf("|                                      |\n");
	printf("|             [DANG NHAP]              |\n");
	printf("|______________________________________|\n");
	printf("|                                      |\n");
	printf("|  Ten dang nhap [________________]    |\n");
	printf("|  Mat khau      [________________]    |\n");
	printf("|                                      |\n");
	printf("|______________________________________|\n");

	char nameInput[TEXT_LENGTH], passInput[TEXT_LENGTH];	
	gotoxy(6, 19);
	scanf("%s", &nameInput);
	gotoxy(7, 19);
	scanf("%s", &passInput);
	gotoxy(10, 0);

	bool check = false;//KIEM TRA CO TIM THAY USERNAME KHONG
	while (1) 
	{
		fread(&user, sizeof(struct USER), 1, fp);
		//printUser(user);
		if (strcmp(user.userName, nameInput) == 0) 
		{
			if (strcmp(user.passWord, passInput)==0) 
			{
				printf("Dang nhap thanh cong!\n");
				printf("Xin chao %s\n", user.name);
				check = true;
			}
			break;
		}
		if (feof(fp)) 
		{
			break;
		}
	}
	if (!check)
	{
		printf("Dang nhap that bai, kiem tra lai ten dang nhat hoac password\n");
		system("pause");
		fclose(fp);
		user = login();
	}
	fclose(fp);
	return user;
}

void printUser(USER user) 
{
	printf("=====================================================\n");
	printf("Ten dang nhap: %s\n",user.userName);
	printf("Password : ********\n");
	printf("Ho va ten : %s\n",user.name);
	printf("Ngay sinh : %d/%d/%d\n",user.dob.day,user.dob.month,user.dob.year);
	printf("Dia chi : %s\n",user.address);
	if (user.gender)
		printf("Gioi tinh : nam\n");
	else
		printf("Gioi tinh : nu\n");
	if (user.type == 1)
	{
		printf("Tai khoan admin\n");
	}
	else
	{
		if (user.type == 2)
			printf("Tai khoan quan ly\n");
		else
			printf("Tai khoang chuyen vien\n");
	}
	printf("=====================================================\n");
}
void logOut(USER &user)
{
	user.type = 0;
	strcpy(user.userName, "");
	strcpy(user.passWord, "");
	//printf("Ban da dang xuat\n");
	system("pause");
	user = login();
}

void changePassword(USER &user) 
{
	char input[TEXT_LENGTH];
	printf(" ______________________________________\n");
	printf("|                                      |\n");
	printf("|           THAY DOI MAT KHAU          |\n");
	printf("|______________________________________|\n");
	printf("> Nhap password hien tai : ");
	
	//getchar();
	scanf("%s", &input);

	if (strcmp(user.passWord, input) == 0) 
	{
		printf("> Nhap password moi : ");
		scanf("%s", &input);
		char input2[TEXT_LENGTH];
		printf("> Nhap lai password moi : ");
		scanf("%s", &input2);
		if (strcmp(input, input2) == 0) 
		{
			strcpy(user.passWord, input);
			printf("> Thay doi password thanh cong\n");
			saveUser(user);
		}
		else 
		{
			printf("> Password khong giong\n");
		}
	}
	else
	{
		printf("> Nhap sai password hien tai\n");
	}
}

void saveUser(USER user) 
{
	FILE *fp = fopen("user.dat", "rb+");
	USER tempUser;
	int i = 0;
	int t=-1;
	while (1) 
	{
		fread(&tempUser, sizeof(struct USER), 1, fp);
		if (strcmp(tempUser.userName, user.userName) == 0)
		{
			
			t = i;	//So dong 
			break;
		}
		i++;
		if (feof(fp))
		{
			break;
		}
	}
	if (t >= 0) 
	{
		fseek(fp, sizeof(struct USER)*t, SEEK_SET);
		fwrite(&user, sizeof(struct USER), 1, fp);
	}
	fclose(fp);
}

void updateUser(USER &user) 
{
	printf(" ______________________________________\n");
	printf("|                                      |\n");
	printf("|         CAP NHAT THONG TIN           |\n");
	printf("|______________________________________|\n");
	char input[TEXT_LENGTH];

	getchar();
	printf("Ho va ten : ");
	gets_s(user.name, TEXT_LENGTH);
	
	printf("Ngay sinh (dd/mm/yy) : ");
	gets_s(input, TEXT_LENGTH);
	user.dob = stringToDATE(input);

	printf("CMND : ");
	gets_s(user.id, TEXT_LENGTH);

	printf("Dia chi : ");
	gets_s(user.address, TEXT_LENGTH);
	
	
	printf("Gioi tinh (1-Nam,0-Nu) : ");
	int tmp;
	scanf("%d", &tmp);
	user.gender = tmp;
	saveUser(user);
}

void addUser() 
{
	USER user;
	printf(" ______________________________________\n");
	printf("|                                      |\n");
	printf("|          TAO NGUOI DUNG MOI          |\n");
	printf("|______________________________________|\n");
	char input[TEXT_LENGTH];
	printf("> Ten dang nhap : ");
	scanf("%s", user.userName);
	if (!checkUserName(user.userName)) 
	{
		printf("> Ten dang nhap da ton tai\n");
		return;
	}
	printf("> Mat khau : ");
	scanf("%s", user.passWord);
	printf("> Ho va ten : ");
	getchar();
	gets_s(user.name, TEXT_LENGTH);
	printf("> Ngay sinh (dd/mm/yy) :");
	char buffer[TEXT_LENGTH];
	scanf("%s", buffer);
	user.dob = stringToDATE(buffer);
	printf("> CMND : ");
	scanf("%s", user.id);
	printf("> Dia chi : ");
	getchar();
	gets_s(user.address);
	int b;
	printf("> Gioi tinh (1-nam,0-nu) : ");
	scanf("%d", &b);
	user.gender = b;
	printf("> Trang thai (0-blocked 1-active) : ");
	scanf("%d", &b);
	user.status = b;
	printf("> Loai nguoi dung (2-quan ly 3-chuyen vien) : ");
	scanf("%d", &user.type);
	getchar();
	printf("> Tao nguoi dung moi thanh cong\n");
	printUser(user);

	FILE*fp = fopen("user.dat", "ab+");
	fwrite(&user, sizeof(struct USER), 1, fp);
	fclose(fp);
}
void changePermission() 
{
	printf(" ______________________________________\n");
	printf("|                                      |\n");
	printf("|         PHAN QUYEN NGUOI DUNG        |\n");
	printf("|______________________________________|\n");
	printf("> Nhap ten dang nhap muon thay doi quyen : ");
	char input[TEXT_LENGTH];
	scanf("%s", input);
	FILE *fp = fopen("user.dat", "rb+");
	USER user;
	bool check = false;
	while (1) 
	{
		fread(&user, sizeof(struct USER), 1, fp);
		if (strcmp(input, user.userName) == 0) 
		{
			printf("> Trang thai : (0-block,1-active):");
			int tmp;
			scanf("%d", &tmp);
			user.status = tmp;
			printf("> Vai tro : (2-quan ly, 3-chuyen vien):");
			scanf("%d", &user.type);
			check = true;
			printf("> Da thay doi quyen cua nguoi dung\n");
			saveUser(user);
			break;
		}
		if (feof(fp))
		{
			break;
		}
	}
	if (!check) 
	{
		printf("> Khong tim thay nguoi dung tren\n");
	}
	fclose(fp);
}
bool checkUserName(char name[]) 
{
	FILE*fp = fopen("user.dat", "rb");
	USER user;
	while (fread(&user,sizeof(struct USER),1,fp)) 
	{
		if (strcmp(name, user.userName)==0)
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
	//system("pause");
	system("cls");
	switch(user.type)
	{
	case 0:
		break;
	case 1:
		printf(" ___________________________________________________________\n");
		printf("|                                                           |\n");
		printf("|                      [ADMIN MENU]                         |\n");
		printf("|___________________________________________________________|\n");

		break;
	case 2:
		printf(" ___________________________________________________________\n");
		printf("|                                                           |\n");
		printf("|                      [QUAN LY MENU]                       |\n");
		printf("|___________________________________________________________|\n");

		break;
	case 3:
		printf(" ___________________________________________________________\n");
		printf("|                                                           |\n");
		printf("|                    [CHUYEN VIEN MENU]                     |\n");
		printf("|___________________________________________________________|\n");
		
		break;
	}
	printf("|                                                           |\n");
	printf("|     1. Quan ly nguoi dung                                 |\n");
	printf("|     2. Quan ly doc gia                                    |\n");
	printf("|     3. Quan ly sach                                       |\n");
	printf("|     4. Quan ly phieu muon/tra                             |\n");
	printf("|     5. Thong ke                                           |\n");
	printf("|     0. Dang xuat                                          |\n");
	printf("|                                                           |\n");
	printf("|     Moi nhap so :                                         |\n");
	printf("|___________________________________________________________|\n");
	gotoxy(13, 20);
	scanf("%d", &n);
	if ((n >0) && (n<=5)) 
	{
		printSubMenu(user, n);
	}
	else
	{
		if (n==0)
		logOut(user);
	}
}
void printSubMenu(USER &user, int &n) 
{
	system("cls");
	bool permission[24];
	for (int i = 0;i < 24;i++) 
		permission[i] = true;

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
	//18-23 cac thong ke
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
	text[9] = "Tim sach theo ten";
	text[10] = "Xem danh sach sach";
	text[11] = "Them sach";
	text[12] = "Chinh sua sach";
	text[13] = "Xoa sach";
	text[14] = "Tim sach theo ISBN";
	text[15] = "Tim sach theo ten sach";
	text[16] = "Lap phieu muon";
	text[17] = "Lap phieu tra";
	text[18] = "Thong ke so luong sach trong thu vien";
	text[19] = "Thong ke so luong sach theo the loai";
	text[20] = "Thong ke so luong doc gia";
	text[21] = "Thong ke so luong doc gia theo gioi tinh";
	text[22] = "Thong ke so sach dang duoc muon";
	text[23] = "Thong ke danh sach doc gia bi tre han";

	int j = 1;
	switch (n) 
	{
	case 1://Quan ly nguoi dung
		printf(" ___________________________________________________________\n");
		printf("|                                                           |\n");
		printf("|                   [QUAN LY NGUOI DUNG]                    |\n");
		printf("|___________________________________________________________|\n");
		printf("|                                                           |\n");
		for (int i = 0;i <= 3;i++) 
		{
			if (permission[i]) 
			{
				printf("|    %d.%-53s|\n",j, text[i]);
			}
			else
			{
				printf("|   [X]%-53s|\n", text[i]);
			}
			j++;
		}
		break;
	case 2://Quan ly doc gia
		printf(" ___________________________________________________________\n");
		printf("|                                                           |\n");
		printf("|                     [QUAN LY DOC GIA]                     |\n");
		printf("|___________________________________________________________|\n");
		printf("|                                                           |\n");
		for (int i = 4;i <= 9;i++)
		{
			if (permission[i])
			{
				printf("|    %d.%-53s|\n", j, text[i]);
			}
			else
			{
				printf("|   [X]%-53s|\n", text[i]);
			}
			j++;
		}
		break;
	case 3://Quan ly sach
		printf(" ___________________________________________________________\n");
		printf("|                                                           |\n");
		printf("|                      [QUAN LY SACH]                       |\n");
		printf("|___________________________________________________________|\n");
		printf("|                                                           |\n");
		for (int i = 10;i <= 15;i++)
		{
			if (permission[i])
			{
				printf("|    %d.%-53s|\n", j, text[i]);
			}
			else
			{
				printf("|   [X]%-53s|\n", text[i]);
			}
			j++;
		}
		break;
	case 4:
		printf(" ___________________________________________________________\n");
		printf("|                                                           |\n");
		printf("|                      [QUAN LY PHIEU]                      |\n");
		printf("|___________________________________________________________|\n");
		printf("|                                                           |\n");
		for (int i = 16;i <= 17;i++)
		{
			if (permission[i])
			{
				printf("|    %d.%-53s|\n", j, text[i]);
			}
			else
			{
				printf("|   [X]%-53s|\n", text[i]);
			}
			j++;
		}
		break;
	case 5:
		printf(" ___________________________________________________________\n");
		printf("|                                                           |\n");
		printf("|                        [THONG KE]                         |\n");
		printf("|___________________________________________________________|\n");
		printf("|                                                           |\n");
		for (int i = 18;i <= 23;i++)
		{
			if (permission[i])
			{
				printf("|    %d.%-53s|\n", j, text[i]);
			}
			else
			{
				printf("|   [X]%-53s|\n", text[i]);
			}
			j++;
		}
		break;
	}
	printf("|    0.Tro ve                                               |\n");
	printf("|___________________________________________________________|\n");
	printf("|_Chon hanh dong : ");
	int c;
	scanf("%d", &c);
	system("cls");
	if (c != 0) 
	{
		switch (n)
		{
		case 1:
		{
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
					changePermission();
					break;
				}
			}
			else
			{
				printf("Ban khong co quyen thuc hien lenh nay\n");
			}
			break;
		}
		case 2:
		{
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
					findBookByName();
					break;
				}
			}
			else
			{
				printf("Ban khong co quyen thuc hien lenh nay\n");
			}
			break;
		}
		case 3:
		{
			if (permission[c + 9])
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
					updateBookInfo();
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
			}
			break;
		}
		case 4:
		{
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
			if (permission[c + 17])
			{
				switch (c)
				{
				case 1:
					bookReport();
					break;
				case 2:
					categoryReport();
					break;
				case 3:
					readerReport();
					break;
				case 4:
					genderReport();
					break;
				case 5:
					listBorrowing();
					break;
				case 6:
					listLate();
					break;
				}
			}
			break;
		}
		}
		system("pause");
	}
	system("cls");
}